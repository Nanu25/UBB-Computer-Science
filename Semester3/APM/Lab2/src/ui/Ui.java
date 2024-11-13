package ui;

import model.Cylinder;
import model.Shape;
import model.Sphere;
import model.Square;
import controller.Controller;

public class Ui {
    private Controller controller;

    public Ui(Controller controller) {
        this.controller = controller;
    }

    public void start() {
        System.out.println("Hello");
        while (true) {
            System.out.println("1. Add shape");
            System.out.println("2. Remove shape");
            System.out.println("3. Show all shapes");
            System.out.println("4. Filter by volume");
            System.out.println("0. Exit");

            int option = 0;
            try {
                option = Integer.parseInt(System.console().readLine());
            } catch (NumberFormatException e) {
                System.out.println("Invalid option");
                continue;
            }

            if(option == 1) {
                System.out.println("Enter the shape: square, sphere, cylinder");
                String shp = System.console().readLine().toLowerCase();
                System.out.println("Enter the volume of the shape");
                int volume = Integer.parseInt(System.console().readLine());

                if (shp.equals("square")) {
                    try {
                        controller.addShape(new Square(volume));
                    } catch (RuntimeException e) {
                        System.out.println(e.getMessage());
                    }
                } else if (shp.equals("sphere")) {
                    try {
                        controller.addShape(new Sphere(volume));
                    } catch (RuntimeException e) {
                        System.out.println(e.getMessage());
                    }
                } else if (shp.equals("cylinder")) {
                    try {
                        controller.addShape(new Cylinder(volume));
                    } catch (RuntimeException e) {
                        System.out.println(e.getMessage());
                    }
                } else {
                    System.out.println("Invalid shape");
                }

            } else if(option == 2) {
                System.out.println("Enter the index");
                int index = Integer.parseInt(System.console().readLine());
                try {
                    controller.removeShape(index);
                } catch (RuntimeException e) {
                    System.out.println(e.getMessage());
                }
            } else if(option == 3) {
                Shape[] aux = controller.getAllShapes();
                int size = this.controller.getRepoSize();
                for(int i = 0; i < size; i++) {
                    System.out.println(aux[i].toString());
                }
            } else if(option == 4) {
                Shape aux[] = controller.filterByVolume();
                for(int i = 0; i < aux.length; i++) {
                    System.out.println(aux[i].toString());
                }
            } else if(option == 0) {
                break;
            } else {
                System.out.println("Invalid option");
            }
        }
    }

}
