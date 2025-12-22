import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

public class HamiltonianCycleForkJoin {
    private final int n;
    private final List<Integer>[] adj;
    private static final int START = 0;
    private ForkJoinPool pool;
    private final AtomicBoolean found = new AtomicBoolean(false);
    private final AtomicReference<List<Integer>> solution = new AtomicReference<>(null);

    public HamiltonianCycleForkJoin(int n, List<Integer>[] adj) {
        this.n = n;
        this.adj = adj;
    }

    public boolean hasHamiltonianCycle(int numThreads) {
        this.pool = new ForkJoinPool(numThreads);
        found.set(false);
        solution.set(null);
        try {
            List<Integer> rootPath = new ArrayList<>();
            rootPath.add(START);
            SearchTask root = new SearchTask(START, 1 << START, 1, numThreads, null, rootPath);
            boolean res = pool.invoke(root);
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            if (pool != null) {
                pool.shutdown();
                this.pool = null;
            }
        }
    }

    /** Return the cycle found (list of vertices starting from START). Null if none. */
    public List<Integer> getSolution() {
        return solution.get();
    }

    private class SearchTask extends RecursiveTask<Boolean> {
        private final int current;
        private final int used;
        private final int depth;
        private final int parallelism;
        private final List<Integer> forced;
        private final List<Integer> pathSoFar;

        SearchTask(int current, int used, int depth, int parallelism, List<Integer> forced, List<Integer> pathSoFar) {
            this.current = current;
            this.used = used;
            this.depth = depth;
            this.parallelism = parallelism;
            this.forced = forced;
            this.pathSoFar = pathSoFar;
        }

        @Override
        protected Boolean compute() {
            // Check if solution already found (early termination)
            if (found.get()) return found.get();

            // Check if Hamiltonian cycle is complete
            if (depth == n) {
                if (adj[current].contains(START)) {
                    solution.compareAndSet(null, new ArrayList<>(pathSoFar));
                    found.set(true);
                    return true;
                }
                return false;
            }

            // Build list of candidates
            List<Integer> candidates = new ArrayList<>();
            if (forced != null) {
                candidates.addAll(forced);
            } else {
                for (int next : adj[current]) {
                    if ((used & (1 << next)) == 0) candidates.add(next);
                }
            }

            int k = candidates.size();
            if (k == 0) return false;

            int workers = (forced != null) ? 1 : parallelism;

            // ---------- Sequential path ----------
            if (workers <= 1 || k <= 1) {
                for (int next : candidates) {
                    if (found.get()) return found.get();

                    int newUsed = used | (1 << next);
                    pathSoFar.add(next);
                    try {
                        if (new SearchTask(next, newUsed, depth + 1, 1, null, pathSoFar).compute()) {
                            found.set(true);
                            return true;
                        }
                    } finally {
                        pathSoFar.remove(pathSoFar.size() - 1);
                    }
                }
                return found.get();
            }

            // ---------- Parallel splitting (using work-stealing) ----------
            List<SearchTask> subtasks = new ArrayList<>();

            if (workers >= k) {
                int base = workers / k;
                int extra = workers % k;
                for (int i = 0; i < k; i++) {
                    int next = candidates.get(i);
                    int newUsed = used | (1 << next);
                    int subWorkers = base + (i < extra ? 1 : 0);
                    List<Integer> newPath = new ArrayList<>(pathSoFar);
                    newPath.add(next);
                    subtasks.add(new SearchTask(next, newUsed, depth + 1, subWorkers, null, newPath));
                }
            } else {
                int base = k / workers;
                int extra = k % workers;
                int idx = 0;
                for (int w = 0; w < workers; w++) {
                    int groupSize = base + (w < extra ? 1 : 0);
                    List<Integer> group = new ArrayList<>(groupSize);
                    for (int j = 0; j < groupSize; j++) group.add(candidates.get(idx++));
                    List<Integer> newPath = new ArrayList<>(pathSoFar);
                    subtasks.add(new SearchTask(current, used, depth, 1, group, newPath));
                }
            }

            // Fork all subtasks (spawn them in parallel)
            for (SearchTask task : subtasks) {
                task.fork();
            }

            // Join all subtasks (wait for them to complete)
            for (SearchTask task : subtasks) {
                task.join();
            }

            // Return whether a solution was found
            return found.get();
        }
    }

    public static void main(String[] args) throws Exception {
        Path path = Paths.get("H:\\LabPPD\\Lab6\\lab6\\src\\graph.txt");
        String content = java.nio.file.Files.readString(path).trim();

        String[] tokens = content.split("\\s+");
        int idx = 0;
        int n = Integer.parseInt(tokens[idx++]);

        List<Integer>[] adj = new List[n];
        for (int i = 0; i < n; i++) adj[i] = new ArrayList<>();

        while (idx + 1 < tokens.length) {
            int u = Integer.parseInt(tokens[idx++]);
            int v = Integer.parseInt(tokens[idx++]);
            adj[u].add(v);
        }

        HamiltonianCycleForkJoin solver = new HamiltonianCycleForkJoin(n, adj);
        int RUNS = 50;
        int[] threadCounts = {1, 2, 4, 8, 16, 32};

        long[] minTime = new long[threadCounts.length];
        long[] maxTime = new long[threadCounts.length];
        long[] sumTime = new long[threadCounts.length];

        for (int i = 0; i < threadCounts.length; i++) {
            minTime[i] = Long.MAX_VALUE;
        }

        for(int run = 1; run <= RUNS; run++) {
            System.out.println("Run #" + run);
            boolean ok = false;

            for (idx = 0; idx < threadCounts.length; idx++) {
                int threads = threadCounts[idx];

                long t0 = System.currentTimeMillis();
                boolean find = solver.hasHamiltonianCycle(threads);
                long t1 = System.currentTimeMillis();

                long elapsed = t1 - t0;

                System.out.printf("Threads %2d   Found: %b   Time: %4d ms%n",
                        threads, find, elapsed);

                if (elapsed < minTime[idx]) minTime[idx] = elapsed;
                if (elapsed > maxTime[idx]) maxTime[idx] = elapsed;
                sumTime[idx] += elapsed;

                if (find) {
                    List<Integer> cycle = solver.getSolution();
                    if (cycle != null) {
                        for (int v : cycle) System.out.print(v + " ");
                        System.out.println(" (back to start)");
                    } else {
                        System.out.println("No cycle found.");
                        ok = true;
                        break;
                    }
                }
            }

            if (ok) break;
        }

        System.out.println("\n======================================");
        System.out.println("      PERFORMANCE SUMMARY (50 runs)");
        System.out.println("======================================");

        for (idx = 0; idx < threadCounts.length; idx++) {
            int threads = threadCounts[idx];
            double avg = sumTime[idx] / (double) RUNS;

            System.out.printf("Threads %2d → Min: %4d ms | Max: %4d ms | Avg: %.2f ms%n",
                    threads, minTime[idx], maxTime[idx], avg);
        }

        System.out.println("======================================");
    }
}