package Utils.MyIFileTable;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

public interface MyIFileTable {
    boolean openFile(String filename);
    void closeFile(String filename);
    int readFile(String filename);
    String toString();
    List<String> getFiles();

    BufferedReader get(String fileName);

    void put(String fileNameStr, BufferedReader br);

    List<Map.Entry<String, BufferedReader>> getAll();
}
