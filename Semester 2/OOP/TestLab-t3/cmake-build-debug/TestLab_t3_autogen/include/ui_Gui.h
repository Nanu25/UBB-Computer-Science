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
    QVBoxLayout *verticalLayout_2;
    QListWidget *EquationWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ALineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *BLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *CLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *AddButton;
    QPushButton *ComputeSolutionButton;
    QLineEdit *SolutionLine;

    void setupUi(QWidget *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName("Gui");
        Gui->resize(493, 389);
        verticalLayout_2 = new QVBoxLayout(Gui);
        verticalLayout_2->setObjectName("verticalLayout_2");
        EquationWidget = new QListWidget(Gui);
        EquationWidget->setObjectName("EquationWidget");

        verticalLayout_2->addWidget(EquationWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Gui);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        ALineEdit = new QLineEdit(Gui);
        ALineEdit->setObjectName("ALineEdit");

        horizontalLayout->addWidget(ALineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(Gui);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        BLineEdit = new QLineEdit(Gui);
        BLineEdit->setObjectName("BLineEdit");

        horizontalLayout_2->addWidget(BLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(Gui);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        CLineEdit = new QLineEdit(Gui);
        CLineEdit->setObjectName("CLineEdit");

        horizontalLayout_3->addWidget(CLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        AddButton = new QPushButton(Gui);
        AddButton->setObjectName("AddButton");

        horizontalLayout_4->addWidget(AddButton);

        ComputeSolutionButton = new QPushButton(Gui);
        ComputeSolutionButton->setObjectName("ComputeSolutionButton");

        horizontalLayout_4->addWidget(ComputeSolutionButton);


        verticalLayout_2->addLayout(horizontalLayout_4);

        SolutionLine = new QLineEdit(Gui);
        SolutionLine->setObjectName("SolutionLine");

        verticalLayout_2->addWidget(SolutionLine);


        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QWidget *Gui)
    {
        Gui->setWindowTitle(QCoreApplication::translate("Gui", "Gui", nullptr));
        label->setText(QCoreApplication::translate("Gui", "a", nullptr));
        label_2->setText(QCoreApplication::translate("Gui", "b", nullptr));
        label_3->setText(QCoreApplication::translate("Gui", "c", nullptr));
        AddButton->setText(QCoreApplication::translate("Gui", "Add", nullptr));
        ComputeSolutionButton->setText(QCoreApplication::translate("Gui", "Compute Solution", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
