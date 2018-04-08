#pragma once
#include "GlobalFunction.h"
#include "PointCloudAlgorithm.h"
#include "Skeleton.h"

class Skeletonization : public PointCloudAlgorithm {
public:
  Skeletonization(RichParameterSet *para);
  ~Skeletonization(void);

public:
  void run();
  void setInput(DataMgr *pData);
  RichParameterSet *getParameterSet() { return para; }
  void setParameterSet(RichParameterSet *_para) { para = _para; }
  void clear();

  void setFirstIterate();
  int getIterateNum() { return nTimeIterated; }
  double getErrorX() { return error_x; }

private:
  void runAutoWlopOneStep();
  void runStep0_WLOPIterationAndBranchGrowing();

  /* step 1 - 3 is for skeletonlization before increase radius */
  void runStep1_DetectFeaturePoints();
  void runStep2_SearchNewBranches();
  void runStep3_UpdateRadius();

  /* for step 0 */
  void updateVirtualHeadFollowSamples(Branch &branch);
  void updateOneBranchFollowSamples(Branch &branch);
  void updateAllBranchesFollowSamples();

  void dealWithVirtualsForTail(Branch &branch); // important
  void dealWithVirtualsForOneBranch(Branch &branch);
  void dealWithVirtualsForAllBranch();
  bool isVirtualTailHealthy(Branch &branch);

  /* for step 1 */
  void removeTooClosePoints();
  void eigenThresholdIdentification();
  void eigenConfidenceSmoothing();

  /* for step 2 */
  void searchNewBranches();
  Branch searchOneBranchFromIndex(int begin_idx);
  Branch searchOneBranchFromDirection(int begin_idx, Point3f head_direction);

  void growVirtualTailUntilStop(Branch &branch);
  void growOneBranchByVirtual(Branch &branch);
  void growAllBranches();

  /* for step 3 */
  // Merge branches
  bool mergeNearEndsGroupFromP(Point3f p0);
  void mergeNearEndsGroup();
  bool isPosVisited(vector<Point3f> &visited_pts, Point3f p,
                    double dist_threshold);

  // connect two branch with similar angle
  enum CONNECT_TYPE { H0_H1, H0_T1, T0_H1, T0_T1, UNKNOWN };
  void compareTwoCurvesEnds(Curve &c0, Curve &c1, double &min_dist,
                            double &angle, CONNECT_TYPE &C_Type);
  double getRealAngeOfTowCurve(Curve &c0, Curve &c1, CONNECT_TYPE C_Type);
  double getMaxAngleOfTwoPair(vector<Point3f> &dir0, vector<Point3f> &dir1);
  bool isTowCurvesTheSame(Curve &c0, Curve &c1);

  Branch mergeTowBranches(Branch &branch0, Branch &branch1,
                          CONNECT_TYPE C_Type = UNKNOWN);
  Curve combineTwoCurvesInOrder(Curve &c0, Curve &c1);
  Curve reverseOneCurve(Curve c0);

  // do some clean up before increase radius
  void cleanPointsNearBranches();
  void labelFixOriginal();
  void rememberVirtualEnds();

  // increase radius
  void increaseRadius();

  // if only a few moving point left, stop the process
  int getMovingPointsNum();

  // final process
  void finalProcess();

  // reconnect before refinement
  void reconnectSkeleton();

  // Segment-Refinement
  void runAllSegment();
  void segmentOneCurve(Curve &c);

  double getNodeAngle(Curve &c, int idx);
  void smoothNode(Curve &c, int idx);
  void smoothCurve(Curve &c, double angle_threshold, int MAX_time);
  void subdivisionNode(Curve &c, int idx);
  void subdivisionCurveOnce(Curve &c);
  void subdivisionCurve(Curve &c, double stop_segment_length);

protected:
  Skeletonization() {}

private:
  void input(CMesh *_samples, CMesh *_original);
  void initVertexes();

  double wlopIterate();
  void computeAverageTerm(CMesh *samples, CMesh *original);
  void computeRepulsionTerm(CMesh *samples);
  void computeDensity(bool isOriginal, double radius);

private:
  RichParameterSet *para;

private:
  CMesh *samples;
  CMesh *original;
  Skeleton *skeleton;

  Box3f box;
  int nTimeIterated;
  double error_x;

  vector<double> samples_density;
  vector<double> original_density;

  vector<Point3f> repulsion;
  vector<double> repulsion_weight_sum;

  vector<Point3f> average;
  vector<double> average_weight_sum;

  bool is_skeleton_locked;

private:
  double iterate_error;
  int iterate_time_in_one_stage;
  Timer time;
};
