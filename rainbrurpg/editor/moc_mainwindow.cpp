/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Aug 14 14:55:40 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RainbruRPG__Editor__EditorMainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      38,   37,   37,   37, 0x08,
      50,   37,   37,   37, 0x08,
      69,   37,   37,   37, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Editor__EditorMainWindow[] = {
    "RainbruRPG::Editor::EditorMainWindow\0"
    "\0scrollLog()\0showScriptEditor()\0about()\0"
};

const QMetaObject RainbruRPG::Editor::EditorMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RainbruRPG__Editor__EditorMainWindow,
      qt_meta_data_RainbruRPG__Editor__EditorMainWindow, 0 }
};

const QMetaObject *RainbruRPG::Editor::EditorMainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Editor::EditorMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Editor__EditorMainWindow))
	return static_cast<void*>(const_cast< EditorMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RainbruRPG::Editor::EditorMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: scrollLog(); break;
        case 1: showScriptEditor(); break;
        case 2: about(); break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
