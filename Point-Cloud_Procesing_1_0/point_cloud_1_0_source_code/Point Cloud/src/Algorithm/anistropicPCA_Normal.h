/****************************************************************************
* VCGLib                                                            o o     *
* Visual and Computer Graphics Library                            o     o   *
*                                                                _   O  _   *
* Copyright(C) 2004                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/

#ifndef ANISTROPIC_PCA
#define ANISTROPIC_PCA

#include <vcg/math/matrix33.h>
#include <vcg/math/linear.h>
#include <vcg/math/lin_algebra.h>
#include <vcg/math/disjoint_set.h>
#include <vcg/space/box3.h>
#include <vcg/space/point3.h>
#include <vcg/space/index/octree.h>
#include <wrap/callback.h>

#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <stdlib.h>

//#include "KnnNeighbor.h"
#include "cmesh.h"

template < class VERTEX_CONTAINER >
class AnistropicPca
{
public:
	typedef typename VERTEX_CONTAINER::value_type	 VertexType;
	typedef 				 VertexType									 * VertexPointer;
	typedef typename VERTEX_CONTAINER::iterator		 VertexIterator;
	typedef typename VertexType::CoordType				 CoordType;
	typedef typename VertexType::NormalType				 NormalType;
	typedef typename VertexType::ScalarType				 ScalarType;
	typedef typename vcg::Box3< ScalarType >			 BoundingBoxType;
	typedef typename vcg::Matrix33<ScalarType>  	 MatrixType;

public:
	class DummyObjectMarker {};

			// Object functor: compute the distance between a vertex and a point
	struct VertPointDistanceFunctor
			{
				inline bool operator()(const VertexType &v, const CoordType &p, ScalarType &d, CoordType &q) const
				{
					ScalarType distance = vcg::Distance(p, v.P());
					if (distance>d)
						return false;

					d = distance;
					q = v.P();
					return true;
				}
			};
			// Plane structure: identify a plain as a <center, normal> pair

	//static void ConvertCMesh2CMeshO(const CMesh &cmesh, CMeshO &cmeshO)
	//{
	//	CMeshO::VertexIterator viO;
	//	CMesh::ConstVertexIterator vi;
	//	for(vi = cmesh.vert.begin(), viO = cmeshO.vert.begin(); vi != cmesh.vert.end(); ++vi, ++viO)
	//	{
	//		viO->P().Import(vi->P());
	//		viO->N().Import(vi->cN());
	//		viO->N().Normalize();
	//	}

	//	cmeshO.vn = cmesh.vn;
	//	cmeshO.bbox.Import(cmesh.bbox);
	//}




	//static void ComputeAPcaNormalsByGrid(CMeshO& cmeshO)
	//{
	//	CMesh cmesh;
	//	ConvertMesh2CMesh<CMeshO>(cmeshO, cmesh);

	//	CMesh::VertexIterator vi;
	//	for(vi = cmesh.vert.begin(); vi != cmesh.vert.end(); ++vi)
	//	{
	//		vi->P()[0] = 0.5; 
	//		vi->N() *= -1;
	//	}

	//	ConvertCMesh2CMeshO(cmesh, cmeshO);
	//}



	static void ComputeAPcaNormalsByKNN(const VertexIterator& begin, const VertexIterator& end, const unsigned int k, double radius, const float sigma)
	{
		vector<vector<int> > neighborMap;
		neighborMap.assign(end - begin, vector<int>());

		int curr_index = 0;
		for (VertexIterator iter=begin; iter!=end; iter++, curr_index++)
		{
			if(iter->neighbors.empty())
				continue;

			for(int j = 0; j < iter->neighbors.size(); j++)
			{
				neighborMap[curr_index].push_back(iter->neighbors[j]);
			}
		}


		double radius2 = radius*radius;
		double iradius16 = -4/radius2; 

		int currIndex = 0;
		for (VertexIterator iter=begin; iter!=end; iter++, currIndex++)
		{
			MatrixType	covariance_matrix;
			CoordType diff;
			covariance_matrix.SetZero();
			int neighborIndex = -1;
			int neighbor_size = iter->neighbors.size();
			for (unsigned int n=0; n<neighbor_size; n++)
			{
				neighborIndex = neighborMap[currIndex][n];
				if(neighborIndex < 0)
					break;
				VertexIterator neighborIter = begin + neighborIndex;

				diff = iter->P() - neighborIter->P();

				Point3f vm = iter->N();
				Point3f tm = neighborIter->N();
				double psi = exp(-pow(1-vm*tm, 2)/pow(max(1e-8,1-cos(sigma /180.0*3.1415926)), 2));

				double dist2 = diff.SquaredNorm();
				double theta = exp(dist2*iradius16);

				for (int i=0; i<3; i++)
					for (int j=0; j<3; j++)
						covariance_matrix[i][j]+= theta * psi * diff[i]*diff[j];
			}

			/*cout << "tset1: " << currIndex <<endl;*/

			CoordType   eigenvalues;
			MatrixType	eigenvectors;
			int required_rotations;
			vcg::Jacobi< MatrixType, CoordType >(covariance_matrix, eigenvalues, eigenvectors, required_rotations);
			vcg::SortEigenvaluesAndEigenvectors< MatrixType, CoordType >(eigenvalues, eigenvectors);


			Point3f normal;
			for (int d=0; d<3; d++)
				normal[d] = eigenvectors[d][2];
			normal.Normalize();

			if(iter->N() * normal < 0)
			{
				for (int d=0; d<3; d++)
					normal[d] *= -1;
			}
			iter->N() = normal;
		}
	}


	static void SmoothNormalsUsingNeighbors(const VertexIterator &begin, const VertexIterator &end, const unsigned int k, bool usedistance, CallBackPos *callback=NULL)
	{
		BoundingBoxType dataset_bb;
		for (VertexIterator iter=begin; iter!=end; iter++)
			dataset_bb.Add(iter->P());
		ScalarType max_distance = dataset_bb.Diag();

		// Step 1: identify the tangent planes used to locally approximate the surface
		int vertex_count = int( std::distance(begin, end) );
		int step				 = int(vertex_count/100)-1;
		int progress		 = 0;
		int percentage;
		char message[128];
		sprintf(message, "Locating neighbors...");

		vcg::Octree< VertexType, ScalarType > octree_for_neighbors;
		octree_for_neighbors.Set( begin, end );

		std::vector< NormalType    > new_normals(vertex_count);

		std::vector< VertexPointer > nearest_vertices;
		std::vector< CoordType	 	 > nearest_points;
		std::vector< ScalarType		 > distances;

		for (VertexIterator iter=begin; iter!=end; iter++)
		{
			if (callback!=NULL && (++progress%step)==0 && (percentage=int((progress*100)/vertex_count))<100) (callback)(percentage, message);
			VertPointDistanceFunctor vpdf;
			DummyObjectMarker dom;
			octree_for_neighbors.GetKClosest(vpdf, dom, k, iter->P(), max_distance, nearest_vertices, distances, nearest_points);

			// for each vertex *iter, compute the normal as avarege of the k-nearest vertices of *iter
			NormalType normal_accum(0.0, 0.0, 0.0);

			ScalarType dist_max = -100.0;
			if(usedistance)
				for (unsigned int n=0; n<k; n++)
				{
					if (distances[n] > dist_max)
						dist_max = distances[n];
				}

				for (unsigned int n=0; n<k; n++)
				{
					if(usedistance)
						normal_accum += (nearest_vertices[n]->N() * distances[n]/dist_max);
					else
						normal_accum += nearest_vertices[n]->N();
				}

				new_normals[iter-begin] = normal_accum;
		}

		sprintf(message, "Assigning normals...");
		progress = 0;
		for (VertexIterator iter=begin; iter!=end; iter++)
		{
			if (callback!=NULL && (++progress%step)==0 && (percentage=int((progress*100)/vertex_count))<100) (callback)(percentage, message);
			iter->N() = new_normals[iter-begin].Normalize();
		}

	};


};


#endif //end of VCG_SPACE_NORMAL_EXTRAPOLATION_H
