/****************************************************************************
** Meta object code from reading C++ file 'dummyPlugin.h'
**
** Created: Tue Mar 10 18:18:50 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dummyPlugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dummyPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dummyPlugin[] = {

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

static const char qt_meta_stringdata_dummyPlugin[] = {
    "dummyPlugin\0"
};

const QMetaObject dummyPlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_dummyPlugin,
      qt_meta_data_dummyPlugin, 0 }
};

const QMetaObject *dummyPlugin::metaObject() const
{
    return &staticMetaObject;
}

void *dummyPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dummyPlugin))
        return static_cast<void*>(const_cast< dummyPlugin*>(this));
    if (!strcmp(_clname, "pluginInterface"))
        return static_cast< pluginInterface*>(const_cast< dummyPlugin*>(this));
    if (!strcmp(_clname, "eu.edujudge.eews.pluginInterface/1.0"))
        return static_cast< pluginInterface*>(const_cast< dummyPlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int dummyPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
