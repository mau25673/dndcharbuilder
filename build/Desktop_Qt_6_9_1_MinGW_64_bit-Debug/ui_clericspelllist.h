/********************************************************************************
** Form generated from reading UI file 'clericspelllist.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLERICSPELLLIST_H
#define UI_CLERICSPELLLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_clericSpellList
{
public:

    void setupUi(QWidget *clericSpellList)
    {
        if (clericSpellList->objectName().isEmpty())
            clericSpellList->setObjectName("clericSpellList");
        clericSpellList->resize(400, 300);

        retranslateUi(clericSpellList);

        QMetaObject::connectSlotsByName(clericSpellList);
    } // setupUi

    void retranslateUi(QWidget *clericSpellList)
    {
        clericSpellList->setWindowTitle(QCoreApplication::translate("clericSpellList", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class clericSpellList: public Ui_clericSpellList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLERICSPELLLIST_H
