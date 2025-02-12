package Model.Statement;

import Model.PrgState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IntValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;
import Utils.MyIHeap.MyIHeap;
import Utils.MyILock.MyILock;
import Utils.MyIStack.MyIStack;

public class LockStmt implements IStmt{
    private String var;

    public LockStmt(String var) {
        this.var = var;
    }

    @Override
    public String toString() {
        return "lock(" + var + ")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stack = state.getStk();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyILock lockTable = state.getLockTable();

        Value foundIndex = symTable.lookup(var);
        if (!foundIndex.getType().equals(new IntType()))
            throw new MyException("Variable " + var + " is not an integer.");

        int index = ((IntValue) foundIndex).getValue();
        if (!lockTable.isDefined(index))
            throw new MyException("Index " + index + " is not in the lock table.");

        if(lockTable.lookup(index) == -1)
            lockTable.update(index, state.getPrgStateId());
        else
            stack.push(this);

        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new LockStmt(var);
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
