import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * Simple implementation of naive polynomial multiplication in Java.
 * - Sequential version: O(n²) with double nested loop.
 * - Parallel version: Parallelizes the outer loop using a thread pool.
 *   Each thread computes contributions for a chunk of the result coefficients.
 * **/
public class PolynomialMultiplyNaive {


     // Generate a random polynomial of degree n-1 (n coefficients).
    private static long[] generateRandomPoly(int n, Random rand) {
        long[] poly = new long[n];
        for (int i = 0; i < n; i++) {
            poly[i] = rand.nextInt(100) + 1; // Small positive ints to avoid overflow too soon
        }
        return poly;
    }

     //Naive sequential multiplication: O(n²)
    public static long[] multiplySequential(long[] p, long[] q) {
        int n = p.length;
        long[] result = new long[2 * n - 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i + j] += p[i] * q[j];
            }
        }
        return result;
    }
    //Parallel multiplication using ExecutorService
    public static long[] multiplyParallel(long[] p, long[] q, int numThreads) throws InterruptedException {
        int n = p.length;
        long[] result = new long[2 * n - 1];
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);

        int chunkSize = n / numThreads;
        for (int t = 0; t < numThreads; t++) {
            final int start = t * chunkSize;
            final int end = (t == numThreads - 1) ? n : (t + 1) * chunkSize;

            executor.submit(() -> {
                for (int i = start; i < end; i++) {
                    for (int j = 0; j < n; j++) {
                        result[i + j] += p[i] * q[j];
                    }
                }
            });
        }

        executor.shutdown();
        executor.awaitTermination(1, TimeUnit.HOURS); // Wait for all tasks to finish
        return result;
    }

    /**
     * Benchmark a multiplication method and return time in ms.
     */
    private static long benchmark(Runnable task) {
        long start = System.nanoTime();
        task.run();
        long end = System.nanoTime();
        return (end - start) / 1_000_000; // ms
    }

    public static void main(String[] args) throws InterruptedException {
        Random rand = new Random(42); // Fixed seed for reproducibility
        int[] sizes = {5, 100, 4000, 80000, 250000};
        int[] threadCounts = {1, 2, 4, 8, 16, 32};

        System.out.println("Benchmarking Naive Polynomial Multiplication");
        System.out.println("------------------------------------------");
        for (int n : sizes) {
            long[] p = generateRandomPoly(n, rand);
            long[] q = generateRandomPoly(n, rand);

            // Sequential
            long seqTime = benchmark(() -> multiplySequential(p, q));
            System.out.printf("n=%d, Sequential: %d ms%n", n, seqTime);

            // Parallel for different threads
            for (int threads : threadCounts) {
                long parTime = benchmark(() -> {
                    try {
                        multiplyParallel(p, q, threads);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                });
                double speedup = (double) seqTime / parTime;
                System.out.printf("n=%d, Parallel (%d threads): %d ms (speedup: %.2fx)%n", n, threads, parTime, speedup);
            }
            System.out.println();
        }
    }
}