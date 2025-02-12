package Model.Statement;

import Model.Exp.Exp;
import Model.Exp.RelationalExp;
import Model.Exp.ValueExp;
import Model.Exp.VarExp;
import Model.PrgState;
import Model.Type.IntType;
import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIStack.MyIStack;
import Exception.MyException;

public class ForStmt implements IStmt {
    private final String var;
    private final Exp exp1, exp2, exp3;
    private final IStmt stmt;

    public ForStmt(String var, Exp e1, Exp e2, Exp e3, IStmt s) {
        this.var = var;
        this.exp1 = e1;
        this.exp2 = e2;
        this.exp3 = e3;
        this.stmt = s;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getStk();

        IStmt transformedStmt = new CompStmt(
                new VarDeclStmt(var, new IntType()),
                new CompStmt(
                        new AssignStmt(var, exp1),
                        new WhileStmt(
                                new RelationalExp(new VarExp(var), exp2, "<"),
                                new CompStmt(stmt, new AssignStmt(var, exp3))
                        )
                )
        );

        stack.push(transformedStmt);
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new ForStmt(var, exp1.deepCopy(), exp2.deepCopy(), exp3.deepCopy(), stmt.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType t1 = exp1.typecheck(typeEnv);
        IType t2 = exp2.typecheck(typeEnv);
        IType t3 = exp3.typecheck(typeEnv);

        if (!(t1.equals(new IntType()) && t2.equals(new IntType()) && t3.equals(new IntType()))) {
            throw new MyException("For statement expressions must be of type int.");
        }

        typeEnv.put(var, new IntType());
        stmt.typecheck(typeEnv);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "for(" + var + " = " + exp1 + "; " + var + " < " + exp2 + "; " + var + " = " + exp3 + ") " + stmt;
    }
}
