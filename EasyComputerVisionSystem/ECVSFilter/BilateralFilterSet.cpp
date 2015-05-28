// CBilateralFilterSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"
#include "opencv/cvwimage.h"
#include "opencv/highgui.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "FilterCommon.h"
using namespace cv;
#include "BilateralFilterSet.h"
#include "afxdialogex.h"
#include "ECVSBase.h"
#include "FilterCommon.h""
#include "ShowImageWnd.h"

// CBilateralFilterSet �Ի���

IMPLEMENT_DYNAMIC(CBilateralFilterSet, CDialogEx)

CBilateralFilterSet::CBilateralFilterSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBilateralFilterSet::IDD, pParent)
{
	m_pShowImgWnd = NULL;
}

CBilateralFilterSet::~CBilateralFilterSet()
{
}

void CBilateralFilterSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBilateralFilterSet, CDialogEx)
	ON_BN_CLICKED(IDC_OPENIMG, &CBilateralFilterSet::OnBnClickedOpenimg)
END_MESSAGE_MAP()


// CBilateralFilterSet ��Ϣ�������


BOOL CBilateralFilterSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_pShowImgWnd = new CShowImageWnd();

	CRect rect;
	GetDlgItem(IDC_SHOWPICTURE)->GetClientRect(rect);
	m_pShowImgWnd->SetParentWnd(this);
	m_pShowImgWnd->Create(_T("asd"), WS_VISIBLE | WS_CHILD, rect, GetDlgItem(IDC_SHOWPICTURE));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CBilateralFilterSet::OnBnClickedOpenimg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	CFileDialog dlg(TRUE, _T("BMP"), _T("*.BMP;*.jpg;*.png"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("ͼ���ļ�(*.BMP;*.jpg;*.png)|*.BMP;*.jpg;*.png|All Files (*.*)|*.*|| "));
	if (dlg.DoModal() != IDOK)
		return;
	CString csName = dlg.GetPathName();
	m_imagSrc = imread(csName.GetBuffer(0));
	m_pShowImgWnd->SetImage(m_imagSrc);
}
