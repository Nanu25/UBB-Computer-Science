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
    QLineEdit *SearchLineEdit;
    QListWidget *SearchEngineWidget;
    QPushButton *ShowBestMatchingButton;

    void setupUi(QWidget *Gui)
    {
        if (Gui->objectName().isEmpty())
            Gui->setObjectName("Gui");
        Gui->resize(603, 392);
        verticalLayout = new QVBoxLayout(Gui);
        verticalLayout->setObjectName("verticalLayout");
        SearchLineEdit = new QLineEdit(Gui);
        SearchLineEdit->setObjectName("SearchLineEdit");

        verticalLayout->addWidget(SearchLineEdit);

        SearchEngineWidget = new QListWidget(Gui);
        SearchEngineWidget->setObjectName("SearchEngineWidget");

        verticalLayout->addWidget(SearchEngineWidget);

        ShowBestMatchingButton = new QPushButton(Gui);
        ShowBestMatchingButton->setObjectName("ShowBestMatchingButton");

        verticalLayout->addWidget(ShowBestMatchingButton);


        retranslateUi(Gui);

        QMetaObject::connectSlotsByName(Gui);
    } // setupUi

    void retranslateUi(QWidget *Gui)
    {
        Gui->setWindowTitle(QCoreApplication::translate("Gui", "Gui", nullptr));
        ShowBestMatchingButton->setText(QCoreApplication::translate("Gui", "Show Best Matching", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gui: public Ui_Gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
