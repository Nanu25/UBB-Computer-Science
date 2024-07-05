//
// Created by alex_ on 5/16/2024.
//
#pragma once

#include <QWidget>
#include "ui_GUIWithDesigner.h"
#include "../Service/Service.h"
#include "../Undo_Redo/UndoRedo.h"


class GUIWithDesigner : public QWidget, public Observer{
Q_OBJECT

private:
    Service service, user_list;
    UndoRedo undoRedo;

public:
    GUIWithDesigner(Service &serv, Service &user_list, QWidget *parent = nullptr);
    ~GUIWithDesigner();
    void setTitle();


private:
    Ui::GUIWithDesignerClass ui;
    void populateList();
    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();
    void displayButtonHandler();
    int getSelectedIndex();
    void undoButtonHandler();
    void redoButtonHandler();
    void update() override;
};


