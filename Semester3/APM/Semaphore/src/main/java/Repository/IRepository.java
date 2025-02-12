package Repository;

import Model.PrgState;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;
import Utils.MyISemaphore.MyISem;
import javafx.util.Pair;

import java.util.Collection;
import java.util.List;
import java.util.Map;

public interface IRepository {

    //PrgState getCurPrg();

    void addPrg(PrgState prg);

    void logPrgStateExec(PrgState prg);

    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> prgList);
    MyIHeap getHeap();

    MyIDictionary getSymTable();

    List<String> getOut();
    List<String> getFileTable();

    PrgState getPrgStateById(int prgStateId);

    MyISem getSemaphoreTable();
}
