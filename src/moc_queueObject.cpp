/****************************************************************************
** Meta object code from reading C++ file 'queueObject.h'
**
** Created: Tue Mar 10 18:18:37 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "queueObject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'queueObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_queueObject[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   13,   12,   12, 0x0a,
      47,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_queueObject[] = {
    "queueObject\0\0record\0addSubmission(QSqlRecord&)\0"
    "calculatePriority()\0"
};

const QMetaObject queueObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_queueObject,
      qt_meta_data_queueObject, 0 }
};

const QMetaObject *queueObject::metaObject() const
{
    return &staticMetaObject;
}

void *queueObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_queueObject))
        return static_cast<void*>(const_cast< queueObject*>(this));
    return QObject::qt_metacast(_clname);
}

int queueObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addSubmission((*reinterpret_cast< QSqlRecord(*)>(_a[1]))); break;
        case 1: calculatePriority(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE