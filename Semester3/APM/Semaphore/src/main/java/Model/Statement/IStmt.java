package Model.Statement;

import Model.PrgState;
import Exception.MyException;
import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException;
    IStmt deepCopy();
    MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException;
}
