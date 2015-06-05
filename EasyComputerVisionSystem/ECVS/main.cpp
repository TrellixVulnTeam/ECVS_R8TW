#include "ecvs.h"
#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>  

//����OpenCV
#ifdef _DEBUG
#pragma  comment(lib,"opencv_world300d.lib" )
#pragma  comment(lib, "opencv_ts300d.lib")
#else
#pragma  comment(lib, "opencv_ts300.lib")
#pragma  comment(lib,"opencv_world300.lib" )
#endif

//�������ģ��
#pragma comment(lib, "ECVSBase.lib")
//����Fillterģ��
#pragma  comment(lib, "ECVSFilter.lib")

//����QScintilla
#pragma  comment(lib, "qscintilla2d.lib")
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ECVS w;
	w.showMaximized();

	w.show();
	int nRet = a.exec();

	return nRet;
}
