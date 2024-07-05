/********************************************************************************
** Form generated from reading UI file 'gui_user.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_USER_H
#define UI_GUI_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_USER
{
public:
    QListWidget *UserListWidget;
    QPushButton *filterButton;
    QPushButton *userWatchListButton;
    QPushButton *LikeButton;
    QPushButton *NextButton;
    QPushButton *dislikeButton;
    QPushButton *increaseLikeButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *TitleLineEdit;
    QLineEdit *GenreLineEdit;

    void setupUi(QWidget *GUI_USER)
    {
        if (GUI_USER->objectName().isEmpty())
            GUI_USER->setObjectName("GUI_USER");
        GUI_USER->resize(640, 526);
        UserListWidget = new QListWidget(GUI_USER);
        UserListWidget->setObjectName("UserListWidget");
        UserListWidget->setGeometry(QRect(160, 30, 361, 301));
        filterButton = new QPushButton(GUI_USER);
        filterButton->setObjectName("filterButton");
        filterButton->setGeometry(QRect(280, 440, 75, 24));
        userWatchListButton = new QPushButton(GUI_USER);
        userWatchListButton->setObjectName("userWatchListButton");
        userWatchListButton->setGeometry(QRect(190, 440, 75, 24));
        LikeButton = new QPushButton(GUI_USER);
        LikeButton->setObjectName("LikeButton");
        LikeButton->setGeometry(QRect(370, 440, 75, 24));
        NextButton = new QPushButton(GUI_USER);
        NextButton->setObjectName("NextButton");
        NextButton->setGeometry(QRect(280, 470, 75, 24));
        dislikeButton = new QPushButton(GUI_USER);
        dislikeButton->setObjectName("dislikeButton");
        dislikeButton->setGeometry(QRect(370, 470, 75, 24));
        increaseLikeButton = new QPushButton(GUI_USER);
        increaseLikeButton->setObjectName("increaseLikeButton");
        increaseLikeButton->setGeometry(QRect(190, 470, 75, 24));
        label = new QLabel(GUI_USER);
        label->setObjectName("label");
        label->setGeometry(QRect(140, 360, 49, 16));
        label_2 = new QLabel(GUI_USER);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 390, 49, 16));
        label_3 = new QLabel(GUI_USER);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(160, 10, 61, 16));
        widget = new QWidget(GUI_USER);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(180, 360, 331, 50));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TitleLineEdit = new QLineEdit(widget);
        TitleLineEdit->setObjectName("TitleLineEdit");

        verticalLayout->addWidget(TitleLineEdit);

        GenreLineEdit = new QLineEdit(widget);
        GenreLineEdit->setObjectName("GenreLineEdit");

        verticalLayout->addWidget(GenreLineEdit);


        retranslateUi(GUI_USER);

        QMetaObject::connectSlotsByName(GUI_USER);
    } // setupUi

    void retranslateUi(QWidget *GUI_USER)
    {
        GUI_USER->setWindowTitle(QCoreApplication::translate("GUI_USER", "GUI_USER", nullptr));
        filterButton->setText(QCoreApplication::translate("GUI_USER", "Filter", nullptr));
        userWatchListButton->setText(QCoreApplication::translate("GUI_USER", "Watch List", nullptr));
        LikeButton->setText(QCoreApplication::translate("GUI_USER", "Like", nullptr));
        NextButton->setText(QCoreApplication::translate("GUI_USER", "Next", nullptr));
        dislikeButton->setText(QCoreApplication::translate("GUI_USER", "Dislike", nullptr));
        increaseLikeButton->setText(QCoreApplication::translate("GUI_USER", "Increase Like", nullptr));
        label->setText(QCoreApplication::translate("GUI_USER", "Title", nullptr));
        label_2->setText(QCoreApplication::translate("GUI_USER", "Genre", nullptr));
        label_3->setText(QCoreApplication::translate("GUI_USER", "User Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_USER: public Ui_GUI_USER {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_USER_H
