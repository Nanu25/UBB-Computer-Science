package Repository;

import Model.PrgState;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;

import java.util.Collection;
import java.util.List;

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
}
