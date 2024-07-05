/********************************************************************************
** Form generated from reading UI file 'Gui.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

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

class Ui_Gui
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *pairLineEdit;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *CompanyLineEdit;
    QPushButton *CalculateTotalButton;
    QLabel *TotalCost;

    void setupUi(QWidget *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName("Gui");
        Gui->resize(471, 406);
        verticalLayout = new QVBoxLayout(Gui);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Gui);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        pairLineEdit = new QLineEdit(Gui);
        pairLineEdit->setObjectName("pairLineEdit");

        horizontalLayout->addWidget(pairLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(Gui);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(Gui);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        CompanyLineEdit = new QLineEdit(Gui);
        CompanyLineEdit->setObjectName("CompanyLineEdit");

        horizontalLayout_2->addWidget(CompanyLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        CalculateTotalButton = new QPushButton(Gui);
        CalculateTotalButton->setObjectName("CalculateTotalButton");

        verticalLayout->addWidget(CalculateTotalButton);

        TotalCost = new QLabel(Gui);
        TotalCost->setObjectName("TotalCost");

        verticalLayout->addWidget(TotalCost);


        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QWidget *Gui)
    {
        Gui->setWindowTitle(QCoreApplication::translate("Gui", "Gui", nullptr));
        label->setText(QCoreApplication::translate("Gui", "Filter", nullptr));
        label_2->setText(QCoreApplication::translate("Gui", "Company Name", nullptr));
        CalculateTotalButton->setText(QCoreApplication::translate("Gui", "Calculate total", nullptr));
        TotalCost->setText(QCoreApplication::translate("Gui", "Total Cost", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
