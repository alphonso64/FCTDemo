/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "CusRectListChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "QMap<int,CusRect>"
QT_MOC_LITERAL(4, 49, 3), // "map"
QT_MOC_LITERAL(5, 53, 17), // "QMap<int,QString>"
QT_MOC_LITERAL(6, 71, 9), // "actionMap"
QT_MOC_LITERAL(7, 81, 8), // "AddClick"
QT_MOC_LITERAL(8, 90, 4), // "flag"
QT_MOC_LITERAL(9, 95, 8), // "DelClick"
QT_MOC_LITERAL(10, 104, 10), // "MatchClick"
QT_MOC_LITERAL(11, 115, 10), // "RecogClick"
QT_MOC_LITERAL(12, 126, 11), // "detectClick"
QT_MOC_LITERAL(13, 138, 13), // "ItemActivated"
QT_MOC_LITERAL(14, 152, 3), // "row"
QT_MOC_LITERAL(15, 156, 3), // "col"
QT_MOC_LITERAL(16, 160, 12), // "proecssBlock"
QT_MOC_LITERAL(17, 173, 1), // "n"
QT_MOC_LITERAL(18, 175, 6), // "capimg"
QT_MOC_LITERAL(19, 182, 7), // "saveimg"
QT_MOC_LITERAL(20, 190, 10), // "camInitRdy"
QT_MOC_LITERAL(21, 201, 9), // "camSelect"
QT_MOC_LITERAL(22, 211, 24), // "on_savePicButton_clicked"
QT_MOC_LITERAL(23, 236, 25), // "on_saveFileButton_clicked"
QT_MOC_LITERAL(24, 262, 25) // "on_loadFileButton_clicked"

    },
    "MainWindow\0CusRectListChanged\0\0"
    "QMap<int,CusRect>\0map\0QMap<int,QString>\0"
    "actionMap\0AddClick\0flag\0DelClick\0"
    "MatchClick\0RecogClick\0detectClick\0"
    "ItemActivated\0row\0col\0proecssBlock\0n\0"
    "capimg\0saveimg\0camInitRdy\0camSelect\0"
    "on_savePicButton_clicked\0"
    "on_saveFileButton_clicked\0"
    "on_loadFileButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x08 /* Private */,
       7,    1,   94,    2, 0x08 /* Private */,
       9,    0,   97,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    0,   99,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    2,  101,    2, 0x08 /* Private */,
      16,    1,  106,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,
      19,    0,  110,    2, 0x08 /* Private */,
      20,    1,  111,    2, 0x08 /* Private */,
      21,    1,  114,    2, 0x08 /* Private */,
      22,    0,  117,    2, 0x08 /* Private */,
      23,    0,  118,    2, 0x08 /* Private */,
      24,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CusRectListChanged((*reinterpret_cast< QMap<int,CusRect>(*)>(_a[1])),(*reinterpret_cast< QMap<int,QString>(*)>(_a[2]))); break;
        case 1: _t->AddClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->DelClick(); break;
        case 3: _t->MatchClick(); break;
        case 4: _t->RecogClick(); break;
        case 5: _t->detectClick(); break;
        case 6: _t->ItemActivated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->proecssBlock((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->capimg(); break;
        case 9: _t->saveimg(); break;
        case 10: _t->camInitRdy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->camSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_savePicButton_clicked(); break;
        case 13: _t->on_saveFileButton_clicked(); break;
        case 14: _t->on_loadFileButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
