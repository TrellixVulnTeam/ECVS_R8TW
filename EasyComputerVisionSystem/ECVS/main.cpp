#include "ecvs.h"
#include <QtWidgets/QApplication>


//导入OpenCV
#ifdef _DEBUG
#pragma  comment(lib,"opencv_world300d.lib" )
#pragma  comment(lib, "opencv_ts300d.lib")
#else
#pragma  comment(lib, "opencv_ts300.lib")
#pragma  comment(lib,"opencv_world300.lib" )
#endif

//导入基础模块
#pragma comment(lib, "ECVSBase.lib")
//导入Fillter模块
#pragma  comment(lib, "ECVSFilter.lib")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ECVS w;
	w.showMaximized();
//	w.show();
	return a.exec();
}
