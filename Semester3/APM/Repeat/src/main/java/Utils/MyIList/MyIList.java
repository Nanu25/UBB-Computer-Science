package Utils.MyIList;

import Model.Values.Value;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public interface MyIList <T>{
    void add(T v);

    ArrayList<T> getAll();
}
