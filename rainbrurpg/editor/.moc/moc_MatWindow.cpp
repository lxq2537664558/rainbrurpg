/****************************************************************************
** Meta object code from reading C++ file 'MatWindow.h'
**
** Created: Sun Dec 31 12:01:55 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MatWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MatWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_MatWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   10,   10,   10, 0x08,
      56,   10,   10,   10, 0x08,
      66,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MatWindow[] = {
    "MatWindow\0\0msgBoxClicked()\0processMat(QTreeWidgetItem*)\0saveMat()\0"
    "updateTexture()\0"
};

const QMetaObject MatWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MatWindow,
      qt_meta_data_MatWindow, 0 }
};

const QMetaObject *MatWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MatWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MatWindow))
	return static_cast<void*>(const_cast<MatWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MatWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: msgBoxClicked(); break;
        case 1: processMat((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 2: saveMat(); break;
        case 3: updateTexture(); break;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MatWindow::msgBoxClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
