/****************************************************************************
** Meta object code from reading C++ file 'dlg_normal_para.h'
**
** Created: Wed Oct 4 15:39:25 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UI/dlg_normal_para.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlg_normal_para.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NormalParaDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   14,   15,   14, 0x08,
      39,   34,   14,   14, 0x08,
      63,   34,   14,   14, 0x08,
      87,   34,   14,   14, 0x08,
     106,   34,   14,   14, 0x08,
     123,   34,   14,   14, 0x08,
     135,   34,   14,   14, 0x08,
     148,   14,   14,   14, 0x08,
     168,   14,   14,   14, 0x08,
     191,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NormalParaDlg[] = {
    "NormalParaDlg\0\0bool\0initWidgets()\0"
    "_val\0getRadiusValues(double)\0"
    "getPcaThreshold(double)\0getIterateNum(int)\0"
    "getSigma(double)\0getKNN(int)\0isAPCA(bool)\0"
    "reorientateNormal()\0applyNormalSmoothing()\0"
    "applyPCANormal()\0"
};

void NormalParaDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NormalParaDlg *_t = static_cast<NormalParaDlg *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->initWidgets();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: _t->getRadiusValues((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->getPcaThreshold((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->getIterateNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->getSigma((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->getKNN((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->isAPCA((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->reorientateNormal(); break;
        case 8: _t->applyNormalSmoothing(); break;
        case 9: _t->applyPCANormal(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NormalParaDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NormalParaDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_NormalParaDlg,
      qt_meta_data_NormalParaDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NormalParaDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NormalParaDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NormalParaDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NormalParaDlg))
        return static_cast<void*>(const_cast< NormalParaDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int NormalParaDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
