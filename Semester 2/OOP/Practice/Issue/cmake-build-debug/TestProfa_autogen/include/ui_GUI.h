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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QVBoxLayout *verticalLayout_2;
    QListWidget *IssueWidget;
    QLineEdit *IssueLine;
    QVBoxLayout *verticalLayout;
    QPushButton *AddButton;
    QPushButton *RemoveButton;
    QPushButton *ResolveButton;

    void setupUi(QWidget *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName("GUI");
        GUI->resize(582, 370);
        verticalLayout_2 = new QVBoxLayout(GUI);
        verticalLayout_2->setObjectName("verticalLayout_2");
        IssueWidget = new QListWidget(GUI);
        IssueWidget->setObjectName("IssueWidget");

        verticalLayout_2->addWidget(IssueWidget);

        IssueLine = new QLineEdit(GUI);
        IssueLine->setObjectName("IssueLine");

        verticalLayout_2->addWidget(IssueLine);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        AddButton = new QPushButton(GUI);
        AddButton->setObjectName("AddButton");

        verticalLayout->addWidget(AddButton);

        RemoveButton = new QPushButton(GUI);
        RemoveButton->setObjectName("RemoveButton");

        verticalLayout->addWidget(RemoveButton);

        ResolveButton = new QPushButton(GUI);
        ResolveButton->setObjectName("ResolveButton");

        verticalLayout->addWidget(ResolveButton);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QWidget *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        AddButton->setText(QCoreApplication::translate("GUI", "Add", nullptr));
        RemoveButton->setText(QCoreApplication::translate("GUI", "Remove", nullptr));
        ResolveButton->setText(QCoreApplication::translate("GUI", "Resolve", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
