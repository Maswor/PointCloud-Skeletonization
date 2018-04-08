#include "UI/dlg_skeleton_para.h"

SkeletonParaDlg::SkeletonParaDlg(QWidget* p, ParameterMgr* _paras, GLArea* _area)
    : QFrame(p)
{
    ui = new Ui::para_skeleton;
    SkeletonParaDlg::ui->setupUi(this);
    m_paras = _paras;
    area = _area;

    iter_click_time = 1;

    if (!initWidgets()) {
	cerr << "Warning:  SkeletonParaDlg::initWidgets failed!" << endl;
	return;
    }

    initConnects();
}

void SkeletonParaDlg::initConnects()
{
    if (!connect(area, SIGNAL(needUpdateStatus()), this, SLOT(initWidgets()))) {
	cout << "can not connect signal" << endl;
    }

    if (!connect(ui->radius, SIGNAL(valueChanged(double)), this, SLOT(getRadiusValues(double)))) {
	cout << "cannot connect SkeletonParaDlg::getDoubleValues(double)." << endl;
    }

    if (!connect(ui->local_density_radius, SIGNAL(valueChanged(double)), this, SLOT(getLocalDensityRadius(double)))) {
	cerr << "cannot connect SkeletonParaDlg::getDoubleValues(double)." << endl;
    }

    if (!connect(area, SIGNAL(radiusValueChanged()), this, SLOT(updatePanel()))) {
	cout << "cannot connect radiusValueChanged" << endl;
    }

    connect(ui->Stop_And_Grow_Error, SIGNAL(valueChanged(double)), this, SLOT(getStopAndGrowRadius(double)));
    connect(ui->Max_Iterate_Time, SIGNAL(valueChanged(double)), this, SLOT(getMaxIterateTime(double)));
    connect(ui->Detect_Feature, SIGNAL(clicked()), this, SLOT(applyDetectFeature()));
    connect(ui->step2_search_branch, SIGNAL(clicked()), this, SLOT(applySearchNewBranches()));
    connect(ui->Step3_Clean_And_Update_Radius, SIGNAL(clicked()), this, SLOT(applyCleanAndUpdateRadius()));
    connect(ui->PCA_Threshold, SIGNAL(valueChanged(double)), this, SLOT(getPcaThreshold(double)));
    connect(ui->Fix_original_weight_3, SIGNAL(valueChanged(double)), this, SLOT(getFixOriginalWeight(double)));
    connect(ui->wlop_branch_search_max_dist, SIGNAL(valueChanged(double)), this, SLOT(getBranchSearchDist1(double)));
    connect(ui->wlop_branch_search_max_dist2, SIGNAL(valueChanged(double)), this, SLOT(getBranchSearchDist2(double)));
    connect(ui->wlop_combine_too_close, SIGNAL(valueChanged(double)), this, SLOT(getTooCloseDist(double)));
    connect(ui->wlop_sigma_knn, SIGNAL(valueChanged(double)), this, SLOT(getSigmaKnn(double)));
    connect(ui->wlop_accept_branch_size, SIGNAL(valueChanged(double)), this, SLOT(getAcceptBranchSize(double)));
    connect(ui->wlop_branch_search_sigma, SIGNAL(valueChanged(double)), this, SLOT(getBranchSearchSigma(double)));

    connect(ui->wlop_branch_merge_dist, SIGNAL(valueChanged(double)), this, SLOT(getBranchMergeDist(double)));
    connect(ui->wlop_clean_near_branch_dist, SIGNAL(valueChanged(double)), this, SLOT(getCleanNearbyBranchesDist(double)));
    connect(ui->wlop_segment_length, SIGNAL(valueChanged(double)), this, SLOT(getSegmentLength(double)));
    connect(ui->wlop_combine_angle, SIGNAL(valueChanged(double)), this, SLOT(getCombineAngle(double)));
    connect(ui->wlop_follow_sample_radius_2, SIGNAL(valueChanged(double)), this, SLOT(getFollowSampleRadius(double)));

    connect(ui->wlop_run_all_segment, SIGNAL(clicked()), this, SLOT(applyAllSegment()));
    connect(ui->wlop_follow_sample_angle, SIGNAL(valueChanged(double)), this, SLOT(getFollowSampleAngle(double)));
    connect(ui->wlop_grow_accept_sigma, SIGNAL(valueChanged(double)), this, SLOT(getGrowAcceptSigma(double)));
    connect(ui->wlop_keep_virtual_angle, SIGNAL(valueChanged(double)), this, SLOT(getKeepVirtualAngle(double)));
    connect(ui->iter_click_num, SIGNAL(valueChanged(int)), this, SLOT(getClickNum(int)));

    connect(ui->compute_density_2, SIGNAL(clicked(bool)), this, SLOT(useDensityCompute(bool)));
    connect(ui->need_refinement, SIGNAL(clicked(bool)), this, SLOT(needRefinement(bool)));

    //new UI for paper
    connect(ui->skeleton_initial_radius, SIGNAL(valueChanged(double)), this, SLOT(getSkeletonInitialRadius(double)));
    connect(ui->skeleton_Radius_Growing_Speed, SIGNAL(valueChanged(double)), this, SLOT(getSkeletonGrowthRate(double)));
    connect(ui->skeleton_mu, SIGNAL(valueChanged(double)), this, SLOT(getSkeletonRepulsionMu(double)));

    connect(ui->skeleton_downsample_num, SIGNAL(valueChanged(double)), this, SLOT(getInitSampleNumber(double)));
    connect(ui->Auto_Wlop_One_Step, SIGNAL(clicked()), this, SLOT(applyAutoWlopOneStep()));
    connect(ui->skeleton_full_auto, SIGNAL(clicked()), this, SLOT(applyAutoRun()));
    connect(ui->skeleton_initial_sampling, SIGNAL(clicked()), this, SLOT(applyDownsampling()));
    connect(ui->skeleton_run_until_growth, SIGNAL(clicked()), this, SLOT(applyAutoRunUntilGrowth()));
}

