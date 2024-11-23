package Utils.MyIHeap;

import Model.Values.Value;

import java.util.Dictionary;
import java.util.Map;
import Exception.MyException;
import java.util.HashMap;
import Exception.HeapException;

public class MyHeap<K,V> implements MyIHeap<K,V> {
    private Map<Integer, Value> heap;
    private int freeLocation;


    public MyHeap() {
        this.heap = new HashMap<>();
        this.freeLocation = 1;
    }

    @Override
    public int add(Value value) {
        this.heap.put(this.freeLocation, value);
        this.freeLocation++;
        return this.freeLocation - 1;
    }

    @Override
    public void update(int address, Value value) throws MyException {
        if (!this.isDefined(address))
            throw new HeapException("Address not found in heap");
        this.heap.put(address, value);
    }

    @Override
    public Value lookup(int address) throws MyException {
        if (!this.isDefined(address))
            throw new HeapException("Address not found in heap");
        return this.heap.get(address);
    }

    @Override
    public boolean isDefined(int address) {
        return this.heap.get(address) != null;
    }

    @Override
    public void remove(int address) throws MyException {
        this.heap.remove(address);
    }

    @Override
    public String toString() {
        return this.heap.toString();
    }

    @Override
    public Map getContent() {
        return this.heap;
    }

    @Override
    public void setContent(Map newContent) {
        this.heap.clear();
        this.heap.putAll(newContent);
    }

}
