#pragma once

#include <QtGui/QFrame>
#include <QtGui/QWidget>
#include <QtGui>
#include <iostream>

#include "ui_upsampling_para.h"

#include "ParameterMgr.h"
#include "glarea.h"

using namespace std;

class UpsamplingParaDlg : public QFrame {
    Q_OBJECT
public:
    UpsamplingParaDlg(QWidget* p, ParameterMgr* _paras, GLArea* _area);
    ~UpsamplingParaDlg();
    void initConnects();

    void setFrameConent();
    //signals:
    //	void parameterChanged();

private slots:
    //Common
    bool initWidgets();
    void runAddPts();
    void runProjection();
    void getRadiusValues(double _val);
    void getSigma(double _val);
    void setEdgeParameter(double _val);
    void setNum(int _val);

    //Threshold Method
    void setThreshold(double _val);
    void setUsingThresholdProcess(bool _val);

    void getSnapShotResolution(double _val);
    void getSnapShotIndex(double _val);
    void getBeginIndex(double _val);
    void getEndIndex(double _val);
    void getSpeed(double _val);
    void applyPlayVideo();

private:
    Ui::Upsampling_para* ui;
    ParameterMgr* m_paras;
    GLArea* area;

    int video_begin_index;
    int video_end_index;
    double video_speed;
};
