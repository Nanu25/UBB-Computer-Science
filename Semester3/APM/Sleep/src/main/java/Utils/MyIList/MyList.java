package Utils.MyIList;

import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements MyIList<T> {
    private List<T> output;

    public MyList() {
        output = new ArrayList<T>();
    }

    @Override
    public void add(T v) {
        this.output.add(v);
    }

    @Override
    public ArrayList<T> getAll() {
        return new ArrayList<>(this.output);
    }

    @Override
    public String toString() {
        return this.output.toString();
    }

}
