/****************************************************************************
** Meta object code from reading C++ file 'dlg_skeleton_para.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/UI/dlg_skeleton_para.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlg_skeleton_para.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SkeletonParaDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      44,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   16,   36,   16, 0x08,
      60,   55,   16,   16, 0x08,
      84,   55,   16,   16, 0x08,
     114,   55,   16,   16, 0x08,
     138,   55,   16,   16, 0x08,
     167,   55,   16,   16, 0x08,
     192,   55,   16,   16, 0x08,
     221,   55,   16,   16, 0x08,
     247,   55,   16,   16, 0x08,
     276,   55,   16,   16, 0x08,
     305,   55,   16,   16, 0x08,
     334,   55,   16,   16, 0x08,
     358,   55,   16,   16, 0x08,
     378,   55,   16,   16, 0x08,
     406,   55,   16,   16, 0x08,
     433,   55,   16,   16, 0x08,
     468,   55,   16,   16, 0x08,
     493,   55,   16,   16, 0x08,
     523,   55,   16,   16, 0x08,
     547,   16,   16,   16, 0x08,
     564,   55,   16,   16, 0x08,
     576,   55,   16,   16, 0x08,
     593,   55,   16,   16, 0x08,
     622,   55,   16,   16, 0x08,
     649,   55,   16,   16, 0x08,
     677,   16,   16,   16, 0x08,
     691,   16,   16,   16, 0x08,
     710,   16,   16,   16, 0x08,
     725,   16,   16,   16, 0x08,
     745,   16,   16,   16, 0x08,
     771,   16,   16,   16, 0x08,
     789,   16,   16,   16, 0x08,
     812,   16,   16,   16, 0x08,
     833,   16,   16,   16, 0x08,
     858,   16,   16,   16, 0x08,
     886,   55,   16,   16, 0x08,
     919,   55,   16,   16, 0x08,
     949,   55,   16,   16, 0x08,
     980,   55,   16,   16, 0x08,
    1006,   55,   16,   16, 0x08,
    1034,   55,   16,   16, 0x08,
    1058,   55,   16,   16, 0x08,
    1086,   55,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SkeletonParaDlg[] = {
    "SkeletonParaDlg\0\0parameterChanged()\0"
    "bool\0initWidgets()\0_val\0getRadiusValues(double)\0"
    "getLocalDensityRadius(double)\0"
    "getPcaThreshold(double)\0"
    "getFixOriginalWeight(double)\0"
    "getHGaussianPara(double)\0"
    "getStopAndGrowRadius(double)\0"
    "getMaxIterateTime(double)\0"
    "getBranchSearchSigma(double)\0"
    "getBranchSearchDist1(double)\0"
    "getBranchSearchDist2(double)\0"
    "getTooCloseDist(double)\0getSigmaKnn(double)\0"
    "getAcceptBranchSize(double)\0"
    "getBranchMergeDist(double)\0"
    "getCleanNearbyBranchesDist(double)\0"
    "getSegmentLength(double)\0"
    "getFollowSampleRadius(double)\0"
    "getCombineAngle(double)\0guessParaMeter()\0"
    "getKNN(int)\0getClickNum(int)\0"
    "getFollowSampleAngle(double)\0"
    "getGrowAcceptSigma(double)\0"
    "getKeepVirtualAngle(double)\0updatePanel()\0"
    "applyFixOriginal()\0applyAutoRun()\0"
    "applyDownsampling()\0applyAutoRunUntilGrowth()\0"
    "applyAllSegment()\0applyAutoWlopOneStep()\0"
    "applyDetectFeature()\0applySearchNewBranches()\0"
    "applyCleanAndUpdateRadius()\0"
    "getSkeletonInitialRadius(double)\0"
    "getSkeletonGrowthRate(double)\0"
    "getSkeletonRepulsionMu(double)\0"
    "getInitRadiusPara(double)\0"
    "getInitSampleNumber(double)\0"
    "useDensityCompute(bool)\0"
    "useRecenteringCompute(bool)\0"
    "needRefinement(bool)\0"
};

void SkeletonParaDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SkeletonParaDlg *_t = static_cast<SkeletonParaDlg *>(_o);
        switch (_id) {
        case 0: _t->parameterChanged(); break;
        case 1: { bool _r = _t->initWidgets();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->getRadiusValues((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->getLocalDensityRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->getPcaThreshold((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->getFixOriginalWeight((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->getHGaussianPara((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->getStopAndGrowRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->getMaxIterateTime((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->getBranchSearchSigma((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->getBranchSearchDist1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->getBranchSearchDist2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->getTooCloseDist((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->getSigmaKnn((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->getAcceptBranchSize((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->getBranchMergeDist((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->getCleanNearbyBranchesDist((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->getSegmentLength((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->getFollowSampleRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->getCombineAngle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->guessParaMeter(); break;
        case 21: _t->getKNN((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->getClickNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->getFollowSampleAngle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 24: _t->getGrowAcceptSigma((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 25: _t->getKeepVirtualAngle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->updatePanel(); break;
        case 27: _t->applyFixOriginal(); break;
        case 28: _t->applyAutoRun(); break;
        case 29: _t->applyDownsampling(); break;
        case 30: _t->applyAutoRunUntilGrowth(); break;
        case 31: _t->applyAllSegment(); break;
        case 32: _t->applyAutoWlopOneStep(); break;
        case 33: _t->applyDetectFeature(); break;
        case 34: _t->applySearchNewBranches(); break;
        case 35: _t->applyCleanAndUpdateRadius(); break;
        case 36: _t->getSkeletonInitialRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 37: _t->getSkeletonGrowthRate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 38: _t->getSkeletonRepulsionMu((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 39: _t->getInitRadiusPara((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 40: _t->getInitSampleNumber((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 41: _t->useDensityCompute((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: _t->useRecenteringCompute((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: _t->needRefinement((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SkeletonParaDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SkeletonParaDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_SkeletonParaDlg,
      qt_meta_data_SkeletonParaDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkeletonParaDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkeletonParaDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkeletonParaDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkeletonParaDlg))
        return static_cast<void*>(const_cast< SkeletonParaDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int SkeletonParaDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    }
    return _id;
}

// SIGNAL 0
void SkeletonParaDlg::parameterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
