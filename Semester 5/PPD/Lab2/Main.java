import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

class ProductQueue {
    private Queue<Integer> queue = new LinkedList<>();
    private int capacity;
    private boolean producerDone = false;

    public ProductQueue(int capacity) {
        this.capacity = capacity;
    }

    public synchronized void produce(int product) throws InterruptedException {
        while (queue.size() == capacity) {
            wait();
        }
        queue.add(product);
        notify();
    }

    // Consumer retrieves products from the queue
    public synchronized Integer consume() throws InterruptedException {
        while (queue.isEmpty() && !producerDone) {
            wait();
        }
        if (queue.isEmpty() && producerDone) {
            return null;
        }
        int product = queue.poll();
        notify();
        return product;
    }

    public synchronized void setProducerDone() {
        producerDone = true;
        notify();
    }
}

class Producer implements Runnable {
    private int[] vector1;
    private int[] vector2;
    private ProductQueue productQueue;

    public Producer(int[] vector1, int[] vector2, ProductQueue productQueue) {
        this.vector1 = vector1;
        this.vector2 = vector2;
        this.productQueue = productQueue;
    }

    @Override
    public void run() {
        try {
            System.out.println("Producer started - computing products...");
            for (int i = 0; i < vector1.length; i++) {
                int product = vector1[i] * vector2[i];
                productQueue.produce(product);
            }

            productQueue.setProducerDone();
            System.out.println("Producer finished - all products computed");

        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.out.println("Producer interrupted");
        }
    }
}

class Consumer implements Runnable {
    private ProductQueue productQueue;
    private long result = 0;

    public Consumer(ProductQueue productQueue) {
        this.productQueue = productQueue;
    }

    @Override
    public void run() {
        try {
            System.out.println("Consumer started - summing products...");

            Integer product;
            int count = 0;

            while ((product = productQueue.consume()) != null) {
                result += product;
                count++;
            }
            System.out.println("Consumer finished - processed " + count + " products");
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            System.out.println("Consumer interrupted");
        }
    }
    public long getResult() {
        return result;
    }
}

public class Main {

    public static long computeScalarProduct(int[] vector1, int[] vector2, int queueSize)
            throws InterruptedException {

        ProductQueue productQueue = new ProductQueue(queueSize);
        Consumer consumer = new Consumer(productQueue);

        Thread producerThread = new Thread(new Producer(vector1, vector2, productQueue));
        Thread consumerThread = new Thread(consumer);

        long startTime = System.nanoTime();

        producerThread.start();
        consumerThread.start();

        producerThread.join();
        consumerThread.join();

        long endTime = System.nanoTime();
        long duration = (endTime - startTime) / 1_000_000;
        System.out.println("Computation completed in " + duration + " ms");

        return consumer.getResult();
    }

    public static void main(String[] args) throws InterruptedException {
        int vectorSize = 1000000;
        int[] vector1 = new int[vectorSize];
        int[] vector2 = new int[vectorSize];

        Random random = new Random();
        for (int i = 0; i < vectorSize; i++) {
            vector1[i] = random.nextInt(10);
            vector2[i] = random.nextInt(10);
        }

        System.out.println("Computing scalar product of two vectors of size " + vectorSize);
        System.out.println("=".repeat(60));

        // Test with different queue sizes
        int[] queueSizes = {1, 10, 100, 1000, 10000};

        for (int queueSize : queueSizes) {
            System.out.println("\n--- Queue Size: " + queueSize + " ---");
            long result = computeScalarProduct(vector1, vector2, queueSize);
            System.out.println("Scalar Product Result: " + result);
        }

        System.out.println("\n" + "=".repeat(60));
        System.out.println("Verifying with direct computation...");
        long startTime = System.nanoTime();
        long directResult = 0;
        for (int i = 0; i < vectorSize; i++) {
            directResult += vector1[i] * vector2[i];
        }
        long endTime = System.nanoTime();
        System.out.println("Direct computation result: " + directResult);
        System.out.println("Direct computation time: " + (endTime - startTime) / 1_000_000 + " ms");
    }
}