package Model.Exp;

import Model.Values.Value;
import Model.Values.IntValue;
import Model.Values.BoolValue;
import Utils.MyIDictionary.MyIDictionary;
import Exception.InvalidOperatorException;
import Exception.MyException;
import Exception.RelationalException;

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
    public Value eval(MyIDictionary<String, Value> symTable) throws MyException {
        Value v1 = exp1.eval(symTable);
        Value v2 = exp2.eval(symTable);

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
}

