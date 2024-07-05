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
    QListWidget *TaskWidget;
    QListWidget *FilteredWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *PriorityLineEdit;
    QPushButton *ShowTaskButton;

    void setupUi(QWidget *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName("Gui");
        Gui->resize(679, 380);
        verticalLayout = new QVBoxLayout(Gui);
        verticalLayout->setObjectName("verticalLayout");
        TaskWidget = new QListWidget(Gui);
        TaskWidget->setObjectName("TaskWidget");

        verticalLayout->addWidget(TaskWidget);

        FilteredWidget = new QListWidget(Gui);
        FilteredWidget->setObjectName("FilteredWidget");

        verticalLayout->addWidget(FilteredWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Gui);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        PriorityLineEdit = new QLineEdit(Gui);
        PriorityLineEdit->setObjectName("PriorityLineEdit");

        horizontalLayout->addWidget(PriorityLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        ShowTaskButton = new QPushButton(Gui);
        ShowTaskButton->setObjectName("ShowTaskButton");

        verticalLayout->addWidget(ShowTaskButton);


        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QWidget *Gui)
    {
        Gui->setWindowTitle(QCoreApplication::translate("Gui", "Gui", nullptr));
        label->setText(QCoreApplication::translate("Gui", "Priority", nullptr));
        ShowTaskButton->setText(QCoreApplication::translate("Gui", "Show Task and Durations", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
