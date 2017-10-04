#include "Algorithm/NormalSmoother.h"


NormalSmoother::NormalSmoother(RichParameterSet* _para)
{
	mesh = NULL;
	para = _para;
}

NormalSmoother::~NormalSmoother(void)
{
	mesh = NULL;
}

void NormalSmoother::setInput(DataMgr* pData)
{
	if(!pData->isSamplesEmpty())
	{
		input(pData->getCurrentSamples());

		if (pData->getCurrentOriginal())
		{
			orignal_mesh = pData->getCurrentOriginal();
		}
		else
			orignal_mesh = new CMesh;
	}
	else
	{
		cout << "ERROR: NormalSmoother::setInput: empty!!" << endl;
		return;
	}
}

void NormalSmoother::run()
{
	if(mesh == NULL )
	{
		cout << "ERROR: NormalSmoother::run() mesh == NULL || original == NULL";
		return;
	}


	if(para->getBool("Run Anistropic PCA"))
	{
		runAnisotropicPCA();
	}
	else
	{
		//int num_iterate = para->getInt("Number Of Iterate");	
		for(int i = 0; i < 1; i++)
		{
			runNormalSmooth();
		}
	}
}

void NormalSmoother::input(CMesh* _mesh)
{
	if(_mesh == NULL)
	{
		cout << "ERROR:  NormalSmoother::setInput mesh == NULL!!" << endl;
		system("Pause");
		return;
	}
	else
	{
		mesh = _mesh;
	}
}



void NormalSmoother::runAnisotropicPCA()
{
	initVertexes();

	int knnNum = para->getInt("PCA KNN");
	GlobalFun::computeAnnNeigbhors(mesh->vert, mesh->vert, knnNum, true, "runAnisotropicPCA");

	double radius = para->getDouble("CGrid Radius");
	AnistropicPca<vector<CVertex> >::ComputeAPcaNormalsByKNN(mesh->vert.begin(), mesh->vert.end(), 10, 
		radius, para->getDouble("Sharpe Feature Bandwidth Sigma"));

}



void NormalSmoother::initVertexes()
{
	CMesh::VertexIterator vi;
	mesh->bbox = Box3f();
	m_box = Box3f();
	for(vi = mesh->vert.begin(); vi != mesh->vert.end(); ++vi) 
	{
		if (vi->is_skel_ignore)
		{
			continue;
		}
		mesh->bbox.Add(vi->P());
		m_box.Add(vi->P());
	}
}

void NormalSmoother::runNormalSmooth()
{
	double sigma = para->getDouble("Sharpe Feature Bandwidth Sigma");
	double radius = para->getDouble("CGrid Radius"); 

	double radius2 = radius * radius;
	double iradius16 = -4 / radius2;

	CMesh* samples = mesh;
	GlobalFun::computeBallNeighbors(samples, NULL, para->getDouble("CGrid Radius"), samples->bbox);

	normal_sum.assign(samples->vert.size(), Point3f(0.,0.,0.));
	normal_weight_sum.assign(samples->vert.size(), 0);

	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];

		for (int j = 0; j < v.neighbors.size(); j++)
		{
			CVertex& t = samples->vert[v.neighbors[j]];

			Point3f diff = v.P() - t.P();
			double dist2  = diff.SquaredNorm();

			double rep; 

			Point3f vm(v.N());
			Point3f tm(t.N());
			Point3f d = vm-tm;
			double psi = exp(-pow(1-vm*tm, 2)/pow(max(1e-8,1-cos(sigma/180.0*3.1415926)), 2));
			double theta = exp(dist2*iradius16);
			rep = psi * theta;
			rep = max(rep, 1e-10);

			normal_weight_sum[i] += rep;
			normal_sum[i] += tm * rep;         
		}

		if (normal_weight_sum[i] > 1e-6)
		{
			v.N() = normal_sum[i] / normal_weight_sum[i];
		}
	}
}











