/********************************************************************************
** Form generated from reading UI file 'CMainForm.uis'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINFORM_H
#define UI_CMAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "CTermTextEdit.h"

QT_BEGIN_NAMESPACE

class Ui_CMainForm
{
public:
    QAction *action;
    QWidget *centralwidget;
    CTermTextEdit *textEdit;
    QPushButton *pushButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CMainForm)
    {
        if (CMainForm->objectName().isEmpty())
            CMainForm->setObjectName(QString::fromUtf8("CMainForm"));
        CMainForm->resize(842, 642);
        action = new QAction(CMainForm);
        action->setObjectName(QString::fromUtf8("action"));
        centralwidget = new QWidget(CMainForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEdit = new CTermTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 671, 591));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(680, 10, 151, 28));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(680, 80, 151, 511));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(680, 40, 151, 28));
        CMainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CMainForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 842, 28));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        CMainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(CMainForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CMainForm->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action);

        retranslateUi(CMainForm);
        QObject::connect(action, SIGNAL(activated()), CMainForm, SLOT(handleAction()));
        QObject::connect(pushButton, SIGNAL(clicked()), CMainForm, SLOT(handlePushButton()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), CMainForm, SLOT(handlePushButton_2()));

        QMetaObject::connectSlotsByName(CMainForm);
    } // setupUi

    void retranslateUi(QMainWindow *CMainForm)
    {
        CMainForm->setWindowTitle(QApplication::translate("CMainForm", "V10Win", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("CMainForm", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 COM \320\277\320\276\321\200\321\202\320\260", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("CMainForm", "\320\234\320\265\320\275\321\216/\320\237\321\200\320\265\321\200\320\262\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("CMainForm", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("CMainForm", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CMainForm: public Ui_CMainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINFORM_H
