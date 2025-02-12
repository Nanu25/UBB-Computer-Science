package Model.Values;

import Model.Type.IType;
import Model.Type.StringType;

public class StringValue implements Value{
    private String val;

    public StringValue(String v) {
        val = v;
    }

    public String getVal() {
        return val;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public Value deepCopy() {
        return new StringValue(val);
    }

    public boolean equals(Object another) {
        return another instanceof StringValue;
    }

    public String toString() {
        return val;
    }

}
