package Utils.MyIFileTable;

import Utils.MyIDictionary.MyDictionary;

import java.io.BufferedReader;
import java.util.*;

import Exception.MyException;
import Exception.FileOpenException;
import Exception.ReadFileException;
import Exception.FileClosedException;
import Exception.FileTypeException;

public class MyFileTable implements MyIFileTable{
    MyDictionary<String, BufferedReader> fileTable;

    public MyFileTable() {
        fileTable = new MyDictionary<>();
    }

    @Override
    public boolean openFile(String filename) throws MyException {
        if (fileTable.isDefined(filename)) {
            throw new FileOpenException("File already opened");
        }
        try {
            BufferedReader br = new BufferedReader(new java.io.FileReader(filename));
            fileTable.put(filename, br);
        } catch (java.io.IOException e) {
            throw new FileOpenException("Could not open file");
        }
        return true;
    }

    @Override
    public void closeFile(String filename) throws MyException {
        try {
            fileTable.remove(filename);
        } catch (Exception e) {
            throw new FileClosedException("Could not close file");
        }
    }

    @Override
    public int readFile(String filename) throws MyException {
        BufferedReader br = null;
        try {
            br = fileTable.lookup(filename);
        } catch (Exception e) {
            throw new FileOpenException("Could not find file");
        }

        String data = null;
        try {
            data = br.readLine();
        } catch (java.io.IOException e) {
            throw new ReadFileException("Could not read from file");
        }

        if(data == null){
            data = "0";
        }

        int answer = 0;
        try {
            answer = Integer.parseInt(data);
        } catch (NumberFormatException exception) {
            throw new FileTypeException("Invalid line in file");
        }
        return answer;
    }

    @Override
    public String toString() {
        StringBuilder answer = new StringBuilder();
        answer.append("File Table:\n");
        for(String name: fileTable.getAllKeys()){
            answer.append(name).append("\n");
        }
        return answer.toString();
    }

    @Override
    public List<String> getFiles() {
        return fileTable.getAllKeys();
    }

    @Override
    public BufferedReader get(String fileName) {
        return fileTable.lookup(fileName);
    }

    @Override
    public void put(String fileNameStr, BufferedReader br) {
        fileTable.put(fileNameStr, br);
    }

    @Override
    public List<Map.Entry<String, BufferedReader>> getAll() {
        return new ArrayList<>(fileTable.getAllEntries());
    }


}
