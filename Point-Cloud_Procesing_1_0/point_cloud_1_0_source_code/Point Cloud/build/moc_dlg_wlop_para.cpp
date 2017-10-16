/****************************************************************************
** Meta object code from reading C++ file 'dlg_wlop_para.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/UI/dlg_wlop_para.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlg_wlop_para.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WlopParaDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   12,   32,   12, 0x08,
      56,   51,   12,   12, 0x08,
      80,   51,   12,   12, 0x08,
      98,   51,   12,   12, 0x08,
     116,   51,   12,   12, 0x08,
     129,   51,   12,   12, 0x08,
     143,   51,   12,   12, 0x08,
     159,   51,   12,   12, 0x08,
     171,   12,   12,   12, 0x08,
     183,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WlopParaDlg[] = {
    "WlopParaDlg\0\0parameterChanged()\0bool\0"
    "initWidgets()\0_val\0getRadiusValues(double)\0"
    "getRepPow(double)\0getFitPow(double)\0"
    "getIter(int)\0getMu(double)\0isDensity(bool)\0"
    "isPca(bool)\0applyWlop()\0applyAnisotropicLop()\0"
};

void WlopParaDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WlopParaDlg *_t = static_cast<WlopParaDlg *>(_o);
        switch (_id) {
        case 0: _t->parameterChanged(); break;
        case 1: { bool _r = _t->initWidgets();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->getRadiusValues((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->getRepPow((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->getFitPow((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->getIter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->getMu((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->isDensity((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->isPca((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->applyWlop(); break;
        case 10: _t->applyAnisotropicLop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WlopParaDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WlopParaDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_WlopParaDlg,
      qt_meta_data_WlopParaDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WlopParaDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WlopParaDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WlopParaDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WlopParaDlg))
        return static_cast<void*>(const_cast< WlopParaDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int WlopParaDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void WlopParaDlg::parameterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
