#pragma once

#include <QtGui/QFrame>
#include <QtGui/QWidget>
#include <QtGui>
#include <iostream>

#include "Algorithm/normal_extrapolation.h"
#include "ui_normal_para.h"

#include "ParameterMgr.h"
#include "glarea.h"

using namespace std;

class NormalParaDlg : public QFrame {
    Q_OBJECT
public:
    NormalParaDlg(QWidget* p, ParameterMgr* _paras, GLArea* _area);
    ~NormalParaDlg();
    void initConnects();

    void setFrameConent();

private slots:
    bool initWidgets();
    void getRadiusValues(double _val);
    void getPcaThreshold(double _val);
    void getIterateNum(int _val);
    void getSigma(double _val);
    void getKNN(int _val);

    void isAPCA(bool _val);
    void reorientateNormal();
    void applyNormalSmoothing();
    void applyPCANormal();

private:
    Ui::normal_paras* ui;
    ParameterMgr* m_paras;
    GLArea* area;
};
