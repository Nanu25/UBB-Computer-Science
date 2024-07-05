/********************************************************************************
** Form generated from reading UI file 'GUIWithDesigner.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIWITHDESIGNER_H
#define UI_GUIWITHDESIGNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUIWithDesignerClass
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Administrator;
    QTableView *AdministratorTable;
    QHBoxLayout *horizontalLayout;
    QLabel *TitleLable;
    QLineEdit *TitleLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *GenreLable;
    QLineEdit *GenreLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *YearLable;
    QLineEdit *YearLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *LikesLAble;
    QLineEdit *LikesLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *TrailerLable;
    QLineEdit *TrailerLineEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QPushButton *displayButton;
    QPushButton *UndoButton;
    QPushButton *RedoButton;

    void setupUi(QWidget *GUIWithDesignerClass)
    {
        if (GUIWithDesignerClass->objectName().isEmpty())
            GUIWithDesignerClass->setObjectName("GUIWithDesignerClass");
        GUIWithDesignerClass->resize(845, 621);
        verticalLayout = new QVBoxLayout(GUIWithDesignerClass);
        verticalLayout->setObjectName("verticalLayout");
        Administrator = new QLabel(GUIWithDesignerClass);
        Administrator->setObjectName("Administrator");

        verticalLayout->addWidget(Administrator);

        AdministratorTable = new QTableView(GUIWithDesignerClass);
        AdministratorTable->setObjectName("AdministratorTable");

        verticalLayout->addWidget(AdministratorTable);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        TitleLable = new QLabel(GUIWithDesignerClass);
        TitleLable->setObjectName("TitleLable");

        horizontalLayout->addWidget(TitleLable);

        TitleLineEdit = new QLineEdit(GUIWithDesignerClass);
        TitleLineEdit->setObjectName("TitleLineEdit");

        horizontalLayout->addWidget(TitleLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        GenreLable = new QLabel(GUIWithDesignerClass);
        GenreLable->setObjectName("GenreLable");

        horizontalLayout_2->addWidget(GenreLable);

        GenreLineEdit = new QLineEdit(GUIWithDesignerClass);
        GenreLineEdit->setObjectName("GenreLineEdit");

        horizontalLayout_2->addWidget(GenreLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        YearLable = new QLabel(GUIWithDesignerClass);
        YearLable->setObjectName("YearLable");

        horizontalLayout_3->addWidget(YearLable);

        YearLineEdit = new QLineEdit(GUIWithDesignerClass);
        YearLineEdit->setObjectName("YearLineEdit");

        horizontalLayout_3->addWidget(YearLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        LikesLAble = new QLabel(GUIWithDesignerClass);
        LikesLAble->setObjectName("LikesLAble");

        horizontalLayout_4->addWidget(LikesLAble);

        LikesLineEdit = new QLineEdit(GUIWithDesignerClass);
        LikesLineEdit->setObjectName("LikesLineEdit");

        horizontalLayout_4->addWidget(LikesLineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        TrailerLable = new QLabel(GUIWithDesignerClass);
        TrailerLable->setObjectName("TrailerLable");

        horizontalLayout_5->addWidget(TrailerLable);

        TrailerLineEdit = new QLineEdit(GUIWithDesignerClass);
        TrailerLineEdit->setObjectName("TrailerLineEdit");

        horizontalLayout_5->addWidget(TrailerLineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        addButton = new QPushButton(GUIWithDesignerClass);
        addButton->setObjectName("addButton");
        addButton->setEnabled(true);
        addButton->setAutoDefault(false);

        verticalLayout->addWidget(addButton);

        deleteButton = new QPushButton(GUIWithDesignerClass);
        deleteButton->setObjectName("deleteButton");

        verticalLayout->addWidget(deleteButton);

        updateButton = new QPushButton(GUIWithDesignerClass);
        updateButton->setObjectName("updateButton");
        updateButton->setEnabled(true);
        updateButton->setAutoDefault(false);

        verticalLayout->addWidget(updateButton);

        displayButton = new QPushButton(GUIWithDesignerClass);
        displayButton->setObjectName("displayButton");
        displayButton->setEnabled(true);
        displayButton->setAutoDefault(false);

        verticalLayout->addWidget(displayButton);

        UndoButton = new QPushButton(GUIWithDesignerClass);
        UndoButton->setObjectName("UndoButton");

        verticalLayout->addWidget(UndoButton);

        RedoButton = new QPushButton(GUIWithDesignerClass);
        RedoButton->setObjectName("RedoButton");

        verticalLayout->addWidget(RedoButton);


        retranslateUi(GUIWithDesignerClass);

        QMetaObject::connectSlotsByName(GUIWithDesignerClass);
    } // setupUi

    void retranslateUi(QWidget *GUIWithDesignerClass)
    {
        GUIWithDesignerClass->setWindowTitle(QCoreApplication::translate("GUIWithDesignerClass", "GUIWithDesigner", nullptr));
        Administrator->setText(QCoreApplication::translate("GUIWithDesignerClass", "Administrator Mode", nullptr));
        TitleLable->setText(QCoreApplication::translate("GUIWithDesignerClass", "Title", nullptr));
        TitleLineEdit->setText(QString());
        GenreLable->setText(QCoreApplication::translate("GUIWithDesignerClass", "Genre", nullptr));
        YearLable->setText(QCoreApplication::translate("GUIWithDesignerClass", "Year", nullptr));
        LikesLAble->setText(QCoreApplication::translate("GUIWithDesignerClass", "Likes", nullptr));
        TrailerLable->setText(QCoreApplication::translate("GUIWithDesignerClass", "Trailer", nullptr));
        addButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Add", nullptr));
        deleteButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Delete", nullptr));
        updateButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Update", nullptr));
        displayButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Display", nullptr));
        UndoButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Undo", nullptr));
        RedoButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Redo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIWithDesignerClass: public Ui_GUIWithDesignerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIWITHDESIGNER_H
