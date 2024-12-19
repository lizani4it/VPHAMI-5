/****************************************************************************
** Meta object code from reading C++ file 'todolistwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../todolistwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'todolistwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASStodolistwindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASStodolistwindowENDCLASS = QtMocHelpers::stringData(
    "todolistwindow",
    "toggleEditMode",
    "",
    "saveChanges",
    "checkTimeAndNotify",
    "onTimeEdited",
    "row",
    "column",
    "onBackButtonClicked",
    "updateEditModeLabel",
    "resizeEvent",
    "QResizeEvent*",
    "event",
    "showContextMenu",
    "pos",
    "addRow",
    "removeRows"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASStodolistwindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    0,   75,    2, 0x08,    2 /* Private */,
       4,    0,   76,    2, 0x08,    3 /* Private */,
       5,    2,   77,    2, 0x08,    4 /* Private */,
       8,    0,   82,    2, 0x08,    7 /* Private */,
       9,    0,   83,    2, 0x08,    8 /* Private */,
      10,    1,   84,    2, 0x08,    9 /* Private */,
      13,    1,   87,    2, 0x08,   11 /* Private */,
      15,    0,   90,    2, 0x08,   13 /* Private */,
      16,    0,   91,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QPoint,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject todolistwindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASStodolistwindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASStodolistwindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASStodolistwindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<todolistwindow, std::true_type>,
        // method 'toggleEditMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveChanges'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkTimeAndNotify'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTimeEdited'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onBackButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateEditModeLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resizeEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QResizeEvent *, std::false_type>,
        // method 'showContextMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'addRow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeRows'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void todolistwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<todolistwindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->toggleEditMode(); break;
        case 1: _t->saveChanges(); break;
        case 2: _t->checkTimeAndNotify(); break;
        case 3: _t->onTimeEdited((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->onBackButtonClicked(); break;
        case 5: _t->updateEditModeLabel(); break;
        case 6: _t->resizeEvent((*reinterpret_cast< std::add_pointer_t<QResizeEvent*>>(_a[1]))); break;
        case 7: _t->showContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 8: _t->addRow(); break;
        case 9: _t->removeRows(); break;
        default: ;
        }
    }
}

const QMetaObject *todolistwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *todolistwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASStodolistwindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int todolistwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
