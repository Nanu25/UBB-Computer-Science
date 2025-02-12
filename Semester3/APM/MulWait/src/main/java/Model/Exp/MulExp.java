package Model.Exp;

import Model.Type.IntType;
import Model.Type.IType;
import Model.Values.IntValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;
import Exception.MyException;

public class MulExp implements Exp {
    private Exp e1, e2;

    public MulExp(Exp e1, Exp e2) {
        this.e1 = e1;
        this.e2 = e2;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap hp) throws MyException {
        Value v1 = e1.eval(tbl, hp);
        Value v2 = e2.eval(tbl, hp);

        if (!(v1 instanceof IntValue) || !(v2 instanceof IntValue))
            throw new MyException("MUL operation requires integer values!");

        int n1 = ((IntValue) v1).getValue();
        int n2 = ((IntValue) v2).getValue();

        return new IntValue((n1 * n2) - (n1 + n2));
    }

    @Override
    public Exp deepCopy() {
        return new MulExp(e1.deepCopy(), e2.deepCopy());
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType t1 = e1.typecheck(typeEnv);
        IType t2 = e2.typecheck(typeEnv);

        if (!t1.equals(new IntType()) || !t2.equals(new IntType()))
            throw new MyException("MUL operation requires integer operands!");

        return new IntType();
    }

    @Override
    public String toString() {
        return "MUL(" + e1 + ", " + e2 + ")";
    }
}
