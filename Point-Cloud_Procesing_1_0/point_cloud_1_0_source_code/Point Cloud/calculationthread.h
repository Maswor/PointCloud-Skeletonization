#ifndef CALCULATIONTHREAD_H
#define CALCULATIONTHREAD_H

#include <QThread>
#include "glarea.h"

class GLArea;

class CalculationThread : public QThread
{
	Q_OBJECT

public:
	CalculationThread();
	~CalculationThread();

	void run(void);
	void stop(void);
	void setArea(GLArea* area);

signals:
	void update();
private:
	GLArea* area;
	
};

#endif // CALCULATIONTHREAD_H
