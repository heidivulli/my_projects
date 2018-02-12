/****************************************************************************
** Meta object code from reading C++ file 'kaupunki.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../24/OmaPuoli/kaupunki.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kaupunki.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OmaPuoli__Kaupunki_t {
    QByteArrayData data[4];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OmaPuoli__Kaupunki_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OmaPuoli__Kaupunki_t qt_meta_stringdata_OmaPuoli__Kaupunki = {
    {
QT_MOC_LITERAL(0, 0, 18), // "OmaPuoli::Kaupunki"
QT_MOC_LITERAL(1, 19, 16), // "lisaa_vihollinen"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12) // "kasvataAikaa"

    },
    "OmaPuoli::Kaupunki\0lisaa_vihollinen\0"
    "\0kasvataAikaa"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OmaPuoli__Kaupunki[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OmaPuoli::Kaupunki::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Kaupunki *_t = static_cast<Kaupunki *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lisaa_vihollinen(); break;
        case 1: _t->kasvataAikaa(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject OmaPuoli::Kaupunki::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OmaPuoli__Kaupunki.data,
      qt_meta_data_OmaPuoli__Kaupunki,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OmaPuoli::Kaupunki::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OmaPuoli::Kaupunki::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OmaPuoli__Kaupunki.stringdata0))
        return static_cast<void*>(const_cast< Kaupunki*>(this));
    if (!strcmp(_clname, "Rajapinta::KaupunkiRP"))
        return static_cast< Rajapinta::KaupunkiRP*>(const_cast< Kaupunki*>(this));
    return QObject::qt_metacast(_clname);
}

int OmaPuoli::Kaupunki::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
