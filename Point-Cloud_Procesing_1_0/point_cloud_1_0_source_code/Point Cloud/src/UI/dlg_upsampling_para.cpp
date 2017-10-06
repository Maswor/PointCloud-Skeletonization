#include "UI/dlg_upsampling_para.h"

UpsamplingParaDlg::UpsamplingParaDlg(QWidget *p, ParameterMgr * _paras, GLArea * _area) : QFrame(p)
{
	ui = new Ui::Upsampling_para;
	UpsamplingParaDlg::ui->setupUi(this);
	m_paras = _paras;
	area = _area;

	video_begin_index = 0;
	video_end_index = 0;
	video_speed = 1.1;

	if(!initWidgets())
	{
		cout << "Warning:  UpsamplingParaDlg::initWidgets failed!" << endl;
		return ;
	}
	initConnects();
}

void UpsamplingParaDlg::initConnects()
{
	if (!connect(area,SIGNAL(needUpdateStatus()),this,SLOT(initWidgets())))
	{
		cout << "can not connect signal" << endl;
	}

	connect(ui->radius,SIGNAL(valueChanged(double)),this,SLOT(getRadiusValues(double)));
	connect(ui->sigma,SIGNAL(valueChanged(double)),this,SLOT(getSigma(double)));

	connect(ui->add_num,SIGNAL(valueChanged(int)),this,SLOT(setNum(int)));
	connect(ui->using_threshol_process,SIGNAL(clicked(bool)),this,SLOT(setUsingThresholdProcess(bool)));
	connect(ui->threshold,SIGNAL(valueChanged(double)),this,SLOT(setThreshold(double)));
	connect(ui->apply_add_point,SIGNAL(clicked()),this,SLOT(runAddPts()));
	connect(ui->pushButton_Projection,SIGNAL(clicked()),this,SLOT(runProjection()));

	connect(ui->edge_paramete,SIGNAL(valueChanged(double)),this,SLOT(setEdgeParameter(double)));

	connect(ui->begin_index,SIGNAL(valueChanged(double)),this,SLOT(getBeginIndex(double)));
	connect(ui->end_index,SIGNAL(valueChanged(double)),this,SLOT(getEndIndex(double)));
	connect(ui->video_speed,SIGNAL(valueChanged(double)),this,SLOT(getSpeed(double)));
	connect(ui->pushButton_play_video,SIGNAL(clicked()),this,SLOT(applyPlayVideo()));
	connect(ui->wlop_snapshot_resolution,SIGNAL(valueChanged(double)),this,SLOT(getSnapShotResolution(double)));
	connect(ui->wlop_snapshot_index,SIGNAL(valueChanged(double)),this,SLOT(getSnapShotIndex(double)));

}

bool UpsamplingParaDlg::initWidgets()
{
	cout << "init" << endl;
	// 
	ui->radius->setValue(m_paras->upsampling.getDouble("CGrid Radius"));
	ui->sigma->setValue(m_paras->upsampling.getDouble("Feature Sigma"));
	ui->add_num->setValue(m_paras->upsampling.getInt("Number of Add Point"));
	
	Qt::CheckState state = m_paras->upsampling.getBool("Using Threshold Process") ? (Qt::CheckState::Checked): (Qt::CheckState::Unchecked);
	ui->using_threshol_process->setCheckState(state);
	
	state = m_paras->upsampling.getBool("Auto Recompute Radius For Dist") ? (Qt::CheckState::Checked): (Qt::CheckState::Unchecked);

	ui->threshold->setValue(m_paras->upsampling.getDouble("Dist Threshold"));
	ui->edge_paramete->setValue(m_paras->upsampling.getDouble("Edge Parameter"));

	ui->wlop_snapshot_resolution->setValue(m_paras->glarea.getDouble("Snapshot Resolution"));
	ui->wlop_snapshot_index->setValue(m_paras->glarea.getDouble("Snapshot Index"));
	//update();
	//repaint();
	return true;
}


void UpsamplingParaDlg::getRadiusValues(double _val)
{
	m_paras->upsampling.setValue("CGrid Radius",DoubleValue(_val));
	m_paras->setGlobalParameter("CGrid Radius", DoubleValue(_val));
	// for debug
	cout << m_paras->upsampling.getDouble("CGrid Radius") << endl;

	area->updateGL();
}


