#pragma once

#include <QtGui/QFrame>
#include <QtGui/QWidget>
#include <QtGui>
#include <iostream>

#include "ui_para_skeletonization.h"

#include "ParameterMgr.h"
#include "calculationthread.h"
#include "glarea.h"

using namespace std;

class SkeletonParaDlg : public QFrame {
    Q_OBJECT
public:
    //SkeletonParaDlg(QWidget *p, ParameterMgr * _paras);
    SkeletonParaDlg(QWidget* p, ParameterMgr* _paras, GLArea* _area);
    ~SkeletonParaDlg();
    void initConnects();
    void setFrameConent();

signals:
    void parameterChanged();

private slots:
    bool initWidgets();
    void getRadiusValues(double _val);

    void getLocalDensityRadius(double _val);
    void getPcaThreshold(double _val);
    void getFixOriginalWeight(double _val);
    void getHGaussianPara(double _val);
    void getStopAndGrowRadius(double _val);
    void getMaxIterateTime(double _val);

    void getBranchSearchSigma(double _val);
    void getBranchSearchDist1(double _val);
    void getBranchSearchDist2(double _val);
    void getTooCloseDist(double _val);
    void getSigmaKnn(double _val);
    void getAcceptBranchSize(double _val);
    void getBranchMergeDist(double _val);
    void getCleanNearbyBranchesDist(double _val);
    void getSegmentLength(double _val);
    void getFollowSampleRadius(double _val);
    void getCombineAngle(double _val);
    void guessParaMeter();
    void getKNN(int _val);
    void getClickNum(int _val);

    void getFollowSampleAngle(double _val);
    void getGrowAcceptSigma(double _val);
    void getKeepVirtualAngle(double _val);

    void updatePanel();
    void applyFixOriginal();

    //new UI for paper
    void applyAutoRun();
    void applyDownsampling();
    void applyAutoRunUntilGrowth();
    void applyAllSegment();
    void applyAutoWlopOneStep();

    void applyDetectFeature();
    void applySearchNewBranches();
    void applyCleanAndUpdateRadius();

    void getSkeletonInitialRadius(double _val);
    void getSkeletonGrowthRate(double _val);
    void getSkeletonRepulsionMu(double _val);

    void getInitRadiusPara(double _val);
    void getInitSampleNumber(double _val);

    void useDensityCompute(bool _val);
    void useRecenteringCompute(bool _val);
    void needRefinement(bool _val);

private:
    int iter_click_time;
    Ui::para_skeleton* ui;
    ParameterMgr* m_paras;
    GLArea* area;

    CalculationThread calculation_thread;
};
