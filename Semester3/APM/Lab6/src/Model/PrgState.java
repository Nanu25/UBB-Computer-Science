package Model;

import Model.Statement.IStmt;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIFileTable.MyIFileTable;
import Utils.MyIHeap.MyIHeap;
import Utils.MyIList.MyIList;
import Utils.MyIStack.MyIStack;
import Model.Values.Value;
import Exception.MyException;
import Exception.StackException;


public class PrgState {
    private MyIStack<IStmt> exeStack;
    private MyIDictionary<String, Value> symTable;
    private MyIList<Value> output;
    private IStmt originalProgram;
    private MyIFileTable symFile;
    private MyIHeap heap;
    private static int id = 0;
    private int prgStateId;

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot, MyIFileTable file, MyIHeap heap,  IStmt prg){
        exeStack = stk;
        symTable = symtbl;
        output = ot;
        originalProgram = prg.deepCopy();
        symFile = file;
        this.heap = heap;
        stk.push(prg);
        this.prgStateId = this.getId();
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

    public synchronized int getId() {
        id++;
        return id;
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }

    @Override
    public String toString() {
        return "Program id:\n" + Integer.toString(this.prgStateId) + "\n" +  "ExeStack:\n" + exeStack.toString() + "\nSymTable:\n" + symTable.toString() + "\nHeapTable\n" + heap.toString() + "\nOutput:\n" + output.toString() + "\n" + symFile.toString() + "\n";
    }
}