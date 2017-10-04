

#pragma once
#include <vector>
#include "CMesh.h"
#include "grid.h"
//#include "LAP_Others/eigen.h"
#include <fstream>
#include <float.h>
#include <QString>
#include <iostream>
#include <time.h>
#include <string>
#include <ctime>
#include<algorithm>
#include <math.h>
#include "ANN/ANN.h"

#define EIGEN_DEFAULT_TO_ROW_MAJOR
#define EIGEN_EXCEPTIONS

//#include <Eigen/Dense>

using namespace std;
using namespace vcg;


//typedef Eigen::MatrixXd Matrix;

#define MyMax(a,b) (((a) > (b)) ? (a) : (b))  
#define MyMin(a,b) (((a) < (b)) ? (a) : (b))  


namespace GlobalFun
{
	void computeKnnNeigbhors(vector<CVertex> &datapts, vector<CVertex> &querypts, int numKnn, bool need_self_included, QString purpose);
	void computeEigen(CMesh* _samples);
	void computeEigenIgnoreBranchedPoints(CMesh* _samples);
	void computeEigenWithTheta(CMesh* _samples, double radius);

	void computeAnnNeigbhors(vector<CVertex> &datapts, vector<CVertex> &querypts, int numKnn, bool need_self_included, QString purpose);
	void computeBallNeighbors(CMesh* mesh0, CMesh* mesh1, double radius, vcg::Box3f& box);

	void static  __cdecl self_neighbors(CGrid::iterator start, CGrid::iterator end, double radius);
	void static  __cdecl other_neighbors(CGrid::iterator starta, CGrid::iterator enda, 
		CGrid::iterator startb, CGrid::iterator endb, double radius);
	void static __cdecl find_original_neighbors(CGrid::iterator starta, CGrid::iterator enda, 
		CGrid::iterator startb, CGrid::iterator endb, double radius); 

	double computeEulerDist(Point3f& p1, Point3f& p2);
	double computeEulerDistSquare(Point3f& p1, Point3f& p2);
	double computeProjDist(Point3f& p1, Point3f& p2, Point3f& normal_of_p1);
	double computeProjDistSquare(Point3f& p1, Point3f& p2, Point3f& normal_of_p1);
	double computePerpendicularDistSquare(Point3f& p1, Point3f& p2, Point3f& normal_of_p1);
	double computePerpendicularDist(Point3f& p1, Point3f& p2, Point3f& normal_of_p1);
	double computeProjPlusPerpenDist(Point3f& p1, Point3f& p2, Point3f& normal_of_p1);
	double getDoubleMAXIMUM();
	vector<int> GetRandomCards(int Max);

	double computeRealAngleOfTwoVertor(Point3f v0, Point3f v1);
	bool isTwoPoint3fTheSame(Point3f& v0, Point3f& v1);
	bool isTwoPoint3fOpposite(Point3f& v0, Point3f& v1);
}

class Timer
{
public:

	void start(const string& str)
	{
		cout << endl;
		starttime = clock();
		mid_start = clock();
		cout << "@@@@@ Time Count Strat For: " << str << endl;

		_str = str;
	}

	void insert(const string& str)
	{
		mid_end = clock();
		timeused = mid_end - mid_start;
		cout << "##" << str << "  time used:  " << timeused / double(CLOCKS_PER_SEC) << " seconds." << endl;
		mid_start = clock();
	}

	void end()
	{
		stoptime = clock();
		timeused = stoptime - starttime;
		cout << /*endl <<*/ "@@@@ finish	" << _str << "  time used:  " << timeused / double(CLOCKS_PER_SEC) << " seconds." << endl;
		cout << endl;
	}

private:
	int starttime, mid_start, mid_end, stoptime, timeused;
	string _str;
};




/* Useful code template

(1)
for(int i = 0; i < samples->vert.size(); i++)
{
CVertex& v = samples->vert[i];

for (int j = 0; j < v.neighbors.size(); j++)
{
CVertex& t = samples->vert[v.neighbors[j]];
}
}

(2)
int count = 0;
time.start("Test 2");
CMesh::VertexIterator vi;
Point3f p0 = Point3f(0,0,0);
for(vi = original->vert.begin(); vi != original->vert.end(); ++vi)
{
count += GlobalFun::computeEulerDistSquare(p0, vi->P());
}
cout << count << endl;
time.end();


time.start("Test 1");
for(int i = 0; i < original->vert.size(); i++)
{
CVertex& v = original->vert[i];
count += (p0 - v.P()).SquaredNorm();
}
cout << count << endl;
time.end();



*/

