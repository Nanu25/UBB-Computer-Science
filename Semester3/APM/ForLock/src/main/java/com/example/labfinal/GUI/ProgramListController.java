package com.example.labfinal.GUI;

import Model.Exp.*;
import Model.PrgState;
import Model.Statement.*;
import Model.Type.*;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.Repository;
import Utils.MyIDictionary.MyDictionary;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIFileTable.MyFileTable;
import Utils.MyIHeap.MyHeap;
import Utils.MyIList.MyList;
import Utils.MyILock.MyLock;
import Utils.MyIStack.MyStack;
import controller.Controller;
import Exception.MyException;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.Stage;

import java.io.IOException;

public class ProgramListController {

    @FXML
    private ListView<String> examplesList;

    @FXML
    private Button runButton;

    private Controller ctr1, ctr2, ctr3, ctr4, ctr5, ctr6, ctr7, ctr8, ctr9, ctr10, crt11, ctr12;
    private IStmt ex1, ex2, ex3, ex4, ex5, ex6, ex7, ex8, ex9, ex10, ex11, ex12;

    public ProgramListController() {
        ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
            new PrintStmt(new VarExp("v")));

        ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)),
                                new ArithExp('*', new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                new CompStmt(new AssignStmt("b", new ArithExp('+', new VarExp("a"),
                                        new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
        ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v",
                                        new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));


        ex4 = new CompStmt(
                new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                new CompStmt(new OpenRFileStmt(new VarExp("varf")), new CompStmt(new VarDeclStmt("varc", new IntType()),
                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")),
                                new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"), new CompStmt(
                                        new PrintStmt(new VarExp("varc")), new CloseRFileStmt(new VarExp("varf"))))))))));

        //A4 examples
        ex5 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(
                                        new HeapAllocStmt("a", new VarExp("v")),
                                        new CompStmt(
                                                new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a"))
                                        )
                                )
                        )
                )
        );

        ex6 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(
                                        new HeapAllocStmt("a", new VarExp("v")),
                                        new CompStmt(
                                                new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                                new PrintStmt(
                                                        new ArithExp(
                                                                '+',
                                                                new ReadHeapExp(new ReadHeapExp(new VarExp("a"))),
                                                                new ValueExp(new IntValue(5))
                                                        ) // print(rH(rH(a)) + 5)
                                                )
                                        )
                                )
                        )
                )
        );

        ex7 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                new CompStmt(
                                        new HeapWritingStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(
                                                new ArithExp(
                                                        '+',
                                                        new ReadHeapExp(new VarExp("v")),
                                                        new ValueExp(new IntValue(5))
                                                )
                                        )
                                )
                        )
                )
        );

        ex8 = new CompStmt(
                new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(
                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(
                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(
                                        new HeapAllocStmt("a", new VarExp("v")),
                                        new CompStmt(
                                                new HeapAllocStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a"))))
                                        )
                                )
                        )
                )
        );

        ex9 = new CompStmt(
                new VarDeclStmt("v", new IntType()),
                new CompStmt(
                        new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(
                                new WhileStmt(
                                        new RelationalExp( new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                        new CompStmt(
                                                new PrintStmt(new VarExp("v")),
                                                new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1))))
                                        )
                                ),
                                new PrintStmt(new VarExp("v"))
                        )
                )
        );

        ex10 = new CompStmt(
                new VarDeclStmt("v", new IntType()), // int v;
                new CompStmt(
                        new VarDeclStmt("a", new RefType(new IntType())), // Ref int a;
                        new CompStmt(
                                new AssignStmt("v", new ValueExp(new IntValue(10))), // v = 10;
                                new CompStmt(
                                        new HeapAllocStmt("a", new ValueExp(new IntValue(22))), // new(a, 22);
                                        new CompStmt(
                                                new ForkStmt( // fork statement starts here
                                                        new CompStmt(
                                                                new HeapWritingStmt("a", new ValueExp(new IntValue(30))), // wH(a, 30);
                                                                new CompStmt(
                                                                        new AssignStmt("v", new ValueExp(new IntValue(32))), // v = 32;
                                                                        new CompStmt(
                                                                                new PrintStmt(new VarExp("v")), // print(v);
                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // print(rH(a));
                                                                        )
                                                                )
                                                        )
                                                ),
                                                new CompStmt(
                                                        new PrintStmt(new VarExp("v")),
                                                        new PrintStmt(new ReadHeapExp(new VarExp("a")))
                                                )

                                        )
                                )
                        )
                )
        );






        IStmt a = new CompStmt(
                new VarDeclStmt("v1", new RefType(new IntType())), // Ref int v1;
                new CompStmt(
                        new VarDeclStmt("v2", new RefType(new IntType())), // Ref int v2;
                        new CompStmt(
                                new VarDeclStmt("x", new IntType()), // int x;
                                new CompStmt(
                                        new VarDeclStmt("q", new IntType()), // int q;
                                        new CompStmt(
                                                new HeapAllocStmt("v1", new ValueExp(new IntValue(20))), // new(v1,20);
                                                new CompStmt(
                                                        new HeapAllocStmt("v2", new ValueExp(new IntValue(30))), // new(v2,30);
                                                        new CompStmt(
                                                                new NewLockStmt("x"), // newLock(x);
                                                                new CompStmt(
                                                                        new ForkStmt(
                                                                                new ForkStmt(
                                                                                        new CompStmt(
                                                                                                new LockStmt("x"), // lock(x);
                                                                                                new CompStmt(
                                                                                                        new HeapWritingStmt("v1",
                                                                                                                new ArithExp('-', new ReadHeapExp(new VarExp("v1")),
                                                                                                                        new ValueExp(new IntValue(1)))
                                                                                                        ), // wh(v1, rh(v1)-1);
                                                                                                        new UnlockStmt("x") // unlock(x);
                                                                                                )
                                                                                        )
                                                                                )
                                                                        ),
                                                                        new CompStmt(
                                                                                new LockStmt("x"), // lock(x);
                                                                                new CompStmt(
                                                                                        new HeapWritingStmt("v1",
                                                                                                new ArithExp('*', new ReadHeapExp(new VarExp("v1")),
                                                                                                        new ValueExp(new IntValue(10)))
                                                                                        ), // wh(v1, rh(v1)*10);
                                                                                        new UnlockStmt("x") // unlock(x);
                                                                                )
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );

        IStmt b = new CompStmt(
                new NewLockStmt("q"), // newLock(q);
                new CompStmt(
                        new ForkStmt(
                                new ForkStmt(
                                        new CompStmt(
                                                new LockStmt("q"), // lock(q);
                                                new CompStmt(
                                                        new HeapWritingStmt("v2",
                                                                new ArithExp('+', new ReadHeapExp(new VarExp("v2")),
                                                                        new ValueExp(new IntValue(5)))
                                                        ), // wh(v2, rh(v2)+5);
                                                        new UnlockStmt("q") // unlock(q);
                                                )
                                        )
                                )
                        ),
                        new CompStmt(
                                new LockStmt("q"), // lock(q);
                                new CompStmt(
                                        new HeapWritingStmt("v2",
                                                new ArithExp('*', new ReadHeapExp(new VarExp("v2")),
                                                        new ValueExp(new IntValue(10)))
                                        ), // wh(v2, rh(v2)*10);
                                        new UnlockStmt("q") // unlock(q);
                                )
                        )
                )
        );

        IStmt exFinal = new CompStmt(
                new NopStmt(), // nop
                new CompStmt(
                        new NopStmt(), // nop
                        new CompStmt(
                                new NopStmt(), // nop
                                new CompStmt(
                                        new NopStmt(), // nop
                                        new CompStmt(
                                                new LockStmt("x"), // lock(x);
                                                new CompStmt(
                                                        new PrintStmt(new ReadHeapExp(new VarExp("v1"))), // print(rh(v1));
                                                        new CompStmt(
                                                                new UnlockStmt("x"), // unlock(x);
                                                                new CompStmt(
                                                                        new LockStmt("q"), // lock(q);
                                                                        new CompStmt(
                                                                                new PrintStmt(new ReadHeapExp(new VarExp("v2"))), // print(rh(v2));
                                                                                new UnlockStmt("q") // unlock(q);
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );

// Combine all into a single execution
        ex11 = new CompStmt(a, new CompStmt(b, exFinal));


        ex12 = new CompStmt(
                new VarDeclStmt("a", new RefType(new IntType())),  // Ref int a;
                new CompStmt(
                        new HeapAllocStmt("a", new ValueExp(new IntValue(20))),  // new(a,20);
                        new CompStmt(
                                new ForStmt("v",
                                        new ValueExp(new IntValue(0)),  // v = 0;
                                        new ValueExp(new IntValue(3)),  // v < 3;
                                        new ArithExp('+', new VarExp("v"), new ValueExp(new IntValue(1))), // v = v + 1;
                                        new ForkStmt(  // fork(print(v); v = v * rh(a));
                                                new CompStmt(
                                                        new PrintStmt(new VarExp("v")),
                                                        new AssignStmt("v", new ArithExp('*', new VarExp("v"), new ReadHeapExp(new VarExp("a"))))
                                                )
                                        )
                                ),
                                new PrintStmt(new ReadHeapExp(new VarExp("a")))  // print(rh(a))
                        )
                )
        );

        ctr1 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex1, new MyLock()), "log1.txt"));
        ctr2 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex2, new MyLock()), "log2.txt"));
        ctr3 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex3, new MyLock()), "log3.txt"));
        ctr4 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex4, new MyLock()), "log4.txt"));
        ctr5 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex5, new MyLock()), "log5.txt"));
        ctr6 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex6, new MyLock()), "log6.txt"));
        ctr7 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex7, new MyLock()), "log7.txt"));
        ctr8 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex8, new MyLock()), "log8.txt"));
        ctr9 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex9, new MyLock()), "log9.txt"));
        ctr10 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex10, new MyLock()), "log10.txt"));
        crt11 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex11, new MyLock()), "log11.txt"));
        ctr12 = new Controller(new Repository(new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex12, new MyLock()), "log12.txt"));
        try {
            typecheckProgram(ex1);
            typecheckProgram(ex2);
            typecheckProgram(ex3);
            typecheckProgram(ex4);
            typecheckProgram(ex5);
            typecheckProgram(ex6);
            typecheckProgram(ex7);
            typecheckProgram(ex8);
            typecheckProgram(ex9);
            typecheckProgram(ex10);
            typecheckProgram(ex11);
            typecheckProgram(ex12);
        }catch (MyException e){
            System.out.println(e.getMessage());
        }
    }

    private static void typecheckProgram(IStmt stmt) throws MyException {
        MyIDictionary<String, IType> typeEnv = new MyDictionary<>();
        stmt.typecheck(typeEnv);
    }

    @FXML
    public void initialize() {
        examplesList.getItems().addAll(
                "Example 1: " + ex1.toString(),
                "Example 2: " + ex2.toString(),
                "Example 3: " + ex3.toString(),
                "Example 4: " + ex4.toString(),
                "Example 5: " + ex5.toString(),
                "Example 6: " + ex6.toString(),
                "Example 7: " + ex7.toString(),
                "Example 8: " + ex8.toString(),
                "Example 9: " + ex9.toString(),
                "Example 10: " + ex10.toString(),
                "Example 11: " + ex11.toString(),
                "Example 12: " + ex12.toString()
        );
    }

    @FXML
    public void runProgram() throws IOException {
        int selectedIndex = examplesList.getSelectionModel().getSelectedIndex();
        // Select the appropriate controller
        Controller selectedController = switch (selectedIndex) {
            case 0 -> ctr1;
            case 1 -> ctr2;
            case 2 -> ctr3;
            case 3 -> ctr4;
            case 4 -> ctr5;
            case 5 -> ctr6;
            case 6 -> ctr7;
            case 7 -> ctr8;
            case 8 -> ctr9;
            case 9 -> ctr10;
            case 10 -> crt11;
            case 11 -> ctr12;
            default -> null;
        };

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/labfinal/GUI/MainWindow.fxml"));
        Parent root = null;
            root = loader.load();

        ToyLanguageController programWindowController = loader.getController();
        programWindowController.setController(selectedController);
        String programName = examplesList.getItems().get(selectedIndex);

        Stage programStage = new Stage();
        programStage.setTitle("Program Viewer");
        programStage.setScene(new Scene(root));
        programStage.show();

    }


}
