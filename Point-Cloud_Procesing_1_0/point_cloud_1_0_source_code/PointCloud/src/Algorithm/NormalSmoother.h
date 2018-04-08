#pragma once
#include "GlobalFunction.h"
#include <algorithm>
#include <iostream>
//#include "Algorithm/normal_extrapolation.h" // this need to include before include GLDrawer
#include "PointCloudAlgorithm.h"
#include "anistropicPCA_Normal.h"
#include <fstream>

using namespace vcg;
using namespace std;


class NormalSmoother : public PointCloudAlgorithm
{
public:
	NormalSmoother(RichParameterSet* _para);
	~NormalSmoother(void);

	void setInput(DataMgr* pData);
	void setParameterSet(RichParameterSet* _para){para = _para;}
	RichParameterSet* getParameterSet(){ return para; }
	void run();
	void clear(){ mesh = NULL; }

	
protected:
	NormalSmoother(){}

private:
	void input(CMesh* _mesh);
	void runAnisotropicPCA();
	void runNormalSmooth(); 
	void initVertexes();
	
private:
	CMesh* mesh;
	CMesh* orignal_mesh;

	RichParameterSet* para;
	Box3f m_box;

	vector<Point3f> normal_sum;
	vector<double>  normal_weight_sum;
};
