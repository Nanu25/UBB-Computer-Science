//
// Created by alex_ on 5/16/2024.
//
#pragma once

#include <QWidget>
#include "ui_GUIWithDesigner.h"
#include "../Service/Service.h"



class GUIWithDesigner : public QWidget {
Q_OBJECT

private:
    Service service, user_list;
//    std::vector<TElement> filtered_movie_list;
//    int current_movie_index;
//    bool iterationStopped;

public:
    GUIWithDesigner(Service &serv, Service &user_list, QWidget *parent = nullptr);
    ~GUIWithDesigner();

private:
    Ui::GUIWithDesignerClass ui;
    void populateList();
    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();
    void displayButtonHandler();
    int getSelectedIndex();
//    void filterButtonHandler();
//    void displayUserWLButtonHandler();
//    void onLikeButtonClicked();
//    void onDislikeButtonClicked();
//    void onNextButtonClicked();
//    void showNextMovie();
//    void increaseLikeButtonHandler();
};


