/****************************************************************************
** Meta object code from reading C++ file 'objectstab.h'
**
** Created: Sun Feb 4 23:49:21 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "objectstab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectstab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RainbruRPG__Editor__ObjectsTab[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      34,   32,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Editor__ObjectsTab[] = {
    "RainbruRPG::Editor::ObjectsTab\0\0,\0"
    "objectTreeClicked(QTreeWidgetItem*,int)\0"
};

const QMetaObject RainbruRPG::Editor::ObjectsTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RainbruRPG__Editor__ObjectsTab,
      qt_meta_data_RainbruRPG__Editor__ObjectsTab, 0 }
};

const QMetaObject *RainbruRPG::Editor::ObjectsTab::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Editor::ObjectsTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Editor__ObjectsTab))
	return static_cast<void*>(const_cast<ObjectsTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int RainbruRPG::Editor::ObjectsTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: objectTreeClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 1;
    }
    return _id;
}
