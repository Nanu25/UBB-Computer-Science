package Utils.MyIList;

import java.util.List;

public class MyList<T> implements MyIList<T> {
    private List<T> output;

    public MyList() {
        output = new java.util.ArrayList<T>();
    }

    @Override
    public void add(T v) {
        this.output.add(v);
    }

    @Override
    public String toString() {
        return this.output.toString();
    }

}
