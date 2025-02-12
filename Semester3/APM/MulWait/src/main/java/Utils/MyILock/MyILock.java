package Utils.MyILock;

import java.util.List;
import java.util.Map;
import Exception.MyException;

public interface MyILock {
    int add();
    void update(int address, int value) throws MyException;
    Integer lookup(int address) throws MyException;
    int getFreeLocation();
    boolean isDefined(int address);
    Map<Integer, Integer> getContent();
    Map<Integer, Integer> toMap();

}
