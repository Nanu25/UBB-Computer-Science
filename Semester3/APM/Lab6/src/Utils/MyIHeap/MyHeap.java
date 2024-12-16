package Utils.MyIHeap;

import Model.Values.Value;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

import Exception.MyException;
import Exception.HeapException;

public class MyHeap<K,V> implements MyIHeap<K,V> {
    private Map<Integer, Value> heap;
    private int freeLocation;

    public MyHeap() {
        this.heap = new ConcurrentHashMap<>();
        this.freeLocation = 1;
    }

    @Override
    public int add(Value value) {
        int i = 1;
        while (heap.containsKey(i) && heap.get(i) != null) {
            i++;
        }
        this.freeLocation = i;
        this.heap.put(this.freeLocation, value);
        return this.freeLocation;
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
