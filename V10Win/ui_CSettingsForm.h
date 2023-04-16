/********************************************************************************
** Form generated from reading UI file 'CSettingsForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSETTINGSFORM_H
#define UI_CSETTINGSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_CSettingsForm
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;

    void setupUi(QDialog *CSettingsForm)
    {
        if (CSettingsForm->objectName().isEmpty())
            CSettingsForm->setObjectName(QString::fromUtf8("CSettingsForm"));
        CSettingsForm->resize(400, 300);
        buttonBox = new QDialogButtonBox(CSettingsForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(CSettingsForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 30, 211, 24));
        label = new QLabel(CSettingsForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 81, 18));
        label_2 = new QLabel(CSettingsForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 90, 71, 18));
        comboBox = new QComboBox(CSettingsForm);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 90, 131, 24));

        retranslateUi(CSettingsForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), CSettingsForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CSettingsForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(CSettingsForm);
    } // setupUi

    void retranslateUi(QDialog *CSettingsForm)
    {
        CSettingsForm->setWindowTitle(QApplication::translate("CSettingsForm", "CSettingsForm", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CSettingsForm", "COM \320\277\320\276\321\200\321\202:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CSettingsForm", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CSettingsForm: public Ui_CSettingsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSETTINGSFORM_H
