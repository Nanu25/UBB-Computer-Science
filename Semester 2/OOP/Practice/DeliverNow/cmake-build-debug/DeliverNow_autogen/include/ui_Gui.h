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
#include <QtWidgets/QComboBox>
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
    QListWidget *courierWidget;
    QListWidget *courierCompanyWidget;
    QLabel *label;
    QPushButton *addButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *recipientLine;
    QLineEdit *streetLine;
    QLineEdit *xLine;
    QLineEdit *yLine;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *deliverButton;
    QComboBox *comboBox;

    void setupUi(QWidget *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName("Gui");
        Gui->resize(845, 498);
        courierWidget = new QListWidget(Gui);
        courierWidget->setObjectName("courierWidget");
        courierWidget->setGeometry(QRect(40, 40, 371, 241));
        courierCompanyWidget = new QListWidget(Gui);
        courierCompanyWidget->setObjectName("courierCompanyWidget");
        courierCompanyWidget->setGeometry(QRect(490, 70, 331, 241));
        label = new QLabel(Gui);
        label->setObjectName("label");
        label->setGeometry(QRect(500, 10, 101, 16));
        addButton = new QPushButton(Gui);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(550, 440, 201, 24));
        layoutWidget = new QWidget(Gui);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(560, 320, 251, 104));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        recipientLine = new QLineEdit(layoutWidget);
        recipientLine->setObjectName("recipientLine");

        verticalLayout->addWidget(recipientLine);

        streetLine = new QLineEdit(layoutWidget);
        streetLine->setObjectName("streetLine");

        verticalLayout->addWidget(streetLine);

        xLine = new QLineEdit(layoutWidget);
        xLine->setObjectName("xLine");

        verticalLayout->addWidget(xLine);

        yLine = new QLineEdit(layoutWidget);
        yLine->setObjectName("yLine");

        verticalLayout->addWidget(yLine);

        layoutWidget1 = new QWidget(Gui);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(500, 320, 51, 101));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        deliverButton = new QPushButton(Gui);
        deliverButton->setObjectName("deliverButton");
        deliverButton->setGeometry(QRect(60, 400, 75, 24));
        comboBox = new QComboBox(Gui);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(500, 40, 321, 22));

        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QWidget *Gui)
    {
        Gui->setWindowTitle(QCoreApplication::translate("Gui", "Gui", nullptr));
        label->setText(QCoreApplication::translate("Gui", "Courier Company", nullptr));
        addButton->setText(QCoreApplication::translate("Gui", "Add", nullptr));
        label_2->setText(QCoreApplication::translate("Gui", "Recipient", nullptr));
        label_3->setText(QCoreApplication::translate("Gui", "Street", nullptr));
        label_4->setText(QCoreApplication::translate("Gui", "X", nullptr));
        label_5->setText(QCoreApplication::translate("Gui", "Y", nullptr));
        deliverButton->setText(QCoreApplication::translate("Gui", "Deliver", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
