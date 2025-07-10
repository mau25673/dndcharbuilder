/********************************************************************************
** Form generated from reading UI file 'wizardspelllist.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIZARDSPELLLIST_H
#define UI_WIZARDSPELLLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wizardSpellList
{
public:

    void setupUi(QWidget *wizardSpellList)
    {
        if (wizardSpellList->objectName().isEmpty())
            wizardSpellList->setObjectName("wizardSpellList");
        wizardSpellList->resize(400, 300);

        retranslateUi(wizardSpellList);

        QMetaObject::connectSlotsByName(wizardSpellList);
    } // setupUi

    void retranslateUi(QWidget *wizardSpellList)
    {
        wizardSpellList->setWindowTitle(QCoreApplication::translate("wizardSpellList", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wizardSpellList: public Ui_wizardSpellList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIZARDSPELLLIST_H
