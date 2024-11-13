

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

//. Se da o colectie de mai multe obiecte
//avind forme de cuburi, sfere si cilindrii.
//Sa se afiseze obiectele avind volumul mai mare
//decit 25cm3.

import repository.InMemoRepo;
import repository.Repository;
import controller.Controller;
import ui.Ui;

public class Main {
    public static void main(String[] args) {
        Repository repo = new InMemoRepo();
        Controller serv = new Controller(repo);
        Ui ui = new Ui(serv);

        ui.start();
    }
}