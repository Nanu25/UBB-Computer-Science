package Model.Statement;

import Model.PrgState;
import Exception.MyException;
import Model.Exp.Exp;
import Exception.TypeException;

public class IfStmt implements IStmt {
    Exp exp;
    IStmt thenS;
    IStmt elseS;

    public IfStmt(Exp e, IStmt t, IStmt el) {
        exp = e;
        thenS = t;
        elseS = el;
    }

    public String toString() {
        return "IF(" + exp.toString() + ") THEN(" + thenS.toString() + ") ELSE(" + elseS.toString() + ")";
    }

    public PrgState execute(PrgState state) throws MyException {
        if(exp.eval(state.getSymTable()) != null) {
            if(exp.eval(state.getSymTable()).getType().toString().equals("bool")) {
                if(exp.eval(state.getSymTable()).toString().equals("true")) {
                    state.getStk().push(thenS);
                } else {
                    state.getStk().push(elseS);
                }
            } else {
                throw new TypeException("Expression is not a boolean");
            }
        }
        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new IfStmt(exp.deepCopy(), thenS.deepCopy(), elseS.deepCopy());
    }

}