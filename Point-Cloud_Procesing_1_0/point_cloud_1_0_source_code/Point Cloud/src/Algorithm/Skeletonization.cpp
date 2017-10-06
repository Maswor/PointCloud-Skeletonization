#include "Skeletonization.h"

void Skeletonization::run()
{
  is_skeleton_locked = false;

	if (para->getBool("Run Auto Wlop One Step"))
	{
		runAutoWlopOneStep();
		cout << "**************iterate Number: " << nTimeIterated << endl;
	}

	if (para->getBool("Step1 Detect Skeleton Feature"))
	{
		runStep1_DetectFeaturePoints();
	}

	if (para->getBool("Step2 Run Search New Branchs"))
	{
		runStep2_SearchNewBranches();
	}

	if (para->getBool("Step3 Clean And Update Radius"))
	{
		runStep3_UpdateRadius();
	}

  if (para->getBool("Run ALL Segment"))
  {
    runAllSegment();
  }
}

void Skeletonization::runAutoWlopOneStep()
{
	runStep0_WLOPIterationAndBranchGrowing();

	if (iterate_error < para->getDouble("Stop And Grow Error") || 
	   	iterate_time_in_one_stage > para->getDouble("Max Iterate Time"))
	{
		cout << "!!!!!!!!!!!!!! Increase Radius Begin !!!!!!!!!!!!!!" << endl;

		runStep1_DetectFeaturePoints();
		runStep2_SearchNewBranches();
		runStep3_UpdateRadius();

    // test if the whole process should stop
    int left_moving_num = getMovingPointsNum();
    double stop_radius = para->getDouble("Max Stop Radius");
    double current_radius = para->getDouble("CGrid Radius");
    if (left_moving_num <= para->getDouble("Accept Branch Size") ||
          current_radius > stop_radius)
    {
      finalProcess();
    }


		if (para->getBool("Run Auto Wlop One Stage"))
		{
			para->setValue("The Skeletonlization Process Should Stop", BoolValue(true));
		}


		cout << "!!!!!!!!!!!!!! Increase Radius End !!!!!!!!!!!!!!" << endl;
    iterate_time_in_one_stage = 0;
	}
}


void Skeletonization::finalProcess()
{
  para->setValue("The Skeletonlization Process Should Stop", BoolValue(true));

  dealWithVirtualsForAllBranch();

  vector<Branch>& branches = skeleton->branches;
  for (int i = 0; i < branches.size(); i++)
  {
    Branch& branch = branches[i];

    //not sure 2013-7-13
    if (branch.isHeadVirtual())
    {
      branch.inactiveAndKeepVirtualHead();
    }
    if (branch.isTailVirtual())
    {
      branch.inactiveAndKeepVirtualTail();
    }
  }

  for(int i = 0; i < samples->vert.size(); i++)
  {
    if (samples->vert[i].isSample_JustMoving())
    {
      samples->vert[i].setSample_FixedAndBranched();
    }
  }

  if (para->getBool("Need Segment Right Away"))
  {
    Timer time;
    time.start("Run refefinement");
    runAllSegment();
    time.end();
  }

}


void Skeletonization::runStep0_WLOPIterationAndBranchGrowing()
{
  if (nTimeIterated == 0)
  {
    double init_radius = para->getDouble("CGrid Radius");
    para->setValue("Initial Radius", DoubleValue(init_radius));
    iterate_time_in_one_stage = 0;
  }
	
  time.start("updateAllCurvesFollowSamples()");
  updateAllBranchesFollowSamples();
  time.end();

  time.start("growAllCurvesWithVirtual()");
  growAllBranches();
  time.end();

  time.start("dealWithVirtualsForAllCurve()");
  dealWithVirtualsForAllBranch();
  time.end();

  if (para->getBool("Use Clean Points When Following Strategy"))
  {
    time.start("cleanPointsNearBranches()");
    cleanPointsNearBranches();
    time.end();
  }

  iterate_error = wlopIterate();
  para->setValue("Current Movement Error", DoubleValue(iterate_error));
  
	iterate_time_in_one_stage++;
	nTimeIterated ++;
	cout << "&&&&&&Iterated: " << nTimeIterated << endl;
}

void Skeletonization::runStep1_DetectFeaturePoints()
{
	cout << "runStep1_DetectFeaturePoints" << endl;

	removeTooClosePoints();

	eigenThresholdIdentification();
}

void Skeletonization::runStep2_SearchNewBranches()
{
	cout << "runStep2_SearchNewBranches" << endl;

	searchNewBranches();

	growAllBranches();
}

void Skeletonization::runStep3_UpdateRadius()
{
	cout << "runStep3_UpdateRadius" << endl;

  mergeNearEndsGroup();
  cleanPointsNearBranches();
  labelFixOriginal();
  rememberVirtualEnds();
  increaseRadius();
}

Skeletonization::Skeletonization(RichParameterSet* _para)
{
	cout << "WLP constructed!!" << endl;
	para = _para;
	samples = NULL;
	original = NULL;
	skeleton = NULL;
	nTimeIterated = 0;
	error_x = 0.0;
	iterate_time_in_one_stage = 0;
}

Skeletonization::~Skeletonization(void)
{
	cout << "Skeletonization destroy!! " << endl; 
}

void Skeletonization::clear()
{
	samples = NULL;
	original = NULL;
	skeleton = NULL;
}

void Skeletonization::setFirstIterate()
{
	nTimeIterated = 0;
}

void Skeletonization::setInput(DataMgr* pData)
{
	if(!pData->isSamplesEmpty() && !pData->isOriginalEmpty())
	{
		CMesh* _samples = pData->getCurrentSamples();
		CMesh* _original = pData->getCurrentOriginal();
		Skeleton* _skeleton = pData->getCurrentSkeleton();

		if(_samples == NULL || _original == NULL)
		{
			cout << "ERROR: Skeletonization::setInput == NULL!!" << endl;
			return;
		}

		error_x = 0.0;
		samples = _samples;
		original = _original;
		skeleton = _skeleton;

		samples_density.assign(samples->vn, 1);
	}
	else
	{
		cout << "ERROR: Skeletonization::setInput: empty!!" << endl;
		return;
	}
}


void Skeletonization::initVertexes()
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
}




void Skeletonization::computeAverageTerm(CMesh* samples, CMesh* original)
{
	double average_power = para->getDouble("Average Power");
	bool need_density = para->getBool("Need Compute Density");
	double radius = para->getDouble("CGrid Radius"); 
  double fix_original_weight = para->getDouble("Fix Original Weight");

	double radius2 = radius * radius;
	double iradius16 = -para->getDouble("H Gaussian Para")/radius2;

	cout << "Original Size:" << samples->vert[0].original_neighbors.size() << endl;
	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];

		if (v.is_fixed_sample) //Here is different from WLOP
		{
			average_weight_sum[i] = 0.;
			continue;
		}

		for (int j = 0; j < v.original_neighbors.size(); j++)
		{
			CVertex& t = original->vert[v.original_neighbors[j]];

			Point3f diff = v.P() - t.P();
			double dist2  = diff.SquaredNorm();

			double w = 1;
			if (average_power < 2)
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

      if (t.is_fixed_original)
      {
        w *= fix_original_weight;
      }

			average[i] += t.P() * w;  
			average_weight_sum[i] += w;  
		}
	}
}


void Skeletonization::computeRepulsionTerm(CMesh* samples)
{
	double repulsion_power = para->getDouble("Repulsion Power");
	double radius = para->getDouble("CGrid Radius"); 

	double radius2 = radius * radius;
	double iradius16 = -para->getDouble("H Gaussian Para")/radius2;

	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];

		if (v.is_fixed_sample || v.is_skel_ignore)//Here is different from WLOP
		{
			repulsion_weight_sum[i] = 0.;
			continue;
		}

		for (int j = 0; j < v.neighbors.size(); j++)
		{
			CVertex& t = samples->vert[v.neighbors[j]];
			Point3f diff = v.P() - t.P();

			double dist2  = diff.SquaredNorm();
			double len = sqrt(dist2);
			if(len <= 0.001 * radius) len = radius*0.001;

			double w = exp(dist2*iradius16);
			double rep = w * pow(1.0 / len, repulsion_power);

			repulsion[i] += diff * rep;  
			repulsion_weight_sum[i] += rep;
		}
	}
}


void Skeletonization::computeDensity(bool isOriginal, double radius)
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


