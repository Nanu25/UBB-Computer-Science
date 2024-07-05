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
    QLineEdit *FilterLineEdit;
    QListWidget *ShoppingWidget;
    QListWidget *FilterWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *CategoryLineEdit;
    QPushButton *ShowItemsButton;

    void setupUi(QWidget *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName("Gui");
        Gui->resize(504, 565);
        verticalLayout = new QVBoxLayout(Gui);
        verticalLayout->setObjectName("verticalLayout");
        FilterLineEdit = new QLineEdit(Gui);
        FilterLineEdit->setObjectName("FilterLineEdit");

        verticalLayout->addWidget(FilterLineEdit);

        ShoppingWidget = new QListWidget(Gui);
        ShoppingWidget->setObjectName("ShoppingWidget");

        verticalLayout->addWidget(ShoppingWidget);

        FilterWidget = new QListWidget(Gui);
        FilterWidget->setObjectName("FilterWidget");

        verticalLayout->addWidget(FilterWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Gui);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        CategoryLineEdit = new QLineEdit(Gui);
        CategoryLineEdit->setObjectName("CategoryLineEdit");

        horizontalLayout->addWidget(CategoryLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        ShowItemsButton = new QPushButton(Gui);
        ShowItemsButton->setObjectName("ShowItemsButton");

        verticalLayout->addWidget(ShowItemsButton);


        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QWidget *Gui)
    {
        Gui->setWindowTitle(QCoreApplication::translate("Gui", "Gui", nullptr));
        label->setText(QCoreApplication::translate("Gui", "Category", nullptr));
        ShowItemsButton->setText(QCoreApplication::translate("Gui", "Show Items", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
