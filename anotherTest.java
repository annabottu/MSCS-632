import java.util.*;
import java.util.concurrent.*;
import java.io.*;
import java.util.concurrent.locks.*;

public class anotherTest {

    private static final queueForTasks taskQueue = new queueForTasks();

    // Shared result list with thread-safe wrapper
    private static final List<String> results = Collections.synchronizedList(new ArrayList<>());

    private static final int workers = 8;
    private static final int tasks = 5;

    public static void main(String[] args) {
        //goes through the requests and add to the queue
        for (int i = 1; i <= tasks; i++) {
            taskQueue.addTask(new RequestRide(i, "pickup " + i, "dropoff " + i));
        }

        ExecutorService executor = Executors.newFixedThreadPool(workers);

        for (int i = 0; i < workers; i++) {
            executor.execute(new Worker(i + 1));
        }

        executor.shutdown();
        //exception handling in Java using try-catch blocks to handle exceptions
        try {
            executor.awaitTermination(5, TimeUnit.MINUTES);
        } catch (InterruptedException e) {
            System.err.println("Error: " + e.getMessage());
        }

        //exception handling using try-catch for file I/O
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("results.txt"))) {
            for (String log : results) {
                writer.write(log);
                writer.newLine();
            }
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }

        System.out.println("check the results.txt file for results.");
    }

    //using ReentrantLock for queue access
    static class queueForTasks {
        private final Queue<RequestRide> queue = new LinkedList<>();
        private final Lock lock = new ReentrantLock();
        //queue structure that supports addTask() and getTask()
        public void addTask(RequestRide task) {
            lock.lock();
            try {
                queue.offer(task);
            } finally {
                lock.unlock();
            }
        }

        public RequestRide getTask() {
            lock.lock();
            try {
                return queue.poll();
            } finally {
                lock.unlock();
            }
        }
    }

    static class RequestRide {
        int request;
        String pickup;
        String dropoff;

        RequestRide(int request, String pickup, String dropoff) {
            this.request = request;
            this.pickup = pickup;
            this.dropoff = dropoff;
        }
    }

    static class Worker implements Runnable {
        private final int id;

        Worker(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            System.out.println("[Driver: " + id + "] started");
            try {
                RequestRide request;
                while ((request = taskQueue.getTask()) != null) {
                    processRequest(request);
                }
            } catch (Exception e) {
                //logging any exception or errors that occur during execution
                System.err.println("[Driver: " + id + "] Error: " + e.getMessage());
            }
            System.out.println("[Driver: " + id + "] Completed.");
        }

        private void processRequest(RequestRide request) {
            try {
                Thread.sleep(new Random().nextInt(1000));
                String result = "[Driver" + id + "] processed" + request.request +
                        " from " + request.pickup + " to " + request.dropoff;
                results.add(result);
            } catch (InterruptedException e) {
                System.err.println("[Driver:" + id + "] Interrupted: " + request.request);
                Thread.currentThread().interrupt();
            }
        }
    }
} 
