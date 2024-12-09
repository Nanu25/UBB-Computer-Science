package Repository;

import Model.PrgState;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

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
}
