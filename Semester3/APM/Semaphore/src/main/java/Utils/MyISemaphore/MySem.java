package Utils.MyISemaphore;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;
import Exception.MyException;

public class MySem implements MyISem {
    private  Map<Integer, Map.Entry<Integer, List<Integer>>> table;
    private  AtomicInteger nextAddress;

    public MySem() {
        this.table = new ConcurrentHashMap<>();
        this.nextAddress = new AtomicInteger(0);
    }

    @Override
    public synchronized int add(int permits) {
        int address = nextAddress.incrementAndGet();
        table.put(address, new AbstractMap.SimpleEntry<>(permits, new ArrayList<>()));
        return address;
    }

    @Override
    public synchronized void update(int address, int permits, List<Integer> waitingThreads) throws MyException {
        if (!table.containsKey(address)) throw new MyException("Address not found in SemaphoreTable");
        table.put(address, new AbstractMap.SimpleEntry<>(permits, new ArrayList<>(waitingThreads)));
    }

    @Override
    public synchronized Map.Entry<Integer, List<Integer>> lookup(int address) throws MyException {
        if (!table.containsKey(address)) throw new MyException("Address not found in SemaphoreTable");
        return table.get(address);
    }

    @Override
    public boolean isDefined(int address) {
        return table.containsKey(address);
    }

    @Override
    public Map<Integer, Map.Entry<Integer, List<Integer>>> getContent() {
        return table;
    }

    @Override
    public Map<Integer, Map.Entry<Integer, List<Integer>>> toMap() {
        return new HashMap<>(table);
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (Map.Entry<Integer, Map.Entry<Integer, List<Integer>>> entry : table.entrySet()) {
            result.append(entry.getKey()).append(" -> ").append(entry.getValue().getKey()).append(" ").append(entry.getValue().getValue()).append("\n");
        }
        return result.toString();
    }

}
