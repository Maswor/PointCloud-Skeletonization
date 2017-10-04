#include "WLOP.h"


WLOP::WLOP(RichParameterSet* _para)
{
	cout << "WLP constructed!!" << endl;
	para = _para;
	samples = NULL;
	original = NULL;
	nTimeIterated = 0;
	error_x = 0.0;
}

WLOP::~WLOP(void)
{
	cout << "WLop destroy!! " << endl; 
}

void WLOP::clear()
{
	samples = NULL;
	original = NULL;
}

void WLOP::setFirstIterate()
{
	nTimeIterated = 0;
}

void WLOP::setInput(DataMgr* pData)
{
	if(!pData->isSamplesEmpty() && !pData->isOriginalEmpty())
	{
		CMesh* _samples = pData->getCurrentSamples();
		CMesh* _original = pData->getCurrentOriginal();

		if(_samples == NULL || _original == NULL)
		{
			cout << "ERROR: WLOP::setInput == NULL!!" << endl;
			return;
		}

		error_x = 0.0;
		samples = _samples;
		original = _original;

		samples_density.assign(samples->vn, 1);
	}
	else
	{
		cout << "ERROR: WLOP::setInput: empty!!" << endl;
		return;
	}
}


void WLOP::initVertexes()
{
	box.SetNull();
	CMesh::VertexIterator vi, vi_end;

	int i = 0;
	vi_end = samples->vert.end();
	for(vi = samples->vert.begin(); vi != vi_end; ++vi) 
	{
		vi->m_index = i++;
		vi->neighbors.clear();
		vi->original_neighbors.clear();

		if (vi->is_skel_ignore)
		{
			continue;
		}
		box.Add(vi->P());
	}
	samples->bbox = box;


	vi_end = original->vert.end();
	i = 0;
	for(vi = original->vert.begin(); vi != vi_end; ++vi) 
	{
		vi->m_index = i++;
		box.Add(vi->P());
	}
	original->bbox = box;


	repulsion.assign(samples->vn, vcg::Point3f(0, 0, 0));
	average.assign(samples->vn, vcg::Point3f(0, 0, 0));

	repulsion_weight_sum.assign(samples->vn, 0);
	average_weight_sum.assign(samples->vn, 0);

	if (para->getBool("Need Compute PCA"))
	{
		CVertex v;
		mesh_temp.assign(samples->vn, v);
	}
}


void WLOP::run()
{
	if (para->getBool("Run Anisotropic LOP"))
	{
		cout << "Run Anisotropic LOP" << endl;
	}
	//int nTimes = para->getDouble("Num Of Iterate Time");
	for(int i = 0; i < 1; i++)
	{ 
		iterate();
		
		nTimeIterated ++;
		cout << "Iterated: " << nTimeIterated << endl;
	}
	cout << "**************iterate Number: " << nTimeIterated << endl;
}

void WLOP::computeAverageTerm(CMesh* samples, CMesh* original)
{
	double average_power = para->getDouble("Average Power");
	bool need_density = para->getBool("Need Compute Density");
	double radius = para->getDouble("CGrid Radius"); 

	double radius2 = radius * radius;
	double iradius16 = -para->getDouble("H Gaussian Para")/radius2;

	cout << "Original Size:" << samples->vert[0].original_neighbors.size() << endl;
	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];

		for (int j = 0; j < v.original_neighbors.size(); j++)
		{
			CVertex& t = original->vert[v.original_neighbors[j]];
			
			Point3f diff = v.P() - t.P();
			double dist2  = diff.SquaredNorm();

			double w = 1;
			if (para->getBool("Run Anisotropic LOP"))
			{
				double len = sqrt(dist2);
				if(len <= 0.001 * radius) len = radius*0.001;
				double hn = diff * v.N();
				double phi = exp(hn * hn * iradius16);
				w = phi / pow(len, 2 - average_power);
			}
			else if (average_power < 2)
			{
				double len = sqrt(dist2);
				if(len <= 0.001 * radius) len = radius*0.001;
				w = exp(dist2 * iradius16) / pow(len, 2 - average_power);
			}
			else
			{
				w = exp(dist2 * iradius16);
			}

			if (need_density)
			{
				w *= original_density[t.m_index];
			}

			average[i] += t.P() * w;  
			average_weight_sum[i] += w;  

		}
	}
}


void WLOP::computeRepulsionTerm(CMesh* samples)
{
	double repulsion_power = para->getDouble("Repulsion Power");
	bool need_density = para->getBool("Need Compute Density");
	double radius = para->getDouble("CGrid Radius"); 

	double radius2 = radius * radius;
	double iradius16 = -para->getDouble("H Gaussian Para")/radius2;

	cout << endl<< endl<< "Sample Neighbor Size:" << samples->vert[0].neighbors.size() << endl<< endl;
	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];
		for (int j = 0; j < v.neighbors.size(); j++)
		{
			CVertex& t = samples->vert[v.neighbors[j]];
			Point3f diff = v.P() - t.P();

			double dist2  = diff.SquaredNorm();
			double len = sqrt(dist2);
			if(len <= 0.001 * radius) len = radius*0.001;

			double w = exp(dist2*iradius16);
			double rep = w * pow(1.0 / len, repulsion_power);

			if (need_density)
			{
				rep *= samples_density[t.m_index];
			}

			repulsion[i] += diff * rep;  
			repulsion_weight_sum[i] += rep;
		}
	}
}


