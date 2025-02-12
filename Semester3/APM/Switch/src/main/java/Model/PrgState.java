package Model;

import Model.Statement.IStmt;
import Utils.MyIDictionary.MyDictionary;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIFileTable.MyIFileTable;
import Utils.MyIHeap.MyIHeap;
import Utils.MyIList.MyIList;
import Utils.MyIProcedure.MyIProcedure;
import Utils.MyIProcedure.MyProcedure;
import Utils.MyIStack.MyIStack;
import Model.Values.Value;
import Exception.MyException;
import Exception.StackException;

import java.util.List;
import java.util.Stack;


public class PrgState {
    private MyIStack<IStmt> exeStack;
    private Stack<MyIDictionary<String, Value>> symTableStack;
    private MyIDictionary<String, Value> symTable;
    private MyIList<Value> output;
    private IStmt originalProgram;
    private MyIFileTable symFile;
    private MyIHeap heap;
    private static int id = 0;
    private int prgStateId;
    private MyIProcedure procTable;

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot, MyIFileTable file, MyIHeap heap,  IStmt prg){
        exeStack = stk;
        symTable = symtbl;
        symTableStack = new Stack<>();
        symTableStack.push(symtbl);
        output = ot;
        originalProgram = prg.deepCopy();
        symFile = file;
        this.heap = heap;
        stk.push(prg);
        this.prgStateId = this.getId();
        procTable = new MyProcedure();
    }

    public MyIStack<IStmt> getStk() {
        return exeStack;
    }

    public MyIDictionary<String, Value> getSymTable() {
        return symTable;
    }

    public MyIFileTable getSymFile() {
        return symFile;
    }

    public List<String> getSymFileContent() {
        return symFile.getFiles();
    }

    public List<String> getSymFileKeys() {
        return symFile.getFiles();
    }

    public MyIList<Value> getOutput() {
        return output;
    }

    public MyIHeap getHeap() {
        return heap;
    }


    public PrgState oneStep() throws MyException {
        if (this.exeStack.isEmpty())
            throw new StackException("prgstate stack is empty");
        IStmt crtStmt = this.exeStack.pop();
        return crtStmt.execute(this);
    }


    public boolean isNotCompleted(){
        return !exeStack.isEmpty();
    }

    private synchronized int getId() {
        id++;
        return id;
    }

    public int getPrgStateId() {
        return prgStateId;
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }

    @Override
    public String toString() {
        return "Program id:\n" + Integer.toString(this.prgStateId) + "\n" +  "ExeStack:\n" + exeStack.toString() + "\nSymTable:\n" + symTable.toString() + "\nHeapTable\n" + heap.toString() + "\nOutput:\n" + output.toString() + "\n" + symFile.toString() + "\n";
    }

    public Stack<MyIDictionary<String, Value>> getSymTableStack() {
        return this.symTableStack;
    }

    public MyIProcedure getProcTable() {
        return this.procTable;
    }
}
