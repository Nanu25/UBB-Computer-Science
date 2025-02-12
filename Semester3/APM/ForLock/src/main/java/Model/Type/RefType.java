package Model.Type;

import Model.Values.RefValue;
import Model.Values.Value;

import java.lang.reflect.Type;

public class RefType implements IType {
    private IType inner;

    public RefType() {

    }

    public RefType(int x, IType inner) {

    }

    public RefType(IType inner) {
        this.inner = inner;
    }

    public IType getInner() {
        return inner;
    }

    public boolean equals(Object another) {
        if(another instanceof RefType) {
            return inner.equals(((RefType) another).getInner());
        }
        return false;
    }


    @Override
    public Value defaultValue() {
        return new RefValue(0, inner);
    }

    @Override
    public String toString() {
        return "Ref(" + inner + ")";
    }

    @Override
    public IType deepCopy() {
        return null;
    }
}
