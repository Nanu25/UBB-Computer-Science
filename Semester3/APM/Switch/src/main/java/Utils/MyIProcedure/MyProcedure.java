package Utils.MyIProcedure;

import Exception.MyException;
import Model.Statement.IStmt;
import Model.Values.Value;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MyProcedure implements MyIProcedure {
    private final Map<String, Pair<List<String>, IStmt>> procedures;

    public MyProcedure() {
        this.procedures = new HashMap<>();
    }

    @Override
    public void add(String name, List<String> params, IStmt body) {
        procedures.put(name, new Pair<>(params, body));
    }

    @Override
    public Pair<List<String>, IStmt> lookup(String name) throws MyException {
        if (!procedures.containsKey(name)) throw new MyException("Procedure not found: " + name);
        return procedures.get(name);
    }

    @Override
    public boolean isDefined(String name) {
        return procedures.containsKey(name);
    }

    @Override
    public Map<String, Pair<List<String>, IStmt>> getContent() {
        return procedures;
    }

    @Override
    public Map<String, Value> toMap() {
        return procedures.entrySet().stream()
                .collect(HashMap::new, (m, e) -> m.put(e.getKey(), null), HashMap::putAll);
    }
}
