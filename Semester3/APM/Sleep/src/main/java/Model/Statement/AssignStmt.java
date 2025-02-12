package Model.Statement;

import Model.PrgState;
import Model.Type.IType;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIStack.MyIStack;
import Exception.MyException;
import Model.Values.Value;
import Model.Exp.Exp;


public class AssignStmt implements IStmt {
    String id;
    Exp exp;


    public AssignStmt(String id, Exp exp) {
        this.id = id;
        this.exp = exp;
    }

    public String toString() {
        return id + "=" + exp.toString();
    }

    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getStk();
        MyIDictionary<String, Value> symTbl = state.getSymTable();

        if (symTbl.isDefined(id)) {
            Value val = null;
            try {
                val = exp.eval(symTbl,  state.getHeap());
            } catch (MyException e) {
                throw new RuntimeException(e);
            }
            IType typId = (symTbl.lookup(id)).getType();
            if (val.getType().equals(typId)) {
                symTbl.update(id, val);
            } else {
                throw new MyException("declared type of variable " + id + " and type of the assigned expression do not match");
            }
        }else {
            throw new MyException("the used variable " + id + " was not declared before");
        }
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new AssignStmt(id, exp.deepCopy());
    }


    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typevar = typeEnv.lookup(id);
        IType typexp = exp.typecheck(typeEnv);
        if (typevar.equals(typexp))
            return typeEnv;
        else
            throw new MyException("Assignment: right hand side and left hand side have different types ");
    }
}
