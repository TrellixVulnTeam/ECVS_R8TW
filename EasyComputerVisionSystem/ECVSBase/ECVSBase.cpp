#include "stdafx.h"
#include <string>
using std::string;
#include "ECVSBase.h"
#include "AlgrithmBase.h"
#include "ECVSCamera.h"
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

QString StdStr2QString(string str)
{
	QByteArray byteArray = QByteArray::fromStdString(str);
	QString qStr = QString::fromLocal8Bit(byteArray);
	return qStr;
}
string  QString2StdStr(QString str)
{
	QByteArray byteArray = str.toLocal8Bit();
	string strStd = byteArray.toStdString();
	return strStd;
}




CAlgrithmBase* CreateAlgrithmGloble(string strAlgrithm)  //���ݲ�ͬ��string�������㷨ʵ��
{
	CAlgrithmBase *pRet = NULL;


	//�ж��ǲ������ECVS_Camera
	string strCamera = "ECVS_Camera";
	if (strAlgrithm.size() > strCamera.size())
	{
		string strName(strAlgrithm.begin(), strAlgrithm.begin() + strCamera.size());
		if (strName == strCamera)
		{
			string strIndex(strAlgrithm.begin() + strCamera.size(), strAlgrithm.end());
			int nIndex = atoi(strIndex.c_str());
			if (nIndex >= 0 && nIndex < CECVSCamera::m_pCameras.size())
			{
				return CECVSCamera::m_pCameras[nIndex];
			}
			
		}
	}
	


	return pRet;
}