void WLOP::computeDensity(bool isOriginal, double radius)
{
	CMesh* mesh;
	if (isOriginal)
	{
		mesh = original;
	}
	else
	{
		mesh = samples;
	}

	double radius2 = radius * radius;
	double iradius16 = -para->getDouble("H Gaussian Para") / radius2;

	for(int i = 0; i < mesh->vert.size(); i++)
	{
		CVertex& v = mesh->vert[i];

		if (isOriginal)
		{
			original_density[i] = 1.;
		}
		else
		{
			samples_density[i] = 1.;
		}

		vector<int>* neighbors = &v.neighbors;

		for (int j = 0; j < neighbors->size(); j++)
		{
			CVertex& t = mesh->vert[(*neighbors)[j]];
			double dist2  = (v.P() - t.P()).SquaredNorm();
			double den = exp(dist2*iradius16);

			if (isOriginal)
			{
				original_density[i] += den;
			}
			else
			{
				samples_density[i] += den;
			}
		}
	}

	for(int i = 0; i < mesh->vert.size(); i++)
	{
		if (isOriginal)
		{
			CVertex& v = mesh->vert[i];
			original_density[i] = 1. / original_density[i];
		}
		else
		{
			samples_density[i] = sqrt(samples_density[i]);
		}
	}

}


double WLOP::iterate()
{
	Timer time;

	initVertexes();

	time.start("Sample Original Neighbor Tree!!!");
	GlobalFun::computeBallNeighbors(samples, original, 
		para->getDouble("CGrid Radius"), box);
	time.end();

	time.start("Sample Sample Neighbor Tree");
	GlobalFun::computeBallNeighbors(samples, NULL, 
		para->getDouble("CGrid Radius"), samples->bbox);
	time.end();
	
	if (nTimeIterated == 0) 
	{
		if (para->getBool("Need Compute Density"))
		{
			double local_density_para = 0.95;
			time.start("Original Original Neighbor Tree");
			GlobalFun::computeBallNeighbors(original, NULL, 
				para->getDouble("CGrid Radius") * local_density_para, original->bbox);
			time.end();

			time.start("Compute Original Density");
			original_density.assign(original->vn, 0);

			computeDensity(true, para->getDouble("CGrid Radius") * local_density_para);
			time.end();
		}
		
	}

	if (para->getBool("Need Compute Density"))
	{
		time.start("Compute Density For Sample");
		computeDensity(false, para->getDouble("CGrid Radius"));
		time.end();
	}

	time.start("Sample Original Neighbor Tree!!!");
	GlobalFun::computeBallNeighbors(samples, original, 
		para->getDouble("CGrid Radius"), box);
	time.end();

	time.start("Compute Average Term");
	computeAverageTerm(samples, original);
	time.end();

	time.start("Compute Repulsion Term");
	computeRepulsionTerm(samples);
	time.end();

	double mu = para->getDouble("Repulsion Mu");
	Point3f c;

	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];
		c = v.P();

		if (average_weight_sum[i] > 1e-20)
		{
			v.P() = average[i] / average_weight_sum[i];
		}

		if (repulsion_weight_sum[i] > 1e-20 && mu >= 0)
		{
			v.P() +=  repulsion[i] * (mu / repulsion_weight_sum[i]);
		}

		if (average_weight_sum[i] > 1e-20 && repulsion_weight_sum[i] > 1e-20 )
		{
			Point3f diff = v.P() - c; 
			double move_error = sqrt(diff.SquaredNorm());

			error_x += move_error; 
		}
	}
	error_x = error_x / samples->vn;

	para->setValue("Current Movement Error", DoubleValue(error_x));
	cout << "****finished compute WLOP error:	" << error_x << endl;

	if (para->getBool("Need Compute PCA"))
	{
		time.start("Recompute PCA");
		recomputePCA_Normal();
		time.end();
	}
	return error_x;
}


void WLOP::recomputePCA_Normal()
{
	for(int i = 0; i < samples->vn; i++)
	{
		mesh_temp[i].P() = samples->vert[i].P();
	}

	int knn = global_paraMgr.norSmooth.getInt("PCA KNN");
	vcg::NormalExtrapolation<vector<CVertex> >::ExtrapolateNormals(mesh_temp.begin(), mesh_temp.end(), knn, -1);

	for(int i = 0; i < samples->vn; i++)
	{
		Point3f& new_normal = mesh_temp[i].N();
		CVertex& v = samples->vert[i];
		if (v.N() * new_normal > 0)
		{
			v.N() = new_normal;
		}
		else
		{
			v.N() = -new_normal;
		}
		v.recompute_m_render();
	}
}