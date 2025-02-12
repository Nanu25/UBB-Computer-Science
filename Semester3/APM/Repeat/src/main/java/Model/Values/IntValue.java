package Model.Values;

import Model.Type.IType;
import Model.Type.IntType;


public class IntValue implements Value {
    private int val;

    public IntValue(int v) {
        this.val = v;
    }
    public int getVal() {
        return val;
    }

    public String toString() {
        return Integer.toString(val);
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    @Override
    public Value deepCopy() {
        return new IntValue(val);
    }

    public boolean equals(Object another) {
        return another instanceof IntValue;
    }

}
