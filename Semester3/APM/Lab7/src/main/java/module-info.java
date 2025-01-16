module com.example.labfinal {
    requires javafx.controls;
    requires javafx.fxml;

    opens com.example.labfinal.GUI to javafx.fxml;
    exports com.example.labfinal.GUI;
}
