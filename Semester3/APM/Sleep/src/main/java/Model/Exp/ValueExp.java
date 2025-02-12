package Model.Exp;

import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;
import Model.Values.Value;
import Utils.MyIHeap.MyIHeap;
import Exception.MyException;


public class ValueExp implements Exp{
    Value e;

    public ValueExp(Value v) {
        e = v;
    }

    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap hp) throws MyException {
        return e;
    }

    public String toString() {
        return e.toString();
    }

    @Override
    public Exp deepCopy() {
        return new ValueExp(e.deepCopy());
    }

    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        return e.getType();
    }


}
