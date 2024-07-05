#pragma once
#include <QWidget>
#include "ui_GUI_USER.h"
#include "../Service/Service.h"


class GUI_USER : public QWidget, public Observer{
Q_OBJECT

public:
    explicit GUI_USER(Service service, Service serv, QWidget *parent = nullptr);
    void setTitle();

    ~GUI_USER() override;

private:
    Ui::GUI_USER ui;
    Service service, user_list;
    std::vector<TElement> filtered_movie_list;
    int current_movie_index;
    bool iterationStopped;

    void filterButtonHandler();
    void displayUserWLButtonHandler();
    void onLikeButtonClicked();
    void onDislikeButtonClicked();
    void onNextButtonClicked();
    void showNextMovie();
    void increaseLikeButtonHandler();
    void update() override;
};

