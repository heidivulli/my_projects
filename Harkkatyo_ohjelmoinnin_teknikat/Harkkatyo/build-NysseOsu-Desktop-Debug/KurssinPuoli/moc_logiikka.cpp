/****************************************************************************
** Meta object code from reading C++ file 'logiikka.hh'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../24/KurssinPuoli/logiikka.hh"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logiikka.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KurssinPuoli__Logiikka_t {
    QByteArrayData data[9];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KurssinPuoli__Logiikka_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KurssinPuoli__Logiikka_t qt_meta_stringdata_KurssinPuoli__Logiikka = {
    {
QT_MOC_LITERAL(0, 0, 22), // "KurssinPuoli::Logiikka"
QT_MOC_LITERAL(1, 23, 5), // "etene"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "konffiMuuttunut"
QT_MOC_LITERAL(4, 46, 4), // "aika"
QT_MOC_LITERAL(5, 51, 5), // "debug"
QT_MOC_LITERAL(6, 57, 12), // "kasvataAikaa"
QT_MOC_LITERAL(7, 70, 17), // "lisaaUusiaBusseja"
QT_MOC_LITERAL(8, 88, 21) // "lisaaUusiaMatkustajia"

    },
    "KurssinPuoli::Logiikka\0etene\0\0"
    "konffiMuuttunut\0aika\0debug\0kasvataAikaa\0"
    "lisaaUusiaBusseja\0lisaaUusiaMatkustajia"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KurssinPuoli__Logiikka[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    2,   40,    2, 0x0a /* Public */,
       6,    0,   45,    2, 0x0a /* Public */,
       7,    0,   46,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QTime, QMetaType::Bool,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KurssinPuoli::Logiikka::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Logiikka *_t = static_cast<Logiikka *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->etene(); break;
        case 1: _t->konffiMuuttunut((*reinterpret_cast< QTime(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->kasvataAikaa(); break;
        case 3: _t->lisaaUusiaBusseja(); break;
        case 4: _t->lisaaUusiaMatkustajia(); break;
        default: ;
        }
    }
}

const QMetaObject KurssinPuoli::Logiikka::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KurssinPuoli__Logiikka.data,
      qt_meta_data_KurssinPuoli__Logiikka,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KurssinPuoli::Logiikka::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KurssinPuoli::Logiikka::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KurssinPuoli__Logiikka.stringdata0))
        return static_cast<void*>(const_cast< Logiikka*>(this));
    return QObject::qt_metacast(_clname);
}

int KurssinPuoli::Logiikka::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
