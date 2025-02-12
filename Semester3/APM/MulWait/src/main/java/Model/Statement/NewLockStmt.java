package Model.Statement;

import Model.PrgState;
import Model.Type.IntType;
import Model.Type.IType;
import Model.Values.IntValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;
import Utils.MyILock.MyILock;

public class NewLockStmt implements IStmt {
    private final String var;

    public NewLockStmt(String v) {
        var = v;
    }

    @Override
    public String toString() {
        return "newLock(" + var + ")";
    }

    @Override
    public PrgState execute(PrgState state) {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyILock lockTable = state.getLockTable();

        if (!symTable.isDefined(var)) {
            throw new RuntimeException("Variable " + var + " is not defined.");
        }
        Value value = symTable.lookup(var);
        if (!(value.getType() instanceof IntType)) {
            throw new RuntimeException("Variable " + var + " must be of type int.");
        }

        synchronized (lockTable) {
            int newLockAddress = lockTable.add(); // Get a new lock address
            symTable.update(var, new IntValue(newLockAddress)); // Store lock ID in var
        }

        return null;
    }


    @Override
    public IStmt deepCopy() {
        return new NewLockStmt(var);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType type = typeEnv.lookup(var);
        if (!type.equals(new IntType())) {
            throw new MyException("Variable " + var + " must be of type int.");
        }
        return typeEnv;
    }
}
