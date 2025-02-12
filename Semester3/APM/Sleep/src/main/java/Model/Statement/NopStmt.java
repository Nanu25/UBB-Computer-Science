package Model.Statement;

import Model.PrgState;
import Exception.MyException;
import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;

public class NopStmt implements IStmt {
    @Override
    public PrgState execute(PrgState state) throws MyException {
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        return null;
    }

    @Override
    public String toString() {
        return "NOP";
    }
}
