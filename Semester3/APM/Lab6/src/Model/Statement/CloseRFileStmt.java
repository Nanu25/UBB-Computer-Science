package Model.Statement;

import Model.Exp.Exp;
import Model.PrgState;
import Exception.MyException;
import Model.Type.IType;
import Model.Type.StringType;
import Model.Values.StringValue;
import Model.Values.Value;
import Exception.FileNotExistsException;
import Exception.FileTypeException;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyTypeException;

public class CloseRFileStmt implements IStmt{
    Exp exp;

    public CloseRFileStmt(Exp e) {
        exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {

        Value expVal = null;
        try {
            expVal = exp.eval(state.getSymTable(), state.getHeap());
        } catch (MyException e) {
            throw new RuntimeException(e);
        }
        if (!(expVal instanceof StringValue)) {
            throw new FileTypeException("Expression is not of type StringType.");
        }

        String fileName = ((StringValue) expVal).getVal();


        try {
            state.getSymFile().closeFile(fileName);
        } catch (MyException e) {
            throw new FileNotExistsException("No entry found in FileTable for file: " + fileName);
        }
        return null;
    }


    @Override
    public IStmt deepCopy() {
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typ = exp.typecheck(typeEnv);
        if (typ.equals(new StringType())) {
            return typeEnv;
        } else {
            throw new MyTypeException("CloseRFileStmt: Expression is not of type string.");
        }
    }

    @Override
    public String toString() {
        return "CloseRFile(" + exp.toString() + ")";
    }

}
