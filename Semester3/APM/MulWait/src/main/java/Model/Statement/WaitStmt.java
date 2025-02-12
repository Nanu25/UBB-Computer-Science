package Model.Statement;

import Model.Exp.ConstExp;
import Model.Exp.ValueExp;
import Model.Exp.VarExp;
import Model.PrgState;
import Model.Type.IType;
import Model.Values.IntValue;
import Utils.MyIDictionary.MyIDictionary;
import Exception.MyException;

public class WaitStmt implements IStmt{
    private int number;

    public WaitStmt(int number){
        this.number = number;
    }

    @Override
    public String toString() {
        return "wait(" + number + ")";
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {
        if(number != 0) {
            IStmt newStmt = new CompStmt(
                    new PrintStmt(new ValueExp(new IntValue(number))),
                    new WaitStmt(number - 1)
            );
            state.getStk().push(newStmt);
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
}
