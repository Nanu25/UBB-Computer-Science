package Model.Values;

import Model.Type.IType;

public interface Value {
    IType getType();
    Value deepCopy();

}
