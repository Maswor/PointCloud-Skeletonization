#include "UI/std_para_dlg.h"

StdParaDlg::StdParaDlg(ParameterMgr* _paras, GLArea * _area, QWidget* parent /* = 0 */) 
  : QDockWidget(QString("Plugin"), parent)
{
	paras = _paras;
	gla = _area;

	init(); // it's important
}

void StdParaDlg::init()
{
	para_wlop = NULL;
	para_normal = NULL;
	para_skeleton = NULL;
	para_upsampling = NULL;

	mainFrame = NULL;
}
// 
bool StdParaDlg::showWlopParaDialog()
{
	// create
	createFrame();
	loadWlopFrame();
	return true;
}

bool StdParaDlg::showNormalParaDlg()
{
	createFrame();
	loadNormalFrame();
	return true;
}


bool StdParaDlg::showSkeletonParaDlg()
{
	createFrame();
	loadSkeletonFrame();
	return true;
}

bool StdParaDlg::showUpsamplingParaDlg()
{	
	createFrame();
	loadUpsamplingFrame();
	return true;
}

void StdParaDlg::createFrame()
{
	if(mainFrame) delete mainFrame;
	QFrame *newFrame = new QFrame;
	setWidget(newFrame);
	setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
	mainFrame = newFrame;	
	
}


void StdParaDlg::loadWlopFrame()
{
	assert(mainFrame);
	//mainFrame->hide();
	QGridLayout *gridLayout = new QGridLayout(mainFrame);
	//QVBoxLayout *vLayout = new QVBoxLayout(mainFrame);
	mainFrame->setLayout(gridLayout);
	setWindowTitle("WLOP");

	para_wlop = new WlopParaDlg(this,paras,gla);
	para_wlop->setFrameConent();
	gridLayout->setRowMinimumHeight(2,620);
	gridLayout->setColumnMinimumWidth(1,225);

	gridLayout->addWidget(para_wlop,1,0,7,10);
	
	mainFrame->showNormal();
	mainFrame->adjustSize();

	//set the minimum size so it will shrink down to the right size
	this->setMinimumSize(mainFrame->sizeHint());
	
	this->showNormal();
	this->adjustSize();
}

void StdParaDlg::loadSkeletonFrame()
{
	assert(mainFrame);
	mainFrame->hide();
	QGridLayout *gridLayout = new QGridLayout(mainFrame);
	//QVBoxLayout *vLayout = new QVBoxLayout(mainFrame);
	mainFrame->setLayout(gridLayout);
	setWindowTitle("L1-Medial Skeleton");


	para_skeleton = new SkeletonParaDlg(this,paras,gla);
	para_skeleton->setFrameConent();
	gridLayout->setRowMinimumHeight(1,610);
	gridLayout->setColumnMinimumWidth(0,315);

	gridLayout->addWidget(para_skeleton,1,0,7,10);


	mainFrame->showNormal();
	mainFrame->adjustSize();
	//set the minimum size so it will shrink down to the right size
	this->setMinimumSize(mainFrame->sizeHint());

	this->showNormal();
	this->adjustSize();
}

void StdParaDlg::loadUpsamplingFrame()
{
	assert(mainFrame);
	mainFrame->hide();
	QGridLayout *gridLayout = new QGridLayout(mainFrame);
	mainFrame->setLayout(gridLayout);
	setWindowTitle("Upsampling Parameters");


	para_upsampling = new UpsamplingParaDlg(this, paras, gla);
	para_upsampling->setFrameConent();

	gridLayout->setRowMinimumHeight(2,380);
	gridLayout->setColumnMinimumWidth(1,180);

	gridLayout->addWidget(para_upsampling,1,0,13,12);

	mainFrame->showNormal();
	mainFrame->adjustSize();
	//set the minimum size so it will shrink down to the right size
	this->setMinimumSize(mainFrame->sizeHint());
	this->showNormal();
	this->adjustSize();
}

void StdParaDlg::loadNormalFrame()
{
	assert(mainFrame);
	mainFrame->hide();
	QGridLayout *gridLayout = new QGridLayout(mainFrame);
	mainFrame->setLayout(gridLayout);
	setWindowTitle("Normal");


	para_normal = new NormalParaDlg(this, paras, gla);
	gridLayout->setRowMinimumHeight(2,540);
	gridLayout->setColumnMinimumWidth(1,225);

	gridLayout->addWidget(para_normal,1,0,5,4);

	mainFrame->showNormal();
	mainFrame->adjustSize();
	//set the minimum size so it will shrink down to the right size
	this->setMinimumSize(mainFrame->sizeHint());
	this->showNormal();
	this->adjustSize();
}




void StdParaDlg::closeClick()
{
	//gla->paraMgr.setGlobalParameter("Skeleton Mode", BoolValue(false));

	cout << "close." << endl;
	
	close();
}

StdParaDlg::~StdParaDlg()
{
	cout << "De-construct StdParaDlg." << endl;

	// just set it to NULL
	gla = NULL;

	if(para_wlop) 
		delete para_wlop;
	para_wlop = NULL;

	if(para_normal)
		delete para_normal;
	para_normal = NULL;

	if (para_skeleton)
		delete para_skeleton;
	para_skeleton = NULL;

	if (para_upsampling)
		delete para_upsampling;
	para_upsampling = NULL;

	if(mainFrame)
		delete mainFrame;
	mainFrame = NULL;
}


