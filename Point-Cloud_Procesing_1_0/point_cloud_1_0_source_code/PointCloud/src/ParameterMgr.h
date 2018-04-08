#pragma once
#include "Parameter.h"
#include "cmesh.h"

class ParameterMgr
{
public:
	ParameterMgr(void);
	~ParameterMgr(void);
	RichParameterSet* getDataParameterSet(){ return &data; }
	RichParameterSet* getDrawerParameterSet(){ return &drawer; }
	RichParameterSet* getGlareaParameterSet(){ return &glarea; }
	RichParameterSet* getWLopParameterSet(){ return &wLop; }
	RichParameterSet* getSkeletonParameterSet(){ return &skeleton; }	
	RichParameterSet* getNormalSmootherParameterSet(){ return &norSmooth; }
	RichParameterSet* getUpsamplingParameterSet(){ return &upsampling; }

	void setGlobalParameter(QString paraName,Value& val);
	typedef enum {GLAREA, DATA, DRAWER, WLOP, NOR_SMOOTH, SKELETON, UPSAMPLING}ParaType;

private:
	void initDataMgrParameter();
	void initDrawerParameter();
	void initGlareaParameter();
	void initWLopParameter();
	void initSkeletonParameter();
	void initNormalSmootherParameter();
	void initUpsamplingParameter();

public:
	RichParameterSet glarea;
	RichParameterSet data;
	RichParameterSet drawer;
	RichParameterSet wLop;
	RichParameterSet norSmooth;
	RichParameterSet skeleton;
	RichParameterSet upsampling;

private:
	static int init_time;
	double grid_r;
};

extern ParameterMgr global_paraMgr;