bool SkeletonParaDlg::initWidgets()
{
    ui->wlop_clean_near_branch_dist->setValue(m_paras->skeleton.getDouble("Clean Near Branches Dist"));
    ui->wlop_follow_sample_angle->setValue(m_paras->skeleton.getDouble("Follow Sample Max Angle"));
    ui->wlop_grow_accept_sigma->setValue(m_paras->skeleton.getDouble("Grow Accept Sigma"));
    ui->wlop_keep_virtual_angle->setValue(m_paras->skeleton.getDouble("Inactive And Keep Virtual Angle"));

    //
    ui->skeleton_downsample_num->setValue(m_paras->data.getDouble("Down Sample Num"));

    ui->radius->setValue(m_paras->skeleton.getDouble("CGrid Radius"));
    ui->Stop_And_Grow_Error->setValue(m_paras->skeleton.getDouble("Stop And Grow Error"));
    ui->Max_Iterate_Time->setValue(m_paras->skeleton.getDouble("Max Iterate Time"));

    ui->Fix_original_weight_3->setValue(m_paras->skeleton.getDouble("Fix Original Weight"));

    ui->wlop_branch_search_max_dist->setValue(m_paras->skeleton.getDouble("Snake Search Max Dist Blue"));
    ui->wlop_branch_search_max_dist2->setValue(m_paras->skeleton.getDouble("Branch Search Max Dist Yellow"));
    ui->wlop_combine_too_close->setValue(m_paras->skeleton.getDouble("Combine Too Close Threshold"));
    ui->wlop_sigma_knn->setValue(m_paras->skeleton.getDouble("Sigma KNN"));
    ui->wlop_accept_branch_size->setValue(m_paras->skeleton.getDouble("Accept Branch Size"));
    ui->wlop_branch_search_sigma->setValue(m_paras->skeleton.getDouble("Branches Search Angle"));

    ui->wlop_branch_merge_dist->setValue(m_paras->skeleton.getDouble("Branches Merge Max Dist"));

    ui->wlop_segment_length->setValue(m_paras->skeleton.getDouble("Curve Segment Length"));
    ui->wlop_combine_angle->setValue(m_paras->skeleton.getDouble("Combine Similar Angle"));
    ui->wlop_follow_sample_radius_2->setValue(m_paras->skeleton.getDouble("Follow Sample Radius"));
    ui->PCA_Threshold->setValue(m_paras->skeleton.getDouble("Eigen Feature Identification Threshold"));

    ui->skeleton_initial_radius->setValue(m_paras->skeleton.getDouble("Initial Radius"));
    ui->skeleton_Radius_Growing_Speed->setValue(m_paras->skeleton.getDouble("Radius Update Speed"));
    ui->skeleton_mu->setValue(m_paras->skeleton.getDouble("Repulsion Mu"));

    Qt::CheckState state;
    state = m_paras->skeleton.getBool("Need Compute Density") ? (Qt::CheckState::Checked) : (Qt::CheckState::Unchecked);
    ui->compute_density_2->setCheckState(state);

    state = m_paras->skeleton.getBool("Need Segment Right Away") ? (Qt::CheckState::Checked) : (Qt::CheckState::Unchecked);
    ui->need_refinement->setCheckState(state);

    update();
    repaint();
    return true;
}

