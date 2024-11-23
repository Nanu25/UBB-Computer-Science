package Repository;

import Model.PrgState;

public interface IRepository {

    PrgState getCurPrg();

    void addPrg(PrgState prg);

    void logPrgStateExec();
}
