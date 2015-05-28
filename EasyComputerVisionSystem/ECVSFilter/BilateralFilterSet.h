#pragma once
class CShowImageWnd;
#include "resource.h"

// BilateralFilterSet �Ի���

class CBilateralFilterSet : public CDialogEx
{
	DECLARE_DYNAMIC(CBilateralFilterSet)

public:
	CBilateralFilterSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBilateralFilterSet();

// �Ի�������
	enum { IDD = IDD_BILATERALFILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CShowImageWnd * m_pShowImgWnd;
	Mat m_imagSrc;
	Mat m_imgDst;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOpenimg();
};
