package Model.Statement;

import Model.PrgState;
import Model.Type.IType;
import Model.Values.Value;
import Utils.MyIDictionary.MyDictionary;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIStack.MyStack;

import Exception.MyException;

public class ForkStmt implements IStmt {
    private final IStmt stmt;

    public ForkStmt(IStmt s) {
        stmt = s;
    }

    @Override
    public String toString() {
        return "fork(" + stmt.toString() + ")";
    }

    @Override
    public PrgState execute(PrgState state) {
        MyStack<IStmt> newExeStack = new MyStack<>();

        MyDictionary<String, Value> newSymTable = (MyDictionary<String, Value>) state.getSymTable().deepCopy();

        return new PrgState(
                newExeStack,
                newSymTable,
                state.getOutput(),
                state.getSymFile(),
                state.getHeap(),
                stmt,
                state.getSemaphoreTable()
        );
    }

    @Override
    public IStmt deepCopy() {
        return new ForkStmt(stmt.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        MyIDictionary typ = stmt.typecheck(typeEnv);
        return typeEnv;
    }
}
