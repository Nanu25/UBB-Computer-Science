package Model.Exp;

import Model.Type.BoolType;
import Model.Type.IType;
import Model.Values.BoolValue;
import Model.Values.Value;
import Exception.MyException;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;


public class NotExp implements Exp {
    private Exp exp;

    public NotExp(Exp exp) {
        this.exp = exp;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> symTable, MyIHeap heap) throws MyException {
        Value val = exp.eval(symTable, heap);
        if (val.getType().equals(new BoolType())) {
            BoolValue boolVal = (BoolValue) val;
            return new BoolValue(!boolVal.getValue());
        } else {
            throw new MyException("Operand for 'not' must be a boolean.");
        }
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typ = exp.typecheck(typeEnv);
        if (typ.equals(new BoolType())) {
            return new BoolType();
        } else {
            throw new MyException("The expression for 'not' must be boolean.");
        }
    }

    @Override
    public String toString() {
        return "!" + exp.toString();
    }

    @Override
    public Exp deepCopy() {
        return null;
    }
}
