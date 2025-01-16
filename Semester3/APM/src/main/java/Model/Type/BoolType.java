package Model.Type;

import Model.Values.BoolValue;
import Model.Values.Value;

public class BoolType implements IType {
    boolean val;

    public BoolType(boolean val) {
        this.val = val;
    }

    public BoolType() {

    }


    public boolean equals(Object obj) {
        return obj instanceof BoolType;
    }

    public String toString() {
        return "bool";
    }

    public boolean getVal() {
        return val;
    }

//    public Boolean getValue() {
//        return val;
//    }

    @Override
    public Value defaultValue() {
        return new BoolValue(false);
    }

    @Override
    public IType deepCopy() {
        return new BoolType(val);
    }
}