double Skeletonization::wlopIterate()
{
	Timer time;

	initVertexes();

	time.start("Samples Initial");
	GlobalFun::computeBallNeighbors(samples, NULL, 
		para->getDouble("CGrid Radius"), samples->bbox);
	GlobalFun::computeEigenWithTheta(samples, para->getDouble("CGrid Radius") / sqrt(para->getDouble("H Gaussian Para")));
	time.end();

	if (nTimeIterated == 0) 
	{
		time.start("Original Initial");
		GlobalFun::computeBallNeighbors(original, NULL, 
			para->getDouble("CGrid Radius"), original->bbox);

		original_density.assign(original->vn, 0);
		if (para->getBool("Need Compute Density"))
		{
			computeDensity(true, para->getDouble("CGrid Radius"));
		}
		time.end();
	}

	time.start("Sample Original neighbor");
	GlobalFun::computeBallNeighbors(samples, original, 
		para->getDouble("CGrid Radius"), box);
	time.end();

	time.start("computeAverageTerm");
	computeAverageTerm(samples, original);
	time.end();

	time.start("computeRepulsionTerm");
	computeRepulsionTerm(samples);
	time.end();

	double min_sigma = GlobalFun::getDoubleMAXIMUM();
	double max_sigma = -1;
	for (int i = 0; i < samples->vn; i++)
	{
		CVertex& v = samples->vert[i];
		if (v.eigen_confidence < min_sigma)
		{
			min_sigma = v.eigen_confidence;
		}
		if (v.eigen_confidence > max_sigma)
		{
			max_sigma = v.eigen_confidence;
		}
	}

	double mu_max = para->getDouble("Repulsion Mu");
	double mu_min = para->getDouble("Repulsion Mu2");
	double mu_length = abs(mu_max - mu_min);
	double sigma_length = abs(max_sigma - min_sigma);
	Point3f c;
	int moving_num = 0;
	double max_error = 0;

	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];
		if (v.is_fixed_sample || v.is_skel_ignore)
		{
			continue;
		}
		c = v.P();

		double mu = (mu_length / sigma_length) * (v.eigen_confidence - min_sigma) + mu_min;

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
			moving_num++;
			Point3f diff = v.P() - c; 
			double move_error = sqrt(diff.SquaredNorm());

			error_x += move_error; 
		}
	}
	error_x = error_x / moving_num;

	para->setValue("Current Movement Error", DoubleValue(error_x));
	cout << "****finished compute Skeletonization error:	" << error_x << endl;
	return error_x;
}


void Skeletonization::removeTooClosePoints()
{
	double near_threshold = para->getDouble("Combine Too Close Threshold");
	double near_threshold2 = near_threshold * near_threshold;

	for (int i = 0; i < samples->vn; i++)
	{
		CVertex& v = samples->vert[i];
		for (int j = 0; j < v.neighbors.size(); j++)
		{
			CVertex& t = samples->vert[v.neighbors[j]];

			if (!t.isSample_JustMoving())
			{
				continue;
			}

			double dist2 = GlobalFun::computeEulerDistSquare(v.P(), t.P());
			if (dist2 < near_threshold2)
			{
				t.remove();
			}
		}
	}
}

void Skeletonization::eigenThresholdIdentification()
{
	int sigma_KNN = para->getDouble("Sigma KNN");

	GlobalFun::computeAnnNeigbhors(samples->vert, samples->vert, sigma_KNN, false, "void Skeletonization::eigenThresholdClassification()");

	if (para->getBool("Use Compute Eigen Ignore Branch Strategy"))
	{
		GlobalFun::computeEigenIgnoreBranchedPoints(samples);
	}
	else
	{
		GlobalFun::computeEigen(samples);
	}

	eigenConfidenceSmoothing();

	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];

		if (!v.isSample_Moving())
		{
			continue;
		}

		double eigen_psi = v.eigen_confidence;
		double eigen_threshold = para->getDouble("Eigen Feature Identification Threshold");

		if (eigen_psi > eigen_threshold)
		{
			v.is_fixed_sample = true;
		}
		else
		{
			v.is_fixed_sample = false;
		}
	}
}

void Skeletonization::eigenConfidenceSmoothing()
{
	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];
		v.eigen_confidence = 1 - v.eigen_confidence;
	}

	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];
		double sum = v.eigen_confidence;
		for (int j = 0; j < v.neighbors.size(); j++)
		{
			sum += samples->vert[v.neighbors[j]].eigen_confidence;
		}
		v.eigen_confidence = sum / (v.neighbors.size() + 1);
	}

	for(int i = 0; i < samples->vert.size(); i++)
	{
		CVertex& v = samples->vert[i];
		v.eigen_confidence = 1 - v.eigen_confidence;

    if (v.eigen_confidence < 0)
    {
      v.eigen_confidence = 0.5;
    }
	}
}

void Skeletonization::searchNewBranches()
{
	int branch_KNN = para->getDouble("Branch Search KNN");
	GlobalFun::computeAnnNeigbhors(samples->vert, samples->vert, branch_KNN, false, "void Skeletonization::searchNewBranches()");

	while(1)
	{
		int max_confidence_id = -1;
		double max_eigen_confidence = 0;
		for (int i = 0; i <samples->vert.size(); i++)
		{
			CVertex& v = samples->vert[i];
			if (!v.isSample_JustFixed())
			{
				continue;
			}

			if (v.eigen_confidence > max_eigen_confidence)
			{
				max_confidence_id = i;
				max_eigen_confidence = v.eigen_confidence;
			}
		}

		if (max_confidence_id < 0)
		{
			break;
		}

		Branch new_branch = searchOneBranchFromIndex(max_confidence_id);

		int accept_branch_size = para->getDouble("Accept Branch Size");
		int add_size = para->getDouble("Add Accept Branch Size");
		double current_radius = para->getDouble("CGrid Radius");
		double init_radius = para->getDouble("Initial Radius");

		int rate = current_radius / init_radius;
		if (rate > 0)
		{
			accept_branch_size += add_size * rate;
		}

		growOneBranchByVirtual(new_branch);

		if (new_branch.isEmpty())
		{
			if (!samples->vert[max_confidence_id].is_skel_virtual)
			{
				samples->vert[max_confidence_id].setSample_JustMoving();
			}
		}
		else if (new_branch.getSize() < accept_branch_size)
		{
      Curve& new_curve = new_branch.curve;
      for (int i = 0; i < new_curve.size(); i++)
      {
        if (!samples->vert[new_curve[i].m_index].is_skel_virtual)
        {
          samples->vert[new_curve[i].m_index].setSample_JustMoving(); //carefull 1-12
        }
      }
		}
		else
		{
			// Virtual Points creat here and remember skel_radius
			for (int i = 0; i < new_branch.getSize(); i++)
			{
				if (new_branch.curve[i].is_skel_virtual) 
				{
					samples->vert[new_branch.curve[i].m_index].setSample_MovingAndVirtual();
					new_branch.branch_id = skeleton->branches.size();
					if (i==0)
					{
						new_branch.rememberVirtualHead();
					}
					else if (i == new_branch.getSize()-1)
					{
						new_branch.rememberVirtualTail();
					}
				}
				else
				{
					samples->vert[new_branch.curve[i].m_index].setSample_FixedAndBranched();
          new_branch.curve[i].skel_radius = current_radius; // skel_radius
				}
			}
			skeleton->branches.push_back(new_branch);
			skeleton->generateBranchSampleMap();
		}
	}

  for (int i = 0; i <samples->vert.size(); i++)
  {
    CVertex& v = samples->vert[i];
    if (v.isSample_JustFixed())
    {
      v.setSample_JustMoving();
    }
  }
}

Branch Skeletonization::searchOneBranchFromIndex(int begin_idx)
{
	Branch new_branch;
	CVertex begin_v = samples->vert[begin_idx];
	if (begin_v.is_skel_branch)
	{
		cout << "why start from branched points ?!" << endl;
		return new_branch;
	}

	if (begin_v.neighbors.size() < 1)
	{
		cout << "empty neighbor of begin_v " << endl;
		return new_branch;
	}

	int nearest_idx = -1;
	for (int i = 0; i < begin_v.neighbors.size(); i++)
	{
		CVertex& t = samples->vert[begin_v.neighbors[i]];
		if (t.isSample_JustFixed())
		{
			nearest_idx = begin_v.neighbors[i];
			break;
		}
	}
	if (nearest_idx < 0)
	{
		return new_branch;
	}


	CVertex& t = samples->vert[nearest_idx];
	Point3f head_direction = (t.P() - begin_v.P()).Normalize();
	vector<int> indexes0, indexes1;
	Branch branch0 = searchOneBranchFromDirection(begin_idx, head_direction);
	Branch branch1 = searchOneBranchFromDirection(begin_idx, -head_direction);

	Curve curve0 = branch0.curve;
	Curve curve1 = branch1.curve;

	Curve::reverse_iterator riter = curve1.rbegin();
	for(int i = 0; i < curve1.size()-1; i++)
	{
		new_branch.pushBackCVertex(*riter);
		riter++;
	}

	for (int i = 0; i < curve0.size(); i++)
	{
		new_branch.pushBackCVertex(curve0[i]);
	}

	return new_branch;
}


Branch Skeletonization::searchOneBranchFromDirection(int begin_idx, Point3f head_direction)
{
	double MAX_Euler_dist = para->getDouble("Snake Search Max Dist Blue");
	double MAX_Perpendicular_dist = para->getDouble("Branch Search Max Dist Yellow");
	double MAX_Too_Close_dist = para->getDouble("Combine Too Close Threshold");

	double MAX_Euler_dist2 = MAX_Euler_dist * MAX_Euler_dist;
	double MAX_Perpendicular_dist2 = MAX_Perpendicular_dist * MAX_Perpendicular_dist;
	double MAX_Too_Close_dist2 = MAX_Too_Close_dist * MAX_Too_Close_dist;

	Branch new_branch;
	int curr_idx = begin_idx;
	do 
	{
		CVertex curr_v = samples->vert[curr_idx];
		new_branch.pushBackCVertex(curr_v);

		int next_idx = -1;
		double min_dist = GlobalFun::getDoubleMAXIMUM();
		for (int i = 0; i < curr_v.neighbors.size(); i++)
		{
			CVertex& t = samples->vert[curr_v.neighbors[i]];
			if (t.is_skel_ignore)
			{
				continue;
			}

			double euler_dist2 = GlobalFun::computeEulerDistSquare(curr_v.P(), t.P());
			if (euler_dist2 > MAX_Euler_dist2)
			{
				continue;
			}

			if (euler_dist2 < MAX_Too_Close_dist2)
			{
				t.remove();
				continue;
			}

			double proj_dist = GlobalFun::computeProjDist(curr_v.P(), t.P(), head_direction);
			if (proj_dist < 0)
			{
				continue;
			}

			next_idx = curr_v.neighbors[i];
			break;
		}

		if (next_idx < 0) // No virtual head/tail
		{
			break;
		}

		CVertex next_v = samples->vert[next_idx]; //2013-7-12
		Point3f new_direction = (next_v.P() - curr_v.P()).Normalize();
		
		double angle = GlobalFun::computeRealAngleOfTwoVertor(head_direction, new_direction);
		if (angle > para->getDouble("Branches Search Angle") || !next_v.is_fixed_sample || next_v.is_skel_branch || next_v.is_skel_virtual)
		{

			next_v.is_skel_virtual = true; // the corresponding sample point is not virtual
			new_branch.pushBackCVertex(next_v);
			break;
		}

		head_direction = new_direction;
		curr_idx = next_idx;

	} while (1);

	return new_branch;
}


