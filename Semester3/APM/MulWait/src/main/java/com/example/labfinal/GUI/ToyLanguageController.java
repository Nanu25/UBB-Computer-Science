package com.example.labfinal.GUI;

import Model.Values.Value;
import controller.Controller;
import Exception.MyException;


import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;


public class ToyLanguageController {
    @FXML
    private TextArea outputArea;

    @FXML
    private TableView<Map.Entry<Integer, Value>> heapTable;

    @FXML
    private TableColumn<Map.Entry<Integer, Value>, Integer> addressColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, Value>, String> valueColumn;

    @FXML
    private TableView<Map.Entry<String, Value>> variableTable;

    @FXML
    private TableColumn<Map.Entry<String, Value>, String> variableName;

    @FXML
    private TableColumn<Map.Entry<String, Value>, Value> variableValue;

    @FXML
    private TextField noOfPrgStates;

    @FXML
    private ListView<String> outListView;

    @FXML
    private ListView<String> fileTableListView;

    @FXML
    private ListView<Integer> prgStateIdsListView; // Displays PrgState IDs

    @FXML
    private ListView<String> exeStackListView; // Displays the ExeStack of the selected PrgState

    @FXML
    private TableView<Map.Entry<Integer, Integer>> lockTable;

    @FXML
    private TableColumn<Map.Entry<Integer, Integer>, Integer> lockIndexColumn;

    @FXML
    private TableColumn<Map.Entry<Integer, Integer>, Integer> lockValueColumn;


    private Controller selectedController;



    public ToyLanguageController() {
    }

    @FXML
    public void initialize() {
        // Make sure this line matches exactly:
        addressColumn.setCellValueFactory(cellData ->
                new SimpleObjectProperty<>(cellData.getValue().getKey()));

        // This is the critical line that needs to be fixed:
        valueColumn.setCellValueFactory(p -> {
            Value val = p.getValue().getValue();
            return new SimpleStringProperty(val.toString());
        });

        variableName.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getKey()));
        variableValue.setCellValueFactory(cellData -> new SimpleObjectProperty<>(cellData.getValue().getValue()));

        lockIndexColumn.setCellValueFactory(cellData ->
                new SimpleIntegerProperty(cellData.getValue().getKey()).asObject());

        lockValueColumn.setCellValueFactory(cellData ->
                new SimpleIntegerProperty(cellData.getValue().getValue()).asObject());

        // Add initial messages to lists
        outListView.getItems().add("Output: ");
        fileTableListView.getItems().add("File Table: ");
        exeStackListView.getItems().add("ExeStack: ");
    }

    @FXML
    private void runExample() {
        if (selectedController != null) {
            try {
                // Execute one step for all program states
                if(selectedController.getRepo().getPrgList().size() == 0){
                    outputArea.setText("Program is done.");
                    return;
                }

                selectedController.executeOneStep();

                if(selectedController.getRepo().getPrgList().size() == 0){
                    outputArea.setText("Program is done.");
                    return;
                }
                // Update the heap table
                updateHeapTable(selectedController.getHeap());
                updateLockTable(selectedController.getLockTable());

                // Update the output list
                outListView.setItems(FXCollections.observableArrayList(selectedController.getOutEntries()));

                // Update the file table
                fileTableListView.setItems(FXCollections.observableArrayList(selectedController.getFileTableEntries()));

                updatePrgStateIds(selectedController);


                // Update the number of program states
                noOfPrgStates.setText(String.valueOf(selectedController.getNoOfPrgStates()));



                // Get selected program state ID
                Integer selectedPrgStateId = prgStateIdsListView.getSelectionModel().getSelectedItem();


                if (selectedPrgStateId != null) {
                    List<String> exeStackEntries = selectedController.getExeStackEntries(selectedPrgStateId);
                    exeStackListView.setItems(FXCollections.observableArrayList(exeStackEntries));

                    // Update SymTable for the selected program state
                    Map<String, Value> symTable = selectedController.getSymTable(selectedPrgStateId);
                    updateSymTable(symTable);
                } else {
                    exeStackListView.setItems(FXCollections.observableArrayList("No program state selected."));
                    variableTable.getItems().clear();
                }

                // Optional: Log the execution or provide feedback
                outputArea.setText("Executed one step successfully.");

            } catch (MyException e) {
                outputArea.setText("Error during execution: " + e.getMessage());
            } catch (InterruptedException e) {
                throw new RuntimeException("Execution interrupted: " + e.getMessage());
            }
        } else {
            outputArea.setText("No program selected to execute.");
        }
    }

    private void updateHeapTable(Map<Integer, Value> heap) {
        heapTable.getItems().clear();
        List<Map.Entry<Integer, Value>> entries = new ArrayList<>(heap.entrySet());
        heapTable.setItems(FXCollections.observableArrayList(entries));
    }

    private void updatePrgStateIds(Controller selectedController) {
        List<Integer> prgStateIds = selectedController.getRepo().getPrgList()
                .stream()
                .map(prgState -> prgState.getPrgStateId())  // Assuming `PrgState` has a method `getId()`
                .collect(Collectors.toList());

        prgStateIdsListView.setItems(FXCollections.observableArrayList(prgStateIds));
    }

    private void updateSymTable(Map<String, Value> symTable) {
        if (symTable == null || symTable.isEmpty()) {
            variableTable.getItems().clear();
            return;
        }
        variableTable.getItems().clear();
        ObservableList<Map.Entry<String, Value>> symTableEntries = FXCollections.observableArrayList(symTable.entrySet());
        variableTable.setItems(symTableEntries);
    }

    private void updateLockTable(Map<Integer, Integer> lckTable) {
        if (lckTable == null || lckTable.isEmpty()) {
            lockTable.getItems().clear();
            return;
        }
        lockTable.getItems().clear();
        ObservableList<Map.Entry<Integer, Integer>> lockTableEntries = FXCollections.observableArrayList(lckTable.entrySet());
        lockTable.setItems(lockTableEntries);
    }


    public void setController(Controller selectedController) {
        this.selectedController = selectedController;
    }
}
