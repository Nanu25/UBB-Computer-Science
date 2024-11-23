package Model.Exp;

import Utils.MyIDictionary.MyIDictionary;
import Model.Values.Value;
import Utils.MyIHeap.MyIHeap;
import Exception.MyException;

public class VarExp implements Exp{
    String id;

    public VarExp() {
        id = "";
    }

    public VarExp(String i) {
        id = i;
    }

    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap hp) throws MyException {
        return tbl.lookup(id);
    }

    public String toString() {
        return id;
    }

    @Override
    public Exp deepCopy() {
        return new VarExp(id);
    }

}
