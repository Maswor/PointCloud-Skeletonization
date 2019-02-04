#include "Skeleton.h"

void Branch::pushBackCVertex(CVertex &new_v) { curve.push_back(new_v); }

int Branch::getSize() { return curve.size(); }

bool Branch::isEmpty() { return curve.empty(); }

double Branch::getNodeAngle(int idx) {
  double angle = -1;
  if (idx < 0 || idx >= curve.size()) {
    return angle;
  }

  Point3f dir0, dir1;
  if (idx == 0) {
    dir0 = curve[0].P() - curve[1].P();
    dir1 = curve[1].P() - curve[2].P();
  } else if (idx == curve.size() - 1) {
    dir0 = curve[curve.size() - 1].P() - curve[curve.size() - 2].P();
    dir1 = curve[curve.size() - 2].P() - curve[curve.size() - 3].P();
  } else {
    dir0 = curve[idx].P() - curve[idx - 1].P();
    dir1 = curve[idx + 1].P() - curve[idx].P();
  }

  angle = GlobalFun::computeRealAngleOfTwoVertor(dir0, dir1);
  return angle;
}

double Branch::getNodeLengthEulerDist(int idx) {
  double length = -1;
  if (idx < 0 || idx >= curve.size()) {
    return length;
  }

  if (idx < curve.size() - 1) {
    length = GlobalFun::computeEulerDist(curve[idx], curve[idx + 1]);
  } else if (idx == curve.size() - 1) {
    length = GlobalFun::computeEulerDist(curve[curve.size() - 1],
                                         curve[curve.size() - 2]);
  }
}

double Branch::getNodeLengthEulerDistSquare(int idx) {
  double length = -1;
  if (idx < 0 || idx >= curve.size()) {
    return length;
  }

  if (idx < curve.size() - 1) {
    length = GlobalFun::computeEulerDistSquare(curve[idx], curve[idx + 1]);
  } else if (idx == curve.size() - 1) {
    length = GlobalFun::computeEulerDistSquare(curve[curve.size() - 1],
                                               curve[curve.size() - 2]);
  }
}

double Branch::getHeadLengthEulerDist() { return getNodeLengthEulerDist(0); }

double Branch::getHeadLengthEulerDistSquare() {
  return getNodeLengthEulerDistSquare(0);
}

double Branch::getTailLengthEulerDist() {
  return getNodeLengthEulerDist(curve.size());
}

double Branch::getTailLengthEulerDistSquare() {
  return getNodeLengthEulerDistSquare(curve.size() - 1);
}

void Branch::reverseBranch() {
  std::reverse(curve.begin(), curve.end());
  Point3f temp = back_up_head;
  back_up_head = back_up_tail;
  back_up_tail = temp;
}

bool Branch::isVirtualHeadHealthy() {
  if (!isHeadVirtual()) {
    return false;
  }

  double save_virtual_angle =
      global_paraMgr.skeleton.getDouble("Save Virtual Angle");
  double save_virtual_dist =
      global_paraMgr.skeleton.getDouble("Branches Merge Max Dist");

  double head_length = GlobalFun::computeEulerDist(curve[0].P(), curve[1].P());
  double bad_virtual_angle =
      global_paraMgr.skeleton.getDouble("Bad Virtual Angle");
  double follow_dist =
      global_paraMgr.skeleton.getDouble("Follow Sample Radius");

  double angle = getHeadAngle();
  if (angle > bad_virtual_angle || head_length > follow_dist) {
    return false;
  }

  if (angle < save_virtual_angle ||
      (head_length < save_virtual_dist && angle < bad_virtual_angle)) {
    return true;
  } else {
    return false;
  }
}

bool Branch::isVirtualTailHealthy() {
  if (!isTailVirtual()) {
    return false;
  }

  double save_virtual_angle =
      global_paraMgr.skeleton.getDouble("Save Virtual Angle");
  double save_virtual_dist =
      global_paraMgr.skeleton.getDouble("Branches Merge Max Dist");
  double bad_virtual_angle =
      global_paraMgr.skeleton.getDouble("Bad Virtual Angle");
  double follow_dist =
      global_paraMgr.skeleton.getDouble("Follow Sample Radius");

  double angle = getTailAngle();
  double tail_length = getTailLengthEulerDist();

  // for basket
  if (angle > bad_virtual_angle || tail_length > follow_dist) {
    return false;
  }
  if (angle < save_virtual_angle ||
      (tail_length < save_virtual_dist && angle < bad_virtual_angle)) {
    return true;
  } else {
    return false;
  }
}

