package Utils.MyIHeap;

import Model.Values.Value;
import Exception.MyException;

import java.util.Map;

public interface MyIHeap<K, V> {
    int add(Value value);
    void update(int address, Value value) throws MyException;
    Value lookup(int address) throws MyException;
    boolean isDefined(int address);
    void remove(int address) throws MyException;
    String toString();
    Map getContent();
    void setContent(Map newContent);
    Map<K, V> toMap();
}