void UpsamplingParaDlg::getSigma(double _val)
{
	m_paras->upsampling.setValue("Feature Sigma",DoubleValue(_val));
}



void UpsamplingParaDlg::runAddPts()
{
	area->runUpsampling();
}

void UpsamplingParaDlg::runProjection()
{
	cout << "void UpsamplingParaDlg::runProjection()" << endl;
	m_paras->upsampling.setValue("Run Projection", BoolValue(true));
	area->runUpsampling();
	m_paras->upsampling.setValue("Run Projection", BoolValue(false));
	area->dataMgr.recomputeQuad();
	area->updateGL();
}


void UpsamplingParaDlg::setNum(int _val)
{
	m_paras->upsampling.setValue("Number of Add Point",IntValue(_val));
}


//
void UpsamplingParaDlg::setThreshold(double _val)
{
	m_paras->upsampling.setValue("Dist Threshold",DoubleValue(_val));
}

void UpsamplingParaDlg::setUsingThresholdProcess(bool _val)
{
	m_paras->upsampling.setValue("Using Threshold Process", BoolValue(_val));
}



void UpsamplingParaDlg::setEdgeParameter(double _val)
{
	m_paras->upsampling.setValue("Edge Parameter",DoubleValue(_val));
	
}


void UpsamplingParaDlg::setFrameConent()
{
	if(layout()) delete layout();
	QGridLayout * vLayout = new QGridLayout(this);
	vLayout->setAlignment(Qt::AlignTop);
	setLayout(vLayout);

	showNormal();
	adjustSize();
}

UpsamplingParaDlg::~UpsamplingParaDlg()
{
	cout << "De-construct UpsamplingParaDlg Frame." << endl;
	delete ui;
	ui = NULL;
	area = NULL;
	m_paras = NULL;
}


void UpsamplingParaDlg::getSnapShotResolution(double _val)
{
	m_paras->glarea.setValue("Snapshot Resolution", DoubleValue(_val));
	area->updateGL();
}

void UpsamplingParaDlg::getSnapShotIndex(double _val)
{
	m_paras->glarea.setValue("Snapshot Index", DoubleValue(_val));
	area->updateGL();
}

void UpsamplingParaDlg::getBeginIndex(double _val)
{
	video_begin_index = _val;

	if (_val > 5)
	{
		CMesh* samples = area->dataMgr.getCurrentSamples();

		for (int i = 0; i < samples->vert.size(); i++)
		{
			samples->vert[i].is_skel_ignore = false;
		}

		for (int i = video_begin_index+1; i < samples->vert.size(); i++)
		{
			samples->vert[i].is_skel_ignore = true;
		}
	}


	area->updateGL();
}

void UpsamplingParaDlg::getEndIndex(double _val)
{
	video_end_index = _val;
}

void UpsamplingParaDlg::getSpeed(double _val)
{
	video_speed = _val;
}


void UpsamplingParaDlg::applyPlayVideo()
{
	m_paras->glarea.setValue("SnapShot Each Iteration", BoolValue(true));
	m_paras->glarea.setValue("No Snap Radius",BoolValue(true));

	CMesh* samples = area->dataMgr.getCurrentSamples();

	int begin_index = video_begin_index;
	int end_index = video_end_index;

	if (begin_index > end_index)
	{
		end_index = samples->vn - 1;
	}

	if (end_index >= samples->vn)
	{
		end_index = samples->vn - 1;
	}

	double speed = video_speed;
	double step_size = 2;

	int current_index = begin_index;
	int last_index = current_index;

	for (int i = current_index+1; i < samples->vert.size(); i++)
	{
		samples->vert[i].is_skel_ignore = true;
	}



	while(current_index < end_index)
	{
		area->saveSnapshot();
		area->updateGL();

		step_size *= speed;
		step_size += 1;
		current_index += step_size;

		if (current_index >= samples->vert.size())
		{
			break;
		}

		for (int i = last_index; i < current_index; i++)
		{
			samples->vert[i].is_skel_ignore = false;
		}

		last_index = current_index;
	}

	for (int i = 0; i < end_index; i++)
	{
		samples->vert[i].is_skel_ignore = false;
	}
	area->saveSnapshot();
	area->updateGL();

}
