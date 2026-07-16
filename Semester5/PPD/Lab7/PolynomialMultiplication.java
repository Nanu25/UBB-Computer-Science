import mpi.*;
import java.util.Arrays;

/*
$env:JAVA_HOME="C:\Users\alex_\.jdks\openjdk-23.0.2"
$env:PATH="$env:JAVA_HOME\bin;$env:PATH"
H:\mpj-v0_44\bin\mpjrun.bat -np 4 -cp "H:\LabPPD\Lab7\Lab7\out\production\Lab7" PolynomialMultiplication
Trebuie sa dau build dupa fiecare modificare
 */

public class PolynomialMultiplication {
    static final int THRESHOLD = 64;

    public static int[] serialNaive(int[] A, int[] B) {
        int m = A.length;
        int p = B.length;
        int[] res = new int[m + p - 1];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                res[i + j] += A[i] * B[j];
            }
        }
        return res;
    }

    public static int[] addArrays(int[] a, int[] b) {
        int maxLen = Math.max(a.length, b.length);
        int[] result = new int[maxLen];
        for (int i = 0; i < a.length; i++) {
            result[i] += a[i];
        }
        for (int i = 0; i < b.length; i++) {
            result[i] += b[i];
        }
        return result;
    }

    public static int[] subtractArrays(int[] a, int[] b) {
        int maxLen = Math.max(a.length, b.length);
        int[] result = new int[maxLen];
        for (int i = 0; i < a.length; i++) {
            result[i] += a[i];
        }
        for (int i = 0; i < b.length; i++) {
            result[i] -= b[i];
        }
        return result;
    }

    public static int[] serialKaratsuba(int[] A, int[] B, int threshold) {
        if (A.length < threshold || B.length < threshold) {
            return serialNaive(A, B);
        }

        int n = Math.max(A.length, B.length);
        if (n % 2 != 0) {
            n++;
        }
        int[] paddedA = Arrays.copyOf(A, n);
        int[] paddedB = Arrays.copyOf(B, n);

        int half = n / 2;
        int[] A0 = Arrays.copyOfRange(paddedA, 0, half);
        int[] A1 = Arrays.copyOfRange(paddedA, half, n);
        int[] B0 = Arrays.copyOfRange(paddedB, 0, half);
        int[] B1 = Arrays.copyOfRange(paddedB, half, n);

        int[] P = serialKaratsuba(A0, B0, threshold);
        int[] Q = serialKaratsuba(A1, B1, threshold);
        int[] A2 = addArrays(A0, A1);
        int[] B2 = addArrays(B0, B1);
        int[] R = serialKaratsuba(A2, B2, threshold);

        int[] mid = subtractArrays(subtractArrays(R, P), Q);

        int[] result = new int[2 * n - 1];
        System.arraycopy(P, 0, result, 0, P.length);
        System.arraycopy(Q, 0, result, n, Q.length);
        System.arraycopy(mid, 0, result, half, mid.length);

        // Trim trailing zeros
        int len = result.length;
        while (len > 0 && result[len - 1] == 0) {
            len--;
        }
        return Arrays.copyOf(result, len);
    }

    public static int[] parallelNaive(int[] A, int[] B) throws MPIException {
        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        // Broadcast lengths
        int[] lengths = new int[2];
        if (rank == 0) {
            lengths[0] = A.length;
            lengths[1] = B.length;
        }
        MPI.COMM_WORLD.Bcast(lengths, 0, 2, MPI.INT, 0);
        int m = lengths[0];
        int n = lengths[1];
        int resLen = m + n - 1;

        // Broadcast A and B
        if (rank != 0) {
            A = new int[m];
            B = new int[n];
        }
        MPI.COMM_WORLD.Bcast(A, 0, m, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(B, 0, n, MPI.INT, 0);

        // Compute chunk
        int chunk = resLen / size;
        int extra = resLen % size;
        int start = rank * chunk + Math.min(rank, extra);
        int end = start + chunk + (rank < extra ? 1 : 0);

        int localLen = end - start;
        int[] localRes = new int[localLen];
        for (int k = start; k < end; k++) {
            int s = 0;
            int low = Math.max(0, k - n + 1);
            int high = Math.min(k + 1, m);
            for (int i = low; i < high; i++) {
                s += A[i] * B[k - i];
            }
            localRes[k - start] = s;
        }

        // Gather lengths
        int[] recvCounts = new int[size];
        MPI.COMM_WORLD.Allgather(new int[]{localLen}, 0, 1, MPI.INT, recvCounts, 0, 1, MPI.INT);

        // Compute displacements
        int[] displs = new int[size];
        displs[0] = 0;
        for (int i = 1; i < size; i++) {
            displs[i] = displs[i - 1] + recvCounts[i - 1];
        }

        int[] result = null;
        if (rank == 0) {
            result = new int[resLen];
        }
        MPI.COMM_WORLD.Gatherv(localRes, 0, localLen, MPI.INT, result, 0, recvCounts, displs, MPI.INT, 0);

        if (rank != 0) {
            result = new int[resLen];
        }
        MPI.COMM_WORLD.Bcast(result, 0, resLen, MPI.INT, 0);

        return result;
    }

    public static int[] parallelKaratsuba(int[] A, int[] B, int threshold) throws MPIException {
        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        // Broadcast lengths
        int[] lengths = new int[2];
        if (rank == 0) {
            lengths[0] = A.length;
            lengths[1] = B.length;
        }
        MPI.COMM_WORLD.Bcast(lengths, 0, 2, MPI.INT, 0);
        int origM = lengths[0];
        int origN = lengths[1];

        if (rank != 0) {
            A = new int[origM];
            B = new int[origN];
        }
        MPI.COMM_WORLD.Bcast(A, 0, origM, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(B, 0, origN, MPI.INT, 0);

        if (A.length < threshold || B.length < threshold || size == 1) {
            int[] C = null;
            if (rank == 0) {
                C = serialKaratsuba(A, B, threshold);
            }
            // Broadcast result length
            int[] resLenBuf = new int[1];
            if (rank == 0) {
                resLenBuf[0] = C.length;
            }
            MPI.COMM_WORLD.Bcast(resLenBuf, 0, 1, MPI.INT, 0);
            int resLen = resLenBuf[0];

            if (rank != 0) {
                C = new int[resLen];
            }
            MPI.COMM_WORLD.Bcast(C, 0, resLen, MPI.INT, 0);
            return C;
        }

        int n = Math.max(A.length, B.length);
        if (n % 2 != 0) {
            n++;
        }
        int[] paddedA = Arrays.copyOf(A, n);
        int[] paddedB = Arrays.copyOf(B, n);

        int half = n / 2;
        int[] A0 = Arrays.copyOfRange(paddedA, 0, half);
        int[] A1 = Arrays.copyOfRange(paddedA, half, n);
        int[] B0 = Arrays.copyOfRange(paddedB, 0, half);
        int[] B1 = Arrays.copyOfRange(paddedB, half, n);
        int[] A2 = addArrays(A0, A1);
        int[] B2 = addArrays(B0, B1);

        // Split into 3 groups
        int gs1 = size / 3;
        int gs2 = size / 3;

        int color;
        if (rank < gs1) {
            color = 0;
        } else if (rank < gs1 + gs2) {
            color = 1;
        } else {
            color = 2;
        }

        Intracomm subComm = MPI.COMM_WORLD.Split(color, rank);

        int[] subA = null;
        int[] subB = null;
        if (color == 0) {
            subA = A0;
            subB = B0;
        } else if (color == 1) {
            subA = A1;
            subB = B1;
        } else {
            subA = A2;
            subB = B2;
        }

        int[] subResult = parallelKaratsuba(subA, subB, threshold);

        // Gather sub_results to root
        int[] P = null;
        int[] Q = null;
        int[] R = null;

        if (rank == 0) {
            P = subResult;  // from color 0
        }

        // Send Q and R to root
        if (color == 1 && subComm.Rank() == 0) {
            // Send length first
            int[] lenBuf = {subResult.length};
            MPI.COMM_WORLD.Send(lenBuf, 0, 1, MPI.INT, 0, 1);
            MPI.COMM_WORLD.Send(subResult, 0, subResult.length, MPI.INT, 0, 2);
        }
        if (color == 2 && subComm.Rank() == 0) {
            int[] lenBuf = {subResult.length};
            MPI.COMM_WORLD.Send(lenBuf, 0, 1, MPI.INT, 0, 3);
            MPI.COMM_WORLD.Send(subResult, 0, subResult.length, MPI.INT, 0, 4);
        }

        if (rank == 0) {
            // Receive Q
            int[] lenBuf = new int[1];
            MPI.COMM_WORLD.Recv(lenBuf, 0, 1, MPI.INT, gs1, 1);
            Q = new int[lenBuf[0]];
            MPI.COMM_WORLD.Recv(Q, 0, Q.length, MPI.INT, gs1, 2);

            // Receive R
            MPI.COMM_WORLD.Recv(lenBuf, 0, 1, MPI.INT, gs1 + gs2, 3);
            R = new int[lenBuf[0]];
            MPI.COMM_WORLD.Recv(R, 0, R.length, MPI.INT, gs1 + gs2, 4);
        }

        int[] result = null;
        if (rank == 0) {
            int[] mid = subtractArrays(subtractArrays(R, P), Q);

            result = new int[2 * n - 1];
            System.arraycopy(P, 0, result, 0, P.length);
            if (Q.length + n - 1 < result.length) {
                System.arraycopy(Q, 0, result, n, Q.length);
            } else {
                System.arraycopy(Q, 0, result, n, result.length - n);
            }
            System.arraycopy(mid, 0, result, half, Math.min(mid.length, result.length - half));

            // Trim trailing zeros
            int len = result.length;
            while (len > 0 && result[len - 1] == 0) {
                len--;
            }
            result = Arrays.copyOf(result, len);
        }

        // Broadcast result length
        int[] resLenBuf = new int[1];
        if (rank == 0) {
            resLenBuf[0] = result.length;
        }
        MPI.COMM_WORLD.Bcast(resLenBuf, 0, 1, MPI.INT, 0);
        int resLen = resLenBuf[0];

        if (rank != 0) {
            result = new int[resLen];
        }
        MPI.COMM_WORLD.Bcast(result, 0, resLen, MPI.INT, 0);

        return result;
    }

    public static void main(String[] args) throws MPIException {
        MPI.Init(args);
        int rank = MPI.COMM_WORLD.Rank();

        int dimensions[] = {5, 100, 4000, 80000, 250000};
        int[] A = null;
        int[] B = null;

        for(int n : dimensions) {
            if (rank == 0) {
                A = new int[n];
                B = new int[n];

                for (int i = 0; i < n; i++) {
                    A[i] = i + 1;
                    B[i] = n - i;
                }

                System.out.println("Running with polynomial size " + n);

                long start = System.currentTimeMillis();
                int[] C_serial_naive = serialNaive(A, B);
                long time_serial_naive = System.currentTimeMillis() - start;
                System.out.printf("Serial Naive time: %.4f s%n", time_serial_naive / 1000.0);

                start = System.currentTimeMillis();
                int[] C_serial_kar = serialKaratsuba(A, B, 32);
                long time_serial_kar = System.currentTimeMillis() - start;
                System.out.printf("Serial Karatsuba time: %.4f s%n", time_serial_kar / 1000.0);
            }

            long start = System.currentTimeMillis();
            int[] C_parallel_naive = parallelNaive(A, B);
            long time_parallel_naive = System.currentTimeMillis() - start;

            if (rank == 0) {
                System.out.printf("Parallel Naive time: %.4f s%n", time_parallel_naive / 1000.0);
            }

            start = System.currentTimeMillis();
            int[] C_parallel_kar = parallelKaratsuba(A, B, THRESHOLD);
            long time_parallel_kar = System.currentTimeMillis() - start;

            if (rank == 0) {
                System.out.printf("Parallel Karatsuba time: %.4f s%n", time_parallel_kar / 1000.0);
                System.out.println("All implementations complete.");
            }

            MPI.COMM_WORLD.Barrier(); // sync all processes before next n
        }

        MPI.Finalize();
    }

}