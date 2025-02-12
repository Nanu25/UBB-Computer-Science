package Model.Statement;

import Model.Exp.Exp;
import Model.PrgState;
import Exception.TypeException;
import Exception.MyException;
import Model.Type.BoolType;
import Model.Type.IType;
import Model.Values.BoolValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIStack.MyIStack;

public class WhileStmt implements IStmt {
    private Exp exp;
    private IStmt stmt;

    public WhileStmt(Exp exp, IStmt stmt) {
        this.exp = exp;
        this.stmt = stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        Value conditionValue = exp.eval(state.getSymTable(), state.getHeap());

        if (!(conditionValue.getType() instanceof BoolType)) {
            throw new TypeException("The condition of the while statement is not a boolean.");
        }

        BoolValue conditionBoolValue = (BoolValue) conditionValue;
        if (conditionBoolValue.getVal()) {
            MyIStack<IStmt> stack = state.getStk();
            stack.push(this);
            stack.push(stmt);
        }

        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new WhileStmt(exp.deepCopy(), stmt.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typeexp = exp.typecheck(typeEnv);
        if (typeexp.equals(new BoolType())) {
            stmt.typecheck(typeEnv.deepCopy());
            return typeEnv;
        } else {
            throw new TypeException("The condition of the while statement has not the type bool.");
        }
    }

    @Override
    public String toString() {
        return "while (" + exp.toString() + ") " + stmt.toString();
    }
}
