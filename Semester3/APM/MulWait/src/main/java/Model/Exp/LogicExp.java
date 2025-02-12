package Model.Exp;

import Model.Type.IType;
import Model.Values.BoolValue;
import Model.Type.BoolType;
import Model.Values.Value;
import Exception.MyException;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;
import Exception.MyTypeException;
import Exception.MyException;

public class LogicExp implements Exp {
    Exp e1;
    Exp e2;
    int op;

    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap hp) throws MyException {
        Value v1, v2;
        v1 = e1.eval(tbl, hp);
        if (v1.getType().equals(new LogicExp())) {
            v2 = e2.eval(tbl, hp);
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

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType type1, type2;
        type1 = e1.typecheck(typeEnv);
        type2 = e2.typecheck(typeEnv);
        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType())) {
                return new BoolType();
            } else {
                throw new MyTypeException("second operand is not a boolean");
            }
        } else {
            throw new MyTypeException("first operand is not a boolean");
        }
    }

}
