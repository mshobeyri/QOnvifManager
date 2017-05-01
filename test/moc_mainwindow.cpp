/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[396];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "onNewDeviceFinded"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "QOnvifDevice*"
QT_MOC_LITERAL(4, 44, 7), // "_device"
QT_MOC_LITERAL(5, 52, 21), // "on_btnRefresh_clicked"
QT_MOC_LITERAL(6, 74, 41), // "on_cmbDevicesComboBox_current..."
QT_MOC_LITERAL(7, 116, 5), // "index"
QT_MOC_LITERAL(8, 122, 25), // "on_btnRefreshData_clicked"
QT_MOC_LITERAL(9, 148, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(10, 173, 28), // "on_btnGetDataAndTime_clicked"
QT_MOC_LITERAL(11, 202, 28), // "on_btsSetDateAndTime_clicked"
QT_MOC_LITERAL(12, 231, 26), // "on_setUsernamePass_clicked"
QT_MOC_LITERAL(13, 258, 23), // "on_btnSetScopes_clicked"
QT_MOC_LITERAL(14, 282, 20), // "on_btngoHome_clicked"
QT_MOC_LITERAL(15, 303, 21), // "on_btnsetHome_clicked"
QT_MOC_LITERAL(16, 325, 29), // "on_btnrefreshPresents_clicked"
QT_MOC_LITERAL(17, 355, 19), // "on_btnRight_pressed"
QT_MOC_LITERAL(18, 375, 20) // "on_btnRight_released"

    },
    "MainWindow\0onNewDeviceFinded\0\0"
    "QOnvifDevice*\0_device\0on_btnRefresh_clicked\0"
    "on_cmbDevicesComboBox_currentIndexChanged\0"
    "index\0on_btnRefreshData_clicked\0"
    "on_actionAbout_triggered\0"
    "on_btnGetDataAndTime_clicked\0"
    "on_btsSetDateAndTime_clicked\0"
    "on_setUsernamePass_clicked\0"
    "on_btnSetScopes_clicked\0on_btngoHome_clicked\0"
    "on_btnsetHome_clicked\0"
    "on_btnrefreshPresents_clicked\0"
    "on_btnRight_pressed\0on_btnRight_released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    1,   88,    2, 0x08 /* Private */,
       8,    0,   91,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onNewDeviceFinded((*reinterpret_cast< QOnvifDevice*(*)>(_a[1]))); break;
        case 1: _t->on_btnRefresh_clicked(); break;
        case 2: _t->on_cmbDevicesComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_btnRefreshData_clicked(); break;
        case 4: _t->on_actionAbout_triggered(); break;
        case 5: _t->on_btnGetDataAndTime_clicked(); break;
        case 6: _t->on_btsSetDateAndTime_clicked(); break;
        case 7: _t->on_setUsernamePass_clicked(); break;
        case 8: _t->on_btnSetScopes_clicked(); break;
        case 9: _t->on_btngoHome_clicked(); break;
        case 10: _t->on_btnsetHome_clicked(); break;
        case 11: _t->on_btnrefreshPresents_clicked(); break;
        case 12: _t->on_btnRight_pressed(); break;
        case 13: _t->on_btnRight_released(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