void Skeletonization::growVirtualTailUntilStop(Branch& branch)
{
	double follow_dist = para->getDouble("Grow Search Radius");
	double follow_dist2 = follow_dist * follow_dist;

	double too_close_dist = para->getDouble("Combine Too Close Threshold");
	double too_close_dist2 = too_close_dist * too_close_dist;

	double grow_accept_sigma = para->getDouble("Grow Accept Sigma");
	double angle_threhold = para->getDouble("Virtual Head Accecpt Angle");
	double save_virtual_angle = para->getDouble("Save Virtual Angle");

	bool is_tail_growing = true;
	bool is_ignore_something = false;

	Curve& curve = branch.curve;
	while(is_tail_growing)
	{
		if (curve.size() < 3 || !branch.isTailVirtual())
		{
			return;
		}

		CVertex tail = curve[curve.size()-1];
		//find nearest red points
		//if (tail.m_index < 0 || tail.m_index >= samples->vert.size() || 
		//	GlobalFun::computeEulerDistSquare(tail.P(), samples->vert[tail.m_index].P()) > 1e-6)
		//{
		//	cout << "grow out of sample index" << endl;
		//	reIndexBranchesVirtualHeadTail();
		//	break;
		//}

		CVertex& v = samples->vert[tail.m_index];
		if (v.neighbors.empty())
		{
			cout << "empty neighbor????" << endl;
			return;
		}

		double min_dist = GlobalFun::getDoubleMAXIMUM();
		int min_idx = -1;
		int near_moving_count = 0;
		Point3f tail_direction = branch.getVirtualTailDirection();
		double candidate_sigma = 0;
		for (int j = 0; j < v.neighbors.size(); j++)
		{
			CVertex& t = samples->vert[v.neighbors[j]];
			if (!t.is_skel_ignore)
			{
				double dist2 = GlobalFun::computeEulerDistSquare(v.P(), t.P());
				if (dist2 < too_close_dist2 && !t.is_skel_virtual)
				{
					t.remove();
					continue;
				}

				if ( dist2 < follow_dist2)
				{
					if (t.isSample_Moving())
					{
						near_moving_count++;
					}

					double proj_dist = GlobalFun::computeProjDist(tail.P(), t.P(), tail_direction);
					if (proj_dist < 0)
					{
						continue;
					}

					if (dist2 < min_dist)
					{
						min_dist = dist2;
						min_idx = v.neighbors[j];
						candidate_sigma = t.eigen_confidence;
					}

				}
			}
		}

		if (min_idx < 0 || candidate_sigma < grow_accept_sigma)
		{
			is_tail_growing = false;
		}
		else
		{
			CVertex& near_v = samples->vert[min_idx];

			CVertex& real_tail = curve[curve.size()-2];
			CVertex& real_tail_last = curve[curve.size()-3];

			Point3f v0 = (real_tail.P() - real_tail_last.P()).Normalize();
			Point3f v1 = (tail.P() - real_tail.P()).Normalize();
			Point3f v2 = (near_v.P() - tail.P()).Normalize();

			double angle0 = GlobalFun::computeRealAngleOfTwoVertor(v0, v1);
			double angle1 = GlobalFun::computeRealAngleOfTwoVertor(v1, v2);

			if (angle0 >= 0 && angle1 >= 0 &&
				 angle0  < angle_threhold && angle1 < angle_threhold)
			{
				if (near_v.is_skel_branch)
				{
					is_tail_growing = false;
				}
				else
				{
					v.setSample_FixedAndBranched();
					curve[curve.size()-1].setSample_FixedAndBranched();

					near_v.setSample_MovingAndVirtual();
					branch.pushBackCVertex(near_v);
					is_tail_growing = true;

					branch.rememberVirtualTail();
				}
			}
			else
			{
				is_tail_growing = false;
			}
		}
	}
}

void Skeletonization::growOneBranchByVirtual(Branch& branch)
{
	if (branch.getSize() < 2)
	{
		return;
	}

	if (branch.isTailVirtual())
	{
		growVirtualTailUntilStop(branch);
	}

	if (branch.isHeadVirtual())
	{
		branch.reverseBranch();
		growVirtualTailUntilStop(branch);
	}
}

void Skeletonization::growAllBranches()
{
	for(int i = 0; i < skeleton->branches.size(); i++)
	{
		growOneBranchByVirtual(skeleton->branches[i]);
	}

}



void Skeletonization::mergeNearEndsGroup()
{
	vector<Point3f> visited_pts;

	for (int i = 0; i < skeleton->branches.size(); i++)
	{
		Point3f head = skeleton->branches[i].getHead();
		Point3f tail = skeleton->branches[i].getTail();

		double dist_between_head_tail_2 = GlobalFun::computeEulerDistSquare(head, tail);
		double merge_dist = para->getDouble("Branches Merge Max Dist");
		merge_dist *= 1.1;
		double merge_dist2 = merge_dist * merge_dist;

		if (dist_between_head_tail_2 > merge_dist2)
		{
			if (!isPosVisited(visited_pts, head, merge_dist2 * 0.6))
			{
				mergeNearEndsGroupFromP(head);
				visited_pts.push_back(head);
			}

			if (!isPosVisited(visited_pts, tail, merge_dist2 * 0.6))
			{
				mergeNearEndsGroupFromP(tail);
				visited_pts.push_back(tail);
			}
		}
		else
		{
      cout << "have danger" << endl;
			//visited_pts.push_back(head);
			//visited_pts.push_back(tail);
		}
	}

}

bool Skeletonization::isPosVisited(vector<Point3f>& visited_pts, Point3f p, double dist_threshold)
{
	for (int i = 0; i < visited_pts.size(); i++)
	{
		double dist2 = GlobalFun::computeEulerDistSquare(p, visited_pts[i]);
		if (dist2 < dist_threshold)
		{
			return true;
		}
	}
	return false;
}


