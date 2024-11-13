package Model.Exp;

import Model.Values.BoolValue;
import Model.Values.IntValue;
import Utils.MyIDictionary.MyIDictionary;
import Model.Values.Value;
import Exception.MyException;

public class ValueExp implements Exp{
    Value e;

    public ValueExp(Value v) {
        e = v;
    }

    public Value eval(MyIDictionary<String, Value> tbl) throws MyException {
        return e;
    }

    public String toString() {
        return e.toString();
    }

    @Override
    public Exp deepCopy() {
        return new ValueExp(e.deepCopy());
    }
}
