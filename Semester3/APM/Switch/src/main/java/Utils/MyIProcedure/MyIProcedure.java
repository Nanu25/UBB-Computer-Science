package Utils.MyIProcedure;

import Exception.MyException;
import Model.Statement.IStmt;
import Model.Values.Value;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

public interface MyIProcedure {
    void add(String name, List<String> params, IStmt body);
//    void update(String name, Procedure procedure) throws MyException;
    public Pair<List<String>, IStmt> lookup(String name) throws MyException;
    boolean isDefined(String name);
    public Map<String, Pair<List<String>, IStmt>> getContent();

    Map<String, Value> toMap();
//    void setContent(Map<String, Procedure> newContent);
}