bool Skeletonization::mergeNearEndsGroupFromP(Point3f p0)
{
	double MAX_Merge_Dist = para->getDouble("Branches Merge Max Dist");
	double MAX_Merge_Dist2 = MAX_Merge_Dist * MAX_Merge_Dist;

	vector<RecordItem> group;

	bool meet_short_branch = false;
	
	Point3f average_P = Point3f(0, 0, 0);
	vector<Point3f> dangerous_Pts;
	vector<Point3f> nearby_Pts;
	for (int i = 0; i < skeleton->branches.size(); i++)
	{
		Curve& curve = skeleton->branches[i].curve;

		double dist_head = GlobalFun::computeEulerDistSquare(curve[0], p0);
		double dist_tail = GlobalFun::computeEulerDistSquare(curve[curve.size()-1], p0);

		if (dist_head < MAX_Merge_Dist2 && dist_tail < MAX_Merge_Dist2)
		{
			meet_short_branch = true;
			if (dist_head < dist_tail)
			{
				group.push_back(RecordItem(i, 0));
				average_P += curve[0].P();
				nearby_Pts.push_back(curve[0].P());
				dangerous_Pts.push_back(curve[curve.size()-1].P());
			}
			else
			{
				group.push_back(RecordItem(i, curve.size()-1));
				average_P += curve[curve.size()-1].P();
				nearby_Pts.push_back(curve[curve.size()-1].P());
				dangerous_Pts.push_back(curve[0].P());
			}
		}
		else if (dist_head < MAX_Merge_Dist2)
		{
			group.push_back(RecordItem(i, 0));
			average_P += curve[0].P();
			nearby_Pts.push_back(curve[0].P());
		}
		else if (dist_tail < MAX_Merge_Dist2)
		{
			group.push_back(RecordItem(i, curve.size()-1));
			average_P += curve[curve.size()-1].P();
			nearby_Pts.push_back(curve[curve.size()-1].P());
		}
	}

	average_P /= group.size();

	assert(nearby_Pts.size() == group.size());
	if (!dangerous_Pts.empty())
	{
		vector<int> exclued_ids;
		for (int i = 0; i < nearby_Pts.size(); i++)
		{
			Point3f p = nearby_Pts[i];
			double dist_to_avg = GlobalFun::computeEulerDistSquare(average_P, p);

			bool neet_to_exclued = false;
			for (int j = 0; j < dangerous_Pts.size(); j++)
			{
				double dist_to_dang = GlobalFun::computeEulerDistSquare(dangerous_Pts[j], p);
				if (dist_to_dang < dist_to_avg)
				{
					neet_to_exclued = true;
					break;
				}
			}

			if (neet_to_exclued)
			{
				exclued_ids.push_back(i);
			}
		}

		if (!exclued_ids.empty())
		{
			vector<RecordItem> temp_group;
			vector<Point3f> temp_nearby_pts;
			Point3f temp_average = Point3f(0, 0 ,0);

			for (int i = 0; i < group.size(); i++)
			{
				if (find(exclued_ids.begin(), exclued_ids.end(), i) == exclued_ids.end())
				{ 
					temp_group.push_back(group[i]);
					temp_nearby_pts.push_back(nearby_Pts[i]);
					temp_average += nearby_Pts[i];
				}
			}

			average_P = temp_average / temp_nearby_pts.size();
			group = temp_group;
		}
	}

	if (group.size() >= 3)
	{
		for (int i = 0; i < group.size(); i++)
		{
			RecordItem& item = group[i];
			Branch& branch = skeleton->branches[group[i].branch_i];
			if (item.node_j == 0)
			{			
				//cout << "inactive head because of:	" << "Group Merge" << endl;
				branch.moveHeadToPt(average_P);
			}
			else
			{
				//cout << "inactive tail because of:	" << "Group Merge" << endl;
				branch.moveTailToPt(average_P);
			}	
		}
		return true;
	}
	else if (group.size() == 2 && !is_skeleton_locked)
	{
		double close_dist = 1e-6;

		RecordItem& item0 = group[0];
		RecordItem& item1 = group[1];

    if (item0.branch_i == item1.branch_i)
    {
      return false;
    }

    Branch& branch0 = skeleton->branches[item0.branch_i];
    Branch& branch1 = skeleton->branches[item1.branch_i];

    Curve& curve0 = branch0.curve;
    Curve& curve1 = branch1.curve;

    Point3f end0 = curve0[item0.node_j];
    Point3f end1 = curve1[item1.node_j];

    double end_dist2 = GlobalFun::computeEulerDistSquare(end0, end1);

    CONNECT_TYPE best_c_type;
    double best_angle = -1;
    double min_dist2 = -1;

    compareTwoCurvesEnds(curve0, curve1, min_dist2, best_angle, best_c_type);

    double diff = end_dist2 - min_dist2;
    double diff2 = diff * diff;
    if (diff2 > 1e-6)
    {
      return false;
    }

    if (min_dist2 > MAX_Merge_Dist2)
    {
      return false;
    }

    double angle_threshold = para->getDouble("Combine Similar Angle");
    if (best_angle > angle_threshold)
    {
      Branch new_branch = mergeTowBranches(branch0, branch1, best_c_type);
      branch0 = new_branch;
      skeleton->branches.erase(skeleton->branches.begin() + branch1.branch_id);
      skeleton->generateBranchSampleMap();
    }
    else if (end_dist2 < 1e-4)
    {
      if (item0.node_j == 0)
      {
        branch0.inactiveAndKeepVirtualHead();
      }
      else
      {
        branch0.inactiveAndKeepVirtualTail();
      }

      if (item1.node_j == 0)
      {
        branch1.inactiveAndKeepVirtualHead();
      }
      else
      {
        branch1.inactiveAndKeepVirtualTail();
      }
    }
	}


	return false;

}


void Skeletonization::compareTwoCurvesEnds(Curve& c0, Curve& c1, double& min_dist, double& angle, CONNECT_TYPE& C_Type)
{
  if (isTowCurvesTheSame(c0, c1))
  {
    return;
  }

  if (c0.size() <= 3 || c1.size() <= 3)
  {
    return;
  }

  vector<Point3f> head0;
  head0.push_back(c0[0].P());
  if (c0[0].is_skel_virtual)
  {
    head0.push_back(c0[1].P());
  }

  vector<Point3f> tail0;
  tail0.push_back(c0[c0.size()-1].P());
  if (c0[c0.size()-1].is_skel_virtual)
  {
    tail0.push_back(c0[c0.size()-2].P());
  }

  vector<Point3f> head1;
  head1.push_back(c1[0].P());
  if (c1[0].is_skel_virtual)
  {
    head1.push_back(c1[1].P());
  }

  vector<Point3f> tail1;
  tail1.push_back(c1[c1.size()-1].P());
  if (c1[c1.size()-1].is_skel_virtual)
  {
    tail1.push_back(c1[c1.size()-2].P());
  }


  min_dist = GlobalFun::getDoubleMAXIMUM();

  double min_H0_H1_dist = GlobalFun::getDoubleMAXIMUM();
  for (int i = 0; i < head0.size(); i++)
  {
    Point3f h0 = head0[i];
    for (int j = 0; j < head1.size(); j++)
    {
      Point3f h1 = head1[j];
      double dist = GlobalFun::computeEulerDistSquare(h0, h1);
      if (dist < min_H0_H1_dist)
      {
        min_H0_H1_dist = dist;
      }
    }
  }

  double min_H0_T1_dist = GlobalFun::getDoubleMAXIMUM();
  for (int i = 0; i < head0.size(); i++)
  {
    Point3f h0 = head0[i];
    for (int j = 0; j < tail1.size(); j++)
    {
      Point3f t1 = tail1[j];
      double dist = GlobalFun::computeEulerDistSquare(h0, t1);
      if (dist < min_H0_T1_dist)
      {
        min_H0_T1_dist = dist;
      }
    }
  }

  double min_T0_H1_dist = GlobalFun::getDoubleMAXIMUM();
  for (int i = 0; i < tail0.size(); i++)
  {
    Point3f t0 = tail0[i];
    for (int j = 0; j < head1.size(); j++)
    {
      Point3f h1 = head1[j];
      double dist = GlobalFun::computeEulerDistSquare(t0, h1);
      if (dist < min_T0_H1_dist)
      {
        min_T0_H1_dist = dist;
      }
    }
  }

  double min_T0_T1_dist = GlobalFun::getDoubleMAXIMUM();
  for (int i = 0; i < tail0.size(); i++)
  {
    Point3f t0 = tail0[i];
    for (int j = 0; j < tail1.size(); j++)
    {
      Point3f t1 = tail1[j];
      double dist = GlobalFun::computeEulerDistSquare(t0, t1);
      if (dist < min_T0_T1_dist)
      {
        min_T0_T1_dist = dist;
      }
    }
  }

  if (min_H0_H1_dist < min_dist)
  {
    min_dist = min_H0_H1_dist;
    C_Type = H0_H1;
  }

  if (min_H0_T1_dist < min_dist)
  {
    min_dist = min_H0_T1_dist;
    C_Type = H0_T1;
  }

  if (min_T0_H1_dist < min_dist)
  {
    min_dist = min_T0_H1_dist;
    C_Type = T0_H1;
  }

  if (min_T0_T1_dist < min_dist)
  {
    min_dist = min_T0_T1_dist;
    C_Type = T0_T1;
  }

  angle = getRealAngeOfTowCurve(c0, c1, C_Type);
}

double Skeletonization::getRealAngeOfTowCurve(Curve& c0, Curve& c1, CONNECT_TYPE C_Type)
{
  double real_angle = 0;

  vector<Point3f> head0_directions;
  head0_directions.push_back(c0[0].P() - c0[1].P());
  if (c0[0].is_skel_virtual)
  {
    head0_directions.push_back(c0[1].P() - c0[2].P());
  }

  vector<Point3f> tail0_directions;
  tail0_directions.push_back(c0[c0.size()-1].P() - c0[c0.size()-2].P());
  if (c0[c0.size()-1].is_skel_virtual)
  {
    tail0_directions.push_back(c0[c0.size()-2].P() - c0[c0.size()-3].P());
  }

  vector<Point3f> head1_directions;
  head1_directions.push_back(c1[0].P() - c1[1].P());
  if (c1[0].is_skel_virtual)
  {
    head1_directions.push_back(c1[1].P() - c1[2].P());
  }

  vector<Point3f> tail1_directions;
  tail1_directions.push_back(c1[c1.size()-1].P() - c1[c1.size()-2].P());
  if (c1[c1.size()-1].is_skel_virtual)
  {
    tail1_directions.push_back(c1[c1.size()-2].P() - c1[c1.size()-3].P());
  }

  switch (C_Type)
  {
  case H0_H1:
    //real_angle = GlobalFun::computeRealAngleOfTwoVertor(head0_direction, head1_direction);
    real_angle = getMaxAngleOfTwoPair(head0_directions, head1_directions);
    break;

  case H0_T1:
    //real_angle = GlobalFun::computeRealAngleOfTwoVertor(head0_direction, tail1_direction);
    real_angle = getMaxAngleOfTwoPair(head0_directions, tail1_directions);
    break;

  case T0_H1:
    //real_angle = GlobalFun::computeRealAngleOfTwoVertor(tail0_direction, head1_direction);
    real_angle = getMaxAngleOfTwoPair(tail0_directions, head1_directions);
    break;

  case T0_T1:
    //real_angle = GlobalFun::computeRealAngleOfTwoVertor(tail0_direction, tail1_direction);
    real_angle = getMaxAngleOfTwoPair(tail0_directions, tail1_directions);
    break;
  }

  return real_angle;
}

