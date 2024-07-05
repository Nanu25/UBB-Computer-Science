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
    QListWidget *EventWidget;
    QPushButton *addButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *nameLine;
    QLineEdit *descriptionLine;
    QLineEdit *locationLine;
    QLineEdit *dateLine;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBox;
    QPushButton *GoingButton;
    QPushButton *TESTButton;

    void setupUi(QWidget *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName("Gui");
        Gui->resize(600, 507);
        EventWidget = new QListWidget(Gui);
        EventWidget->setObjectName("EventWidget");
        EventWidget->setGeometry(QRect(100, 30, 341, 301));
        addButton = new QPushButton(Gui);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(100, 460, 141, 24));
        layoutWidget = new QWidget(Gui);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(100, 340, 341, 104));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nameLine = new QLineEdit(layoutWidget);
        nameLine->setObjectName("nameLine");

        verticalLayout->addWidget(nameLine);

        descriptionLine = new QLineEdit(layoutWidget);
        descriptionLine->setObjectName("descriptionLine");

        verticalLayout->addWidget(descriptionLine);

        locationLine = new QLineEdit(layoutWidget);
        locationLine->setObjectName("locationLine");

        verticalLayout->addWidget(locationLine);

        dateLine = new QLineEdit(layoutWidget);
        dateLine->setObjectName("dateLine");

        verticalLayout->addWidget(dateLine);

        layoutWidget1 = new QWidget(Gui);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(30, 350, 63, 84));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        comboBox = new QComboBox(Gui);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(110, 0, 311, 22));
        GoingButton = new QPushButton(Gui);
        GoingButton->setObjectName("GoingButton");
        GoingButton->setGeometry(QRect(290, 460, 111, 21));
        TESTButton = new QPushButton(Gui);
        TESTButton->setObjectName("TESTButton");
        TESTButton->setGeometry(QRect(470, 460, 75, 24));

        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QWidget *Gui)
    {
        Gui->setWindowTitle(QCoreApplication::translate("Gui", "Gui", nullptr));
        addButton->setText(QCoreApplication::translate("Gui", "Add", nullptr));
        label->setText(QCoreApplication::translate("Gui", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("Gui", "Description", nullptr));
        label_3->setText(QCoreApplication::translate("Gui", "Location", nullptr));
        label_4->setText(QCoreApplication::translate("Gui", "Date", nullptr));
        GoingButton->setText(QCoreApplication::translate("Gui", "Going", nullptr));
        TESTButton->setText(QCoreApplication::translate("Gui", "Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
