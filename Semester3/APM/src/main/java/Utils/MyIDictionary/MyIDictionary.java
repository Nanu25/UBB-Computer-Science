package Utils.MyIDictionary;

import Model.Values.Value;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public interface MyIDictionary <K, V>{
    void put(K key, V value);
    V lookup(K key);
    boolean isDefined(K key);

    void update(K id, V val);

    void remove(K fileName);

    List<K> getAllKeys();
    Map<K, V> getContent();
    MyIDictionary<K, V> deepCopy();

    HashMap<K, V> getAll();
}
