import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

class BankAccount {
    private final int id;
    private long balance;
    private final ReentrantLock lock;

    public BankAccount(int id, long initialBalance) {
        this.id = id;
        this.balance = initialBalance;
        this.lock = new ReentrantLock();
    }

    public long getBalance() {
        return balance;
    }

    public void deposit(long amount) {
        balance += amount;
    }

    public void withdraw(long amount) {
        balance -= amount;
    }

    public ReentrantLock getLock() {
        return lock;
    }
}

class Bank {
    private final BankAccount[] accounts;
    private final long initialTotalBalance;

    public Bank(int numAccounts, long initialBalance) {
        accounts = new BankAccount[numAccounts];
        for (int i = 0; i < numAccounts; i++) {
            accounts[i] = new BankAccount(i, initialBalance);
        }
        this.initialTotalBalance = (long) numAccounts * initialBalance;
    }

    public int getAccountCount() {
        return accounts.length;
    }

    public void transfer(int fromId, int toId, long amount) {
        BankAccount from = accounts[fromId];
        BankAccount to = accounts[toId];
        BankAccount first = fromId < toId ? from : to;
        BankAccount second = fromId < toId ? to : from;

        first.getLock().lock();
        try {
            second.getLock().lock();
            try {
                if (from.getBalance() >= amount) {
                    from.withdraw(amount);
                    to.deposit(amount);
                }
            } finally {
                second.getLock().unlock();
            }
        } finally {
            first.getLock().unlock();
        }
    }

    public boolean checkConsistency() {
        for (BankAccount account : accounts) {
            account.getLock().lock();
        }
        try {
            long totalBalance = 0;
            for (BankAccount account : accounts) {
                totalBalance += account.getBalance();
            }
            boolean consistent = (totalBalance == initialTotalBalance);
            if (!consistent) {
                System.err.println("INCONSISTENCY DETECTED! Expected: " +
                        initialTotalBalance + ", Found: " + totalBalance);
            }
            return consistent;
        } finally {
            for (int i = accounts.length - 1; i >= 0; i--) {
                accounts[i].getLock().unlock();
            }
        }
    }
}

/**
 * New thread class dedicated to periodically checking bank consistency.
 */
class ConsistencyChecker implements Runnable {
    private final Bank bank;
    // 'volatile' ensures that changes to this variable are immediately visible to all threads.
    private volatile boolean running = true;
    private final long checkIntervalMillis;

    public ConsistencyChecker(Bank bank, long checkIntervalMillis) {
        this.bank = bank;
        this.checkIntervalMillis = checkIntervalMillis;
    }

    /**
     * Signals the checker to stop running.
     */
    public void stop() {
        this.running = false;
    }

    @Override
    public void run() {
        System.out.println("Consistency checker thread started.");
        int checksPassed = 0;
        int checksFailed = 0;

        while (running) {
            try {
                if (bank.checkConsistency()) {
                    checksPassed++;
                } else {
                    checksFailed++;
                }
                Thread.sleep(checkIntervalMillis);
            } catch (InterruptedException e) {
                running = false;
                Thread.currentThread().interrupt(); // Preserve the interrupted status
            }
        }
        System.out.println("Consistency checker thread finished. Checks passed: "
                + checksPassed + ", Checks failed: " + checksFailed);
    }
}

/**
 * Simplified worker that only performs transfers.
 */
class TransferWorker implements Runnable {
    private final Bank bank;
    private final Random random;
    private final int operationsToPerform;

    public TransferWorker(Bank bank, long seed, int operationsToPerform) {
        this.bank = bank;
        this.random = new Random(seed);
        this.operationsToPerform = operationsToPerform;
    }

    @Override
    public void run() {
        for (int i = 0; i < operationsToPerform; i++) {
            int fromId = random.nextInt(bank.getAccountCount());
            int toId = random.nextInt(bank.getAccountCount());
            while (toId == fromId) {
                toId = random.nextInt(bank.getAccountCount());
            }
            long amount = random.nextInt(10000) + 1;
            bank.transfer(fromId, toId, amount);
        }
    }
}


public class Main {
    public static final int MAX_ACCOUNTS = 10;
    public static final int TOTAL_TRANSACTIONS = 10_000_000;

    public static void runSimulation(int numAccounts, int numThreads, long initialBalance) {
        System.out.println("\n" + "=".repeat(70));
        System.out.println("SIMULATION PARAMETERS:");
        System.out.println("  Accounts: " + numAccounts);
        System.out.println("  Threads: " + numThreads);
        System.out.println("  Total Transactions: " + TOTAL_TRANSACTIONS);
        System.out.println("  Initial balance per account: $" + initialBalance);
        System.out.println("=".repeat(70));

        Bank bank = new Bank(numAccounts, initialBalance);
        System.out.println("\nInitial consistency check: " + (bank.checkConsistency() ? "PASSED" : "FAILED"));

        ConsistencyChecker checker = new ConsistencyChecker(bank, 100); // Check every 100ms
        Thread checkerThread = new Thread(checker);
        checkerThread.start();

        int transactionsPerThread = TOTAL_TRANSACTIONS / numThreads;
        Thread[] threads = new Thread[numThreads];
        long startTime = System.nanoTime();

        for (int i = 0; i < numThreads; i++) {
            threads[i] = new Thread(new TransferWorker(bank, System.nanoTime() + i, transactionsPerThread));
            threads[i].start();
        }

        // Wait for all transfer worker threads to complete
        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        long endTime = System.nanoTime();

        checker.stop();
        try {
            checkerThread.join(); // Wait for the checker to terminate gracefully
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        double elapsedSeconds = (endTime - startTime) / 1_000_000_000.0;

        // Final consistency check
        System.out.println("\nFinal consistency check: " + (bank.checkConsistency() ? "PASSED" : "FAILED"));

        System.out.println("\nPerformance Metrics:");
        System.out.println("  Total time: " + String.format("%.3f", elapsedSeconds) + " seconds");
    }

    public static void main(String[] args) {
        try (PrintStream fileOut = new PrintStream(new File("simulation_output.txt"))) {
            System.setOut(fileOut); // Redirect System.out to the file

            System.out.println("Bank Transfer Simulation with Concurrent Threads");

            runSimulation(MAX_ACCOUNTS, 1, 10000);
            runSimulation(MAX_ACCOUNTS, 2, 10000);
            runSimulation(MAX_ACCOUNTS, 4, 10000);
            runSimulation(MAX_ACCOUNTS, 8, 10000);
            runSimulation(MAX_ACCOUNTS, 16, 10000);
            runSimulation(MAX_ACCOUNTS, 50, 10000);

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}