double Skeletonization::getMaxAngleOfTwoPair(vector<Point3f>& dir0, vector<Point3f>& dir1)
{
  double max_angle = -1;
  for (int i = 0; i < dir0.size(); i++)
  {
    Point3f d0 = dir0[i];
    for (int j = 0; j < dir1.size(); j++)
    {
      Point3f d1 = dir1[j];
      double angle = GlobalFun::computeRealAngleOfTwoVertor(d0, d1);
      if (angle > max_angle)
      {
        max_angle = angle;
      }
    }
  }

  return max_angle;
}

 bool Skeletonization::isTowCurvesTheSame(Curve& c0, Curve& c1)
 {
   if (c0.size() != c1.size())
   {
     return false;
   }

   if (c0.empty() || c1.empty())
   {
     return false;
   }

   double dist1 = GlobalFun::computeEulerDistSquare(c0[0].P(), c1[0].P());
   if (dist1 > 1e-6)
   {
     return false;
   }

   double dist2 = GlobalFun::computeEulerDistSquare(c0[c0.size()-1].P(), c1[c1.size()-1].P());
   if (dist2 > 1e-6)
   {
     return false;
   }

   return true;
 }

 Branch Skeletonization::mergeTowBranches(Branch& branch0, Branch& branch1, CONNECT_TYPE C_Type)
 {
   Curve& c0 = branch0.curve;
   Curve& c1 = branch1.curve;

   if (C_Type == UNKNOWN)
   {
     double min_dist, best_angle;
     compareTwoCurvesEnds(c0, c1, min_dist, best_angle, C_Type);
   }

   bool is_head0_virtual = branch0.isHeadVirtual();
   bool is_tail0_virtual = branch0.isTailVirtual();
   bool is_head1_virtual = branch1.isHeadVirtual();
   bool is_tail1_virtual = branch1.isTailVirtual();

   Branch new_branch;
   Curve& new_curve = new_branch.curve;

   switch (C_Type)
   {
   case H0_H1:
     if (is_head0_virtual)
     {
       branch0.inactiveAndKeepVirtualHead();
     }
     if (is_head1_virtual)
     {
       branch1.inactiveAndKeepVirtualHead();
     }
     new_curve = combineTwoCurvesInOrder(reverseOneCurve(c0), c1);
     new_branch.back_up_head = branch0.back_up_tail;
     new_branch.back_up_tail = branch1.back_up_tail;
     
      cout << "H0_T0 H0_T0" << endl << endl;
     break;

   case H0_T1:

     if (is_head0_virtual)
     {
       branch0.inactiveAndKeepVirtualHead();
     }
     if (is_tail1_virtual)
     {
       branch1.inactiveAndKeepVirtualTail();
     }

     new_curve = combineTwoCurvesInOrder(reverseOneCurve(c0), reverseOneCurve(c1));
     new_branch.back_up_head = branch0.back_up_tail;
     new_branch.back_up_tail = branch1.back_up_head;

     cout << "H0_T1 H0_T1" << endl << endl;
     break;

   case T0_H1:

     if (is_tail0_virtual)
     {
       branch0.inactiveAndKeepVirtualTail();
     }
     if (is_head1_virtual)
     {
       branch1.inactiveAndKeepVirtualHead();
     }
     new_curve = combineTwoCurvesInOrder(c0, c1);
     new_branch.back_up_head = branch0.back_up_head;
     new_branch.back_up_tail = branch1.back_up_tail;

     cout << "T0_H1 T0_H1" << endl << endl;
     break;

   case T0_T1:

     if (is_tail0_virtual)
     {
        branch0.inactiveAndKeepVirtualTail();
     }
     if (is_tail1_virtual)
     {
       branch1.inactiveAndKeepVirtualTail();
     }
     new_curve = combineTwoCurvesInOrder(c0, reverseOneCurve(c1));
     new_branch.back_up_head = branch0.back_up_head;
     new_branch.back_up_tail = branch1.back_up_head;

     cout << "T0_T1 T0_T1" << endl << endl;
     break;
   }

   return new_branch;
 }


 Curve Skeletonization::combineTwoCurvesInOrder(Curve& c0, Curve& c1)
 {
   if (isTowCurvesTheSame(c0, c1))
   {
     return c0;
   }

   Curve c;

   for (int i = 0; i < c0.size(); i++)
   {
     c.push_back(c0[i]);
   }

   int i = 0;
   if (GlobalFun::computeEulerDistSquare(c0[c0.size()-1], c1[0]) < 1e-6)
   {
     i = 1;
   }

   for (; i < c1.size(); i++)
   {
     c.push_back(c1[i]);
   }

   return c;
 }

 Curve Skeletonization::reverseOneCurve(Curve c0)
 {
   Curve c;

   Curve::reverse_iterator riter = c0.rbegin();
   for (; riter != c0.rend(); ++riter)
   {
     c.push_back(*riter);
   }

   return c;
 }


void Skeletonization::cleanPointsNearBranches()
{
  double clean_dist = para->getDouble("Clean Near Branches Dist");
  double clean_dist2 = clean_dist * clean_dist;

  for (int i = 0; i < samples->vert.size(); i++)
  {
    CVertex& v = samples->vert[i];
    if (v.is_fixed_sample || v.is_skel_branch)
    {
      for (int j = 0; j < v.neighbors.size(); j++)
      {
        CVertex& t = samples->vert[v.neighbors[j]];

        if (t.isSample_JustMoving())
        {
          double dist2 = GlobalFun::computeEulerDistSquare(v.P(), t.P());
          if (dist2 < clean_dist2)
          {
            //t.is_skel_ignore = true;
            t.remove();
          }
        }
      }
    }

    //if (v.is_fixed_sample && !v.is_skel_branch)
    //{
    //  v.is_skel_ignore = true;
    //}
  }

}


void Skeletonization::labelFixOriginal()
{
  int mode = para->getInt("Fix Original Mode");
  //double pca_para = para->getDouble("PCA Radius Para");
  double pca_para = 1.0;
  switch(mode)
  {
  case 1:
    GlobalFun::computeBallNeighbors(samples, original, 
      para->getDouble("CGrid Radius") / sqrt(para->getDouble("H Gaussian Para")) * pca_para, original->bbox);

    for (int i = 0; i < original->vert.size(); i++)
    {
      CVertex& t = original->vert[i];
      t.is_fixed_original = true;
    }

    for (int i = 0; i < samples->vert.size(); i++)
    {
      CVertex& v = samples->vert[i];

      if (!v.is_fixed_sample)
      {
        vector<int>& ori_neighbors = v.original_neighbors;

        for(int j = 0; j < ori_neighbors.size(); j++)
        {
          CVertex& t = original->vert[ori_neighbors[j]];
          t.is_fixed_original = false;
        }
      }

      if (v.is_fixed_sample)
      {
        vector<int>& ori_neighbors = v.original_neighbors;

        for(int j = 0; j < ori_neighbors.size(); j++)
        {
          CVertex& t = original->vert[ori_neighbors[j]];
          t.is_fixed_original = true;
        }
      }
    }

    break;
  case 2:

    GlobalFun::computeBallNeighbors(samples, original, 
      para->getDouble("CGrid Radius") / sqrt(para->getDouble("H Gaussian Para")) * pca_para, original->bbox);

    for (int i = 0; i < original->vert.size(); i++)
    {
      CVertex& t = original->vert[i];
      t.is_fixed_original = true;
    }

    for (int i = 0; i < samples->vert.size(); i++)
    {
      CVertex& v = samples->vert[i];

      if (!v.is_fixed_sample)
      {
        vector<int>& ori_neighbors = v.original_neighbors;

        for(int j = 0; j < ori_neighbors.size(); j++)
        {
          CVertex& t = original->vert[ori_neighbors[j]];
          t.is_fixed_original = false;
        }
      }

    }

    GlobalFun::computeBallNeighbors(samples, original, 
      para->getDouble("Local Density Radius") / sqrt(para->getDouble("H Gaussian Para")) * pca_para, original->bbox);

    for (int i = 0; i < samples->vert.size(); i++)
    {
      CVertex& v = samples->vert[i];

      if (v.is_fixed_sample)
      {
        vector<int>& ori_neighbors = v.original_neighbors;

        for(int j = 0; j < ori_neighbors.size(); j++)
        {
          CVertex& t = original->vert[ori_neighbors[j]];
          t.is_fixed_original = true;
        }
      }
    }


    break;
  case 3:
    GlobalFun::computeBallNeighbors(samples, original, 
      para->getDouble("CGrid Radius") / sqrt(para->getDouble("H Gaussian Para")) * pca_para, original->bbox);

    for (int i = 0; i < original->vert.size(); i++)
    {
      CVertex& t = original->vert[i];
      t.is_fixed_original = true;
    }

    for (int i = 0; i < samples->vert.size(); i++)
    {
      CVertex& v = samples->vert[i];

      if (!v.is_fixed_sample)
      {
        vector<int>& ori_neighbors = v.original_neighbors;

        for(int j = 0; j < ori_neighbors.size(); j++)
        {
          CVertex& t = original->vert[ori_neighbors[j]];
          t.is_fixed_original = false;
        }
      }

    }
    break;

  case 4:
    GlobalFun::computeBallNeighbors(samples, original, 
      para->getDouble("CGrid Radius") / sqrt(para->getDouble("H Gaussian Para")) * pca_para, original->bbox);

    for (int i = 0; i < original->vert.size(); i++)
    {
      CVertex& t = original->vert[i];
      t.is_fixed_original = false;
    }

    for (int i = 0; i < samples->vert.size(); i++)
    {
      CVertex& v = samples->vert[i];

      if (v.is_fixed_sample)
      {
        vector<int>& ori_neighbors = v.original_neighbors;

        for(int j = 0; j < ori_neighbors.size(); j++)
        {
          CVertex& t = original->vert[ori_neighbors[j]];
          t.is_fixed_original = true;
        }
      }

    }
    break;

  case 5:
    for (int i = 0; i < original->vert.size(); i++)
    {
      CVertex& t = original->vert[i];
      t.is_fixed_original = false;
    }

    break;
  }


}

