#include "Console.h"
#include "mainwindow.h"
#include <QtGui/QApplication>

//函数入口，一般不做修改
int main(int argc, char* argv[])
{
    // CConsoleOutput::Instance();
    //QApplication app(argc, argv);
    glutInit(&argc, argv);
    QApplication::setStyle(QStyleFactory::create("cleanlooks"));
    /* 
	"windows", "motif", "cde", "plastique" and "cleanlooks". Depending on the platform, "windowsxp", "windowsvista" and "macintosh" may be available.
	Note that keys are case insensitive.
	*/

    QApplication a(argc, argv);
    MainWindow* mainWindow = new MainWindow(NULL);
    mainWindow->showMaximized();
    //mainWindow->show();

    return a.exec();
}
