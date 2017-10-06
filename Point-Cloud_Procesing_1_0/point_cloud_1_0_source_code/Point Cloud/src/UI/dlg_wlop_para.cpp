#include "UI/dlg_wlop_para.h"

WlopParaDlg::WlopParaDlg(QWidget *p, ParameterMgr * _paras, GLArea * _area) : QFrame(p)
{
	ui = new Ui::para_wlop;
	WlopParaDlg::ui->setupUi(this);
	m_paras = _paras;
	area = _area;

	if(!initWidgets())
	{
		cerr << "Warning:  WlopParaDlg::initWidgets failed!" << endl;
		 return ;
	}

	initConnects();
}


void WlopParaDlg::initConnects()
{
	if (!connect(area,SIGNAL(needUpdateStatus()),this,SLOT(initWidgets())))
	{
		cout << "can not connect signal" << endl;
	}

	if(!connect(ui->radius,SIGNAL(valueChanged(double)),this,SLOT(getRadiusValues(double))))
	{
		cerr << "cannot connect WlopParaDlg::getDoubleValues(double)." << endl;
	}

	//if(!connect(ui->rep_pow,SIGNAL(valueChanged(double)),this,SLOT(getRepPow(double))))
	//{
	//	cerr << "cannot connect WlopParaDlg::getDoubleValues(double)." << endl;
	//}
	//if(!connect(ui->fit_pow,SIGNAL(valueChanged(double)),this,SLOT(getFitPow(double))))
	//{
	//	cerr << "cannot connect WlopParaDlg::getDoubleValues(double)." << endl;
	//}
	if(!connect(ui->mu,SIGNAL(valueChanged(double)),this,SLOT(getMu(double))))
	{
		cerr << "cannot connect WlopParaDlg::getDoubleValues(double)." << endl;
	}
	if(!connect(ui->iter,SIGNAL(valueChanged(int)),this,SLOT(getIter(int))))
	{
		cerr << "cannot connect WlopParaDlg::getDoubleValues(double)." << endl;
	}
	if(!connect(ui->compute_density,SIGNAL(clicked(bool)),this,SLOT(isDensity(bool))))
	{
		cerr << "cannot connect WlopParaDlg::getDoubleValues(double)." << endl;
	}
	if(!connect(ui->compute_pca,SIGNAL(clicked(bool)),this,SLOT(isPca(bool))))
	{
		cerr << "cannot connect WlopParaDlg::getDoubleValues(double)." << endl;
	}
	//
	if(!connect(ui->wlop_apply,SIGNAL(clicked()),this,SLOT(applyWlop())))
	{
		cerr << "cannot connect WlopParaDlg::applyWlop()." << endl;
	}
	connect(ui->anisotropic_lop_apply,SIGNAL(clicked()),this,SLOT(applyAnisotropicLop()));

}


bool WlopParaDlg::initWidgets()
{
	ui->radius->setValue(m_paras->wLop.getDouble("CGrid Radius"));
	ui->mu->setValue(m_paras->wLop.getDouble("Repulsion Mu"));
	/*ui->rep_pow->setValue(m_paras->wLop.getDouble("Repulsion Power"));
	ui->fit_pow->setValue(m_paras->wLop.getDouble("Average Power"));*/
	ui->iter->setValue(m_paras->wLop.getDouble("Num Of Iterate Time"));
	
	Qt::CheckState state = m_paras->wLop.getBool("Need Compute Density") ? (Qt::CheckState::Checked): (Qt::CheckState::Unchecked);
	ui->compute_density->setCheckState(state);

	state = m_paras->wLop.getBool("Need Compute PCA") ? (Qt::CheckState::Checked): (Qt::CheckState::Unchecked);
	ui->compute_pca->setCheckState(state);
	update();
	repaint();
	return true;
}

void WlopParaDlg::setFrameConent()
{
	if(layout()) delete layout();
	QGridLayout * vLayout = new QGridLayout(this);
	vLayout->setAlignment(Qt::AlignTop);
	setLayout(vLayout);

	showNormal();
	adjustSize();
}

void WlopParaDlg::getRadiusValues(double _val)
{
	m_paras->setGlobalParameter("CGrid Radius",DoubleValue(_val));
	area->updateGL();
}


void WlopParaDlg::getRepPow(double _val)
{
	m_paras->wLop.setValue("Repulsion Power",DoubleValue(_val));
}

void WlopParaDlg::getFitPow(double _val)
{
	m_paras->wLop.setValue("Average Power",DoubleValue(_val));
}

void WlopParaDlg::getIter(int _val)
{
	m_paras->wLop.setValue("Num Of Iterate Time",DoubleValue(_val));
}

void WlopParaDlg::getMu(double _val)
{
	m_paras->wLop.setValue("Repulsion Mu",DoubleValue(_val));
}

void WlopParaDlg::isDensity(bool _val)
{
	m_paras->wLop.setValue("Need Compute Density",BoolValue(_val));
	if (_val)
	{
		area->wlop.setFirstIterate();
	}
}

void WlopParaDlg::isPca(bool _val)
{
	m_paras->wLop.setValue("Need Compute PCA",BoolValue(_val));

}

// apply
void WlopParaDlg::applyWlop()
{
	//Timer timer;
	//timer.start("WWWWLLLLLOOOOOPPPP Time");
	//area->runWlop();
	//timer.end();

  if (global_paraMgr.glarea.getBool("SnapShot Each Iteration"))
  {
    area->runWlop();
  }
  else
  {
    global_paraMgr.glarea.setValue("Running Algorithm Name", StringValue("WLOP"));
    calculation_thread.setArea(area);
    calculation_thread.start();
  }

}

void WlopParaDlg::applyAnisotropicLop()
{
	if (global_paraMgr.glarea.getBool("SnapShot Each Iteration"))
	{
		m_paras->wLop.setValue("Run Anisotropic LOP", BoolValue(true));
		area->runWlop();
		m_paras->wLop.setValue("Run Anisotropic LOP", BoolValue(false));
	}
	else
	{
		m_paras->wLop.setValue("Run Anisotropic LOP", BoolValue(true));
		global_paraMgr.glarea.setValue("Running Algorithm Name", StringValue("WLOP"));
		calculation_thread.setArea(area);
		calculation_thread.start();
	}

}

WlopParaDlg::~WlopParaDlg()
{
	cout << "De-construct WlopParaDlg Frame." << endl;
	delete ui;
	ui = NULL;
}