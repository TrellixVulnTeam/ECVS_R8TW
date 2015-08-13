#include "stdafx.h"
#include "resource.h"
#include "FilterCommon.h"
#include "BilateralFilter.h"
#include "opencv2/imgproc.hpp"
#include "BilateralFilterSet.h"
#include <windows.h>
#include <QDateTime>
#include <string>
using std::string;
CBilateralFilter::CBilateralFilter() :CAlgrithmBase() 
{
	//������������ʼ��Ϊ1
	m_nDiameter = 1;
	m_dbSigmaColor = 1;
	m_dbSigmaSpace = 1;
	CToolOutput *pOutImg = new CToolOutput(DataType::TYPE_IMAGE);
	pOutImg->SetStringInfo("���ͼ��");
	m_vectOutput.push_back(pOutImg);

	CToolInput* pInputImg = new CToolInput(DataType::TYPE_IMAGE);
	pInputImg->SetStringInfo("����ͼ��");
	m_vectInput.push_back(pInputImg);

	m_strAlgrithmName = string("ECVS_BilateralFilter");
	m_strClassName = string("CBilateralFilter");
	m_strShowText = "˫���˲�";
}


CBilateralFilter::~CBilateralFilter()
{
}

CBilateralFilter::CBilateralFilter(const CBilateralFilter& rhs)
{
	Clone(rhs);
}
void CBilateralFilter::Run()
{

	//QDateTime t1 = QDateTime::currentDateTime(); 
	

	int t1 = GetTickCount();
	CToolInput *pInput = m_vectInput[0];  //����ͼ��
	Mat pImgSrc;
	bool bTrue = pInput->GetValue().GetImageValue(pImgSrc);



	if (pImgSrc.data != NULL)
	{
		Mat imgOut;
		//ִ���㷨
		bilateralFilter(pImgSrc, imgOut, m_nDiameter, m_dbSigmaColor, m_dbSigmaSpace);
		//cv::threshold(pImgSrc, imgOut, 128, 255, cv::THRESH_BINARY);
		//�������ͼ��
		CInputOutputInfo info(DataType::TYPE_IMAGE);
		info.SetImageValue(imgOut);
		m_vectOutput[3]->SetValue(info);


		//������ʾͼ��

		CInputOutputInfo infoShow(DataType::TYPE_IMAGE);
		infoShow.SetImageValue(imgOut.clone());
		m_vectOutput[2]->SetValue(infoShow);

		CInputOutputInfo err(DataType::TYPE_INT);
		err.SetIntValue(ECVS_ERROR_NO_ERROR);
		m_vectOutput[0]->SetValue(err);

	}
	else
	{
		CInputOutputInfo err(DataType::TYPE_INT);
		err.SetIntValue(ECVS_ERROR_HAS_NO_IMG_INPUT);
		m_vectOutput[0]->SetValue(err);
	}

	//�����㷨ִ��ʱ��
	int tall = GetTickCount() - t1;
	CInputOutputInfo t(DataType::TYPE_DOUBLE);
	t.SetDoubleValue(tall);
	m_vectOutput[1]->SetValue(t);

}


Mat CBilateralFilter::Run(Mat inputimg,int nD, double dbSigmaColor, double dbSigmaSpace)
{
	Mat imgOut;
	bilateralFilter(inputimg, imgOut, nD, dbSigmaColor, dbSigmaSpace);
	return imgOut;
}
bool CBilateralFilter::Set()
{


 	CBilateralFilterSet setF(this);

	
	setF.exec();
	if (setF.result() == QDialog::Accepted)
	{
		return true;
	}
	return false;
// 	setF.setWindowModality(Qt::WindowModal);
// 	setF.show();
// 	setF.DoModal();
}
string CBilateralFilter::GetErrorMsg()
{
	string strErr = CAlgrithmBase::GetErrorMsg();

	if (strErr == "")
	{
		return "δ�������";
	}
	return strErr;


}




CAlgrithmBase* CBilateralFilter::CreateAlgrithm()
{
	return new CBilateralFilter();
}

//�鹹�캯��
CAlgrithmBase* CBilateralFilter::Clone()
{
	return new CBilateralFilter(*this);
}


void CBilateralFilter::Clone(const CBilateralFilter& rhs) //���ڸ��ƹ��캯���͸�ֵ������ʹ�� 
{
	__super::Clone(rhs);
	m_nDiameter = rhs.m_nDiameter;
	m_dbSigmaColor = rhs.m_dbSigmaColor;
	m_dbSigmaSpace = rhs.m_dbSigmaSpace;
}


IML_REFLECT_CLASS(CBilateralFilter)




// void CBilateralFilter::RegistClass()
// {
// 	CAlgrithmBase::m_mapCreatedFucn.insert(std::make_pair("CBilateralFilter", CBilateralFilter::CreateAlgrithm));
// }
