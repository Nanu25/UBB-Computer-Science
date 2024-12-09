package Model.Statement;

import Model.PrgState;
import Model.Values.Value;
import Utils.MyIDictionary.MyDictionary;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIStack.MyStack;


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
                stmt
        );
    }

    @Override
    public IStmt deepCopy() {
        return new ForkStmt(stmt.deepCopy());
    }
}
