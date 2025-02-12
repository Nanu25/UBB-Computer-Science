package Model.Statement;

import Model.PrgState;
import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;

public class SleepStmt implements IStmt{
    int number;

    public SleepStmt(int number){
        this.number = number;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        if(this.number != 0){
            state.getStk().push(new SleepStmt(this.number - 1));
        }
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "Sleep(" + this.number + ")";
    }
}
