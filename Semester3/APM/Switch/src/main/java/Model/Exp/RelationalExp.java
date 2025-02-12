package Model.Exp;

import Model.Type.BoolType;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.Value;
import Model.Values.IntValue;
import Model.Values.BoolValue;
import Utils.MyIDictionary.MyIDictionary;
import Exception.InvalidOperatorException;
import Exception.RelationalException;
import Utils.MyIHeap.MyIHeap;
import Exception.MyException;

public class RelationalExp implements Exp {
    private Exp exp1;
    private Exp exp2;
    private String op;

    public RelationalExp(Exp exp1, Exp exp2, String op) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.op = op;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> symTable, MyIHeap hp) throws MyException {
        Value v1 = exp1.eval(symTable, hp);
        Value v2 = exp2.eval(symTable, hp);

        if (!(v1 instanceof IntValue) || !(v2 instanceof IntValue)) {
            throw new RelationalException("Relational expression operands must be integers.");
        }

        int int1 = ((IntValue) v1).getVal();
        int int2 = ((IntValue) v2).getVal();

        switch (op) {
            case "<":
                return new BoolValue(int1 < int2);
            case "<=":
                return new BoolValue(int1 <= int2);
            case "==":
                return new BoolValue(int1 == int2);
            case "!=":
                return new BoolValue(int1 != int2);
            case ">":
                return new BoolValue(int1 > int2);
            case ">=":
                return new BoolValue(int1 >= int2);
            default:
                throw new InvalidOperatorException("Invalid relational operator: " + op);
        }
    }

    @Override
    public String toString() {
        return exp1.toString() + " " + op + " " + exp2.toString();
    }

    @Override
    public Exp deepCopy() {
        return new RelationalExp(exp1.deepCopy(), exp2.deepCopy(), op);
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType type1, type2;
        type1 = exp1.typecheck(typeEnv);
        type2 = exp2.typecheck(typeEnv);

        if (type1.equals(new IntType()) && type2.equals(new IntType())) {
            return new BoolType();
        } else {
            throw new RelationalException("Relational expression operands must be integers.");
        }
    }
}

