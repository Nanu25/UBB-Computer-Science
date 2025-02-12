package Model.Type;

import Model.Values.Value;

public interface IType {
    Value defaultValue();
    IType deepCopy();
}
