/****************************************************************************
** Meta object code from reading C++ file 'meshviewerstats.h'
**
** Created: Sun Feb 4 23:49:32 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "meshviewerstats.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'meshviewerstats.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_RainbruRPG__Editor__MeshViewerStats[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      37,   36,   36,   36, 0x0a,
      49,   36,   36,   36, 0x0a,
      61,   36,   36,   36, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RainbruRPG__Editor__MeshViewerStats[] = {
    "RainbruRPG::Editor::MeshViewerStats\0\0setFps(int)\0setTri(int)\0"
    "updateCamStats()\0"
};

const QMetaObject RainbruRPG::Editor::MeshViewerStats::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RainbruRPG__Editor__MeshViewerStats,
      qt_meta_data_RainbruRPG__Editor__MeshViewerStats, 0 }
};

const QMetaObject *RainbruRPG::Editor::MeshViewerStats::metaObject() const
{
    return &staticMetaObject;
}

void *RainbruRPG::Editor::MeshViewerStats::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RainbruRPG__Editor__MeshViewerStats))
	return static_cast<void*>(const_cast<MeshViewerStats*>(this));
    return QWidget::qt_metacast(_clname);
}

int RainbruRPG::Editor::MeshViewerStats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setFps((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setTri((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: updateCamStats(); break;
        }
        _id -= 3;
    }
    return _id;
}
