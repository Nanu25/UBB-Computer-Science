package Model.Statement;

import Model.PrgState;
import Exception.MyException;
import Model.Exp.Exp;
import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;

public class PrintStmt implements IStmt {
    Exp exp;

    public PrintStmt(Exp e) {
        exp = e;
    }


    @Override
    public String toString() {
        return "print(" + exp.toString() + ")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        try {
            state.getOutput().add(exp.eval(state.getSymTable(), state.getHeap()));
        } catch (MyException e) {
            throw new RuntimeException(e);
        }
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new PrintStmt(exp.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        exp.typecheck(typeEnv);
        return typeEnv;
    }

}
