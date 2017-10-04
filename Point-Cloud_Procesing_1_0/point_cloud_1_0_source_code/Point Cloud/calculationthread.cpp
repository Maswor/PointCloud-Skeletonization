#include "calculationthread.h"

class GLArea;

CalculationThread::CalculationThread()
{

}

CalculationThread::~CalculationThread()
{

}

void CalculationThread::run( void )
{
	QString running_name = global_paraMgr.glarea.getString("Running Algorithm Name");
	if (running_name == QString("WLOP"))
	{
		area->runWlop();
	}
	else if (running_name == QString("Skeletonization"))
	{
		area->runSkeletonization_paralleled();
	}
}

void CalculationThread::setArea( GLArea* area )
{
	this->area = area;
}