void Skeletonization::rememberVirtualEnds()
{
  for (int i = 0; i < skeleton->branches.size(); i++)
  {
    Branch& branch = skeleton->branches[i];
    branch.rememberVirtualHead();
    branch.rememberVirtualTail();
  }
}


void Skeletonization::increaseRadius()
{
  double current_radius = para->getDouble("CGrid Radius");
  double speed = para->getDouble("Radius Update Speed");

  if (speed <= 0 || speed >= 100)
  {
    speed = 0.5;
  }

  current_radius *= (1 + speed);
  para->setValue("CGrid Radius", DoubleValue(current_radius));


  // for KangXue: maybe you want to save the skel_radius for virtual points here
  // but the best way is to save it whenever the virtual point is inactive
  //
  vector<Branch>& branches = skeleton->branches;
  for (int i = 0; i < branches.size(); i++)
  {
    Branch& branch = branches[i];
    Curve& curve = branch.curve;
    for (int j = 0; j < curve.size(); j++)
    {
      if (curve[j].skel_radius < 0)
      {
        curve[j].skel_radius = current_radius;
      }
    }
  }



}

int Skeletonization::getMovingPointsNum()
{
  int cnt = 0;
  for(int i = 0; i < samples->vert.size(); i++)
  {
    if (samples->vert[i].isSample_Moving())
    {
      cnt++;
    }
  }
  return cnt;
}



void Skeletonization::updateOneBranchFollowSamples(Branch& branch)
{
  if (branch.isHeadVirtual())
  {
    updateVirtualHeadFollowSamples(branch);
  }

  if (branch.isTailVirtual())
  {
    branch.reverseBranch();
    updateVirtualHeadFollowSamples(branch);
  }
}


void Skeletonization::updateVirtualHeadFollowSamples(Branch& branch)
{
  double follow_dist = para->getDouble("Follow Sample Radius");
  double follow_dist2 = follow_dist * follow_dist;

  double too_close_dist = para->getDouble("Combine Too Close Threshold");
  double too_close_dist2 = too_close_dist * too_close_dist;

  double follow_angle =  para->getDouble("Follow Sample Max Angle");
  double merge_dist = para->getDouble("Branches Merge Max Dist");
  bool use_perpend_dist_strategy = para->getBool("Use Plus Perpendicular Dist Strategy");
  bool use_kill_too_close_strategy = para->getBool("Use Kill Too Close Strategy");

  Curve& curve = branch.curve;
  CVertex& head = curve[0];

  CVertex& v = samples->vert[head.m_index];
  v.setSample_MovingAndVirtual();

  vector<int> follow_cadidates;
  follow_cadidates.push_back(head.m_index);

  int near_by_virtual_num = 0; // 1-13
  for (int j = 0; j < v.neighbors.size(); j++)
  {
    CVertex& t = samples->vert[v.neighbors[j]];
    if (t.isSample_Moving())
    {
      follow_cadidates.push_back(v.neighbors[j]);
    }
  }

  if (follow_cadidates.size() < 2)
  {
    return;
  }

  Point3f real_head_direction = branch.getTrueHeadDirection();
  Point3f real_head_P = curve[1].P();
  Point3f virtual_head_P = curve[0].P();
  int min_idx = -1;
  double min_dist = GlobalFun::getDoubleMAXIMUM();
  //bool have_follow_point = false;

  if (use_perpend_dist_strategy)
  {
    for (int i = 0; i < follow_cadidates.size(); i++)
    {
      CVertex& t = samples->vert[follow_cadidates[i]];

      double dist;
      dist = GlobalFun::computeProjPlusPerpenDist(real_head_P, t.P(), real_head_direction);
      //double dist = GlobalFun::computeEulerDist(real_head_P, t.P());

      if (dist < 0)
      {
        continue;
      }

      if (use_kill_too_close_strategy && dist < too_close_dist && !t.is_skel_virtual)
      {
        t.is_skel_ignore = true;
        continue;
      }

      if (dist < follow_dist && dist > too_close_dist)
      {
        Point3f virtual_direction = (t.P() - real_head_P).Normalize();
        double angle = GlobalFun::computeRealAngleOfTwoVertor(real_head_direction, virtual_direction);

        //have_follow_point = true;
        if (angle > 0 && angle < follow_angle && dist < min_dist)
        {
          min_dist = dist;
          min_idx = follow_cadidates[i];
        }

      }
    }

  }
  else
  {
    for (int i = 0; i < follow_cadidates.size(); i++)
    {
      CVertex& t = samples->vert[follow_cadidates[i]];

      double dist2;
      dist2 = GlobalFun::computeEulerDistSquare(real_head_P, t.P());

      //double dist = GlobalFun::computeEulerDist(real_head_P, t.P());
      if (use_kill_too_close_strategy && dist2 < too_close_dist2 && !t.is_skel_virtual)
      {
        t.is_skel_ignore = true;
      }

      if (dist2 < follow_dist2 && dist2 > too_close_dist2)
      {
        Point3f virtual_direction = (t.P() - real_head_P).Normalize();
        double angle = GlobalFun::computeRealAngleOfTwoVertor(real_head_direction, virtual_direction);

        //have_follow_point = true;
        if (angle > 0 && angle < follow_angle && dist2 < min_dist)
        {
          min_dist = dist2;
          min_idx = follow_cadidates[i];
        }
      }
    }
  }


  if (min_idx >= 0 && (head.m_index != min_idx))
  {
    samples->vert[head.m_index].setSample_JustMoving(); // not sure, other curve may using this
    head.m_index = min_idx;
    samples->vert[head.m_index].setSample_MovingAndVirtual();
    head.P() = samples->vert[head.m_index].P();

    branch.rememberVirtualHead();	
  }
  else
  {
    branch.curve[0].P() = samples->vert[head.m_index].P();
  }

}


void Skeletonization::updateAllBranchesFollowSamples()
{

  for (int i = 0; i < skeleton->branches.size(); i++)
  {
    Branch& branch = skeleton->branches[i];
    if (branch.curve.size() <= 3)
    {
      continue;
    }

    updateOneBranchFollowSamples(branch);
  }
}


void Skeletonization::dealWithVirtualsForOneBranch(Branch& branch)
{
  if (branch.isTailVirtual())
  {
    dealWithVirtualsForTail(branch);
  }

  if (branch.isHeadVirtual())
  {
    branch.reverseBranch();
    dealWithVirtualsForTail(branch);
  }

  return ;
}


void Skeletonization::dealWithVirtualsForAllBranch()
{
  for (int i = 0; i < skeleton->branches.size(); i++)
  {
    Branch& branch = skeleton->branches[i];
    if (branch.curve.size() <= 3)
    {
      continue;
    }

    dealWithVirtualsForOneBranch(branch);
  }
}

bool Skeletonization::isVirtualTailHealthy(Branch& branch)
{
  Curve& c = branch.curve;
  if (!branch.isTailVirtual())
  {
    return false;
  }

  double save_virtual_angle = para->getDouble("Save Virtual Angle");
  double save_virtual_dist = para->getDouble("Branches Merge Max Dist");
  double bad_virtual_angle = para->getDouble("Bad Virtual Angle");
  double follow_dist = para->getDouble("Follow Sample Radius");

  double angle = branch.getTailAngle();
  double tail_length = GlobalFun::computeEulerDist(c[c.size()-1].P(), c[c.size()-2].P());

  // 2013-7-12
  if (angle > bad_virtual_angle && tail_length > follow_dist)
  {
    return false;
  }
  if (angle < save_virtual_angle || (tail_length < follow_dist && angle < bad_virtual_angle))
  {
    return true; 
  }
  else
  {
    return false;
  }
}

