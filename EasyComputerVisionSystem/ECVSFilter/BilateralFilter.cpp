#define  ECVS_BUILD_DLL
#include "FilterCommon.h"
#include "BilateralFilter.h"
#include ""

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
	CToolInput *pInput = m_vectInput[0];  //����ͼ��
	Mat pImgSrc;
	bool bTrue = pInput->GetValue().GetImageValue(pImgSrc);
	
	if (pImgSrc.data != NULL)
	{
		Mat imgOut;
		bilateralFilter(pImgSrc, imgOut, m_nDiameter, m_dbSigmaColor, m_dbSigmaSpace);

	}


}