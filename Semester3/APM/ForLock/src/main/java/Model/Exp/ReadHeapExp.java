package Model.Exp;

import Model.Type.IType;
import Model.Type.RefType;
import Model.Values.RefValue;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;
import Utils.MyIHeap.MyIHeap;
import Exception.MyException;

import Exception.TypeException;
import Exception.MyTypeException;

public class ReadHeapExp implements Exp{
    private Exp exp;

    public ReadHeapExp(Exp e){
        exp = e;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap hp) throws MyException {
        Value v = exp.eval(tbl, hp);

        if (!(v instanceof RefValue)) {
            throw new TypeException("Expression is not of RefType.");
        }

        int address = ((RefValue) v).getAddress();

        if (!hp.isDefined(address)) {
            throw new MyException("Address " + address + " not found in the heap.");
        }

        return hp.lookup(address);
    }


    @Override
    public Exp deepCopy() {
        return new ReadHeapExp(exp.deepCopy());
    }

    @Override
    public String toString(){
        return "ReadHeap(" + exp.toString() + ")";
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typ = exp.typecheck(typeEnv);
        if (typ instanceof RefType) {
            RefType reft = (RefType) typ;
            return reft.getInner();
        } else {
            throw new MyTypeException("The rH argument is not a Ref Type");
        }
    }
}
