package Model.Statement;

import Model.Exp.Exp;
import Model.Exp.RelationalExp;
import Model.PrgState;
import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;
import Utils.MyIStack.MyIStack;

public class SwitchStmt implements IStmt {
    private final Exp exp, exp1, exp2;
    private final IStmt stmt1, stmt2, stmt3;

    public SwitchStmt(Exp exp, Exp exp1, Exp exp2, IStmt stmt1, IStmt stmt2, IStmt stmt3) {
        this.exp = exp;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.stmt1 = stmt1;
        this.stmt2 = stmt2;
        this.stmt3 = stmt3;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getStk();

        IStmt newStmt = new IfStmt(
                new RelationalExp(exp, exp1, "=="),
                stmt1,
                new IfStmt(
                        new RelationalExp(exp, exp2, "=="),
                        stmt2,
                        stmt3
                )
        );

        stk.push(newStmt);
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typeExp = exp.typecheck(typeEnv);
        IType typeExp1 = exp1.typecheck(typeEnv);
        IType typeExp2 = exp2.typecheck(typeEnv);

        if (!typeExp.equals(typeExp1) || !typeExp.equals(typeExp2)) {
            throw new MyException("Switch statement: The expressions must have the same type!");
        }

        stmt1.typecheck(typeEnv.deepCopy());
        stmt2.typecheck(typeEnv.deepCopy());
        stmt3.typecheck(typeEnv.deepCopy());

        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new SwitchStmt(exp.deepCopy(), exp1.deepCopy(), exp2.deepCopy(), stmt1.deepCopy(), stmt2.deepCopy(), stmt3.deepCopy());
    }

    @Override
    public String toString() {
        return "switch(" + exp + ") (case " + exp1 + ": " + stmt1 + ") (case " + exp2 + ": " + stmt2 + ") (default: " + stmt3 + ")";
    }
}
