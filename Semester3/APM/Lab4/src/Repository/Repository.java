package Repository;

import Model.PrgState;

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

    @Override
    public PrgState getCurPrg() {
        return this.Repo.get(0);
    }

    @Override
    public void addPrg(PrgState prg) {
        this.Repo.add(prg);
    }

    @Override
    public void logPrgStateExec() {
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

}
