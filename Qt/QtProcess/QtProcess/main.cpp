#include "QtProcess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtProcess w;
	//w.init();
	w.cmdTest();
    w.show();
    return a.exec();
}
