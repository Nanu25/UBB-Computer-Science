package Model.Statement;

import Model.PrgState;
import Exception.MyException;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException;
    IStmt deepCopy();
}
