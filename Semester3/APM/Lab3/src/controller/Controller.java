package controller;

import Model.PrgState;
import Model.Statement.IStmt;
import Repository.IRepository;
import Utils.MyIStack.MyIStack;
import Exception.MyException;

public class Controller {
    private IRepository repo;
    Boolean displayFlag = false;

    public Controller(IRepository repo) {
        this.repo = repo;
    }

    public void setDisplayFlag() {
        displayFlag = true;
    }

    PrgState oneStep(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getStk();
        if (stk.isEmpty())
            throw new MyException("prgstate stack is empty");
        IStmt crtStmt = stk.pop();
        return crtStmt.execute(state);

    }

    public void allStep() {
        PrgState prg = repo.getCurPrg();
        repo.logPrgStateExec();
        while (!prg.getStk().isEmpty()) {

            oneStep(prg);
            if(displayFlag == true)
                System.out.println(prg);
            repo.logPrgStateExec();
        }
    }
}
