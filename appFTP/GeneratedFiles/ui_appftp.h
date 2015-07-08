/********************************************************************************
** Form generated from reading ui file 'appftp.ui'
**
** Created: Tue Jul 7 15:54:29 2015
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_APPFTP_H
#define UI_APPFTP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_appFTPClass
{
public:

    void setupUi(QWidget *appFTPClass)
    {
    if (appFTPClass->objectName().isEmpty())
        appFTPClass->setObjectName(QString::fromUtf8("appFTPClass"));
    appFTPClass->resize(600, 400);

    retranslateUi(appFTPClass);

    QMetaObject::connectSlotsByName(appFTPClass);
    } // setupUi

    void retranslateUi(QWidget *appFTPClass)
    {
    appFTPClass->setWindowTitle(QApplication::translate("appFTPClass", "appFTP", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(appFTPClass);
    } // retranslateUi

};

namespace Ui {
    class appFTPClass: public Ui_appFTPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPFTP_H
