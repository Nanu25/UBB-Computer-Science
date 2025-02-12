package Model.Statement;

import Model.Exp.Exp;
import Model.PrgState;
import Exception.MyException;
import Model.Type.IType;
import Model.Type.StringType;
import Model.Values.StringValue;
import Model.Values.Value;
import Exception.TypeException;
import Exception.FileOpenException;
import Utils.MyIDictionary.MyIDictionary;

public class OpenRFileStmt implements IStmt{
    private Exp exp;


    public OpenRFileStmt(Exp exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        Value expValue = null;
        try {
            expValue = exp.eval(state.getSymTable(), state.getHeap());
        } catch (MyException e) {
            throw new RuntimeException(e);
        }
        if (!(expValue instanceof StringValue)) {
            throw new TypeException("Expression is not of type StringType.");
        }

        StringValue fileName = (StringValue) expValue;
        String fileNameStr = fileName.getVal();

        if (!state.getSymFile().openFile(fileNameStr)) {
            throw new FileOpenException("File is already opened: " + fileNameStr);
        }
//
//        BufferedReader br;
//        try {
//            br = new BufferedReader(new java.io.FileReader(fileNameStr));
//           // state.getSymFile().put(fileNameStr, br);
//        } catch (IOException e) {
//            throw new MyException("Could not open file: " + fileNameStr);
//        }


        return null;
    }



    @Override
    public IStmt deepCopy() {
        return new OpenRFileStmt(exp.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType expType = exp.typecheck(typeEnv);

        if (!expType.equals(new StringType())) {
            throw new MyException("OpenRFileStmt: Expression type " + expType + " is not StringType.");
        }

        return typeEnv;
    }

    @Override
    public String toString() {
        return "OpenRFile(" + exp.toString() + ")";
    }

}
