package View;

import Model.Exp.*;
import Model.PrgState;
import Model.Statement.*;
import Model.Type.BoolType;
import Model.Type.RefType;
import Model.Type.StringType;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;
import Repository.IRepository;
import Repository.Repository;
import Model.Type.IntType;
import Utils.MyIDictionary.MyDictionary;
import Utils.MyIDictionary.MyIDictionary;
import Utils.MyIFileTable.MyFileTable;
import Utils.MyIHeap.MyHeap;
import Utils.MyIHeap.MyIHeap;
import Utils.MyIList.MyIList;
import Utils.MyIList.MyList;
import Utils.MyIStack.MyIStack;
import Utils.MyIStack.MyStack;
import controller.Controller;


public class Interpreter {
    public static void main(String[] args) {
        test();
        IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new PrintStmt(new VarExp("v")));

        IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)),
                                new ArithExp('*', new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                new CompStmt(new AssignStmt("b", new ArithExp('+', new VarExp("a"),
                                        new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));

        IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v",
                                        new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));

        IStmt program = new CompStmt(
                new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("src/files/test.in"))),
                        new CompStmt(new OpenRFileStmt(new VarExp("varf")), new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"), new CompStmt(
                                                                new PrintStmt(new VarExp("varc")), new CloseRFileStmt(new VarExp("varf"))))))))));

        PrgState prg1 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex1);
        IRepository repo1 = new Repository(prg1, "log1.txt");
        Controller ctr1 = new Controller(repo1);

        PrgState prg2 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(),new MyHeap(), ex2);
        IRepository repo2 = new Repository(prg2, "log2.txt");
        Controller ctr2 = new Controller(repo2);

        PrgState prg3 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(),new MyHeap(), ex3);
        IRepository repo3 = new Repository(prg3, "log3.txt");
        Controller ctr3 = new Controller(repo3);

        PrgState prg4 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(),new MyHeap(), program);
        IRepository repo4 = new Repository(prg4, "log4.txt");
        Controller ctr4 = new Controller(repo4);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
        menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
        menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
        menu.addCommand(new RunExample("4", program.toString(), ctr4));

        menu.show();
    }

    public static void test() {
        //A4 examples
//        IStmt program = new CompStmt(
//                new VarDeclStmt("v", new RefType(new IntType())),
//                new CompStmt(
//                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
//                        new CompStmt(
//                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
//                                new CompStmt(
//                                        new HeapAllocStmt("a", new VarExp("v")),
//                                        new CompStmt(
//                                                new PrintStmt(new VarExp("v")),
//                                                new PrintStmt(new VarExp("a"))
//                                        )
//                                )
//                        )
//                )
//        );

//        IStmt program = new CompStmt(
//                new VarDeclStmt("v", new RefType(new IntType())),
//                new CompStmt(
//                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
//                        new CompStmt(
//                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
//                                new CompStmt(
//                                        new HeapAllocStmt("a", new VarExp("v")),
//                                        new CompStmt(
//                                                new PrintStmt(new ReadHeapExp(new VarExp("v"))),
//                                                new PrintStmt(
//                                                        new ArithExp(
//                                                                '+',
//                                                                new ReadHeapExp(new ReadHeapExp(new VarExp("a"))),
//                                                                new ValueExp(new IntValue(5))
//                                                        ) // print(rH(rH(a)) + 5)
//                                                )
//                                        )
//                                )
//                        )
//                )
//        );


//        IStmt program = new CompStmt(
//                new VarDeclStmt("v", new RefType(new IntType())),
//                new CompStmt(
//                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
//                        new CompStmt(
//                                new PrintStmt(new ReadHeapExp(new VarExp("v"))),
//                                new CompStmt(
//                                        new HeapWritingStmt("v", new ValueExp(new IntValue(30))),
//                                        new PrintStmt(
//                                                new ArithExp(
//                                                        '+',
//                                                        new ReadHeapExp(new VarExp("v")),
//                                                        new ValueExp(new IntValue(5))
//                                                )
//                                        )
//                                )
//                        )
//                )
//        );

//        IStmt program = new CompStmt(
//                new VarDeclStmt("v", new RefType(new IntType())),
//                new CompStmt(
//                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
//                        new CompStmt(
//                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
//                                new CompStmt(
//                                        new HeapAllocStmt("a", new VarExp("v")),
//                                        new CompStmt(
//                                                new HeapAllocStmt("v", new ValueExp(new IntValue(30))),
//                                                new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a"))))
//                                        )
//                                )
//                        )
//                )
//        );


//        IStmt program = new CompStmt(
//                new VarDeclStmt("v", new IntType()),
//                new CompStmt(
//                        new AssignStmt("v", new ValueExp(new IntValue(4))),
//                        new CompStmt(
//                                new WhileStmt(
//                                        new RelationalExp( new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
//                                        new CompStmt(
//                                                new PrintStmt(new VarExp("v")),
//                                                new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1))))
//                                        )
//                                ),
//                                new PrintStmt(new VarExp("v"))
//                        )
//                )
//        );

//        //A5
        IStmt program = new CompStmt(
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

//        IStmt program = new CompStmt(
//                new VarDeclStmt("v", new IntType()), // int v;
//                new CompStmt(
//                        new VarDeclStmt("a", new RefType(new IntType())), // Ref int a;
//                        new CompStmt(
//                                new AssignStmt("v", new ValueExp(new IntValue(10))), // v = 10;
//                                new CompStmt(
//                                        new HeapAllocStmt("a", new ValueExp(new IntValue(22))), // new(a, 22);
//                                        new CompStmt(
//                                                new ForkStmt( // fork statement starts here
//                                                        new CompStmt(
//                                                                new HeapWritingStmt("a", new ValueExp(new IntValue(30))), // wH(a, 30);
//                                                                new CompStmt(
//                                                                        new AssignStmt("v", new ValueExp(new IntValue(32))), // v = 32;
//                                                                        new CompStmt(
//                                                                                new PrintStmt(new VarExp("v")), // print(v);
//                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // print(rH(a));
//                                                                        )
//                                                                )
//                                                        )
//                                                ),
//                                                new CompStmt(
//                                                        new PrintStmt(new VarExp("v")), // Parent thread prints v
//                                                        new CompStmt(
//                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))), // Parent thread prints rH(a)
//                                                                new CompStmt(
//                                                                        new AssignStmt("v", new ValueExp(new IntValue(42))), // Parent thread: v = 42
//                                                                        new CompStmt(
//                                                                                new PrintStmt(new VarExp("v")), // Parent thread prints updated v
//                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // Parent thread prints rH(a) again
//                                                                        )
//                                                                )
//                                                        )
//                                                )
//                                        )
//                                )
//                        )
//                )
//        );

//
//        IStmt program = new CompStmt(
//                new VarDeclStmt("v", new IntType()), // int v;
//                new CompStmt(
//                        new VarDeclStmt("a", new RefType(new IntType())), // Ref int a;
//                        new CompStmt(
//                                new AssignStmt("v", new ValueExp(new IntValue(10))), // v = 10;
//                                new CompStmt(
//                                        new HeapAllocStmt("a", new ValueExp(new IntValue(22))), // new(a, 22);
//                                        new CompStmt(
//                                                new ForkStmt( // First fork starts here
//                                                        new CompStmt(
//                                                                new HeapWritingStmt("a", new ValueExp(new IntValue(30))), // wH(a, 30);
//                                                                new CompStmt(
//                                                                        new AssignStmt("v", new ValueExp(new IntValue(32))), // v = 32;
//                                                                        new CompStmt(
//                                                                                new PrintStmt(new VarExp("v")), // print(v);
//                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // print(rH(a));
//                                                                        )
//                                                                )
//                                                        )
//                                                ),
//                                                new CompStmt(
//                                                        new ForkStmt( // Second fork starts here
//                                                                new CompStmt(
//                                                                        new HeapWritingStmt("a", new ValueExp(new IntValue(40))), // wH(a, 40);
//                                                                        new CompStmt(
//                                                                                new AssignStmt("v", new ValueExp(new IntValue(42))), // v = 42;
//                                                                                new CompStmt(
//                                                                                        new PrintStmt(new VarExp("v")), // print(v);
//                                                                                        new PrintStmt(new ReadHeapExp(new VarExp("a"))) // print(rH(a));
//                                                                                )
//                                                                        )
//                                                                )
//                                                        ),
//                                                        new CompStmt(
//                                                                new PrintStmt(new VarExp("v")), // Parent process: print(v);
//                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // Parent process: print(rH(a));
//                                                        )
//                                                )
//                                        )
//                                )
//                        )
//                )
//        );



        MyIStack<IStmt> stack = new MyStack<>();
        MyIDictionary<String, Value> symT = new MyDictionary<>();
        MyIList<Value> out = new MyList<>();
        MyIHeap heap = new MyHeap();
        MyFileTable fileTable = new MyFileTable();

        PrgState prgState = new PrgState(stack, symT, out, fileTable, heap, program);

        IRepository repo = new Repository(prgState, "log.txt");
        Controller controller = new Controller(repo);

        try {
            controller.allStep();
        } catch (Exception e) {
            System.out.println("Error during execution: " + e.getMessage());
        }

    }
}