void SkeletonParaDlg::setFrameConent()
{
    if (layout())
	delete layout();
    QGridLayout* vLayout = new QGridLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    setLayout(vLayout);

    showNormal();
    adjustSize();
}

void SkeletonParaDlg::getRadiusValues(double _val)
{
    auto temp_val = DoubleValue(_val);
    m_paras->setGlobalParameter("CGrid Radius", temp_val);
    update();
    area->update();
    //emit parameterChanged();
}

void SkeletonParaDlg::getHGaussianPara(double _val)
{
    auto temp_val2 = DoubleValue(_val);
    m_paras->setGlobalParameter("H Gaussian Para", temp_val2);
    update();
    area->update();
}

void SkeletonParaDlg::getStopAndGrowRadius(double _val)
{
    m_paras->skeleton.setValue("Stop And Grow Error", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getMaxIterateTime(double _val)
{
    m_paras->skeleton.setValue("Max Iterate Time", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getBranchSearchSigma(double _val)
{
    m_paras->skeleton.setValue("Branches Search Angle", DoubleValue(_val));
    m_paras->skeleton.setValue("Virtual Head Accecpt Angle", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getBranchSearchDist1(double _val)
{
    m_paras->skeleton.setValue("Snake Search Max Dist Blue", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getBranchSearchDist2(double _val)
{
    m_paras->skeleton.setValue("Branch Search Max Dist Yellow", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getTooCloseDist(double _val)
{
    m_paras->skeleton.setValue("Combine Too Close Threshold", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getSigmaKnn(double _val)
{
    m_paras->skeleton.setValue("Sigma KNN", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getAcceptBranchSize(double _val)
{
    m_paras->skeleton.setValue("Accept Branch Size", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getBranchMergeDist(double _val)
{
    m_paras->skeleton.setValue("Branches Merge Max Dist", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getCleanNearbyBranchesDist(double _val)
{
    m_paras->skeleton.setValue("Clean Near Branches Dist", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getSegmentLength(double _val)
{
    m_paras->skeleton.setValue("Curve Segment Length", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getFollowSampleRadius(double _val)
{
    m_paras->skeleton.setValue("Follow Sample Radius", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getCombineAngle(double _val)
{
    m_paras->skeleton.setValue("Combine Similar Angle", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::needRefinement(bool _val)
{
    m_paras->skeleton.setValue("Need Segment Right Away", BoolValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getClickNum(int _val)
{
    iter_click_time = _val;
}

void SkeletonParaDlg::guessParaMeter()
{
    double radius = m_paras->skeleton.getDouble("CGrid Radius");
    double influence_radius = m_paras->skeleton.getDouble("CGrid Radius") / sqrt(m_paras->skeleton.getDouble("H Gaussian Para"));

    m_paras->skeleton.setValue("Initial Radius", DoubleValue(radius * 1.0));
    m_paras->skeleton.setValue("Local Density Radius", DoubleValue(radius * 0.8));
    m_paras->skeleton.setValue("Follow Sample Radius", DoubleValue(influence_radius * 7.0));
    m_paras->skeleton.setValue("Combine Too Close Threshold", DoubleValue(influence_radius * 0.06));
    m_paras->skeleton.setValue("Snake Search Max Dist Blue", DoubleValue(influence_radius * 4.0));
    m_paras->skeleton.setValue("Branches Merge Max Dist", DoubleValue(influence_radius * 1));
    m_paras->skeleton.setValue("Clean Near Branches Dist", DoubleValue(influence_radius * 0.05));
    m_paras->skeleton.setValue("Curve Segment Length", DoubleValue(influence_radius * 1.0));
    m_paras->skeleton.setValue("Stop And Grow Error", DoubleValue(influence_radius * 0.0005));

    updatePanel();
}

void SkeletonParaDlg::updatePanel()
{
    //cout << "SkeletonParaDlg::updatePanel()" << endl;
    initWidgets();
    update();
}

void SkeletonParaDlg::getLocalDensityRadius(double _val)
{
    auto temp_val3 = DoubleValue(_val);
    m_paras->setGlobalParameter("Local Density Radius", temp_val3);
}

void SkeletonParaDlg::getPcaThreshold(double _val)
{
    m_paras->skeleton.setValue("Eigen Feature Identification Threshold", DoubleValue(_val));
}

void SkeletonParaDlg::getFixOriginalWeight(double _val)
{
    m_paras->skeleton.setValue("Fix Original Weight", DoubleValue(_val));
}

void SkeletonParaDlg::getKNN(int _val)
{
    m_paras->skeleton.setValue("WLOP KNN", IntValue(_val));
}

// apply
void SkeletonParaDlg::applyDetectFeature()
{
    m_paras->skeleton.setValue("Step1 Detect Skeleton Feature", BoolValue(true));
    area->runSkeletonization_linear();
    m_paras->skeleton.setValue("Step1 Detect Skeleton Feature", BoolValue(false));
}

void SkeletonParaDlg::applyFixOriginal()
{
    m_paras->skeleton.setValue("Run Fix Original", BoolValue(true));
    area->runSkeletonization_linear();
    m_paras->skeleton.setValue("Run Fix Original", BoolValue(false));
}

void SkeletonParaDlg::applySearchNewBranches()
{

    m_paras->skeleton.setValue("Step2 Run Search New Branchs", BoolValue(true));
    area->runSkeletonization_linear();
    m_paras->skeleton.setValue("Step2 Run Search New Branchs", BoolValue(false));
    update();
    area->update();
}

void SkeletonParaDlg::applyCleanAndUpdateRadius()
{
    m_paras->skeleton.setValue("Step3 Clean And Update Radius", BoolValue(true));
    area->runSkeletonization_linear();
    m_paras->skeleton.setValue("Step3 Clean And Update Radius", BoolValue(false));
    update();
    area->update();
}

void SkeletonParaDlg::applyAllSegment()
{
    m_paras->skeleton.setValue("Run ALL Segment", BoolValue(true));
    area->runSkeletonization_linear();
    m_paras->skeleton.setValue("Run ALL Segment", BoolValue(false));
    update();
    area->update();
}

SkeletonParaDlg::~SkeletonParaDlg()
{
    cout << "De-construct SkeletonParaDlg Frame." << endl;
    delete ui;
    ui = NULL;
    //paras = NULL;
}

void SkeletonParaDlg::getFollowSampleAngle(double _val)
{
    m_paras->skeleton.setValue("Follow Sample Max Angle", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getGrowAcceptSigma(double _val)
{
    m_paras->skeleton.setValue("Grow Accept Sigma", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getKeepVirtualAngle(double _val)
{
    m_paras->skeleton.setValue("Inactive And Keep Virtual Angle", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getSkeletonInitialRadius(double _val)
{
    if (m_paras->glarea.getBool("GLarea Busying")) {
	return;
    }

    m_paras->skeleton.setValue("Initial Radius", DoubleValue(_val));
    m_paras->skeleton.setValue("CGrid Radius", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getSkeletonGrowthRate(double _val)
{
    if (m_paras->glarea.getBool("GLarea Busying")) {
	return;
    }
    m_paras->skeleton.setValue("Radius Update Speed", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getSkeletonRepulsionMu(double _val)
{
    if (m_paras->glarea.getBool("GLarea Busying")) {
	return;
    }

    m_paras->skeleton.setValue("Repulsion Mu", DoubleValue(_val));

    double mu = m_paras->skeleton.getDouble("Repulsion Mu");
    double mu2 = m_paras->skeleton.getDouble("Repulsion Mu2");
    if (mu <= mu2) {
	m_paras->skeleton.setValue("Repulsion Mu2", DoubleValue(0));
    } else {
	m_paras->skeleton.setValue("Repulsion Mu2", DoubleValue(mu2));
    }
    update();
    area->update();
}

void SkeletonParaDlg::getInitRadiusPara(double _val)
{
    if (m_paras->glarea.getBool("GLarea Busying")) {
	return;
    }

    m_paras->data.setValue("Init Radius Para", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::getInitSampleNumber(double _val)
{
    if (m_paras->glarea.getBool("GLarea Busying")) {
	return;
    }

    m_paras->data.setValue("Down Sample Num", DoubleValue(_val));
    update();
    area->update();
}

void SkeletonParaDlg::applyDownsampling()
{
    if (m_paras->glarea.getBool("GLarea Busying")) {
	m_paras->glarea.setValue("Algorithom Stop", BoolValue(true));
	return;
    }

    area->dataMgr.downSamplesByNum();
    area->dataMgr.skeleton.clear();
    area->initSetting();
    update();
    area->update();
}

void SkeletonParaDlg::useDensityCompute(bool _val)
{
    m_paras->skeleton.setValue("Need Compute Density", BoolValue(_val));
    //m_paras->skeleton.setValue("Use Local Density",BoolValue(_val));
}

void SkeletonParaDlg::useRecenteringCompute(bool _val)
{
    m_paras->skeleton.setValue("Need Recentering", BoolValue(_val));
}

void SkeletonParaDlg::applyAutoWlopOneStep()
{
    if (m_paras->glarea.getBool("GLarea Busying")) {
	return;
    }

    if (area->dataMgr.isOriginalEmpty() || area->dataMgr.isSamplesEmpty()) {
	return;
    }

    m_paras->skeleton.setValue("The Skeletonlization Process Should Stop", BoolValue(false));

    //global_paraMgr.glarea.setValue("Running Algorithm Name", StringValue("Skeletonization"));
    //calculation_thread.setArea(area);
    //calculation_thread.start();

    for (int i = 0; i < iter_click_time; i++) {
	initWidgets();
	m_paras->skeleton.setValue("Run Auto Wlop One Step", BoolValue(true));
	area->runSkeletonization_linear();
	m_paras->skeleton.setValue("Run Auto Wlop One Step", BoolValue(false));

	if (m_paras->skeleton.getBool("The Skeletonlization Process Should Stop")) {
	    break;
	}
    }
}

void SkeletonParaDlg::applyAutoRunUntilGrowth()
{
    if (m_paras->glarea.getBool("GLarea Busying")) {
	return;
    }

    if (area->dataMgr.isOriginalEmpty() || area->dataMgr.isSamplesEmpty()) {
	return;
    }

    m_paras->skeleton.setValue("The Skeletonlization Process Should Stop", BoolValue(false));
    m_paras->glarea.setValue("Algorithom Stop", BoolValue(false));

    m_paras->skeleton.setValue("Run Auto Wlop One Stage", BoolValue(true));

    global_paraMgr.glarea.setValue("Running Algorithm Name", StringValue("Skeletonization"));
    calculation_thread.setArea(area);
    calculation_thread.start();
}

void SkeletonParaDlg::applyAutoRun()
{
    if (global_paraMgr.glarea.getBool("SnapShot Each Iteration")) {
	area->runSkeletonization_linear();
    } else {
	m_paras->glarea.setValue("Algorithom Stop", BoolValue(false));
	global_paraMgr.glarea.setValue("Running Algorithm Name", StringValue("Skeletonization"));
	calculation_thread.setArea(area);
	calculation_thread.start();
    }
}
