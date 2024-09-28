/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../project_client2/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[16];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 16), // "register_clicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "login_clicked"
QT_MOC_LITERAL(4, 39, 10), // "ready_read"
QT_MOC_LITERAL(5, 50, 18), // "user_register_back"
QT_MOC_LITERAL(6, 69, 5), // "Pack&"
QT_MOC_LITERAL(7, 75, 4), // "pack"
QT_MOC_LITERAL(8, 80, 15), // "user_login_back"
QT_MOC_LITERAL(9, 96, 20), // "user_createroom_back"
QT_MOC_LITERAL(10, 117, 21), // "user_get_newroom_back"
QT_MOC_LITERAL(11, 139, 19), // "user_flushroom_back"
QT_MOC_LITERAL(12, 159, 18), // "user_joinroom_back"
QT_MOC_LITERAL(13, 178, 21), // "user_get_newuser_back"
QT_MOC_LITERAL(14, 200, 26), // "user_flush_otherusers_back"
QT_MOC_LITERAL(15, 227, 20) // "user_deleteuser_back"

    },
    "Widget\0register_clicked\0\0login_clicked\0"
    "ready_read\0user_register_back\0Pack&\0"
    "pack\0user_login_back\0user_createroom_back\0"
    "user_get_newroom_back\0user_flushroom_back\0"
    "user_joinroom_back\0user_get_newuser_back\0"
    "user_flush_otherusers_back\0"
    "user_deleteuser_back"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    1,   77,    2, 0x0a /* Public */,
       8,    1,   80,    2, 0x0a /* Public */,
       9,    1,   83,    2, 0x0a /* Public */,
      10,    1,   86,    2, 0x0a /* Public */,
      11,    1,   89,    2, 0x0a /* Public */,
      12,    1,   92,    2, 0x0a /* Public */,
      13,    1,   95,    2, 0x0a /* Public */,
      14,    1,   98,    2, 0x0a /* Public */,
      15,    1,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->register_clicked(); break;
        case 1: _t->login_clicked(); break;
        case 2: _t->ready_read(); break;
        case 3: _t->user_register_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        case 4: _t->user_login_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        case 5: _t->user_createroom_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        case 6: _t->user_get_newroom_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        case 7: _t->user_flushroom_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        case 8: _t->user_joinroom_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        case 9: _t->user_get_newuser_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        case 10: _t->user_flush_otherusers_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        case 11: _t->user_deleteuser_back((*reinterpret_cast< Pack(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