void Skeletonization::dealWithVirtualsForTail(Branch& branch)
{
  Curve& curve0 = branch.curve;

  double MAX_Merge_Dist = para->getDouble("Branches Merge Max Dist");
  double MAX_Merge_Dist2 = MAX_Merge_Dist * MAX_Merge_Dist;

  bool use_virtual_group_strategy = para->getBool("Use Virtual Group Merge Strategy");
 
  // deal with head eat tail problem
  if (branch.isHeadVirtual())
  {
    double head_tail_dist2 = GlobalFun::computeEulerDistSquare(branch.getHead(), branch.getTail());
    if (head_tail_dist2 < MAX_Merge_Dist)
    {
      double head_angle = branch.getHeadAngle();
      double tail_angle = branch.getTailAngle();
      if (head_angle > tail_angle)
      {
        branch.inactiveAndDropVirtualHead();
      }
      else
      {
        branch.inactiveAndDropVirtualTail();
        return;
      }
    }
  }

  // try to combine two(only two) nearby virtual
  if (isVirtualTailHealthy(branch) /*&& para->getBool("Use Nearby Combine Strategy")*/)
  {
    Point3f tail_P = curve0[curve0.size()-1].P();

    vector<int> branch_ids;
    vector<Branch>& branches = skeleton->branches;
    for (int i = 0; i < branches.size(); i++)
    {
      Curve& curve1 = branches[i].curve;

      if (isTowCurvesTheSame(curve0, curve1))
      {
        continue;
      }

      double dist_head_2 = GlobalFun::computeEulerDistSquare(curve1[0], tail_P);
      double dist_tail_2 = GlobalFun::computeEulerDistSquare(curve1[curve1.size()-1], tail_P);

      if (dist_head_2 < MAX_Merge_Dist2 || dist_tail_2 < MAX_Merge_Dist2)
      {
        if (!(dist_head_2 < MAX_Merge_Dist2 && dist_tail_2 < MAX_Merge_Dist2))
        {
          branch_ids.push_back(i);
        }
      }
    }

    if (!branch_ids.empty())
    {
      is_skeleton_locked = true;
      mergeNearEndsGroupFromP(tail_P);
      is_skeleton_locked = false;
    }

    //if (branch_ids.size() == 1 && para->getBool("Use Nearby Combine Strategy"))
    //{
    //  Curve& curve1 = curves[branch_ids[0]];

    //  if (!isCurveDangerous(curve1))
    //  {
    //    double dist2, angle;
    //    CONNECT_TYPE c_type;
    //    compareTwoCurvesEnds(curve0, curve1, dist2, angle, c_type);
    //    cout << "finished compareTwoCurvesEnds" << endl;
    //    if (angle > para->getDouble("Combine Similar Angle") /*|| dist2 < 1e-6*/)// not sure 1-14
    //    {
    //      if (dist2 < MAX_Merge_Dist2)
    //      {
    //        mergeTwoCurvesSimilarDirection(curve0, curve1, c_type);
    //      }
    //    }
    //  }
    //}
    //else if (branch_ids.size() > 1)
    //{
    //  //1-17
    //  if (!isCurveDangerous(curve0) && use_virtual_group_strategy)
    //  {
    //    mergeNearEndsGroupFromP(curve0[curve0.size()-1]);
    //  }
    //}
  }


  //try to inactive because close to branch body
  //if (isVirtualTailHealthy(branch))
  if (branch.getTailAngle() < para->getDouble("Bad Virtual Angle"))  
  {
   vector<Branch>& branches = skeleton->branches;
    Point3f tail_P = curve0[curve0.size()-1].P();

    for (int i = 0; i < branches.size(); i++)
    {
       Curve& curve1 = branches[i].curve;

      if (isTowCurvesTheSame(curve0, curve1) || curve1.size() <= 3)
      {
        continue;
      }

      double min_dist = 100000;
      double min_id = -1;

      for (int j = 0; j < curve1.size(); j++)
      {
        CVertex& t = curve1[j];

        Point3f tail_direction = curve0[curve0.size()-2].P() - curve0[curve0.size()-3].P();
        Point3f near_direction = t.P() - curve0[curve0.size()-2].P(); 
        double dist_tail_t2 = GlobalFun::computeEulerDistSquare(t.P(), tail_P);

        if (dist_tail_t2 < MAX_Merge_Dist2 && dist_tail_t2 < min_dist
          && tail_direction * near_direction > 0)
        {
          min_dist = dist_tail_t2;
          min_id = j;
        }
      }

      if (min_id >= 0 && !curve1[min_id].is_skel_virtual)
      {

        // 2013-1-18
        if (branch.moveTailToPt(curve1[min_id].P()))
        {
          break;
        }
        if (para->getBool("Use Virtual Near Body Stop Strategy"))
        {
          branch.inactiveAndKeepVirtualTail();
        }


      }

    }


  }

  //try to inactive bad condition virtual tail
  //int follow_candidate_num = 0;
  int avaiable_cnt = 0;
  if (branch.isTailVirtual())
  {
    bool is_virtial_tail_bad = false;

    double tail_angle = branch.getTailAngle();
    double tail_length = branch.getTailLengthEulerDist();   

    if (tail_angle < 0 || (tail_angle > para->getDouble("Bad Virtual Angle") && tail_length > MAX_Merge_Dist))
    {
      //cout << "inactive because of:	" << "Moving To Bad Angle" << endl;
      is_virtial_tail_bad = true;
      //inactiveAndDropVirtualTail(curve0);
    }
    else
    {
      double follow_radius = para->getDouble("Follow Sample Radius");
      double follow_radius2 = follow_radius * follow_radius;
      double too_close_threshold = para->getDouble("Combine Too Close Threshold");
      double too_close_threshold2 = too_close_threshold * too_close_threshold;

      CVertex tail = curve0[curve0.size()-1];

      CVertex& v = samples->vert[tail.m_index];
      if (!v.neighbors.empty())
      {
        Point3f real_tail_P = curve0[curve0.size()-2];
        Point3f real_tail_direction = (curve0[curve0.size()-2].P() - curve0[curve0.size()-3].P()).Normalize();

        for (int j = 0; j < v.neighbors.size(); j++)
        {
          CVertex& t = samples->vert[v.neighbors[j]];

          if (!t.isSample_Moving())
            continue;

          double proj_dist = GlobalFun::computeProjDist(real_tail_P, t.P(), real_tail_direction);
          if (proj_dist < 0)
          {
            continue;
          }

          double dist2 = GlobalFun::computeEulerDistSquare(real_tail_P, t.P());
          if (/*dist2 < too_close_threshold2 && || */dist2 > follow_radius2)
          {
            continue;
          }

          avaiable_cnt++;
        }

        if (avaiable_cnt == 0)
        {
         // cout << "inactive because of:	" << "No follow candidate around!" << endl;
          is_virtial_tail_bad = true;
        }
      }
    }

    if (is_virtial_tail_bad)
    {
      branch.inactiveAndDropVirtualTail();
    }
  }
}


void Skeletonization::runAllSegment()
{
  //dealWithVirtualsForAllBranch();

  reconnectSkeleton();

  bool need_remember = para->getBool("Need Segment Right Away");
  para->setValue("Need Segment Right Away", BoolValue(true));

  vector<Branch>& branches = skeleton->branches;
  for (int i = 0; i < branches.size(); i++)
  {
    Branch& branch = branches[i];
    segmentOneCurve(branch.curve);
  }

  para->setValue("Need Segment Right Away", BoolValue(need_remember));
}

void Skeletonization::segmentOneCurve(Curve& c)
{
  //if (isCurveHeadVirtual(c) || isCurveTailVirtual(c) || !para->getBool("Need Segment Right Away"))
  //{
  //  return;
  //}

  //subdivisionCurve(c, para->getDouble("Curve Segment Length") * 1.2);
  smoothCurve(c, para->getDouble("Branches Search Angle") / 1.5, 3);
  subdivisionCurve(c, para->getDouble("Curve Segment Length") * 0.1);

  if (c.size() < 5)
  {
    cout << "too short for segment!!" << endl;
    return;
  }

  int curr_idx = 0;
  double segment_len = para->getDouble("Curve Segment Length");

  Curve new_curve;
  vector<int> new_ids;
  int left_id = 0;
  Point3f left_P = c[0].P();
  int right_id = c.size()-1;
  Point3f right_P = c[right_id].P();

  vector<int> new_ids_left;
  vector<int> new_ids_right;
  new_ids_left.push_back(left_id);
  new_ids_right.push_back(right_id);
  bool is_far_meet = false;

  double segment_len2 = segment_len * segment_len;
  double segment_meet_len = segment_len * 0.7;
  double segment_meet_len2 = segment_meet_len * segment_meet_len;
  while(1)
  {
    int j = left_id;
    Point3f left_next_P = c[j].P();

    while(1) 
    {
      j++;
      if (j >= right_id)
      {
        break;
      }

      left_next_P = c[j].P();
      double dist2 = GlobalFun::computeEulerDistSquare(left_P, left_next_P);
      if (dist2 > segment_len2)
      {
        break;
      }
    }


    if (j >= right_id)
    {
      break;
    }

    double left_right_dist2 = GlobalFun::computeEulerDistSquare(left_next_P, right_P);
    if (left_right_dist2 <= segment_meet_len2)
    {
      is_far_meet = true;
      break;
    }

    new_ids_left.push_back(j);
    left_id = j;
    left_P = c[left_id].P();

    //right
    int k = right_id;
    Point3f right_next_P = c[k].P();
    while(1)
    {
      k--;
      if (k <= left_id)
      {
        break;
      }

      right_next_P = c[k].P();
      double dist2 = GlobalFun::computeEulerDistSquare(right_P, right_next_P);
      if (dist2 > segment_len2)
      {
        break;
      }
    }


    if (k <= left_id)
    {
      break;
    }
    left_right_dist2 = GlobalFun::computeEulerDistSquare(right_next_P, left_P);
    if (left_right_dist2 <= segment_meet_len2)
    {
      is_far_meet = true;
      break;
    }

    new_ids_right.push_back(k);
    right_id = k;
    right_P = c[right_id].P();
  }

  if (is_far_meet)
  {
    new_ids_left.push_back((left_id + right_id) / 2);
  }

  for (int i = 0; i < new_ids_left.size(); i++)
  {
    new_curve.push_back(c[new_ids_left[i]]);
  }

  for (vector<int>::reverse_iterator riter = new_ids_right.rbegin(); riter != new_ids_right.rend(); ++riter)
  {
    new_curve.push_back(c[*riter]);
  }

  //int one_step_size = 0;
  //Point3f p0 = c[0];
  //for (int i = 1; i < c.size() - 1; i++)
  //{
  //	Point3f next_P = c[i].P();
  //	double dist2 = GlobalFun::computeEulerDistSquare(p0, next_P);
  //	if (dist2 > segment_len2)
  //	{
  //		break;
  //	}
  //	else
  //	{
  //		one_step_size++;
  //	}
  //}
  //one_step_size--;


  //int end_id = c.size() - 3;
  //while(curr_idx < end_id)
  //{
  //	Point3f curr_P = c[curr_idx].P();
  //	new_curve.push_back(c[curr_idx]);
  //	int j = curr_idx + 1;
  //	for (; j < end_id; j++)
  //	{
  //		Point3f next_P = c[j].P();
  //		double dist2 = GlobalFun::computeEulerDistSquare(curr_P, next_P);
  //		if (dist2 > segment_len2)
  //		{
  //			break;
  //		}
  //	}
  //	if (j == end_id)
  //	{
  //		break;
  //	}
  //	curr_idx = j;
  //}
  //new_curve.push_back(c[c.size()-1]);

  c = new_curve;

}


