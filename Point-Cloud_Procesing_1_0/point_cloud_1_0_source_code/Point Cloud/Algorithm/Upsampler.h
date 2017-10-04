#pragma once

#include "GlobalFunction.h"
#include "PointCloudAlgorithm.h"
#include "Parameter.h"

#include <iostream>
#include <algorithm>
#include <set>

using namespace vcg;
using namespace std;

// better code is going to be in CGAL 
class Upsampler : public PointCloudAlgorithm
{
public:
	Upsampler(RichParameterSet* _para);
	~Upsampler(void);

	void setInput(DataMgr* pData);
	void run();
	void setParameterSet(RichParameterSet* _para){ para = _para;}
	RichParameterSet* getParameterSet(){ return para; }
	void clear(){ samples = NULL; }
	void recomputeAllNeighbors();

private:
	void input(CMesh* _samples);

	void initVertexes();
	void doUpsampling();

	void getLineVertNeighorsIndex(set<int> & neighbors, int firstV, int secV);
	void getNewPointNeighbors(CVertex & newv,set<int> & neighbors, bool isBoth);
	double findMaxMidpoint(CVertex & v, int & neighbor_index);

	//wsh 
	void clearAllThresholdFlag();
	void insertPointsByThreshold();

	double getPredictThreshold();
	double getPredictThresholdFirstTime(); 

	void computeNewVertexNormAvgMethod(CVertex & v, int firstV, int secV);
	void computeNewVertexProjDist_Sigma(CVertex & v, int firstV, int secV);
	void computeEigenVerctorForRendering();


	
protected:
	Upsampler(void);

public:
	bool b_first;

private:
	RichParameterSet* para;
	CMesh* samples;

	double radius;
	double old_radius;
	double sigma;

private:
	double G_value;
	double d;
	double wd;
	vector<bool> is_abandon_by_threshold;
	//vector<double> best_dist_set;

	/******    Projection:   *******/
private:
	void optimizeProjection();

	void static  __cdecl self_optimize_upsamples_global(CGrid::iterator start, CGrid::iterator end, double radius);
	void static  __cdecl other_optimize_upsamples_global(CGrid::iterator starta, CGrid::iterator enda, 
		CGrid::iterator startb, CGrid::iterator endb, double radius);
	inline void static updateVT_proj(CVertex& v, CVertex& t, double weight);

	void static  __cdecl self_optimize_normals(CGrid::iterator start, CGrid::iterator end, double radius);
	void static  __cdecl other_optimize_normals(CGrid::iterator starta, CGrid::iterator enda, 
		CGrid::iterator startb, CGrid::iterator endb, double radius);
	inline void static updateVT_proj_normal(CVertex& v, CVertex& t, double weight, double radius);

private:
	static vector<double> proj_dist;
	static vector<double> proj_weight;

	static vector<Point3f> sum_N;
	static vector<Point3f> sum_Gw;
	static vector<Point3f> sum_Gf;

};
