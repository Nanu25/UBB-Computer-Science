package controller;

import Model.PrgState;
import Model.Statement.IStmt;
import Model.Values.RefValue;
import Model.Values.Value;
import Repository.IRepository;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIHeap.MyIHeap;
import Utils.MyIStack.MyIStack;
import Exception.MyException;
import controller.GarbageCollector;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentLinkedDeque;
import java.util.stream.Collectors;

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
//
//    public Map<Integer, Value> unsafeGarbageCollector(List<Integer> symTableAddr, Map<Integer, Value> heap) {
//        return heap.entrySet().stream()
//                .filter(e -> symTableAddr.contains(e.getKey()))
//                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
//    }
//
//    public List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
//        return symTableValues.stream()
//                .filter(v -> v instanceof RefValue)
//                .map(v -> ((RefValue) v).getAddress())
//                .collect(Collectors.toList());
//    }


    //safe- corect, colecteaza adresele referite direct si indirect din Symtable
    List<Integer> getAllAddresses1(Collection<Value> symTableValues, MyIHeap heapTable){
        //avem nevoie de o structura cu acces concurent (LinkedList nu e suficient)
        ConcurrentLinkedDeque<Integer> symTableAdr = symTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toCollection(ConcurrentLinkedDeque::new));

        System.out.println("symTable adr: "+symTableAdr);

        //procesarea elementelor din lista + posibilitatea de a adauga elemente in stream care sa fie prelucrate
        //==> acces concurent
        symTableAdr.stream()
                .forEach(a-> {
                    Value v= (Value) heapTable.getContent().get(a);
                    if (v instanceof  RefValue)
                        if (!symTableAdr.contains(((RefValue)v).getAddress()))
                            symTableAdr.add(((RefValue)v).getAddress());});


        System.out.println("symTable ~intersected heapTable adr: "+symTableAdr);


        return symTableAdr.stream().toList();
    }


    Map<Integer, Value> safeGarbageCollector1(List<Integer> symTableAddr, Map<Integer,Value> heap){
        return heap.entrySet().stream()
                .filter(e->symTableAddr.contains(e.getKey())).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }


    public void allStep() {
        PrgState prg = repo.getCurPrg();
        repo.logPrgStateExec();
        while (!prg.getStk().isEmpty()) {

            oneStep(prg);
            if(displayFlag == true)
                System.out.println(prg);
//            prg.getHeap().setContent(
//                    unsafeGarbageCollector(
//                            getAddrFromSymTable(prg.getSymTable().getContent().values()),
//                            prg.getHeap().getContent()
//                    )
//            );

            prg.getHeap().setContent(
                    safeGarbageCollector1(
                            getAllAddresses1(prg.getSymTable().getContent().values(), prg.getHeap()),
                            prg.getHeap().getContent()));

            repo.logPrgStateExec();
        }
    }
}