void Branch::rememberVirtualHead() {
  if (!isVirtualHeadHealthy()) {
    return;
  }

  Point3f old_virtual_head = back_up_head;

  if (old_virtual_head.X() < -5) {
    back_up_head = curve[0].P();
    return;
  }

  Point3f new_virtual_head = curve[0].P();
  Point3f real_head = curve[1].P();

  double old_length =
      GlobalFun::computeEulerDistSquare(old_virtual_head, real_head);
  double new_length =
      GlobalFun::computeEulerDistSquare(new_virtual_head, real_head);

  if (new_length > old_length) {
    back_up_head = curve[0].P();
  }
}

void Branch::rememberVirtualTail() {
  if (!isVirtualTailHealthy()) {
    return;
  }

  Point3f old_virtual_tail = back_up_tail;
  if (old_virtual_tail.X() < -5) {
    back_up_tail = curve[curve.size() - 1].P();
    return;
  }

  Point3f new_virtual_tail = curve[curve.size() - 1].P();
  Point3f real_tail = curve[curve.size() - 2].P();

  double old_length =
      GlobalFun::computeEulerDistSquare(old_virtual_tail, real_tail);
  double new_length =
      GlobalFun::computeEulerDistSquare(new_virtual_tail, real_tail);

  if (new_length > old_length || old_virtual_tail.X() < -5) {
    back_up_tail = curve[curve.size() - 1].P();
  }
}

void Skeleton::generateBranchSampleMap() {
  vector<Branch>::iterator iter;
  for (iter = branches.begin(); iter != branches.end();) {
    if (iter->isEmpty()) {
      iter = branches.erase(iter);
    } else {
      ++iter;
    }
  }

  branch_sample_map.clear();
  int cnt = 0;
  for (int i = 0; i < branches.size(); i++) {
    branches[i].branch_id = i;
    Curve &curve = branches[i].curve;
    if (curve.size() <= 1) {
      for (int j = 0; j < curve.size(); j++) {
        branch_sample_map.push_back(RecordItem(i, j, 0));
        cnt++;
      }
    } else {
      int j = 0;
      for (; j < curve.size() - 1; j++) {
        branch_sample_map.push_back(RecordItem(i, j, 0));
        cnt++;
      }
      branch_sample_map.push_back(RecordItem(i, j, 0));

      cnt++;
    }
  }
  size = cnt;
  branch_num = branches.size();
  chosen_branches.clear();
}

Point3f Branch::getVirtualTailDirection() {
  return (curve[curve.size() - 1].P() - curve[curve.size() - 2].P())
      .Normalize();
}

Point3f Branch::getTrueTailDirection() {
  if (!isTailVirtual()) {
    return (curve[curve.size() - 1].P() - curve[curve.size() - 2].P())
        .Normalize();
  } else {
    return (curve[curve.size() - 2].P() - curve[curve.size() - 3].P())
        .Normalize();
  }
}

Point3f Branch::getVirtualHeadDirection() {
  return (curve[0].P() - curve[1].P()).Normalize();
}

Point3f Branch::getTrueHeadDirection() {
  if (!isHeadVirtual()) {
    return (curve[0].P() - curve[1].P()).Normalize();
  } else {
    return (curve[1].P() - curve[2].P()).Normalize();
  }
}

void Branch::inactiveAndKeepVirtualHead() {
  if (!isHeadVirtual()) {
    return;
  }

  CVertex &head = curve[0];
  head.is_skel_virtual = false;
}

void Branch::inactiveAndDropVirtualHead() {
  if (!isHeadVirtual()) {
    return;
  }

  CVertex &head = curve[0];
  head.is_skel_virtual = false;

  if (back_up_head.X() > -5) {
    head.P() = back_up_head;

    if (getHeadAngle() > 100) {
      curve.erase(curve.begin());
    }
  } else {
    curve.erase(curve.begin());
  }
}

void Branch::inactiveAndKeepVirtualTail() {
  if (!isTailVirtual()) {
    return;
  }

  CVertex &tail = curve[curve.size() - 1];
  tail.is_skel_virtual = false;
}

void Branch::inactiveAndDropVirtualTail() {
  if (!isTailVirtual()) {
    return;
  }

  CVertex &tail = curve[curve.size() - 1];
  tail.is_skel_virtual = false;

  if (back_up_tail.X() > -5) {
    tail.P() = back_up_tail;

    if (getTailAngle() > 100) {
      curve.pop_back();
    }
  } else {
    curve.pop_back();
  }
}

bool Branch::moveHeadToPt(Point3f p_target) {
  if (getSize() < 2) {
    return false;
  }

  inactiveAndKeepVirtualHead();
  curve[0].P() = p_target;

  return true;
}

bool Branch::moveTailToPt(Point3f p_target) {
  if (getSize() < 2) {
    return false;
  }

  inactiveAndKeepVirtualTail();
  curve[curve.size() - 1].P() = p_target;

  return true;
}
