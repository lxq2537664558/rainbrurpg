/****************************************************************************
** Meta object code from reading C++ file 'tabenvironment.h'
**
** Created: Thu Aug 14 14:56:01 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tabenvironment.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabenvironment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RainbruRPG__Editor__TabEnvironment[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Editor__TabEnvironment[] = {
    "RainbruRPG::Editor::TabEnvironment\0"
};

const QMetaObject RainbruRPG::Editor::TabEnvironment::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RainbruRPG__Editor__TabEnvironment,
      qt_meta_data_RainbruRPG__Editor__TabEnvironment, 0 }
};

const QMetaObject *RainbruRPG::Editor::TabEnvironment::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Editor::TabEnvironment::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Editor__TabEnvironment))
	return static_cast<void*>(const_cast< TabEnvironment*>(this));
    return QWidget::qt_metacast(_clname);
}

int RainbruRPG::Editor::TabEnvironment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
