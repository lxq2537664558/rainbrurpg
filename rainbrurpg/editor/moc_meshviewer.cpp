/****************************************************************************
** Meta object code from reading C++ file 'meshviewer.h'
**
** Created: Thu Jan 24 15:13:26 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "meshviewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'meshviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RainbruRPG__Editor__MeshViewer[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      32,   31,   31,   31, 0x05,
      52,   31,   31,   31, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Editor__MeshViewer[] = {
    "RainbruRPG::Editor::MeshViewer\0\0"
    "updateFpsCount(int)\0updateTriCount(int)\0"
};

const QMetaObject RainbruRPG::Editor::MeshViewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RainbruRPG__Editor__MeshViewer,
      qt_meta_data_RainbruRPG__Editor__MeshViewer, 0 }
};

const QMetaObject *RainbruRPG::Editor::MeshViewer::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Editor::MeshViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Editor__MeshViewer))
	return static_cast<void*>(const_cast< MeshViewer*>(this));
    return QWidget::qt_metacast(_clname);
}

int RainbruRPG::Editor::MeshViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateFpsCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: updateTriCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void RainbruRPG::Editor::MeshViewer::updateFpsCount(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RainbruRPG::Editor::MeshViewer::updateTriCount(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
