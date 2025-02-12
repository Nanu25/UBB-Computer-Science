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
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public class AcquireStmt implements IStmt {
    private String var1;

    public AcquireStmt(String v) {
        var1 = v;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getStk();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyISem semaphoreTable = state.getSemaphoreTable();

        if (!symTable.isDefined(var1))
            throw new MyException("Variable " + var1 + " is not defined.");

        Value foundIndex = symTable.lookup(var1);

        if (!foundIndex.getType().equals(new IntType()))
            throw new MyException("Variable " + var1 + " is not an integer.");

        int index = ((IntValue) foundIndex).getValue();
        if (!semaphoreTable.isDefined(index))
            throw new MyException("Index " + index + " is not in the semaphore table.");

        synchronized (semaphoreTable) {
            Map.Entry<Integer, List<Integer>> semEntry = semaphoreTable.lookup(index);
             int N1 = semEntry.getKey();
            List<Integer> List1 = semEntry.getValue();
            int NL = List1.size();

            int prgId = state.getPrgStateId();

            if (N1 > NL) {
                if (!List1.contains(prgId)) {
                    List1.add(prgId);
                    semaphoreTable.update(index, N1, List1);
                }
            } else {
                stack.push(this);
            }
        }


        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new AcquireStmt(var1);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        if (!typeEnv.lookup(var1).equals(new IntType()))
            throw new MyException("Acquire statement variable must be of type int.");
        return typeEnv;
    }

    @Override
    public String toString() {
        return "acquire(" + var1 + ")";
    }
}
