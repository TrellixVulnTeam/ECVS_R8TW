#pragma once


// CBilateralFilterSet �Ի���

class CBilateralFilterSet : public CDialogEx
{
	DECLARE_DYNAMIC(CBilateralFilterSet)

public:
	CBilateralFilterSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBilateralFilterSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_BILATERALFILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
