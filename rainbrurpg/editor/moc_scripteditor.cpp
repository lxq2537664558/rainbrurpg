/****************************************************************************
** Meta object code from reading C++ file 'scripteditor.h'
**
** Created: Fri Apr 13 14:08:46 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scripteditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scripteditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RainbruRPG__Editor__ScriptEditor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      34,   33,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Editor__ScriptEditor[] = {
    "RainbruRPG::Editor::ScriptEditor\0\0"
    "cursorPositionChanged()\0"
};

const QMetaObject RainbruRPG::Editor::ScriptEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RainbruRPG__Editor__ScriptEditor,
      qt_meta_data_RainbruRPG__Editor__ScriptEditor, 0 }
};

const QMetaObject *RainbruRPG::Editor::ScriptEditor::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Editor::ScriptEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Editor__ScriptEditor))
	return static_cast<void*>(const_cast<ScriptEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int RainbruRPG::Editor::ScriptEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cursorPositionChanged(); break;
        }
        _id -= 1;
    }
    return _id;
}
