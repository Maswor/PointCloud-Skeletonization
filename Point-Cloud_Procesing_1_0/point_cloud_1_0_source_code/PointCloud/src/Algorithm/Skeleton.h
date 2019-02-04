#pragma once
#include "GlobalFunction.h"
#include "ParameterMgr.h"

typedef vector<CVertex> Curve;

class Branch {
public:
  Branch()
      : back_up_head(Point3f(-10, -10, -10)),
        back_up_tail(Point3f(-10, -10, -10)), branch_id(0) {}
  ~Branch() {}

  Branch(const Branch &b) {
    curve = b.curve;
    back_up_head = b.back_up_head;
    back_up_tail = b.back_up_tail;
    branch_id = b.branch_id;
  }

  Branch &operator=(const Branch &b) {
    if (&b != this) {
      curve = b.curve;
      back_up_head = b.back_up_head;
      back_up_tail = b.back_up_tail;
      branch_id = b.branch_id;
    }
    return *this;
  }

public:
  void pushBackCVertex(CVertex &new_v);
  CVertex getCVertexOfIndex(int index) { return curve[index]; }
  int getSize();
  bool isEmpty();
  bool isHeadVirtual() { return curve[0].is_skel_virtual; }
  bool isTailVirtual() { return curve[curve.size() - 1].is_skel_virtual; }
  bool isVirtualHeadHealthy();
  bool isVirtualTailHealthy();
  void rememberVirtualHead();
  void rememberVirtualTail();

  double getNodeAngle(int idx);
  double getHeadAngle() { return getNodeAngle(0); }
  double getTailAngle() { return getNodeAngle(curve.size() - 1); }

  double getNodeLengthEulerDist(int idx);
  double getNodeLengthEulerDistSquare(int idx);
  double getHeadLengthEulerDist();
  double getHeadLengthEulerDistSquare();
  double getTailLengthEulerDist();
  double getTailLengthEulerDistSquare();

  Point3f getVirtualTailDirection();
  Point3f getTrueTailDirection();
  Point3f getVirtualHeadDirection();
  Point3f getTrueHeadDirection();

  Point3f getHead() { return curve[0].P(); }
  Point3f getTail() { return curve[curve.size() - 1].P(); }

  bool moveHeadToPt(Point3f p_target);
  bool moveTailToPt(Point3f p_target);

  void inactiveAndKeepVirtualTail();
  void inactiveAndDropVirtualTail();
  void inactiveAndKeepVirtualHead();
  void inactiveAndDropVirtualHead();

  void reverseBranch();

public:
public:
  Curve curve;
  Point3f back_up_head;
  Point3f back_up_tail;
  int branch_id;
};

class RecordItem {
public:
  RecordItem() {}
  RecordItem(int i, int j, int k = 0)
      : branch_i(i), node_j(j), sample_index(k) {}
  int branch_i;
  int node_j;
  int sample_index;
};

class Skeleton {
public:
  Skeleton() {
    size = 0;
    branch_num = 0;
  }
  Skeleton(const Skeleton &s) {
    branches = s.branches;
    size = s.size;
    branch_sample_map = s.branch_sample_map;
    chosen_branches = s.chosen_branches;
    branch_num = s.branch_num;
  }

  Skeleton &operator=(const Skeleton &s) {
    branches = s.branches;
    size = s.size;
    branch_sample_map = s.branch_sample_map;
    chosen_branches = s.chosen_branches;
    branch_num = s.branch_num;

    return *this;
  }

  bool isEmpty() { return branches.empty(); }
  void generateBranchSampleMap();

public:
  vector<Branch> branches;
  vector<RecordItem> branch_sample_map;
  vector<int> chosen_branches;

  int size;
  int branch_num;

public:
  void clear() {
    branches.clear();
    branch_sample_map.clear();
    size = 0;
  }
};
