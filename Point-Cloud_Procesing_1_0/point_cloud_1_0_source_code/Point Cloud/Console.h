/************************************************************************/
/*                    console output the debug info.                    */
/************************************************************************/

#ifndef _CONSOLE_H
#define _CONSOLE_H
#include <iostream>
#include <string>
using namespace std;

//CConsoleOutput类主要为了在QT中添加控制台功能
class CConsoleOutput
{
public:
	//output information in console 
	static void Destory();
	static CConsoleOutput * Instance();
public:
	virtual ~CConsoleOutput();

protected:
	CConsoleOutput();

private:
	static CConsoleOutput* m_instance;
	FILE *file;
};

#endif

