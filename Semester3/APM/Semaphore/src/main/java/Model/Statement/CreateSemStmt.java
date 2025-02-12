package Model.Statement;

import Model.Exp.Exp;
import Model.PrgState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IntValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;
import Utils.MyIHeap.MyIHeap;
import Utils.MyISemaphore.MyISem;

public class CreateSemStmt implements IStmt{
    private final String var;
    private final Exp exp1;

    public CreateSemStmt(String var, Exp exp1) {
        this.var = var;
        this.exp1 = exp1;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();
        MyISem semaphoreTable = state.getSemaphoreTable();

        Value val = exp1.eval(symTable, heap);

        if (!(val instanceof IntValue))
            throw new MyException("Expression must evaluate to an integer");

        int permits = ((IntValue) val).getVal();

        int newAddress = semaphoreTable.add(permits);

        if (!symTable.isDefined(var))
            throw new MyException("Variable " + var + " is not defined");

        if (!(symTable.lookup(var).getType() instanceof IntType))
            throw new MyException("Variable " + var + " must be of type int");

        symTable.update(var, new IntValue(newAddress));

        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new CreateSemStmt(var, exp1);
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typeVar = typeEnv.lookup(var);
        IType typeExp = exp1.typecheck(typeEnv);

        if (!typeVar.equals(new IntType()))
            throw new MyException("Variable " + var + " must be of type int");

        if (!typeExp.equals(new IntType()))
            throw new MyException("Expression must evaluate to an int");

        return typeEnv;
    }

    @Override
    public String toString() {
        return "createSemaphore(" + var + ", " + exp1 + ")";
    }
}

