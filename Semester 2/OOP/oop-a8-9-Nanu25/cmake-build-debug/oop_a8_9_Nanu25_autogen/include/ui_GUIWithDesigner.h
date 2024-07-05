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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUIWithDesignerClass
{
public:
    QLabel *Administrator;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QPushButton *displayButton;
    QLineEdit *TitleLineEdit;
    QLabel *TitleLable;
    QLineEdit *GenreLineEdit;
    QLineEdit *YearLineEdit;
    QLineEdit *LikesLineEdit;
    QLineEdit *TrailerLineEdit;
    QLabel *GenreLable;
    QLabel *YearLable;
    QLabel *LikesLAble;
    QLabel *TrailerLable;
    QListWidget *MovieListWidget;

    void setupUi(QWidget *GUIWithDesignerClass)
    {
        if (GUIWithDesignerClass->objectName().isEmpty())
            GUIWithDesignerClass->setObjectName("GUIWithDesignerClass");
        GUIWithDesignerClass->resize(609, 621);
        Administrator = new QLabel(GUIWithDesignerClass);
        Administrator->setObjectName("Administrator");
        Administrator->setGeometry(QRect(90, 10, 261, 16));
        addButton = new QPushButton(GUIWithDesignerClass);
        addButton->setObjectName("addButton");
        addButton->setEnabled(true);
        addButton->setGeometry(QRect(130, 550, 151, 24));
        addButton->setAutoDefault(false);
        deleteButton = new QPushButton(GUIWithDesignerClass);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(130, 580, 151, 24));
        updateButton = new QPushButton(GUIWithDesignerClass);
        updateButton->setObjectName("updateButton");
        updateButton->setEnabled(true);
        updateButton->setGeometry(QRect(320, 550, 151, 24));
        updateButton->setAutoDefault(false);
        displayButton = new QPushButton(GUIWithDesignerClass);
        displayButton->setObjectName("displayButton");
        displayButton->setEnabled(true);
        displayButton->setGeometry(QRect(320, 580, 151, 24));
        displayButton->setAutoDefault(false);
        TitleLineEdit = new QLineEdit(GUIWithDesignerClass);
        TitleLineEdit->setObjectName("TitleLineEdit");
        TitleLineEdit->setGeometry(QRect(80, 390, 421, 21));
        TitleLable = new QLabel(GUIWithDesignerClass);
        TitleLable->setObjectName("TitleLable");
        TitleLable->setGeometry(QRect(30, 390, 49, 16));
        GenreLineEdit = new QLineEdit(GUIWithDesignerClass);
        GenreLineEdit->setObjectName("GenreLineEdit");
        GenreLineEdit->setGeometry(QRect(80, 420, 421, 21));
        YearLineEdit = new QLineEdit(GUIWithDesignerClass);
        YearLineEdit->setObjectName("YearLineEdit");
        YearLineEdit->setGeometry(QRect(80, 450, 421, 21));
        LikesLineEdit = new QLineEdit(GUIWithDesignerClass);
        LikesLineEdit->setObjectName("LikesLineEdit");
        LikesLineEdit->setGeometry(QRect(80, 480, 421, 21));
        TrailerLineEdit = new QLineEdit(GUIWithDesignerClass);
        TrailerLineEdit->setObjectName("TrailerLineEdit");
        TrailerLineEdit->setGeometry(QRect(80, 510, 421, 21));
        GenreLable = new QLabel(GUIWithDesignerClass);
        GenreLable->setObjectName("GenreLable");
        GenreLable->setGeometry(QRect(30, 420, 49, 16));
        YearLable = new QLabel(GUIWithDesignerClass);
        YearLable->setObjectName("YearLable");
        YearLable->setGeometry(QRect(30, 450, 49, 16));
        LikesLAble = new QLabel(GUIWithDesignerClass);
        LikesLAble->setObjectName("LikesLAble");
        LikesLAble->setGeometry(QRect(30, 480, 49, 16));
        TrailerLable = new QLabel(GUIWithDesignerClass);
        TrailerLable->setObjectName("TrailerLable");
        TrailerLable->setGeometry(QRect(20, 510, 49, 16));
        MovieListWidget = new QListWidget(GUIWithDesignerClass);
        MovieListWidget->setObjectName("MovieListWidget");
        MovieListWidget->setGeometry(QRect(90, 30, 411, 341));

        retranslateUi(GUIWithDesignerClass);

        QMetaObject::connectSlotsByName(GUIWithDesignerClass);
    } // setupUi

    void retranslateUi(QWidget *GUIWithDesignerClass)
    {
        GUIWithDesignerClass->setWindowTitle(QCoreApplication::translate("GUIWithDesignerClass", "GUIWithDesigner", nullptr));
        Administrator->setText(QCoreApplication::translate("GUIWithDesignerClass", "Administrator Mode", nullptr));
        addButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Add", nullptr));
        deleteButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Delete", nullptr));
        updateButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Update", nullptr));
        displayButton->setText(QCoreApplication::translate("GUIWithDesignerClass", "Display", nullptr));
        TitleLineEdit->setText(QString());
        TitleLable->setText(QCoreApplication::translate("GUIWithDesignerClass", "Title", nullptr));
        GenreLable->setText(QCoreApplication::translate("GUIWithDesignerClass", "Genre", nullptr));
        YearLable->setText(QCoreApplication::translate("GUIWithDesignerClass", "Year", nullptr));
        LikesLAble->setText(QCoreApplication::translate("GUIWithDesignerClass", "Likes", nullptr));
        TrailerLable->setText(QCoreApplication::translate("GUIWithDesignerClass", "Trailer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUIWithDesignerClass: public Ui_GUIWithDesignerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIWITHDESIGNER_H
