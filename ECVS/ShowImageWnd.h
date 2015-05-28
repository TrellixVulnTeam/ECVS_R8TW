#pragma once

//��ʾͼ�񴰿ڣ����и�ϵͳĬ����ʾͼ�񴰿� ��ʹ�������������Ĵ��ڣ�
//���Ա��̳� 2015-5-22

// CShowImageWnd
#define  WM_SHOWIMGFIXWINDOW WM_USER + 5017  //�Զ�����Ϣ��������Ӧ������ʾͼƬ
enum ShowImageWndOperator
{
	OperatorNone,   //���κβ���,Ĭ��Ϊѡ�����
	OperatorMoveObj, //�ƶ�����
	OperatorZoomLeft,
	OperatorZoomLeftTop,
	OperatorZoomTop,
	OperatorZoomRightTop,
	OperatorZoomRight,
	OperatorZoomRightBottom,
	OperatorZoomBottom,
	OperatorZoomLeftBottom,

};

class ECVS_EXPORT CShowImageWnd : public CStatic
{
	DECLARE_DYNAMIC(CShowImageWnd)

public:
	CShowImageWnd();
	virtual ~CShowImageWnd();


public:
	afx_msg void OnPaint();

	// ������ʾͼ��
	void SetImage(Mat img);  //////////////////////////////////////////////////////////////////////////
	void SetParentWnd(CWnd* pPrarent)
	{
		m_pParentWnd = pPrarent;
	}

protected:
	DECLARE_MESSAGE_MAP()

private:
	CBrush m_backBrush; //������ˢ
	CWnd*	m_pParentWnd; //������
	//���ڻ�ͼ����
	HDC		m_hdcDraw;
	HBITMAP	m_hBmpCompatible;
	HDC		m_hdcDoubleBuffer;
	CRect	m_rectShowImgRect; // ��ʾͼ��Ĵ���
	HGDIOBJ			m_hImage;
	void*			m_pImg;
	BITMAPINFO*		m_pBmpInfo;
	HDC				m_hMemdc;

	//ͼ��
	Mat			m_matShowImg;
	Mat			m_matShowImgClone;
	int m_nCols, m_nRows;  //��ǰͼ��ĳ���
	ShowImageWndOperator m_OperatorOnView;


	//����ͼ�����Ų����ı���
	int m_nCurRate;      //��ǰ���ʣ��Ŵ� ��С����
	double	m_dbShowPersent;  //��ǰ��ʾͼ��İٷֱ�
	CPoint		m_ptCoordinateOffset; //ͼ����ʾ������������Ͻǵ�ƫ����

private:  //˽�з���

	//������Դ��ɾ����Դ����
	bool Init();
	bool Init(int nRows, int nClos, int nChannels);
	bool Delete();

	//�Ŵ����С��ʾ����bEnlarge = true �Ŵ� ptCenter Ϊ�Ŵ�����ĵ�
	void Enlarge(bool bEnlarge, CPoint ptCenter);
	void EnlargeCenter(bool bEnlarge);  //��ͼ�����ĵ�Ϊ��׼����
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


