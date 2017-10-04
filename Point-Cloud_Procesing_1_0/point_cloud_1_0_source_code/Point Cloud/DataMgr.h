#pragma once
#include "cmesh.h"
#include "Parameter.h"
#include "GlobalFunction.h"
#include "Algorithm/Skeleton.h"



#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/export.h>

#include <sstream>
#include <fstream>
#include <set>


using namespace vcg;
using namespace std;
using namespace tri;


class DataMgr
{
public:
	DataMgr(RichParameterSet* _para);
	~DataMgr(void);

	void loadPlyToOriginal(QString fileName);
	void loadPlyToSample(QString fileName);
	void savePly(QString fileName, CMesh& mesh);
	void loadImage(QString fileName);
  void loadXYZN(QString fileName);

	bool isSamplesEmpty();
	bool isOriginalEmpty();
  bool isSkeletonEmpty();

	CMesh* getCurrentSamples();
	CMesh* getCurrentOriginal();
	Skeleton* getCurrentSkeleton();

	void recomputeBox();
	double getInitRadiuse();

	void downSamplesByNum(bool use_random_downsample = true);
	void subSamples();

	void normalizeROSA_Mesh(CMesh& mesh);
	Box3f normalizeAllMesh();

	void eraseRemovedSamples();
	void clearData();
	void recomputeQuad();

	void loadSkeletonFromSkel(QString fileName);
	void saveSkeletonAsSkel(QString fileName);


private:
	void clearCMesh(CMesh& mesh);

public:
	CMesh original;
	CMesh samples;
	Skeleton skeleton;
	//cv::Mat image;

	RichParameterSet* para;
	double init_radius;
	QString curr_file_name;
};

