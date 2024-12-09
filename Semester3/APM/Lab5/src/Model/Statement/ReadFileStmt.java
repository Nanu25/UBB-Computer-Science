package Model.Statement;

import Model.Exp.Exp;
import Model.PrgState;
import Exception.MyException;
import Model.Type.IntType;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import Exception.TypeException;
import Exception.FileNotExistsException;
import Exception.FileTypeException;
import Exception.ReadFileException;

import java.io.BufferedReader;
import java.io.IOException;


public class ReadFileStmt implements IStmt {
    private Exp exp;
    String var_name;

    public ReadFileStmt(Exp exp, String var_name) {
        this.exp = exp;
        this.var_name = var_name;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        if (!state.getSymTable().isDefined(var_name.toString())) {
            throw new MyException("Variable " + var_name + " is not defined.");
        }


        Value varValue = state.getSymTable().lookup(var_name.toString());
        if (!(varValue.getType() instanceof IntType)) {
            throw new MyException("Variable " + var_name + " is not of type integer.");
        }

        Value expValue = null;
        try {
            expValue = exp.eval(state.getSymTable(), state.getHeap());
        } catch (MyException e) {
            throw new RuntimeException(e);
        }
        if (!(expValue instanceof StringValue)) {
            throw new TypeException("Expression is not of type String.");
        }

        String fileName = ((StringValue) expValue).getVal();

        BufferedReader br = state.getSymFile().get(fileName);
        if (br == null) {
            throw new FileNotExistsException("No entry found in FileTable for file: " + fileName);
        }

        int intValue;
        try {
            String line = br.readLine();
            if (line == null) {
                intValue = 0;
            } else {
                intValue = Integer.parseInt(line);
            }
        } catch (IOException e) {
            throw new FileTypeException("Error reading from file: " + fileName);
        } catch (NumberFormatException e) {
            throw new ReadFileException("Could not parse integer from file line.");
        }

        state.getSymTable().update(var_name.toString(), new IntValue(intValue));
        return null;
    }



    @Override
    public IStmt deepCopy() {
        return new ReadFileStmt(exp.deepCopy(), var_name);
    }

    @Override
    public String toString() {
        return "ReadFile(" + exp.toString() + ", " + var_name.toString() + ")";
    }

}
