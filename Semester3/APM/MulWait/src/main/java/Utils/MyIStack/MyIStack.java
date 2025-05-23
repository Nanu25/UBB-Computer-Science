package Utils.MyIStack;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public interface MyIStack<T> {

    T pop();
    void push(T v);

    boolean isEmpty();
    public List<T> getReversed();

    ArrayList<T> getAll();
}
