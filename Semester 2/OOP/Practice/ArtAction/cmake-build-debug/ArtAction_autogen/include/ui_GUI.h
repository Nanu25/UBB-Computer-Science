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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QVBoxLayout *verticalLayout_4;
    QComboBox *comboBox;
    QListWidget *ItemWidget;
    QListWidget *OffertsWirget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *nameLineEdit;
    QLineEdit *categoryLineEdit;
    QLineEdit *priceLineEdit;
    QLineEdit *BidLineEdit;
    QPushButton *BidButton;
    QPushButton *addButton;

    void setupUi(QWidget *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName("GUI");
        GUI->resize(819, 607);
        verticalLayout_4 = new QVBoxLayout(GUI);
        verticalLayout_4->setObjectName("verticalLayout_4");
        comboBox = new QComboBox(GUI);
        comboBox->setObjectName("comboBox");

        verticalLayout_4->addWidget(comboBox);

        ItemWidget = new QListWidget(GUI);
        ItemWidget->setObjectName("ItemWidget");

        verticalLayout_4->addWidget(ItemWidget);

        OffertsWirget = new QListWidget(GUI);
        OffertsWirget->setObjectName("OffertsWirget");

        verticalLayout_4->addWidget(OffertsWirget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(GUI);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(GUI);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        label_3 = new QLabel(GUI);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        label_4 = new QLabel(GUI);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        nameLineEdit = new QLineEdit(GUI);
        nameLineEdit->setObjectName("nameLineEdit");

        verticalLayout->addWidget(nameLineEdit);

        categoryLineEdit = new QLineEdit(GUI);
        categoryLineEdit->setObjectName("categoryLineEdit");

        verticalLayout->addWidget(categoryLineEdit);

        priceLineEdit = new QLineEdit(GUI);
        priceLineEdit->setObjectName("priceLineEdit");

        verticalLayout->addWidget(priceLineEdit);


        verticalLayout_2->addLayout(verticalLayout);

        BidLineEdit = new QLineEdit(GUI);
        BidLineEdit->setObjectName("BidLineEdit");

        verticalLayout_2->addWidget(BidLineEdit);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout);

        BidButton = new QPushButton(GUI);
        BidButton->setObjectName("BidButton");

        verticalLayout_4->addWidget(BidButton);

        addButton = new QPushButton(GUI);
        addButton->setObjectName("addButton");

        verticalLayout_4->addWidget(addButton);


        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QWidget *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        label->setText(QCoreApplication::translate("GUI", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("GUI", "Category", nullptr));
        label_3->setText(QCoreApplication::translate("GUI", "Price", nullptr));
        label_4->setText(QCoreApplication::translate("GUI", "Bid", nullptr));
        BidButton->setText(QCoreApplication::translate("GUI", "Bid", nullptr));
        addButton->setText(QCoreApplication::translate("GUI", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
