/********************************************************************************
** Form generated from reading UI file 'NewForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFORM_H
#define UI_NEWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewForm
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NewForm)
    {
        if (NewForm->objectName().isEmpty())
            NewForm->setObjectName(QString::fromUtf8("NewForm"));
        NewForm->resize(800, 600);
        centralwidget = new QWidget(NewForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        NewForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NewForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        NewForm->setMenuBar(menubar);
        statusbar = new QStatusBar(NewForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NewForm->setStatusBar(statusbar);

        retranslateUi(NewForm);

        QMetaObject::connectSlotsByName(NewForm);
    } // setupUi

    void retranslateUi(QMainWindow *NewForm)
    {
        NewForm->setWindowTitle(QApplication::translate("NewForm", "NewForm", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewForm: public Ui_NewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFORM_H
