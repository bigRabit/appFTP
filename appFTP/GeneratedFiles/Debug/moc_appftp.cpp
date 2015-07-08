/****************************************************************************
** Meta object code from reading C++ file 'appftp.h'
**
** Created: Wed Jul 8 11:03:21 2015
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../appftp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appftp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_appFTP[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      28,    7,    7,    7, 0x08,
      52,    7,    7,    7, 0x08,
      77,   75,    7,    7, 0x08,
     106,    7,    7,    7, 0x08,
     129,   75,    7,    7, 0x08,
     179,  171,    7,    7, 0x08,
     211,  199,    7,    7, 0x08,
     245,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_appFTP[] = {
    "appFTP\0\0quitButtonClicked()\0"
    "downloadButtonClicked()\0connectButtonClicked()\0"
    ",\0ftpCommandFinished(int,bool)\0"
    "ftpCommandStarted(int)\0"
    "updateDataTransferProgress(qint64,qint64)\0"
    "urlInfo\0addToList(QUrlInfo)\0item,column\0"
    "processItem(QTreeWidgetItem*,int)\0"
    "refreshButtonClicked()\0"
};

const QMetaObject appFTP::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_appFTP,
      qt_meta_data_appFTP, 0 }
};

const QMetaObject *appFTP::metaObject() const
{
    return &staticMetaObject;
}

void *appFTP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_appFTP))
	return static_cast<void*>(const_cast< appFTP*>(this));
    return QWidget::qt_metacast(_clname);
}

int appFTP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: quitButtonClicked(); break;
        case 1: downloadButtonClicked(); break;
        case 2: connectButtonClicked(); break;
        case 3: ftpCommandFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: ftpCommandStarted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: updateDataTransferProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 6: addToList((*reinterpret_cast< const QUrlInfo(*)>(_a[1]))); break;
        case 7: processItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: refreshButtonClicked(); break;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
