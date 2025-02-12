package Model.Type;

import Model.Values.IntValue;
import Model.Values.Value;

public class IntType implements IType {
    Integer val;
    String type = "Int";

    public IntType() {
        val = 0;
    }

    public boolean equals(Object obj) {
        return obj instanceof IntType;
    }

    public String toString() {
        return "int";
    }

    @Override
    public Value defaultValue() {
        return new IntValue(0);
    }

    @Override
    public IType deepCopy() {
        return new IntType();
    }

    public Integer getVal() {
        return val;
    }
}
