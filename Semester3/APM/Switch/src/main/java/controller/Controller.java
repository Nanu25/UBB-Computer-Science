package controller;

import Model.PrgState;
import Model.Statement.IStmt;
import Model.Values.RefValue;
import Model.Values.Value;
import Repository.IRepository;
import Repository.Repository;
import Utils.MyIDictionary.MyDictionary;
import Utils.MyIFileTable.MyFileTable;
import Utils.MyIHeap.MyHeap;
import Utils.MyIHeap.MyIHeap;
import Utils.MyIList.MyList;
import Exception.MyException;
import Utils.MyIStack.MyStack;

import java.util.*;
import java.util.concurrent.*;
import java.util.stream.Collectors;


public class Controller {
    private IRepository repo;
    Boolean displayFlag = false;
    ExecutorService executor;

    public Controller(IRepository repo) {
        this.repo = repo;
        executor = Executors.newFixedThreadPool(3);
    }

    public void setDisplayFlag() {
        displayFlag = true;
    }


    //safe- corect, colecteaza adresele referite direct si indirect din Symtable
    List<Integer> getAllAddresses1(Collection<Value> symTableValues, MyIHeap heapTable){
        //avem nevoie de o structura cu acces concurent (LinkedList nu e suficient)
        ConcurrentLinkedDeque<Integer> symTableAdr = symTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddress();})
                .collect(Collectors.toCollection(ConcurrentLinkedDeque::new));

        //System.out.println("symTable adr: "+symTableAdr);

        //procesarea elementelor din lista + posibilitatea de a adauga elemente in stream care sa fie prelucrate
        //==> acces concurent
        symTableAdr.stream()
                .forEach(a-> {
                    Value v= (Value) heapTable.getContent().get(a);
                    if (v instanceof  RefValue)
                        if (!symTableAdr.contains(((RefValue)v).getAddress()))
                            symTableAdr.add(((RefValue)v).getAddress());});


        //System.out.println("symTable ~intersected heapTable adr: "+symTableAdr);


        return symTableAdr.stream().toList();
    }


    Map<Integer, Value> safeGarbageCollector1(List<Integer> symTableAddr, Map<Integer,Value> heap){
        return heap.entrySet().stream()
                .filter(e->symTableAddr.contains(e.getKey())).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    Map<Integer, Value> conservativeGarbageCollector(List<Integer> addresses, Map<Integer, Value> heap) {
        return heap.entrySet().stream()
                .filter(entry -> addresses.contains(entry.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }


//    public void allStep() {
//        PrgState prg = repo.getCurPrg();
//        repo.logPrgStateExec();
//        while (!prg.getStk().isEmpty()) {
//
//            oneStep(prg);
//            if(displayFlag == true)
//                System.out.println(prg);
////            prg.getHeap().setContent(
////                    unsafeGarbageCollector(
////                            getAddrFromSymTable(prg.getSymTable().getContent().values()),
////                            prg.getHeap().getContent()
////                    )
////            );
//
//            prg.getHeap().setContent(
//                    safeGarbageCollector1(
//                            getAllAddresses1(prg.getSymTable().getContent().values(), prg.getHeap()),
//                            prg.getHeap().getContent()));
//
//            repo.logPrgStateExec();
//        }
//    }
//    public void allStep() throws MyException {
//        PrgState prg = repo.getCurPrg();
//        repo.logPrgStateExec(prg);
//        try {
//            while (!prg.getStk().isEmpty()) {
//                prg.oneStep();
//                repo.logPrgStateExec(prg);
//                if (displayFlag == true)
//                    System.out.println(prg);
//                prg.getHeap().setContent(
//                        safeGarbageCollector1(
//                                getAllAddresses1(prg.getSymTable().getContent().values(), prg.getHeap()),
//                                prg.getHeap().getContent()));
//                repo.logPrgStateExec(prg);
//            }
//        }catch (MyException e){
//            throw new MyException(e.getMessage());
//        }
//    }
//
    public void allStep() throws MyException, InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());
        while (prgList.size() > 0) {
            executeOneStep();

            List<Integer> referencedAddresses = getAllAddresses1(repo.getSymTable().getContent().values(), repo.getHeap());
            Map<Integer, Value> filteredHeap = conservativeGarbageCollector(referencedAddresses, repo.getHeap().getContent());
            repo.getHeap().setContent(filteredHeap);

            prgList = removeCompletedPrg(repo.getPrgList());
            System.out.println("prgList size: \n"+prgList.size() + "\n");
            System.out.println("\n\n");
        }

        executor.shutdownNow();
        repo.setPrgList(prgList);
    }
//
//
    List <PrgState> removeCompletedPrg(List<PrgState> inPrgList){
        return inPrgList.stream()
                .filter(p->p.isNotCompleted())
                .collect(Collectors.toList());
    }


//    void oneStepForAllPrg(List<PrgState> prgList) throws MyException, InterruptedException {
//        prgList.forEach(prg -> {repo.logPrgStateExec(prg);});
//        List<Callable<PrgState>> callList = prgList.stream()
//                .map((PrgState p) -> (Callable<PrgState>)(() -> {return p.oneStep();}))
//                .collect(Collectors.toList());
//
//        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
//                .map(future -> {
//                    try {
//                        return future.get();
//                    }  catch (ExecutionException e) {
//                        throw new ExecutorException(e.toString());
//                    } catch (InterruptedException e) {
//                        throw new RuntimeException(e);
//                    }
//                })
//                .filter(p -> p != null)
//                .collect(Collectors.toList());
//
//
//        prgList.addAll(newPrgList);
//        prgList.forEach(prg -> {repo.logPrgStateExec(prg);});
//        repo.setPrgList(prgList);
//    }

    public void executeOneStep() throws MyException, InterruptedException {
        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());

        List<Callable<PrgState>> stepList = prgList.stream()
                .map((PrgState p) -> (Callable<PrgState>) (() -> p.oneStep()))
                .collect(Collectors.toList());


        List<PrgState>   newPrgList = executor.invokeAll(stepList).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        } catch (Exception e) {
                            throw new RuntimeException(e.toString());
                        }
                    })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());

        prgList.addAll(newPrgList);


        List<Integer> referencedAddresses = getAllAddresses1(repo.getSymTable().getContent().values(), repo.getHeap());
        Map<Integer, Value> filteredHeap = conservativeGarbageCollector(referencedAddresses, repo.getHeap().getContent());
        repo.getHeap().setContent(filteredHeap);

        prgList.forEach(prgState -> repo.logPrgStateExec(prgState));
        repo.setPrgList(prgList);
    }

