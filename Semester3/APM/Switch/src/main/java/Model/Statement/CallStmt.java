package Model.Statement;

import Model.Exp.Exp;
import Model.PrgState;
import Model.Type.IType;
import Model.Values.Value;
import Exception.MyException;
import Utils.MyIDictionary.MyDictionary;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;
import Utils.MyIProcedure.MyIProcedure;
import Utils.MyIStack.MyIStack;
import Utils.MyIProcedure.MyProcedure;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class CallStmt implements IStmt {
    private final String fname;
    private final List<Exp> arguments;

    public CallStmt(String fname, List<Exp> arguments) {
        this.fname = fname;
        this.arguments = arguments;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> exeStack = state.getStk();
        MyIHeap heap = state.getHeap();
        MyIProcedure procTable = state.getProcTable();

        MyIDictionary<String, Value> currentSymTable = state.getSymTable().peek(); // Get current symbol table
        if (!procTable.isDefined(fname))
            throw new MyException("Procedure " + fname + " is not defined.");

        Pair<List<String>, IStmt> procedureInfo = procTable.lookup(fname);
        List<String> formalParams = procedureInfo.getKey();
        IStmt body = procedureInfo.getValue();

        if (formalParams.size() != arguments.size())
            throw new MyException("Incorrect number of arguments for procedure " + arguments);

        // Evaluate actual parameters
        List<Value> evaluatedValues = new ArrayList<>();
        for (Exp exp : arguments) {
            evaluatedValues.add(exp.eval(currentSymTable, heap));
        }

        // Create a new symbol table for the procedure
        MyIDictionary<String, Value> newSymTable = new MyDictionary<>();
        for (int i = 0; i < formalParams.size(); i++) {
            newSymTable.put(formalParams.get(i), evaluatedValues.get(i));
        }

        // Push the new symbol table onto the stack
        state.getSymTableStack().push(newSymTable);

        // Push return statement to restore previous symbol table
        exeStack.push(new ReturnStmt());

        // Push procedure body to execute
        exeStack.push(body);

        return null;
    }


    @Override
    public IStmt deepCopy() {
        return new CallStmt(fname, arguments.stream().map(Exp::deepCopy).collect(Collectors.toList()));
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        return typeEnv;
    }

    @Override
    public String toString() {
        return "call " + fname + "(" + arguments + ")";
    }
}
