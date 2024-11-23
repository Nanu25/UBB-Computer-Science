package Model.Exp;

import Utils.MyIDictionary.MyIDictionary;
import Model.Values.Value;
import Utils.MyIHeap.MyIHeap;
import Exception.MyException;

public class ConstExp implements Exp {
    private final Value value;

    public ConstExp(Value value) {
        this.value = value;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap hp) throws MyException {
        // Since this is a constant expression, it simply returns the stored value.
        return value;
    }

    @Override
    public String toString() {
        return value.toString();
    }

    @Override
    public Exp deepCopy() {
        // Assuming Value has a deepCopy method, we call it here to ensure immutability.
        return new ConstExp(value.deepCopy());
    }
}
