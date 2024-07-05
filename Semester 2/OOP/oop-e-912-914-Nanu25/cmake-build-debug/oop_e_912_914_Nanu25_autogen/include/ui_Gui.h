/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gui
{
public:
    QPushButton *addButton;
    QPushButton *saveButton;
    QPushButton *SaveAllButton;
    QPushButton *developButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *titleLineEdit;
    QLineEdit *descriptionLineEdit;
    QLineEdit *durationLineEdit;
    QListWidget *IdeeaWidget;
    QTableView *IdeeaTableView;

    void setupUi(QWidget *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName("Gui");
        Gui->resize(720, 475);
        addButton = new QPushButton(Gui);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(50, 370, 75, 24));
        saveButton = new QPushButton(Gui);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(50, 410, 75, 24));
        SaveAllButton = new QPushButton(Gui);
        SaveAllButton->setObjectName("SaveAllButton");
        SaveAllButton->setGeometry(QRect(170, 370, 75, 24));
        developButton = new QPushButton(Gui);
        developButton->setObjectName("developButton");
        developButton->setGeometry(QRect(170, 410, 75, 24));
        layoutWidget = new QWidget(Gui);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 280, 63, 62));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        layoutWidget1 = new QWidget(Gui);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(80, 270, 281, 77));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleLineEdit = new QLineEdit(layoutWidget1);
        titleLineEdit->setObjectName("titleLineEdit");

        verticalLayout_2->addWidget(titleLineEdit);

        descriptionLineEdit = new QLineEdit(layoutWidget1);
        descriptionLineEdit->setObjectName("descriptionLineEdit");

        verticalLayout_2->addWidget(descriptionLineEdit);

        durationLineEdit = new QLineEdit(layoutWidget1);
        durationLineEdit->setObjectName("durationLineEdit");

        verticalLayout_2->addWidget(durationLineEdit);

        IdeeaWidget = new QListWidget(Gui);
        IdeeaWidget->setObjectName("IdeeaWidget");
        IdeeaWidget->setGeometry(QRect(420, 30, 256, 221));
        IdeeaTableView = new QTableView(Gui);
        IdeeaTableView->setObjectName("IdeeaTableView");
        IdeeaTableView->setGeometry(QRect(20, 30, 381, 231));

        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QWidget *Gui)
    {
        Gui->setWindowTitle(QCoreApplication::translate("Gui", "Gui", nullptr));
        addButton->setText(QCoreApplication::translate("Gui", "Add", nullptr));
        saveButton->setText(QCoreApplication::translate("Gui", "Save", nullptr));
        SaveAllButton->setText(QCoreApplication::translate("Gui", "Save All", nullptr));
        developButton->setText(QCoreApplication::translate("Gui", "Develop", nullptr));
        label->setText(QCoreApplication::translate("Gui", "Title", nullptr));
        label_2->setText(QCoreApplication::translate("Gui", "Description", nullptr));
        label_3->setText(QCoreApplication::translate("Gui", "Duration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
