package Model.Exp;

import Utils.MyIDictionary.MyIDictionary;
import Model.Values.Value;
import Exception.MyException;

public interface Exp {
    Value eval(MyIDictionary<String, Value> tbl) throws MyException;
    String toString();
    Exp deepCopy();
}
