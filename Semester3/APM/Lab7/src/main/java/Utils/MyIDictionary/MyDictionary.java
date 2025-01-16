package Utils.MyIDictionary;

import java.util.*;

import Exception.DuplicateKeyException;
import Exception.KeyNotFoundException;


public class MyDictionary <K, V> implements MyIDictionary<K,V> {
    private Map<K, V> map;

    public MyDictionary () {
        this.map = new HashMap<K, V>();
    }

    public MyDictionary (Map<K, V> map) {
        this.map = map;
    }


    public void put(K key, V value) {
        if (!this.map.containsKey(key))
            this.map.put(key, value);
        else throw new DuplicateKeyException();
    }

    public boolean isDefined(K key) {
        return this.map.get(key) != null;
    }

    @Override
    public V lookup(K key) {
        if (!this.isDefined(key))
            throw new KeyNotFoundException();
        return this.map.get(key);
    }

    @Override
    public void update(K id, V val) {
//        if (!this.isDefined(id))
//            throw new DuplicateKeyException();
        this.map.put(id, val);
    }

    @Override
    public void remove(K fileName) {
        if (!this.isDefined(fileName))
            throw new KeyNotFoundException();
        this.map.remove(fileName);
    }

    @Override
    public List<K> getAllKeys() {
        return new ArrayList<>(this.map.keySet());
    }

    @Override
    public Map<K, V> getContent() {
        return this.map;
    }

    @Override
    public MyIDictionary<K, V> deepCopy() {
        return new MyDictionary(this.map);
    }

    @Override
    public HashMap<K, V> getAll() {
        return new HashMap<>(this.map);
    }

    @Override
    public String toString() {
        return this.map.toString();
    }

    public Set<Map.Entry<K, V>> getAllEntries() {
        return map.entrySet();
    }
}
