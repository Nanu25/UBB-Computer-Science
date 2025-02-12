package Utils.MyILock;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;
import Exception.MyException;

public class MyLock implements MyILock{
    private Map<Integer, Integer> lockTable;
    private AtomicInteger freeLocation;

    public MyLock() {
        this.lockTable = new ConcurrentHashMap<>();
        this.freeLocation = new AtomicInteger(0);
    }

    @Override
    public synchronized int add() {
        int address = freeLocation.incrementAndGet();
        lockTable.put(address, -1);
        return address;
    }

    @Override
    public void update(int address, int value) throws MyException {
        lockTable.put(address, value);
    }

    @Override
    public  synchronized Integer lookup(int address) throws MyException {
        if (!lockTable.containsKey(address)) throw new MyException("Address not found in LockTable");
        return lockTable.get(address);
    }

    @Override
    public int getFreeLocation() {
        return freeLocation.get();
    }

    @Override
    public boolean isDefined(int address) {
        return lockTable.containsKey(address);
    }

    @Override
    public Map<Integer, Integer> getContent() {
        return lockTable;
    }

    @Override
    public Map<Integer, Integer> toMap() {
        return lockTable;
    }
}
