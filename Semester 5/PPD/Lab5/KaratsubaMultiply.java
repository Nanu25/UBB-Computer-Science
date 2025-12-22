import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.TimeUnit;

public class KaratsubaMultiply {

    private static final int THRESHOLD = 128; // Base case: use naive if n <= this

    private static long[] generateRandomPoly(int n, Random rand) {
        long[] poly = new long[n];
        for (int i = 0; i < n; i++) {
            poly[i] = rand.nextInt(100) + 1;
        }
        return poly;
    }

    /**
     * Naive multiply (for base case).
     */
    private static long[] naiveMultiply(long[] p, long[] q) {
        int m = p.length;
        int n = q.length;
        long[] result = new long[m + n - 1];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[i + j] += p[i] * q[j];
            }
        }
        return trimLeadingZeros(result);
    }

    private static long[] add(long[] a, long[] b) {
        int maxLen = Math.max(a.length, b.length);
        long[] sum = new long[maxLen];
        for (int i = 0; i < a.length; i++) sum[i] += a[i];
        for (int i = 0; i < b.length; i++) sum[i] += b[i];
        return trimLeadingZeros(sum);
    }

    private static long[] subtract(long[] a, long[] b) {
        int maxLen = Math.max(a.length, b.length);
        long[] diff = new long[maxLen];
        for (int i = 0; i < a.length; i++) diff[i] += a[i];
        for (int i = 0; i < b.length; i++) diff[i] -= b[i];
        return trimLeadingZeros(diff);
    }

    /**
     * Helper: Shift left by k (multiply by x^k).
     */
    private static long[] shiftLeft(long[] poly, int k) {
        if (k == 0) return poly.clone();
        long[] shifted = new long[poly.length + k];
        System.arraycopy(poly, 0, shifted, k, poly.length);
        return shifted;
    }

    /**
     * Trim leading zeros from polynomial.
     */
    private static long[] trimLeadingZeros(long[] poly) {
        int len = poly.length;
        while (len > 0 && poly[len - 1] == 0) len--;
        return len == poly.length ? poly : Arrays.copyOf(poly, len == 0 ? 1 : len); // At least [0]
    }

    /**
     * Sequential Karatsuba.
     */
    public static long[] multiplyKaratsubaSequential(long[] p, long[] q) {
        int n = Math.max(p.length, q.length);
        if (n <= THRESHOLD) {
            return naiveMultiply(p, q);
        }

        // Pad to same length
        p = Arrays.copyOf(p, n);
        q = Arrays.copyOf(q, n);

        int m = n / 2;

        long[] p0 = Arrays.copyOfRange(p, 0, m);
        long[] p1 = Arrays.copyOfRange(p, m, n);
        long[] q0 = Arrays.copyOfRange(q, 0, m);
        long[] q1 = Arrays.copyOfRange(q, m, n);

        long[] m1 = multiplyKaratsubaSequential(p0, q0);
        long[] m2 = multiplyKaratsubaSequential(p1, q1);
        long[] m3 = multiplyKaratsubaSequential(add(p0, p1), add(q0, q1));

        long[] middle = subtract(m3, add(m1, m2));

        return add(add(m1, shiftLeft(middle, m)), shiftLeft(m2, 2 * m));
    }

    /**
     * Parallel Karatsuba Task.
     */
    static class KaratsubaTask extends RecursiveTask<long[]> {
        private final long[] p;
        private final long[] q;

        KaratsubaTask(long[] p, long[] q) {
            this.p = p;
            this.q = q;
        }

        @Override
        protected long[] compute() {
            int n = Math.max(p.length, q.length);
            if (n <= THRESHOLD) {
                return naiveMultiply(p, q);
            }

            // Pad
            long[] pp = Arrays.copyOf(p, n);
            long[] qq = Arrays.copyOf(q, n);

            int m = n / 2;

            long[] p0 = Arrays.copyOfRange(pp, 0, m);
            long[] p1 = Arrays.copyOfRange(pp, m, n);
            long[] q0 = Arrays.copyOfRange(qq, 0, m);
            long[] q1 = Arrays.copyOfRange(qq, m, n);

            // Fork the three sub-tasks
            KaratsubaTask task1 = new KaratsubaTask(p0, q0);
            KaratsubaTask task2 = new KaratsubaTask(p1, q1);
            KaratsubaTask task3 = new KaratsubaTask(add(p0, p1), add(q0, q1));

            task1.fork();
            task2.fork();
            task3.fork();

            long[] m1 = task1.join();
            long[] m2 = task2.join();
            long[] m3 = task3.join();

            long[] middle = subtract(m3, add(m1, m2));

            return add(add(m1, shiftLeft(middle, m)), shiftLeft(m2, 2 * m));
        }
    }

    /**
     * Parallel Karatsuba using ForkJoinPool with given parallelism.
     */
    public static long[] multiplyKaratsubaParallel(long[] p, long[] q, int parallelism) {
        ForkJoinPool pool = new ForkJoinPool(parallelism);
        try {
            return pool.invoke(new KaratsubaTask(p, q));
        } finally {
            pool.shutdown();
            try {
                pool.awaitTermination(1, TimeUnit.HOURS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    private static long computeTime(Runnable task) {
        long start = System.nanoTime();
        task.run();
        return (System.nanoTime() - start) / 1_000_000; // ms
    }

    public static void main(String[] args) {
        Random rand = new Random(42);
        int[] sizes = {5, 100, 4000, 80000, 250000, 500000, 1000000};
        int[] threadCounts = {1, 2, 4, 8, 16, 32};

        System.out.println("Karatsuba Polynomial Multiplication");
        System.out.println("------------------------------------------------");
        for (int n : sizes) {
            long[] p = generateRandomPoly(n, rand);
            long[] q = generateRandomPoly(n, rand);

            // Sequential
            long seqTime = computeTime(() -> multiplyKaratsubaSequential(p, q));
            System.out.printf("n=%d, Sequential: %d ms%n", n, seqTime);

            // Parallel
            for (int threads : threadCounts) {
                long parTime = computeTime(() -> multiplyKaratsubaParallel(p, q, threads));
                double speedup = (double) seqTime / parTime;
                System.out.printf("n=%d, Parallel (%d threads): %d ms (speedup: %.2fx)%n", n, threads, parTime, speedup);
            }
            System.out.println();
        }
    }
}