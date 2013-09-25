/****************************************************************************
** Meta object code from reading C++ file 'luahighlighter.h'
**
** Created: Wed Apr 4 18:07:29 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "luahighlighter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'luahighlighter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RainbruRPG__Editor__LuaHighlighter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Editor__LuaHighlighter[] = {
    "RainbruRPG::Editor::LuaHighlighter\0"
};

const QMetaObject RainbruRPG::Editor::LuaHighlighter::staticMetaObject = {
    { &Highlighter::staticMetaObject, qt_meta_stringdata_RainbruRPG__Editor__LuaHighlighter,
      qt_meta_data_RainbruRPG__Editor__LuaHighlighter, 0 }
};

const QMetaObject *RainbruRPG::Editor::LuaHighlighter::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Editor::LuaHighlighter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Editor__LuaHighlighter))
	return static_cast<void*>(const_cast<LuaHighlighter*>(this));
    return Highlighter::qt_metacast(_clname);
}

int RainbruRPG::Editor::LuaHighlighter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Highlighter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
