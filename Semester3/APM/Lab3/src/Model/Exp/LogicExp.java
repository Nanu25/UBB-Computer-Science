package Model.Exp;

import Model.Values.BoolValue;
import Model.Type.BoolType;
import Utils.MyIDictionary.MyDictionary;
import Model.Values.Value;
import Exception.MyException;
import Utils.MyIDictionary.MyIDictionary;

public class LogicExp implements Exp {
    Exp e1;
    Exp e2;
    int op;

    public Value eval(MyIDictionary<String, Value> tbl) throws MyException{
        Value v1, v2;
        v1 = e1.eval(tbl);
        if (v1.getType().equals(new LogicExp())) {
            v2 = e2.eval(tbl);
            if(v2.getType().equals(new LogicExp())) {
                BoolType b1 = (BoolType)v1;
                BoolType b2 = (BoolType)v2;

                boolean n1, n2;
                n1 = b1.getVal();
                n2 = b2.getVal();

                if (op==1) return new BoolValue(n1 && n2);
                if (op==2) return new BoolValue(n1 || n2);
            } else {
                throw new MyException("second operand is not a boolean");
            }
        }else {
            throw new MyException("first operand is not a boolean");
        }
        return null;
    }

    public String toString() {
        if(op == 1)
            return e1.toString() + "&&" + e2.toString();
        if(op == 2)
            return e1.toString() + "||" + e2.toString();
        return "";
    }

    @Override
    public Exp deepCopy() {
        return null;
    }

}
