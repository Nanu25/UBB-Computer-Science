package Model.Statement;

import Model.PrgState;
import Exception.MyException;
import Model.Exp.Exp;

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
        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new PrintStmt(exp.deepCopy());
    }
}
