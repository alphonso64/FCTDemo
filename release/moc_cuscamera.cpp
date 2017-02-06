/****************************************************************************
** Meta object code from reading C++ file 'cuscamera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cuscamera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cuscamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CusCamera_t {
    QByteArrayData data[5];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CusCamera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CusCamera_t qt_meta_stringdata_CusCamera = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CusCamera"
QT_MOC_LITERAL(1, 10, 6), // "capRdy"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 10), // "camInitRdy"
QT_MOC_LITERAL(4, 29, 7) // "timeOut"

    },
    "CusCamera\0capRdy\0\0camInitRdy\0timeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CusCamera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CusCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CusCamera *_t = static_cast<CusCamera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->capRdy(); break;
        case 1: _t->camInitRdy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->timeOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CusCamera::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CusCamera::capRdy)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CusCamera::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CusCamera::camInitRdy)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CusCamera::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CusCamera.data,
      qt_meta_data_CusCamera,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CusCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CusCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CusCamera.stringdata0))
        return static_cast<void*>(const_cast< CusCamera*>(this));
    return QThread::qt_metacast(_clname);
}

int CusCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CusCamera::capRdy()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void CusCamera::camInitRdy(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
