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
        state.getOutput().add(exp.eval(state.getSymTable()));
        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new PrintStmt(exp.deepCopy());
    }
}
