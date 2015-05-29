#include "stdafx.h"
#include <string>
using std::string;
#include "ECVSBase.h"

//����OpenCV
#ifdef _DEBUG
#pragma  comment(lib,"opencv_world300d.lib" )
#pragma  comment(lib, "opencv_ts300d.lib")
#else
#pragma  comment(lib, "opencv_ts300.lib")
#pragma  comment(lib,"opencv_world300.lib" )
#endif


string GetErrorMsg(int nCode)
{
	switch (nCode)
	{
	case ECVS_ERROR_NO_ERROR:
		return string("�ɹ�");
	case ECVS_ERR_HAS_NO_EXECUTE:
		return string("�㷨δִ��");
	case ECVS_ERROR_HAS_NO_IMG_INPUT:
		return "û��ͼ������";
	default:
		return string();
	//	break;
	}

}