package Repository;

import Model.PrgState;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;
import Utils.MyISemaphore.MyISem;
import javafx.util.Pair;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Repository implements IRepository{
    private List<PrgState> Repo;
    String logFilePath;

    public Repository(PrgState state, String logFilePath) {
        this.Repo = new ArrayList<>();
        this.Repo.add(state);
        this.logFilePath = logFilePath;

    }

//    @Override
//    //TODO this will be removed.
//    public PrgState getCurPrg() {
//        return this.Repo.get(0);
//    }

    @Override
    public void addPrg(PrgState prg) {
        this.Repo.add(prg);
    }

    @Override
    public void logPrgStateExec(PrgState prg) {
        if(this.logFilePath != null) {
            PrintWriter logFile = null;
            try {
                logFile = new PrintWriter(
                        new BufferedWriter(new FileWriter(logFilePath, true)));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            logFile.println(this.Repo.get(0).toString());
            logFile.close();
        }
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.Repo;
    }

    @Override
    public void setPrgList(List<PrgState> prgList) {
        this.Repo = prgList;
    }

    @Override
    public MyIHeap getHeap() {
        return this.Repo.get(0).getHeap();
    }

    @Override
    public MyIDictionary getSymTable() {
        return this.Repo.get(0).getSymTable();
    }

    @Override
    public List<String> getOut() {
        return this.Repo.get(0).getOutput()
                .getAll() // Assuming `MyIList` has a method to retrieve all elements as a list
                .stream()
                .map(Value::toString) // Convert each Value to its String representation
                .collect(Collectors.toList());
    }

    @Override
    public List<String> getFileTable() {
        return this.Repo.get(0).getSymFileContent();
    }


    @Override
    public PrgState getPrgStateById(int prgStateId) {
        return this.Repo.stream()
                .filter(prg -> prg.getPrgStateId() == prgStateId)
                .findFirst()
                .orElse(null);
    }

    @Override
    public MyISem getSemaphoreTable() {
        return this.Repo.get(0).getSemaphoreTable();
    }


}
