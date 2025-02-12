package Model.Statement;

import Exception.MyException;
import Model.PrgState;
import Model.Type.IType;
import Model.Values.Value;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIProcedure.MyIProcedure;
import java.util.List;

public class ProcedureStmt implements IStmt {
    private final String name;
    private final List<String> parameters;
    private final IStmt body;

    public ProcedureStmt(String name, List<String> parameters, IStmt body) {
        this.name = name;
        this.parameters = parameters;
        this.body = body;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIProcedure procedureTable = state.getProcTable();

        if (procedureTable.isDefined(name)) {
            throw new MyException("Procedure " + name + " is already defined!");
        }

        procedureTable.add(name, parameters, body);
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new ProcedureStmt(name, parameters, body.deepCopy());
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        return typeEnv; // Type checking will be handled when calling procedures
    }

    @Override
    public String toString() {
        return "procedure " + name + "(" + String.join(",", parameters) + ") " + body.toString();
    }
}
