#include "stdafx.h"
#include "resource.h"
#include "FilterCommon.h"
#include "BilateralFilter.h"
#include "opencv2/imgproc.hpp"
#include "BilateralFilterSet.h"
CBilateralFilter::CBilateralFilter() :CAlgrithmBase()
{
	CToolOutput *pOutImg = new CToolOutput(DataType::TYPE_IMAGE);
	pOutImg->SetStringInfo("���ͼ��");
	m_vectOutput.push_back(pOutImg);

	CToolInput* pInputImg = new CToolInput(DataType::TYPE_IMAGE);
	pInputImg->SetStringInfo("����ͼ��");
	m_vectInput.push_back(pInputImg);
	
}


CBilateralFilter::~CBilateralFilter()
{
}


void CBilateralFilter::Run()
{
	int t1 = GetTickCount();
	CToolInput *pInput = m_vectInput[0];  //����ͼ��
	Mat pImgSrc;
	bool bTrue = pInput->GetValue().GetImageValue(pImgSrc);



	if (pImgSrc.data != NULL)
	{
		Mat imgOut;
		//ִ���㷨
		bilateralFilter(pImgSrc, imgOut, m_nDiameter, m_dbSigmaColor, m_dbSigmaSpace);

		//�������ͼ��
		CInputOutputInfo info(DataType::TYPE_IMAGE);
		info.SetImageValue(imgOut);
		m_vectOutput[2]->SetValue(info);

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

void CBilateralFilter::Set()
{


 	CBilateralFilterSet setF;
 	setF.DoModal();
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