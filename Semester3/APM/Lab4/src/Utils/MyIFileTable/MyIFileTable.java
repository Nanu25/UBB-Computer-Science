package Utils.MyIFileTable;

import java.io.BufferedReader;
import java.util.List;

public interface MyIFileTable {
    boolean openFile(String filename);
    void closeFile(String filename);
    int readFile(String filename);
    String toString();
    List<String> getFiles();

    BufferedReader get(String fileName);

    void put(String fileNameStr, BufferedReader br);
}
