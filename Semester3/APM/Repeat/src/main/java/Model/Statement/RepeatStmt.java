package Model.Statement;

import Model.Exp.Exp;
import Model.Exp.NotExp;
import Model.PrgState;
import Model.Type.IType;
import Exception.MyException;
import Utils.MyIDictionary.MyIDictionary;

public class RepeatStmt implements IStmt{
    private IStmt stmt;
    private Exp exp;

    public RepeatStmt(IStmt stmt, Exp exp) {
        this.stmt = stmt;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) {
        Exp negatedCondition = new NotExp(exp);  // NotExp negates the expression
        state.getStk().push(new CompStmt(stmt, new WhileStmt(negatedCondition, stmt)));
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new RepeatStmt(stmt.deepCopy(), exp.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "repeat(" + stmt + ") until " + exp;
    }
}