//    public void allStep() throws MyException, InterruptedException {
//        this.executor = Executors.newFixedThreadPool(2);
//        while (true) {
//            List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());
//            if (prgList.isEmpty()) {
//                break;
//            }
//            executeOneStep();
//        }
//
//        executor.shutdownNow();
//        repo.setPrgList(removeCompletedPrg(repo.getPrgList()));
//
//    }

    public void displayCurrentState() {
        repo.getPrgList().forEach(prg -> System.out.println(prg + "\n"));
    }

    public void setProgram(IStmt statement) throws MyException {

        repo.addPrg(new PrgState(
                new MyStack<>(),
                new MyDictionary<>(),
                new MyList<>(),
                new MyFileTable(),
                new MyHeap(),
                statement
        ));

        repo.logPrgStateExec(repo.getPrgList().get(0));
    }

    //get repository
    public Repository getRepo() {
        return (Repository) repo;
    }

    public int getNoOfPrgStates() {
        return repo.getPrgList().size();
    }


    //get Heap
    public Map<Integer, Value> getHeap() {
        return repo.getHeap().toMap();
    }
    public List<String> getOutEntries() {
        return this.repo.getOut();
    }

    public List<String> getFileTableEntries() {
        return this.repo.getFileTable();
    }

    public List<String> getExeStackEntries(int prgStateId) {
        return repo.getPrgStateById(prgStateId).getStk()
                .getAll()
                .stream()
                .map(Object::toString)
                .collect(Collectors.toList());
    }

    public Map<String, Value> getSymTable(int selectedPrgStateId) {
        PrgState prgState = repo.getPrgStateById(selectedPrgStateId);
        return new HashMap<>(prgState.getSymTable().getAll());
    }

    public Map<String, Value> getProcTable() {
        return repo.getProcTable().toMap();
    }
}
