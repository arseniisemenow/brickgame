/****************************************************************************
** Meta object code from reading C++ file 'view_tab_switcher.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/gui/desktop/View/view_tab_switcher/view_tab_switcher.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view_tab_switcher.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS = QtMocHelpers::stringData(
    "s21::ViewTabSwitcher",
    "SetExpressionCurrentIndex",
    "",
    "SetGraphCurrentIndex",
    "SetCreditCurrentIndex",
    "SetDepositCurrentIndex",
    "InitStackedWidgetIndex",
    "SetStyle",
    "QPushButton*"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[21];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[22];
    char stringdata5[23];
    char stringdata6[23];
    char stringdata7[9];
    char stringdata8[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS_t qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS = {
    {
        QT_MOC_LITERAL(0, 20),  // "s21::ViewTabSwitcher"
        QT_MOC_LITERAL(21, 25),  // "SetExpressionCurrentIndex"
        QT_MOC_LITERAL(47, 0),  // ""
        QT_MOC_LITERAL(48, 20),  // "SetGraphCurrentIndex"
        QT_MOC_LITERAL(69, 21),  // "SetCreditCurrentIndex"
        QT_MOC_LITERAL(91, 22),  // "SetDepositCurrentIndex"
        QT_MOC_LITERAL(114, 22),  // "InitStackedWidgetIndex"
        QT_MOC_LITERAL(137, 8),  // "SetStyle"
        QT_MOC_LITERAL(146, 12)   // "QPushButton*"
    },
    "s21::ViewTabSwitcher",
    "SetExpressionCurrentIndex",
    "",
    "SetGraphCurrentIndex",
    "SetCreditCurrentIndex",
    "SetDepositCurrentIndex",
    "InitStackedWidgetIndex",
    "SetStyle",
    "QPushButton*"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSs21SCOPEViewTabSwitcherENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    0,   52,    2, 0x0a,    3 /* Public */,
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    0,   54,    2, 0x0a,    5 /* Public */,
       7,    1,   55,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject s21::ViewTabSwitcher::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSs21SCOPEViewTabSwitcherENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ViewTabSwitcher, std::true_type>,
        // method 'SetExpressionCurrentIndex'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SetGraphCurrentIndex'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SetCreditCurrentIndex'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SetDepositCurrentIndex'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'InitStackedWidgetIndex'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SetStyle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPushButton *, std::false_type>
    >,
    nullptr
} };

void s21::ViewTabSwitcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ViewTabSwitcher *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SetExpressionCurrentIndex(); break;
        case 1: _t->SetGraphCurrentIndex(); break;
        case 2: _t->SetCreditCurrentIndex(); break;
        case 3: _t->SetDepositCurrentIndex(); break;
        case 4: _t->InitStackedWidgetIndex(); break;
        case 5: _t->SetStyle((*reinterpret_cast< std::add_pointer_t<QPushButton*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *s21::ViewTabSwitcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *s21::ViewTabSwitcher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSs21SCOPEViewTabSwitcherENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int s21::ViewTabSwitcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
