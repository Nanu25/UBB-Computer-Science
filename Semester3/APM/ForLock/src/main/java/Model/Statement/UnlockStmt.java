package Model.Statement;

import Model.PrgState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IntValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;
import Utils.MyILock.MyILock;

public class UnlockStmt implements IStmt {
    private final String var;

    public UnlockStmt(String v) {
        var = v;
    }

    @Override
    public String toString() {
        return "unlock(" + var + ")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyILock lockTable = state.getLockTable();

        if(!symTable.isDefined(var))
            throw new MyException("Variable " + var + " is not defined.");

        Value foundIndex = symTable.lookup(var);

        int index = ((IntValue) foundIndex).getValue();

        if(!lockTable.isDefined(index))
            throw new MyException("Index " + index + " is not in the lock table.");

        synchronized (lockTable) {
            if(lockTable.lookup(index) == state.getPrgStateId())
                lockTable.update(index, -1);
        }

        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new UnlockStmt(var);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        if (!typeEnv.isDefined(var)) {
            throw new MyException("Variable " + var + " is not defined in the type environment.");
        }

        IType type = typeEnv.lookup(var);
        if (!(type instanceof IntType)) {
            throw new MyException("Variable " + var + " must be of type int.");
        }

        return typeEnv;
    }
}
