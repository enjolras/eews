/****************************************************************************
** Meta object code from reading C++ file 'settingsGod.h'
**
** Created: Tue Mar 10 18:18:44 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "settingsGod.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsGod.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_settingsGod[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_settingsGod[] = {
    "settingsGod\0"
};

const QMetaObject settingsGod::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_settingsGod,
      qt_meta_data_settingsGod, 0 }
};

const QMetaObject *settingsGod::metaObject() const
{
    return &staticMetaObject;
}

void *settingsGod::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_settingsGod))
        return static_cast<void*>(const_cast< settingsGod*>(this));
    return QObject::qt_metacast(_clname);
}

int settingsGod::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
