/****************************************************************************
** Meta object code from reading C++ file 'highlighter.h'
**
** Created: Thu Aug 14 14:56:28 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "highlighter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'highlighter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RainbruRPG__Editor__Highlighter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      52,   33,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Editor__Highlighter[] = {
    "RainbruRPG::Editor::Highlighter\0\0"
    "from,removed,added\0highlight(int,int,int)\0"
};

const QMetaObject RainbruRPG::Editor::Highlighter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RainbruRPG__Editor__Highlighter,
      qt_meta_data_RainbruRPG__Editor__Highlighter, 0 }
};

const QMetaObject *RainbruRPG::Editor::Highlighter::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Editor::Highlighter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Editor__Highlighter))
	return static_cast<void*>(const_cast< Highlighter*>(this));
    return QObject::qt_metacast(_clname);
}

int RainbruRPG::Editor::Highlighter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: highlight((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
