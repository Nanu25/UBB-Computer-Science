package Model.Statement;

import Model.PrgState;
import Exception.MyException;
import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;

public class ReturnStmt implements IStmt {
    @Override
    public PrgState execute(PrgState state) throws MyException {
        if (state.getSymTableStack().size() == 1) {
            throw new MyException("Cannot return from the main program.");
        }
        state.getSymTableStack().pop(); // Restore caller's symbol table
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new ReturnStmt();
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "return";
    }
}
