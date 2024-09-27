/****************************************************************************
** Meta object code from reading C++ file 'View.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/gui/desktop/View/View.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'View.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
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
struct qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS = QtMocHelpers::stringData(
    "s21::View",
    "SignalMoveUp",
    "",
    "SignalMoveDown",
    "SignalMoveLeft",
    "SignalMoveRight",
    "SignalEscapeButton",
    "SignalEnterButton",
    "SignalPauseButton",
    "SignalNoneButton",
    "StartTetrisGame",
    "StartSnakeGame"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[10];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[15];
    char stringdata5[16];
    char stringdata6[19];
    char stringdata7[18];
    char stringdata8[18];
    char stringdata9[17];
    char stringdata10[16];
    char stringdata11[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS_t qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "s21::View"
        QT_MOC_LITERAL(10, 12),  // "SignalMoveUp"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 14),  // "SignalMoveDown"
        QT_MOC_LITERAL(39, 14),  // "SignalMoveLeft"
        QT_MOC_LITERAL(54, 15),  // "SignalMoveRight"
        QT_MOC_LITERAL(70, 18),  // "SignalEscapeButton"
        QT_MOC_LITERAL(89, 17),  // "SignalEnterButton"
        QT_MOC_LITERAL(107, 17),  // "SignalPauseButton"
        QT_MOC_LITERAL(125, 16),  // "SignalNoneButton"
        QT_MOC_LITERAL(142, 15),  // "StartTetrisGame"
        QT_MOC_LITERAL(158, 14)   // "StartSnakeGame"
    },
    "s21::View",
    "SignalMoveUp",
    "",
    "SignalMoveDown",
    "SignalMoveLeft",
    "SignalMoveRight",
    "SignalEscapeButton",
    "SignalEnterButton",
    "SignalPauseButton",
    "SignalNoneButton",
    "StartTetrisGame",
    "StartSnakeGame"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSs21SCOPEViewENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    1 /* Public */,
       3,    0,   75,    2, 0x06,    2 /* Public */,
       4,    0,   76,    2, 0x06,    3 /* Public */,
       5,    0,   77,    2, 0x06,    4 /* Public */,
       6,    0,   78,    2, 0x06,    5 /* Public */,
       7,    0,   79,    2, 0x06,    6 /* Public */,
       8,    0,   80,    2, 0x06,    7 /* Public */,
       9,    0,   81,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,   82,    2, 0x08,    9 /* Private */,
      11,    0,   83,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject s21::View::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSs21SCOPEViewENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<View, std::true_type>,
        // method 'SignalMoveUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SignalMoveDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SignalMoveLeft'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SignalMoveRight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SignalEscapeButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SignalEnterButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SignalPauseButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SignalNoneButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'StartTetrisGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'StartSnakeGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void s21::View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<View *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalMoveUp(); break;
        case 1: _t->SignalMoveDown(); break;
        case 2: _t->SignalMoveLeft(); break;
        case 3: _t->SignalMoveRight(); break;
        case 4: _t->SignalEscapeButton(); break;
        case 5: _t->SignalEnterButton(); break;
        case 6: _t->SignalPauseButton(); break;
        case 7: _t->SignalNoneButton(); break;
        case 8: _t->StartTetrisGame(); break;
        case 9: _t->StartSnakeGame(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (View::*)();
            if (_t _q_method = &View::SignalMoveUp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (_t _q_method = &View::SignalMoveDown; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (_t _q_method = &View::SignalMoveLeft; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (_t _q_method = &View::SignalMoveRight; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (_t _q_method = &View::SignalEscapeButton; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (_t _q_method = &View::SignalEnterButton; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (_t _q_method = &View::SignalPauseButton; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (_t _q_method = &View::SignalNoneButton; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *s21::View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *s21::View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSs21SCOPEViewENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int s21::View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void s21::View::SignalMoveUp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void s21::View::SignalMoveDown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void s21::View::SignalMoveLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void s21::View::SignalMoveRight()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void s21::View::SignalEscapeButton()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void s21::View::SignalEnterButton()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void s21::View::SignalPauseButton()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void s21::View::SignalNoneButton()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
