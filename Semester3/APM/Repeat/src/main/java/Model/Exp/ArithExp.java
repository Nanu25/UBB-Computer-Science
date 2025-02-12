package Model.Exp;

import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;
import Model.Type.IntType;
import Model.Values.IntValue;
import Model.Values.Value;
import Exception.DivisionByZeroException;
import Exception.MyException;
import Utils.MyIHeap.MyIHeap;
import Exception.MyTypeException;

import java.lang.reflect.Type;

public class ArithExp implements Exp{
    Exp e1;
    Exp e2;

    int op; //1-plus, 2-minus, 3-star, 4-divide

    public ArithExp(char op, Exp e1, Exp e2) {
        this.e1 = e1;
        this.e2 = e2;
        if(op=='+') this.op=1;
        if(op=='-') this.op=2;
        if(op=='*') this.op=3;
        if(op=='/') this.op=4;

    }

    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap hp) throws MyException {
        Value v1, v2;
        v1 = e1.eval(tbl, hp);
        if (v1.getType().equals(new IntType())) {
            v2 = e2.eval(tbl, hp);
            if (v2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue)v1;
                IntValue i2 = (IntValue)v2;
                int n1, n2;
                n1 = i1.getVal();
                n2 = i2.getVal();
                if (op==1) return new IntValue(n1+n2);
                if (op==2) return new IntValue(n1-n2);
                if (op==3) return new IntValue(n1*n2);
                if (op==4) {
                    if (n2==0) throw new DivisionByZeroException();
                    return new IntValue(n1/n2);
                }
            } else
                throw new MyException("second operand is not an integer");
        } else
            throw new MyException("first operand is not an integer");
        return null;
    }

    public String toString() {
        if(op == 1)
            return e1.toString() + "+" + e2.toString();
        if(op == 2)
            return e1.toString() + "-" + e2.toString();
        if(op == 3)
            return e1.toString() + "*" + e2.toString();
        if(op == 4)
            return e1.toString() + "/" + e2.toString();
        return "";
    }

    @Override
    public Exp deepCopy() {
        return null;
    }

    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if (typ1.equals(new IntType())){
            if (typ2.equals(new IntType())){
                return new IntType();
            }else
                throw new MyTypeException("second operand is not an integer");
        }else
            throw new MyTypeException("first operand is not an integer");
    }

}
