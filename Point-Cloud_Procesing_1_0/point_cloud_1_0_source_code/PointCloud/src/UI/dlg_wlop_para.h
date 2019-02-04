#pragma once

#include <QtGui/QFrame>
#include <QtGui/QWidget>
#include <QtGui>
#include <iostream>

#include "ui_para_wlop.h"

#include "ParameterMgr.h"
#include "calculationthread.h"
#include "glarea.h"

using namespace std;

class WlopParaDlg : public QFrame {
  Q_OBJECT
public:
  WlopParaDlg(QWidget *p, ParameterMgr *_paras, GLArea *_area);
  ~WlopParaDlg();
  void initConnects();
  void setFrameConent();
signals:
  void parameterChanged();

private slots:
  bool initWidgets();
  void getRadiusValues(double _val);
  void getRepPow(double _val);
  void getFitPow(double _val);
  void getIter(int _val);
  void getMu(double _val);
  void isDensity(bool _val);
  void isPca(bool _val);
  //
  void applyWlop();
  void applyAnisotropicLop();

private:
  Ui::para_wlop *ui;
  ParameterMgr *m_paras;
  GLArea *area;

  CalculationThread calculation_thread;
};
