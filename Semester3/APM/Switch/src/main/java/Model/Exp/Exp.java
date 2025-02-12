package Model.Exp;

import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;
import Model.Values.Value;
import Utils.MyIHeap.MyIHeap;
import Exception.MyException;

public interface Exp {
    Value eval(MyIDictionary<String, Value> tbl, MyIHeap hp) throws MyException;
    String toString();
    Exp deepCopy();
    IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException;
}
