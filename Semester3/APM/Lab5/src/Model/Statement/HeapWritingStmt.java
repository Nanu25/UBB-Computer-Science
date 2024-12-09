package Model.Statement;

import Model.Exp.Exp;
import Model.PrgState;
import Exception.MyException;
import Model.Type.RefType;
import Model.Values.RefValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;
import Exception.HeapWriteException;
import Exception.TypeException;

public class HeapWritingStmt implements IStmt {
    String var_name;
    Exp exp;

    public HeapWritingStmt(String var_name, Exp exp) {
        this.var_name = var_name;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, Value> symTable = state.getSymTable();
        MyIHeap heap = state.getHeap();

        if (!symTable.isDefined(var_name)) {
            throw new HeapWriteException("Variable " + var_name + " not defined in the symbol table.");
        }

        Value val = symTable.lookup(var_name);

        if (!(val instanceof RefValue)) {
            throw new TypeException("Variable " + var_name + " is not a reference.");
        }

        int address = ((RefValue) val).getAddress();
        if (!heap.isDefined(address)) {
            throw new HeapWriteException("Address " + address + " is not defined in the heap.");
        }

        Value newVal = exp.eval(state.getSymTable(), state.getHeap());
        Value heapValue = state.getHeap().lookup(address);
        if (!newVal.getType().equals(heapValue.getType())) {
            throw new TypeException("Type of the expression does not match the type of the referenced location.");
        }

        state.getHeap().update(address, newVal);
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new HeapWritingStmt(var_name, exp.deepCopy());
    }

    @Override
    public String toString() {
        return "HeapWriting(" + var_name + ", " + exp.toString() + ")";
    }
}
