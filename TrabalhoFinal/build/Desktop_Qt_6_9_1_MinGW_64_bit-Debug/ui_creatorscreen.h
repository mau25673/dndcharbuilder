/********************************************************************************
** Form generated from reading UI file 'creatorscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATORSCREEN_H
#define UI_CREATORSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_creatorScreen
{
public:

    void setupUi(QWidget *creatorScreen)
    {
        if (creatorScreen->objectName().isEmpty())
            creatorScreen->setObjectName("creatorScreen");
        creatorScreen->resize(400, 300);

        retranslateUi(creatorScreen);

        QMetaObject::connectSlotsByName(creatorScreen);
    } // setupUi

    void retranslateUi(QWidget *creatorScreen)
    {
        creatorScreen->setWindowTitle(QCoreApplication::translate("creatorScreen", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class creatorScreen: public Ui_creatorScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATORSCREEN_H
