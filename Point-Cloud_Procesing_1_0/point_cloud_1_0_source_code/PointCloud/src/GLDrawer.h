#pragma once
#include "cmesh.h"
#include "ParameterMgr.h"

#include <QtOpenGL/QGLWidget>
#include <iostream>
#include <GL/glut.h>
#include "Algorithm/Skeleton.h"

using namespace std;
using namespace vcg;

class GLColor
{
public:
	GLColor(const float& _r = 0, const float& _g = 0, const float& _b = 0, const float& _a = 1.0):r(_r),g(_g),b(_b),a(_a){}
	GLColor(const QColor & qcolor)
	{
		int _r;
		int _g;
		int _b;
		qcolor.getRgb(&_r, &_g, &_b);
		r = _r / 255.0;
		g = _g / 255.0;
		b = _b / 255.0;
	}
	float r;
	float g;
	float b;
	float a;
};

static GLColor cBrown(0.7, 0, 0);
static GLColor cRed(1, 0, 0);
static GLColor cGreen(0, 1, 0);
static GLColor cBlue(0, 0, 1);
static GLColor cWhite(1, 1, 1);
static GLColor cBlack(0, 0, 0);
static GLColor cYellow(0.2, 1, 0.2);
static GLColor cOrange(0.6, 0.4, 0);
static GLColor cSnow(0.5, 0.5, 0.5);
static GLColor cPink(0.8, 0.1, 0.5);



class GLDrawer
{
public:
	GLDrawer(RichParameterSet* _para);
	~GLDrawer(void);
	typedef enum {DOT, QUADE, CIRCLE, NORMAL, SPHERE}DrawType;

	void setViewPoint(const Point3f& view){ view_point = view; }
	void draw(DrawType type, CMesh* mesh);
	void drawCurveSkeleton(Skeleton& skeleton);

	void updateDrawer(vector<int>& pickList);

	void cleanPickPoint();
	void drawPickPoint(CMesh* samples, vector<int>& pickList, bool bShow_as_dot);
	void setRGBNormals(vector<Point3f>& normals){RGB_normals = normals; }

private:
	GLColor getColorByType(const CVertex& v);
	void draw(DrawType type);
	bool isCanSee(const Point3f& pos,  const Point3f& normal);

	void drawDot(const CVertex& v);
	void drawSphere(const CVertex& v);
	void drawCircle(const CVertex& v);
	void drawQuade(const CVertex& v);
	void drawNormal(const CVertex& v);


	void glDrawLine(Point3f& p0, Point3f& p1, GLColor color, double width);
	void glDrawPoint(Point3f& p, GLColor color, double size);
	void glDrawSphere(Point3f& p, GLColor color, double radius, int slide);
	void glDrawCylinder(Point3f& p0, Point3f& p1, GLColor color, double width);
	void glDrawBranches(vector<Branch>& branches, GLColor gl_color);	
	//void glDrawCurves(vector<Curve>& curves, GLColor gl_color);


private:
	int x1, y1, x2, y2;
	bool doPick;
	vector<int> pickList;
	int pickPoint(int x, int y, vector<int> &result, int width=4, int height=4, bool only_one = true);

public:
  vector<GLColor> random_color_list;
  void generateRandomColorList(int num = 1000);

private:

	bool bCullFace;
	bool bUseIndividualColor;
	bool useNormalColor;
  bool useDifferBranchColor;

	double original_draw_width;
	double sample_draw_width;
	double normal_width;
	double normal_length;
	double sample_dot_size;
	double original_dot_size;

	QColor original_color;
	QColor sample_color;
	QColor feature_color;
	QColor normal_color;
	GLColor pick_color;

	QColor skel_bone_color;
	QColor skel_node_color;
	QColor skel_branch_color;
	double skel_bone_width;
	double skel_node_size;
	double skel_branch_size;


	int prevPickIndex;
	Point3f curr_pick;
	int curr_pick_indx;
	vector<Point3f> RGB_normals;

public:
	RichParameterSet* para;
	Point3f view_point;
};


class SnapshotSetting
{
public:
	QString outdir;
	QString file_name;
	QString basename;
	int counter;
	int resolution;
	bool transparentBackground;

	SnapshotSetting()
	{
		outdir=".\\snapshot\\";
		basename="snapshot";
		counter=0;
		resolution = global_paraMgr.glarea.getDouble("Snapshot Resolution");
		transparentBackground=true;
	};

	void setOutDir(QString str)
	{
		outdir = str;
	}

	void GetSysTime()
	{
		basename = file_name + QDateTime::currentDateTime().toString(Qt::ISODate);
		basename.replace(":", "-");
	}
};
