package Model.Values;


import Model.Type.BoolType;
import Model.Type.IType;

public class BoolValue implements Value {
    boolean val;

    public BoolValue(boolean v) {
        val = v;
    }
    public boolean getVal() {
        return val;
    }


    public String toString() {
        return Boolean.toString(val);
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public Value deepCopy() {
        return new BoolValue(val);
    }

    public boolean equals(Object another) {
        return another instanceof BoolValue;
    }

}
