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
#include <QtWidgets/QHBoxLayout>
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
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QListWidget *userListWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *TitleLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *GenreLineEdit;
    QPushButton *LikeButton;
    QPushButton *filterButton;
    QPushButton *userWatchListButton;
    QPushButton *dislikeButton;
    QPushButton *NextButton;
    QPushButton *increaseLikeButton;

    void setupUi(QWidget *GUI_USER)
    {
        if (GUI_USER->objectName().isEmpty())
            GUI_USER->setObjectName("GUI_USER");
        GUI_USER->resize(640, 526);
        verticalLayout = new QVBoxLayout(GUI_USER);
        verticalLayout->setObjectName("verticalLayout");
        label_3 = new QLabel(GUI_USER);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        userListWidget = new QListWidget(GUI_USER);
        userListWidget->setObjectName("userListWidget");

        verticalLayout->addWidget(userListWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(GUI_USER);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        TitleLineEdit = new QLineEdit(GUI_USER);
        TitleLineEdit->setObjectName("TitleLineEdit");

        horizontalLayout->addWidget(TitleLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(GUI_USER);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        GenreLineEdit = new QLineEdit(GUI_USER);
        GenreLineEdit->setObjectName("GenreLineEdit");

        horizontalLayout_2->addWidget(GenreLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        LikeButton = new QPushButton(GUI_USER);
        LikeButton->setObjectName("LikeButton");

        verticalLayout->addWidget(LikeButton);

        filterButton = new QPushButton(GUI_USER);
        filterButton->setObjectName("filterButton");

        verticalLayout->addWidget(filterButton);

        userWatchListButton = new QPushButton(GUI_USER);
        userWatchListButton->setObjectName("userWatchListButton");

        verticalLayout->addWidget(userWatchListButton);

        dislikeButton = new QPushButton(GUI_USER);
        dislikeButton->setObjectName("dislikeButton");

        verticalLayout->addWidget(dislikeButton);

        NextButton = new QPushButton(GUI_USER);
        NextButton->setObjectName("NextButton");

        verticalLayout->addWidget(NextButton);

        increaseLikeButton = new QPushButton(GUI_USER);
        increaseLikeButton->setObjectName("increaseLikeButton");

        verticalLayout->addWidget(increaseLikeButton);


        retranslateUi(GUI_USER);

        QMetaObject::connectSlotsByName(GUI_USER);
    } // setupUi

    void retranslateUi(QWidget *GUI_USER)
    {
        GUI_USER->setWindowTitle(QCoreApplication::translate("GUI_USER", "GUI_USER", nullptr));
        label_3->setText(QCoreApplication::translate("GUI_USER", "User Mode", nullptr));
        label->setText(QCoreApplication::translate("GUI_USER", "Title", nullptr));
        label_2->setText(QCoreApplication::translate("GUI_USER", "Genre", nullptr));
        LikeButton->setText(QCoreApplication::translate("GUI_USER", "Like", nullptr));
        filterButton->setText(QCoreApplication::translate("GUI_USER", "Filter", nullptr));
        userWatchListButton->setText(QCoreApplication::translate("GUI_USER", "Watch List", nullptr));
        dislikeButton->setText(QCoreApplication::translate("GUI_USER", "Dislike", nullptr));
        NextButton->setText(QCoreApplication::translate("GUI_USER", "Next", nullptr));
        increaseLikeButton->setText(QCoreApplication::translate("GUI_USER", "Increase Like", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_USER: public Ui_GUI_USER {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_USER_H
