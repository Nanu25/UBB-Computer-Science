package Model.Statement;

import Model.PrgState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IntValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;
import Utils.MyIHeap.MyIHeap;
import Utils.MyISemaphore.MyISem;
import Utils.MyIStack.MyIStack;

import java.util.List;
import java.util.Map;

public class ReleaseStmt implements IStmt {
    private String var1;

    public ReleaseStmt(String var1) {
        this.var1 = var1;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getStk();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyISem semaphoreTable = state.getSemaphoreTable();

        if (!symTable.isDefined(var1))
            throw new MyException("Variable " + var1 + " is not defined.");

        Value foundIndexValue = symTable.lookup(var1);

        if (!(foundIndexValue instanceof IntValue))
            throw new MyException("Variable " + var1 + " must be of type int.");

        int index = ((IntValue) foundIndexValue).getVal();

        if (!semaphoreTable.isDefined(index))
            throw new MyException("Semaphore index " + index + " is not defined.");

        synchronized (semaphoreTable) {
            Map.Entry<Integer, List<Integer>> semEntry = semaphoreTable.lookup(index);
            List<Integer> waitingList = semEntry.getValue();

            int prgId = state.getPrgStateId();

            if (waitingList.contains(prgId)) {
                waitingList.remove((Integer) prgId);
                semaphoreTable.update(index, semEntry.getKey(), waitingList);
            }
        }

        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new ReleaseStmt(var1);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType type = typeEnv.lookup(var1);
        if (!type.equals(new IntType()))
            throw new MyException("Variable " + var1 + " must be of type int.");
        return typeEnv;
    }

    @Override
    public String toString() {
        return "release(" + var1 + ")";
    }

}
