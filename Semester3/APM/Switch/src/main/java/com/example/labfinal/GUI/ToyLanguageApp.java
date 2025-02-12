    package com.example.labfinal.GUI;

    import javafx.application.Application;
    import javafx.fxml.FXMLLoader;
    import javafx.scene.Scene;
    import javafx.stage.Stage;

    public class ToyLanguageApp extends Application {

        @Override
        public void start(Stage primaryStage) {
            try {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/labfinal/GUI/ProgramList.fxml"));
                primaryStage.setScene(new Scene(loader.load()));
                primaryStage.setTitle("Toy Language Interpreter");
                primaryStage.show();
            } catch (Exception e) {
                e.printStackTrace();
                System.err.println("Failed to load FXML file: " + e.getMessage());
            }
        }

        public static void main(String[] args) {
            launch(args);
        }
    }
