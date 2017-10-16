/****************************************************************************
** Meta object code from reading C++ file 'dlg_upsampling_para.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/UI/dlg_upsampling_para.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlg_upsampling_para.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UpsamplingParaDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   18,   19,   18, 0x08,
      38,   18,   18,   18, 0x08,
      50,   18,   18,   18, 0x08,
      71,   66,   18,   18, 0x08,
      95,   66,   18,   18, 0x08,
     112,   66,   18,   18, 0x08,
     137,   66,   18,   18, 0x08,
     149,   66,   18,   18, 0x08,
     170,   66,   18,   18, 0x08,
     201,   66,   18,   18, 0x08,
     231,   66,   18,   18, 0x08,
     256,   66,   18,   18, 0x08,
     278,   66,   18,   18, 0x08,
     298,   66,   18,   18, 0x08,
     315,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UpsamplingParaDlg[] = {
    "UpsamplingParaDlg\0\0bool\0initWidgets()\0"
    "runAddPts()\0runProjection()\0_val\0"
    "getRadiusValues(double)\0getSigma(double)\0"
    "setEdgeParameter(double)\0setNum(int)\0"
    "setThreshold(double)\0"
    "setUsingThresholdProcess(bool)\0"
    "getSnapShotResolution(double)\0"
    "getSnapShotIndex(double)\0getBeginIndex(double)\0"
    "getEndIndex(double)\0getSpeed(double)\0"
    "applyPlayVideo()\0"
};

void UpsamplingParaDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UpsamplingParaDlg *_t = static_cast<UpsamplingParaDlg *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->initWidgets();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: _t->runAddPts(); break;
        case 2: _t->runProjection(); break;
        case 3: _t->getRadiusValues((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->getSigma((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->setEdgeParameter((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->setNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setThreshold((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setUsingThresholdProcess((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->getSnapShotResolution((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->getSnapShotIndex((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->getBeginIndex((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->getEndIndex((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->getSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->applyPlayVideo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UpsamplingParaDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UpsamplingParaDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_UpsamplingParaDlg,
      qt_meta_data_UpsamplingParaDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UpsamplingParaDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UpsamplingParaDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UpsamplingParaDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UpsamplingParaDlg))
        return static_cast<void*>(const_cast< UpsamplingParaDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int UpsamplingParaDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
