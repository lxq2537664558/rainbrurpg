/****************************************************************************
** Meta object code from reading C++ file 'objectlist.h'
**
** Created: Mon Jul 23 20:27:33 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "objectlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RainbruRPG__Gui__ObjectList[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Gui__ObjectList[] = {
    "RainbruRPG::Gui::ObjectList\0"
};

const QMetaObject RainbruRPG::Gui::ObjectList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RainbruRPG__Gui__ObjectList,
      qt_meta_data_RainbruRPG__Gui__ObjectList, 0 }
};

const QMetaObject *RainbruRPG::Gui::ObjectList::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Gui::ObjectList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Gui__ObjectList))
	return static_cast<void*>(const_cast< ObjectList*>(this));
    return QWidget::qt_metacast(_clname);
}

int RainbruRPG::Gui::ObjectList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
