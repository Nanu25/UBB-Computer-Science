import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    private static final boolean DEBUG = false;
    private static Lock printLock = new ReentrantLock();

    // Compute a single element of the result matrix
    private static int computeElement(int[][] matrixA, int[][] matrixB, int row, int col, int threadId) {
        if (DEBUG && matrixA[0].length == 5) {
            printLock.lock();
            try {
                System.out.printf("Thread %d computing element (%d, %d)%n", threadId, row, col);
            } finally {
                printLock.unlock();
            }
        }
        int sum = 0;
        for (int k = 0; k < matrixA[0].length; k++) {
            sum += matrixA[row][k] * matrixB[k][col];
        }
        return sum;
    }

    // Approach 1: Row-wise consecutive elements
    static class RowWiseTask implements Runnable {
        private final int[][] matrixA;
        private final int[][] matrixB;
        private final int[][] result;
        private final int threadId;
        private final int totalThreads;

        public RowWiseTask(int[][] matrixA, int[][] matrixB, int[][] result,
                           int threadId, int totalThreads) {
            this.matrixA = matrixA;
            this.matrixB = matrixB;
            this.result = result;
            this.threadId = threadId;
            this.totalThreads = totalThreads;
        }

        @Override
        public void run() {
            int rows = result.length;
            int cols = result[0].length;
            int totalElements = rows * cols;
            int elementsPerThread = totalElements / totalThreads;
            int startElement = threadId * elementsPerThread;
            int endElement = (threadId == totalThreads - 1) ? totalElements : (threadId + 1) * elementsPerThread;

            for (int idx = startElement; idx < endElement; idx++) {
                int row = idx / cols;
                int col = idx % cols;
                result[row][col] = computeElement(matrixA, matrixB, row, col, threadId);
            }
        }
    }
    // Approach 2: Column-wise consecutive elements
    static class ColumnWiseTask implements Runnable {
        private final int[][] matrixA;
        private final int[][] matrixB;
        private final int[][] result;
        private final int threadId;
        private final int totalThreads;

        public ColumnWiseTask(int[][] matrixA, int[][] matrixB, int[][] result,
                              int threadId, int totalThreads) {
            this.matrixA = matrixA;
            this.matrixB = matrixB;
            this.result = result;
            this.threadId = threadId;
            this.totalThreads = totalThreads;
        }

        @Override
        public void run() {
            int rows = result.length;
            int cols = result[0].length;
            int totalElements = rows * cols;
            int elementsPerThread = totalElements / totalThreads;
            int startElement = threadId * elementsPerThread;
            int endElement = (threadId == totalThreads - 1) ? totalElements : (threadId + 1) * elementsPerThread;

            for (int idx = startElement; idx < endElement; idx++) {
                int col = idx / rows;
                int row = idx % rows;
                result[row][col] = computeElement(matrixA, matrixB, row, col, threadId);
            }
        }
    }

    // Approach 3: Strided/Interleaved (every k-th element)
    static class StridedTask implements Runnable {
        private final int[][] matrixA;
        private final int[][] matrixB;
        private final int[][] result;
        private final int threadId;
        private final int totalThreads;

        public StridedTask(int[][] matrixA, int[][] matrixB, int[][] result,
                           int threadId, int totalThreads) {
            this.matrixA = matrixA;
            this.matrixB = matrixB;
            this.result = result;
            this.threadId = threadId;
            this.totalThreads = totalThreads;
        }

        @Override
        public void run() {
            int rows = result.length;
            int cols = result[0].length;
            int totalElements = rows * cols;

            for (int idx = threadId; idx < totalElements; idx += totalThreads) {
                int row = idx / cols;
                int col = idx % cols;
                result[row][col] = computeElement(matrixA, matrixB, row, col, threadId);
            }
        }
    }

    // Helper method to run threads and measure time
    private static long runParallelMultiplication(int[][] matrixA, int[][] matrixB,
                                                  int[][] result, int numThreads,
                                                  String approach) throws InterruptedException {
        List<Thread> threads = new ArrayList<>();

        long startTime = System.nanoTime();

        for (int i = 0; i < numThreads; i++) {
            Runnable task;
            switch (approach) {
                case "row":
                    task = new RowWiseTask(matrixA, matrixB, result, i, numThreads);
                    break;
                case "column":
                    task = new ColumnWiseTask(matrixA, matrixB, result, i, numThreads);
                    break;
                case "strided":
                    task = new StridedTask(matrixA, matrixB, result, i, numThreads);
                    break;
                default:
                    throw new IllegalArgumentException("Unknown approach: " + approach);
            }
            Thread thread = new Thread(task);
            threads.add(thread);
            thread.start();
        }

        for (Thread thread : threads) {
            thread.join();
        }

        long endTime = System.nanoTime();
        return endTime - startTime;
    }

    private static int[][] initializeMatrix(int rows, int cols) {
        int[][] matrix = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = (int) (Math.random());
            }
        }
        return matrix;
    }

    public static void main(String[] args) throws InterruptedException {
        int[] matrixSizes = {5, 100, 500, 1000};
        int[] threadCounts = {1, 2, 4, 8, 16, 32};
        String[] approaches = {"row", "column", "strided"};

        System.out.println("Matrix Multiplication Performance Comparison");
        System.out.println("=".repeat(80));

        for (int size : matrixSizes) {
            System.out.printf("%nMatrix Size: %dx%d%n", size, size);
            System.out.println("-".repeat(80));
            int[][] matrixA = initializeMatrix(size, size);
            int[][] matrixB = initializeMatrix(size, size);

            for (String approach : approaches) {
                System.out.printf("%nApproach: %s%n", approach.toUpperCase());
                System.out.printf("%-10s %-15s%n", "Threads", "Time (ms)");

                for (int numThreads : threadCounts) {
                    int[][] result = new int[size][size];
                    long totalTime = runParallelMultiplication(matrixA, matrixB, result, numThreads, approach);
                    double avgTimeMs = totalTime / 1_000_000.0;
                    System.out.printf("%-10d %-15.2f%n", numThreads, avgTimeMs);
                }
            }
        }
    }
}