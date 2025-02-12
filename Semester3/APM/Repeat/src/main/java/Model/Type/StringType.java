package Model.Type;

import Model.Values.StringValue;
import Model.Values.Value;

public class StringType implements IType{
    String value;

    public StringType(String s) {
        value = s;
    }

    public StringType() {
        value = "";
    }

    public String toString() {
        return "String";
    }
    @Override
    public Value defaultValue() {
        return (Value) new StringValue("");
    }

    @Override
    public IType deepCopy() {
        return new StringType();
    }

    @Override
    public boolean equals(Object obj) {
        // Checks if obj is an instance of StringType
        return obj instanceof StringType;
    }

}
