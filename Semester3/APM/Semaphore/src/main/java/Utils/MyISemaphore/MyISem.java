package Utils.MyISemaphore;

import java.util.List;
import java.util.Map;
import Exception.MyException;

public interface MyISem {
    int add(int permits);
    void update(int address, int permits, List<Integer> waitingThreads) throws MyException;
    Map.Entry<Integer, List<Integer>> lookup(int address) throws MyException;
    boolean isDefined(int address);
    Map<Integer, Map.Entry<Integer, List<Integer>>> getContent();
    Map<Integer, Map.Entry<Integer, List<Integer>>> toMap();
}
