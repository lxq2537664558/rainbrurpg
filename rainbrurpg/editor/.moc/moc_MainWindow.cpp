/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Thu Dec 28 13:18:32 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x0a,
      38,   11,   11,   11, 0x08,
      50,   11,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      85,   11,   11,   11, 0x08,
     100,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     139,   11,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     164,   11,   11,   11, 0x08,
     178,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     225,   11,   11,   11, 0x08,
     242,   11,   11,   11, 0x08,
     263,   11,   11,   11, 0x08,
     275,   11,   11,   11, 0x08,
     297,   11,   11,   11, 0x08,
     314,   11,   11,   11, 0x08,
     328,   11,   11,   11, 0x08,
     345,   11,   11,   11, 0x08,
     367,   11,   11,   11, 0x08,
     384,   11,   11,   11, 0x08,
     404,   11,   11,   11, 0x08,
     420,   11,   11,   11, 0x08,
     437,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0meshName\0loadObj(QString)\0scrollLog()\0addObj()\0"
    "setFog(int)\0setFogColor()\0setShadow(int)\0setBackgroundColor()\0"
    "setAmbientLight()\0addLight()\0modifyLight()\0deleteLight()\0"
    "setDiffuseLightColor()\0setSpecularLightColor()\0createNewLight()\0"
    "setRenderDetail(int)\0setLOD(int)\0setBoundingBoxes(int)\0"
    "setSkeleton(int)\0setMaterial()\0updateMaterial()\0"
    "setAnimation(QString)\0setAnimLoop(int)\0setAnimEnabled(int)\0"
    "setScriptPath()\0setTexturePath()\0about()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
	return static_cast<void*>(const_cast<MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadObj((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: scrollLog(); break;
        case 2: addObj(); break;
        case 3: setFog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setFogColor(); break;
        case 5: setShadow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setBackgroundColor(); break;
        case 7: setAmbientLight(); break;
        case 8: addLight(); break;
        case 9: modifyLight(); break;
        case 10: deleteLight(); break;
        case 11: setDiffuseLightColor(); break;
        case 12: setSpecularLightColor(); break;
        case 13: createNewLight(); break;
        case 14: setRenderDetail((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: setLOD((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: setBoundingBoxes((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: setSkeleton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: setMaterial(); break;
        case 19: updateMaterial(); break;
        case 20: setAnimation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: setAnimLoop((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: setAnimEnabled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: setScriptPath(); break;
        case 24: setTexturePath(); break;
        case 25: about(); break;
        }
        _id -= 26;
    }
    return _id;
}
