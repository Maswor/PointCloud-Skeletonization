/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      51,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      36,   30,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      92,   11,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     114,   11,   11,   11, 0x08,
     127,   11,   11,   11, 0x08,
     139,   11,   11,   11, 0x08,
     155,   11,   11,   11, 0x08,
     167,   11,   11,   11, 0x08,
     182,   11,   11,   11, 0x08,
     194,   11,   11,   11, 0x08,
     205,   11,   11,   11, 0x08,
     216,   11,   11,   11, 0x08,
     232,   11,   11,   11, 0x08,
     246,   11,   11,   11, 0x08,
     262,   11,   11,   11, 0x08,
     280,   11,   11,   11, 0x08,
     298,   11,   11,   11, 0x08,
     317,   11,   11,   11, 0x08,
     336,   11,   11,   11, 0x08,
     355,   11,   11,   11, 0x08,
     373,   11,   11,   11, 0x08,
     383,   11,   11,   11, 0x08,
     402,   11,   11,   11, 0x08,
     412,   11,   11,   11, 0x0a,
     428,   11,   11,   11, 0x0a,
     453,  448,   11,   11, 0x08,
     470,  448,   11,   11, 0x08,
     489,  448,   11,   11, 0x08,
     507,  448,   11,   11, 0x08,
     525,  448,   11,   11, 0x08,
     544,  448,   11,   11, 0x08,
     561,  448,   11,   11, 0x08,
     583,  448,   11,   11, 0x08,
     610,  448,   11,   11, 0x08,
     640,  448,   11,   11, 0x08,
     666,  448,   11,   11, 0x08,
     697,  448,   11,   11, 0x08,
     727,  448,   11,   11, 0x08,
     761,  754,   11,   11, 0x08,
     785,  754,   11,   11, 0x08,
     811,   11,   11,   11, 0x08,
     825,   11,   11,   11, 0x08,
     841,   11,   11,   11, 0x08,
     859,   11,   11,   11, 0x08,
     873,   11,   11,   11, 0x08,
     888,   11,   11,   11, 0x08,
     903,   11,   11,   11, 0x08,
     918,   11,   11,   11, 0x08,
     934,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0updateStatusBar()\0event\0"
    "dropEvent(QDropEvent*)\0"
    "dragEnterEvent(QDragEnterEvent*)\0"
    "openFile()\0saveFile()\0downSample()\0"
    "subSample()\0normalizeData()\0clearData()\0"
    "saveSnapshot()\0openImage()\0saveView()\0"
    "saveSkel()\0getQianSample()\0showWLopDlg()\0"
    "showNormalDlg()\0showSkeletonDlg()\0"
    "showUpsampleDlg()\0autoPlaySkeleton()\0"
    "stepPlaySkeleton()\0jumpPlaySkeleton()\0"
    "initialSampling()\0setStop()\0"
    "removePickPoints()\0runWLop()\0"
    "runPCA_Normal()\0reorientateNormal()\0"
    "_val\0lightOnOff(bool)\0showOriginal(bool)\0"
    "showSamples(bool)\0showNormals(bool)\0"
    "showSkeleton(bool)\0cullPoints(bool)\0"
    "showNormalColor(bool)\0showNeighborhoodBall(bool)\0"
    "showAllNeighborhoodBall(bool)\0"
    "showIndividualColor(bool)\0"
    "setSnapshotEachIteration(bool)\0"
    "setNoSnapshotWithRadius(bool)\0"
    "showColorfulBranches(bool)\0action\0"
    "setSmapleType(QAction*)\0"
    "setOriginalType(QAction*)\0sampleColor()\0"
    "originalColor()\0backGroundColor()\0"
    "normalColor()\0featureColor()\0"
    "ambientColor()\0diffuseColor()\0"
    "specularColor()\0recomputeQuad()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->updateStatusBar(); break;
        case 1: _t->dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 2: _t->dragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 3: _t->openFile(); break;
        case 4: _t->saveFile(); break;
        case 5: _t->downSample(); break;
        case 6: _t->subSample(); break;
        case 7: _t->normalizeData(); break;
        case 8: _t->clearData(); break;
        case 9: _t->saveSnapshot(); break;
        case 10: _t->openImage(); break;
        case 11: _t->saveView(); break;
        case 12: _t->saveSkel(); break;
        case 13: _t->getQianSample(); break;
        case 14: _t->showWLopDlg(); break;
        case 15: _t->showNormalDlg(); break;
        case 16: _t->showSkeletonDlg(); break;
        case 17: _t->showUpsampleDlg(); break;
        case 18: _t->autoPlaySkeleton(); break;
        case 19: _t->stepPlaySkeleton(); break;
        case 20: _t->jumpPlaySkeleton(); break;
        case 21: _t->initialSampling(); break;
        case 22: _t->setStop(); break;
        case 23: _t->removePickPoints(); break;
        case 24: _t->runWLop(); break;
        case 25: _t->runPCA_Normal(); break;
        case 26: _t->reorientateNormal(); break;
        case 27: _t->lightOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->showOriginal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->showSamples((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->showNormals((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->showSkeleton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->cullPoints((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->showNormalColor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->showNeighborhoodBall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->showAllNeighborhoodBall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: _t->showIndividualColor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->setSnapshotEachIteration((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: _t->setNoSnapshotWithRadius((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->showColorfulBranches((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->setSmapleType((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 41: _t->setOriginalType((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 42: _t->sampleColor(); break;
        case 43: _t->originalColor(); break;
        case 44: _t->backGroundColor(); break;
        case 45: _t->normalColor(); break;
        case 46: _t->featureColor(); break;
        case 47: _t->ambientColor(); break;
        case 48: _t->diffuseColor(); break;
        case 49: _t->specularColor(); break;
        case 50: _t->recomputeQuad(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