double Skeletonization::getNodeAngle(Curve& c, int idx)
{
  double angle = -1;
  if (idx < 0 || idx >= c.size())
  {
    return angle;
  }

  Point3f dir0, dir1;
  if (idx == 0)
  {
    dir0 = c[0].P() - c[1].P();
    dir1 = c[1].P() - c[2].P();
  }
  else if (idx == c.size()-1)
  {
    dir0 = c[c.size()-1].P() - c[c.size()-2].P();
    dir1 = c[c.size()-2].P() - c[c.size()-3].P();
  }
  else
  {
    dir0 = c[idx].P() - c[idx-1].P();
    dir1 = c[idx+1].P() - c[idx].P();
  }

  angle = GlobalFun::computeRealAngleOfTwoVertor(dir0, dir1);
  return angle;
}

void Skeletonization::smoothNode(Curve& c, int idx)
{
  if (idx <= 0 || idx >= c.size()-1)
  {
    return;
  }

  c[idx].P() = c[idx].P()/2 + c[idx-1].P()/4 + c[idx+1].P()/4;
}

void Skeletonization::smoothCurve(Curve& c, double angle_threshold, int MAX_time)
{
  if (c.size() < 3)
  {
    return;
  }

  bool need_smooth_again;
  int iterate = 1;
  do 
  {
    need_smooth_again =false;
    for (int i = 1; i < c.size()-1; i++)
    {
      double angle = getNodeAngle(c, i);
      if (angle > angle_threshold)
      {
        need_smooth_again = true;
        smoothNode(c, i);
      }
    }

  } while (need_smooth_again && iterate++ < MAX_time);
}

void Skeletonization::subdivisionCurveOnce(Curve& c)
{
  if (c.size() < 5)
  {
    return;
  }

  Curve new_curve;
  CVertex new_v;
  for (int i = 0; i < c.size()-1; i++)
  {
    new_curve.push_back(c[i]);
    new_v = c[i];
    if (i == 0)
    {
      new_v.P() = (c[i].P()*3 + c[i+1].P()*6 - c[i+2].P()) / 8.;
      //new_v.P() = (c[i].P() + c[i+1].P()) / 2;

    }
    else if (i == c.size() - 2)
    {
      new_v.P() = (c[i-1].P()*(-1) + c[i].P()*6 + c[i+1].P()*3) / 8.;
      //new_v.P() = (c[i].P() + c[i+1].P()) / 2;
    }
    else
    {
      new_v.P() = (c[i-1].P()*(-1) + c[i].P()*9 + c[i+1].P()*9 - c[i+2].P()) / 16.;
    }
    new_curve.push_back(new_v);
  }
  new_curve.push_back(c[c.size()-1]);

  c = new_curve;
}

void Skeletonization::subdivisionCurve(Curve& c, double stop_segment_length)
{
  for (int k = 0; k < 5; k++)
  {
    double max_length2 = 0;
    for(int i = 0; i < c.size()-1; i++)
    {
      double dist2 = GlobalFun::computeEulerDistSquare(c[i].P(), c[i+1].P());
      if (dist2 > max_length2)
      {
        max_length2 = dist2;
      }
    }
    double max_length = sqrt(max_length2);

    if (max_length < stop_segment_length)
    {
      break;
    }

    subdivisionCurveOnce(c);
  }
}


void Skeletonization::reconnectSkeleton()
{
  double nearby_dist2 = 1e-6;
  vector<Branch>& branches = skeleton->branches;

  // deal with self-eat problem
  while(1)
  {
    bool have_erase = false;
    for (int i = 0; i < branches.size(); i++)
    {
      Branch& branch = branches[i];
      double head_tail_dist2 = GlobalFun::computeEulerDistSquare(branch.getHead(), branch.getTail());
      if (head_tail_dist2 < nearby_dist2)
      {
        if (branch.getSize() < 8)
        {
          branches.erase(branches.begin()+i);
          skeleton->generateBranchSampleMap();
          have_erase = true;
          break;
        }
        else
        {
          branch.curve.pop_back(); //maybe need more consideration
        }
      }
    }

    if (!have_erase)
    {
      break;
    }
  }

  //break joint nodes
  while(1)
  {
    int break_branch_id = -1;
    int break_node_id = -1;

    for (int i = 0; i < branches.size(); i++)
    {
      Branch& branch = branches[i];

      Point3f& head_P = branch.getHead();
      Point3f& tail_P = branch.getTail();

      break_branch_id = -1;
      break_node_id = -1;

      for (int j = 0; j < branches.size(); j++)
      {
        Curve& curve1 = branches[j].curve;
        if (j == i || curve1.size() < 2)
        {
          continue;
        }

        for (int k = 1; k < curve1.size()-1; k++)
        {
          Point3f p = curve1[k].P();
          double dist_head2 = GlobalFun::computeEulerDistSquare(p, head_P);
          double dist_tail2 = GlobalFun::computeEulerDistSquare(p, tail_P);

          if (dist_tail2 < nearby_dist2 || dist_head2 < nearby_dist2)
          {
            break_branch_id = j;
            break_node_id = k;
            break;
          }
        }
      }
      if (break_branch_id >= 0)
      {
        break;
      }

    }

    if (break_branch_id >= 0)
    {
      Branch& break_branch = branches[break_branch_id];
      Curve& break_curve = break_branch.curve;

      Curve::iterator break_iter = break_curve.begin() + break_node_id;
      Curve::iterator end_iter = break_curve.end();
      
      Branch copy_branch;
      Curve& copy_curve = copy_branch.curve;
      copy_curve.resize(break_curve.size() - break_node_id);
      std::copy(break_iter, end_iter, copy_curve.begin());
      break_curve.erase(break_iter+1, end_iter);

      skeleton->branches.push_back(copy_branch);
      skeleton->generateBranchSampleMap();	
    }
    else
    {
      break;
    }

  }


  //combine connected branches
  while(1)
  {
    int combine_curve_id0 = -1;
    int combine_curve_id1 = -1;
    bool have_new_combine = false;

    for (int i = 0; i < branches.size(); i++)
    {
      Branch& branch0 = branches[i];

      Point3f& head0_P = branch0.getHead();
      Point3f& tail0_P = branch0.getTail();

      combine_curve_id0 = i;
      combine_curve_id1 = -1;
      vector<int> head_connect_curves_ids;
      vector<int> tail_connect_curves_ids;

      for (int j = 0; j < branches.size(); j++)
      {
        if (j == i)
          continue;

        Branch& branch1 = branches[j];
        Point3f& head1_P = branch1.getHead();
        Point3f& tail1_P = branch1.getTail();

        vector<double> dists_head;
        vector<double> dists_tail;

        dists_head.push_back(GlobalFun::computeEulerDistSquare(head0_P, head1_P));
        dists_head.push_back(GlobalFun::computeEulerDistSquare(head0_P, tail1_P));
        dists_tail.push_back(GlobalFun::computeEulerDistSquare(tail0_P, head1_P));
        dists_tail.push_back(GlobalFun::computeEulerDistSquare(tail0_P, tail1_P));

        for (int k = 0; k < 2; k++)
        {
          if (dists_head[k] < nearby_dist2)
          {
            head_connect_curves_ids.push_back(j);
          }
        }
        for (int k = 0; k < 2; k++)
        {
          if (dists_tail[k] < nearby_dist2)
          {
            tail_connect_curves_ids.push_back(j);
          }
        }
      }

      if (head_connect_curves_ids.size() == 1)
      {
        have_new_combine = true;
        combine_curve_id1 = head_connect_curves_ids[0];
        break;
      }
      if (tail_connect_curves_ids.size() == 1)
      {
        have_new_combine = true;
        combine_curve_id1 = tail_connect_curves_ids[0];
        break;
      }
    }

    if (have_new_combine)
    {
      Branch& branch0 = skeleton->branches[combine_curve_id0];
      Branch& branch1 = skeleton->branches[combine_curve_id1];

      Branch new_branch = mergeTowBranches(branch0, branch1, UNKNOWN);
      branch0 = new_branch;
      skeleton->branches.erase(skeleton->branches.begin() + branch1.branch_id);

      skeleton->generateBranchSampleMap();
    }
    else
    {
      break;
    }

  }
}