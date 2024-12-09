package Model.Statement;

import Exception.MyException;
import Model.PrgState;
import Model.Type.IType;
import Model.Type.IntType;


public class VarDeclStmt implements IStmt {
    private String name;
    private IType type;


    public VarDeclStmt(String name, IType type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        state.getSymTable().put(name, type.defaultValue());
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new VarDeclStmt(name, new IntType());
    }

    @Override
    public String toString() {
        return type.toString() + " " + name;
    }

}
