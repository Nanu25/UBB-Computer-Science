//package View;
//
//import Model.Exp.*;
//import Model.PrgState;
//import Model.Statement.*;
//import Model.Type.*;
//import Model.Values.BoolValue;
//import Model.Values.IntValue;
//import Model.Values.StringValue;
//import Model.Values.Value;
//import Repository.IRepository;
//import Repository.Repository;
//import Utils.MyIDictionary.MyDictionary;
//import Utils.MyIDictionary.MyIDictionary;
//import Utils.MyIFileTable.MyFileTable;
//import Utils.MyIHeap.MyHeap;
//import Utils.MyIHeap.MyIHeap;
//import Utils.MyIList.MyIList;
//import Utils.MyIList.MyList;
//import Utils.MyIStack.MyIStack;
//import Utils.MyIStack.MyStack;
//import controller.Controller;
//import Exception.MyException;
//
//public class Interpreter {
//    public static void main(String[] args) {
//        try {
//            IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
//                    new PrintStmt(new VarExp("v")));
//
//            IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
//                    new CompStmt(new VarDeclStmt("b", new IntType()),
//                            new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)),
//                                    new ArithExp('*', new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
//                                    new CompStmt(new AssignStmt("b", new ArithExp('+', new VarExp("a"),
//                                            new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
//
//            IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
//                    new CompStmt(new VarDeclStmt("v", new IntType()),
//                            new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
//                                    new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v",
//                                            new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))),
//                                            new PrintStmt(new VarExp("v"))))));
//
//            IStmt program = new CompStmt(
//                    new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("src/files/test.in"))),
//                    new CompStmt(new OpenRFileStmt(new VarExp("varf")), new CompStmt(new VarDeclStmt("varc", new IntType()),
//                            new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"), new CompStmt(new PrintStmt(new VarExp("varc")),
//                                    new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"), new CompStmt(
//                                            new PrintStmt(new VarExp("varc")), new CloseRFileStmt(new VarExp("varf"))))))))));
//
//            //A4 examples
//            IStmt ex5 = new CompStmt(
//                    new VarDeclStmt("v", new RefType(new IntType())),
//                    new CompStmt(
//                            new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
//                            new CompStmt(
//                                    new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
//                                    new CompStmt(
//                                            new HeapAllocStmt("a", new VarExp("v")),
//                                            new CompStmt(
//                                                    new PrintStmt(new VarExp("v")),
//                                                    new PrintStmt(new VarExp("a"))
//                                            )
//                                    )
//                            )
//                    )
//            );
//
//            IStmt ex6 = new CompStmt(
//                    new VarDeclStmt("v", new RefType(new IntType())),
//                    new CompStmt(
//                            new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
//                            new CompStmt(
//                                    new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
//                                    new CompStmt(
//                                            new HeapAllocStmt("a", new VarExp("v")),
//                                            new CompStmt(
//                                                    new PrintStmt(new ReadHeapExp(new VarExp("v"))),
//                                                    new PrintStmt(
//                                                            new ArithExp(
//                                                                    '+',
//                                                                    new ReadHeapExp(new ReadHeapExp(new VarExp("a"))),
//                                                                    new ValueExp(new IntValue(5))
//                                                            ) // print(rH(rH(a)) + 5)
//                                                    )
//                                            )
//                                    )
//                            )
//                    )
//            );
//
//            IStmt ex7 = new CompStmt(
//                    new VarDeclStmt("v", new RefType(new IntType())),
//                    new CompStmt(
//                            new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
//                            new CompStmt(
//                                    new PrintStmt(new ReadHeapExp(new VarExp("v"))),
//                                    new CompStmt(
//                                            new HeapWritingStmt("v", new ValueExp(new IntValue(30))),
//                                            new PrintStmt(
//                                                    new ArithExp(
//                                                            '+',
//                                                            new ReadHeapExp(new VarExp("v")),
//                                                            new ValueExp(new IntValue(5))
//                                                    )
//                                            )
//                                    )
//                            )
//                    )
//            );
//
//            IStmt ex8 = new CompStmt(
//                    new VarDeclStmt("v", new RefType(new IntType())),
//                    new CompStmt(
//                            new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
//                            new CompStmt(
//                                    new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
//                                    new CompStmt(
//                                            new HeapAllocStmt("a", new VarExp("v")),
//                                            new CompStmt(
//                                                    new HeapAllocStmt("v", new ValueExp(new IntValue(30))),
//                                                    new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a"))))
//                                            )
//                                    )
//                            )
//                    )
//            );
//
//            IStmt ex9 = new CompStmt(
//                    new VarDeclStmt("v", new IntType()),
//                    new CompStmt(
//                            new AssignStmt("v", new ValueExp(new IntValue(4))),
//                            new CompStmt(
//                                    new WhileStmt(
//                                            new RelationalExp( new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
//                                            new CompStmt(
//                                                    new PrintStmt(new VarExp("v")),
//                                                    new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1))))
//                                            )
//                                    ),
//                                    new PrintStmt(new VarExp("v"))
//                            )
//                    )
//            );
//
//            IStmt ex10 = new CompStmt(
//                    new VarDeclStmt("v", new IntType()), // int v;
//                    new CompStmt(
//                            new VarDeclStmt("a", new RefType(new IntType())), // Ref int a;
//                            new CompStmt(
//                                    new AssignStmt("v", new ValueExp(new IntValue(10))), // v = 10;
//                                    new CompStmt(
//                                            new HeapAllocStmt("a", new ValueExp(new IntValue(22))), // new(a, 22);
//                                            new CompStmt(
//                                                    new ForkStmt( // fork statement starts here
//                                                            new CompStmt(
//                                                                    new HeapWritingStmt("a", new ValueExp(new IntValue(30))), // wH(a, 30);
//                                                                    new CompStmt(
//                                                                            new AssignStmt("v", new ValueExp(new IntValue(32))), // v = 32;
//                                                                            new CompStmt(
//                                                                                    new PrintStmt(new VarExp("v")), // print(v);
//                                                                                    new PrintStmt(new ReadHeapExp(new VarExp("a"))) // print(rH(a));
//                                                                            )
//                                                                    )
//                                                            )
//                                                    ),
//                                                    new CompStmt(
//                                                            new PrintStmt(new VarExp("v")),
//                                                            new PrintStmt(new ReadHeapExp(new VarExp("a")))
//                                                    )
//
//                                            )
//                                    )
//                            )
//                    )
//            );
//
//            typecheckProgram(ex1);
//            typecheckProgram(ex2);
//            typecheckProgram(ex3);
//            typecheckProgram(program);
//            typecheckProgram(ex5);
//            typecheckProgram(ex6);
//            typecheckProgram(ex7);
//            typecheckProgram(ex8);
//            typecheckProgram(ex9);
//            typecheckProgram(ex10);
//
//            //Example of failing program
////            IStmt failingProgram = new CompStmt(
////                    new VarDeclStmt("x", new IntType()),
////                    new AssignStmt("x", new ValueExp(new BoolValue(true)))
////            );
////
////            typecheckProgram(failingProgram);
//
//
//            PrgState prg1 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex1);
//            IRepository repo1 = new Repository(prg1, "log1.txt");
//            Controller ctr1 = new Controller(repo1);
//
//            PrgState prg2 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex2);
//            IRepository repo2 = new Repository(prg2, "log2.txt");
//            Controller ctr2 = new Controller(repo2);
//
//            PrgState prg3 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex3);
//            IRepository repo3 = new Repository(prg3, "log3.txt");
//            Controller ctr3 = new Controller(repo3);
//
//            PrgState prg4 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), program);
//            IRepository repo4 = new Repository(prg4, "log4.txt");
//            Controller ctr4 = new Controller(repo4);
//
//            PrgState prg5 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex5);
//            IRepository repo5 = new Repository(prg5, "log5.txt");
//            Controller ctr5 = new Controller(repo5);
//
//            PrgState prg6 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex6);
//            IRepository repo6 = new Repository(prg6, "log6.txt");
//            Controller ctr6 = new Controller(repo6);
//
//            PrgState prg7 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex7);
//            IRepository repo7 = new Repository(prg7, "log7.txt");
//            Controller ctr7 = new Controller(repo7);
//
//            PrgState prg8 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex8);
//            IRepository repo8 = new Repository(prg8, "log8.txt");
//            Controller ctr8 = new Controller(repo8);
//
//            PrgState prg9 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex9);
//            IRepository repo9 = new Repository(prg9, "log9.txt");
//            Controller ctr9 = new Controller(repo9);
//
//            PrgState prg10 = new PrgState(new MyStack<>(), new MyDictionary<>(), new MyList<>(), new MyFileTable(), new MyHeap(), ex10);
//            IRepository repo10 = new Repository(prg10, "log10.txt");
//            Controller ctr10 = new Controller(repo10);
//
//            TextMenu menu = new TextMenu();
//            menu.addCommand(new ExitCommand("0", "exit"));
//            menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
//            menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
//            menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
//            menu.addCommand(new RunExample("4", program.toString(), ctr4));
//            menu.addCommand(new RunExample("5", ex5.toString(), ctr5));
//            menu.addCommand(new RunExample("6", ex6.toString(), ctr6));
//            menu.addCommand(new RunExample("7", ex7.toString(), ctr7));
//            menu.addCommand(new RunExample("8", ex8.toString(), ctr8));
//            menu.addCommand(new RunExample("9", ex9.toString(), ctr9));
//            menu.addCommand(new RunExample("10", ex10.toString(), ctr10));
//
//            menu.show();
//        } catch (MyException e) {
//            System.err.println("Typecheck failed: " + e.getMessage());
//        }
//    }
//
//    private static void typecheckProgram(IStmt stmt) throws MyException {
//        MyIDictionary<String, IType> typeEnv = new MyDictionary<>();
//        stmt.typecheck(typeEnv);
//    }
//
//
//    public static void test() {
//        //A4 examples
////        IStmt program = new CompStmt(
////                new VarDeclStmt("v", new RefType(new IntType())),
////                new CompStmt(
////                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
////                        new CompStmt(
////                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
////                                new CompStmt(
////                                        new HeapAllocStmt("a", new VarExp("v")),
////                                        new CompStmt(
////                                                new PrintStmt(new VarExp("v")),
////                                                new PrintStmt(new VarExp("a"))
////                                        )
////                                )
////                        )
////                )
////        );
//
////        IStmt program = new CompStmt(
////                new VarDeclStmt("v", new RefType(new IntType())),
////                new CompStmt(
////                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
////                        new CompStmt(
////                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
////                                new CompStmt(
////                                        new HeapAllocStmt("a", new VarExp("v")),
////                                        new CompStmt(
////                                                new PrintStmt(new ReadHeapExp(new VarExp("v"))),
////                                                new PrintStmt(
////                                                        new ArithExp(
////                                                                '+',
////                                                                new ReadHeapExp(new ReadHeapExp(new VarExp("a"))),
////                                                                new ValueExp(new IntValue(5))
////                                                        ) // print(rH(rH(a)) + 5)
////                                                )
////                                        )
////                                )
////                        )
////                )
////        );
//
//
////        IStmt program = new CompStmt(
////                new VarDeclStmt("v", new RefType(new IntType())),
////                new CompStmt(
////                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
////                        new CompStmt(
////                                new PrintStmt(new ReadHeapExp(new VarExp("v"))),
////                                new CompStmt(
////                                        new HeapWritingStmt("v", new ValueExp(new IntValue(30))),
////                                        new PrintStmt(
////                                                new ArithExp(
////                                                        '+',
////                                                        new ReadHeapExp(new VarExp("v")),
////                                                        new ValueExp(new IntValue(5))
////                                                )
////                                        )
////                                )
////                        )
////                )
////        );
//
////        IStmt program = new CompStmt(
////                new VarDeclStmt("v", new RefType(new IntType())),
////                new CompStmt(
////                        new HeapAllocStmt("v", new ValueExp(new IntValue(20))),
////                        new CompStmt(
////                                new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
////                                new CompStmt(
////                                        new HeapAllocStmt("a", new VarExp("v")),
////                                        new CompStmt(
////                                                new HeapAllocStmt("v", new ValueExp(new IntValue(30))),
////                                                new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a"))))
////                                        )
////                                )
////                        )
////                )
////        );
//
//
////        IStmt program = new CompStmt(
////                new VarDeclStmt("v", new IntType()),
////                new CompStmt(
////                        new AssignStmt("v", new ValueExp(new IntValue(4))),
////                        new CompStmt(
////                                new WhileStmt(
////                                        new RelationalExp( new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
////                                        new CompStmt(
////                                                new PrintStmt(new VarExp("v")),
////                                                new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1))))
////                                        )
////                                ),
////                                new PrintStmt(new VarExp("v"))
////                        )
////                )
////        );
//
////        //A5
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
//                                                        new PrintStmt(new VarExp("v")),
//                                                        new PrintStmt(new ReadHeapExp(new VarExp("a")))
//                                                )
//
//                                        )
//                                )
//                        )
//                )
//        );
//
////        IStmt program = new CompStmt(
////                new VarDeclStmt("v", new IntType()), // int v;
////                new CompStmt(
////                        new VarDeclStmt("a", new RefType(new IntType())), // Ref int a;
////                        new CompStmt(
////                                new AssignStmt("v", new ValueExp(new IntValue(10))), // v = 10;
////                                new CompStmt(
////                                        new HeapAllocStmt("a", new ValueExp(new IntValue(22))), // new(a, 22);
////                                        new CompStmt(
////                                                new ForkStmt( // fork statement starts here
////                                                        new CompStmt(
////                                                                new HeapWritingStmt("a", new ValueExp(new IntValue(30))), // wH(a, 30);
////                                                                new CompStmt(
////                                                                        new AssignStmt("v", new ValueExp(new IntValue(32))), // v = 32;
////                                                                        new CompStmt(
////                                                                                new PrintStmt(new VarExp("v")), // print(v);
////                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // print(rH(a));
////                                                                        )
////                                                                )
////                                                        )
////                                                ),
////                                                new CompStmt(
////                                                        new PrintStmt(new VarExp("v")), // Parent thread prints v
////                                                        new CompStmt(
////                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))), // Parent thread prints rH(a)
////                                                                new CompStmt(
////                                                                        new AssignStmt("v", new ValueExp(new IntValue(42))), // Parent thread: v = 42
////                                                                        new CompStmt(
////                                                                                new PrintStmt(new VarExp("v")), // Parent thread prints updated v
////                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // Parent thread prints rH(a) again
////                                                                        )
////                                                                )
////                                                        )
////                                                )
////                                        )
////                                )
////                        )
////                )
////        );
//
////
////        IStmt program = new CompStmt(
////                new VarDeclStmt("v", new IntType()), // int v;
////                new CompStmt(
////                        new VarDeclStmt("a", new RefType(new IntType())), // Ref int a;
////                        new CompStmt(
////                                new AssignStmt("v", new ValueExp(new IntValue(10))), // v = 10;
////                                new CompStmt(
////                                        new HeapAllocStmt("a", new ValueExp(new IntValue(22))), // new(a, 22);
////                                        new CompStmt(
////                                                new ForkStmt( // First fork starts here
////                                                        new CompStmt(
////                                                                new HeapWritingStmt("a", new ValueExp(new IntValue(30))), // wH(a, 30);
////                                                                new CompStmt(
////                                                                        new AssignStmt("v", new ValueExp(new IntValue(32))), // v = 32;
////                                                                        new CompStmt(
////                                                                                new PrintStmt(new VarExp("v")), // print(v);
////                                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // print(rH(a));
////                                                                        )
////                                                                )
////                                                        )
////                                                ),
////                                                new CompStmt(
////                                                        new ForkStmt( // Second fork starts here
////                                                                new CompStmt(
////                                                                        new HeapWritingStmt("a", new ValueExp(new IntValue(40))), // wH(a, 40);
////                                                                        new CompStmt(
////                                                                                new AssignStmt("v", new ValueExp(new IntValue(42))), // v = 42;
////                                                                                new CompStmt(
////                                                                                        new PrintStmt(new VarExp("v")), // print(v);
////                                                                                        new PrintStmt(new ReadHeapExp(new VarExp("a"))) // print(rH(a));
////                                                                                )
////                                                                        )
////                                                                )
////                                                        ),
////                                                        new CompStmt(
////                                                                new PrintStmt(new VarExp("v")), // Parent process: print(v);
////                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))) // Parent process: print(rH(a));
////                                                        )
////                                                )
////                                        )
////                                )
////                        )
////                )
////        );
//
//
//
//        MyIStack<IStmt> stack = new MyStack<>();
//        MyIDictionary<String, Value> symT = new MyDictionary<>();
//        MyIList<Value> out = new MyList<>();
//        MyIHeap heap = new MyHeap();
//        MyFileTable fileTable = new MyFileTable();
//
//        PrgState prgState = new PrgState(stack, symT, out, fileTable, heap, program);
//
//        IRepository repo = new Repository(prgState, "log.txt");
//        Controller controller = new Controller(repo);
//
//        try {
//            controller.allStep();
//        } catch (Exception e) {
//            System.out.println("Error during execution: " + e.getMessage());
//        }
//
//    }
//}
//
