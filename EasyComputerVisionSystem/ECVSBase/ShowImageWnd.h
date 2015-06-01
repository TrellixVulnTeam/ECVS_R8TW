#ifndef SHOWIMAGEWND_H
#define SHOWIMAGEWND_H
#include "ECVSBase.h"
#include <QGraphicsView>

#define  WM_SHOWIMGFIXWINDOW WM_USER + 5017  //�Զ�����Ϣ��������Ӧ������ʾͼƬ
#define NUMOFCANNEL 1
#define	MAXRATE	 26
#define	MINRATE	 -15
#define	ONEPERCENT  7
class ECVS_EXPORT CShowImageWnd : public QFrame
{
	Q_OBJECT
public:
	CShowImageWnd(QWidget *parent);
	~CShowImageWnd();
	
	void SetImage(Mat img); //������ʾͼ��
	bool GetBackImg(Mat& imgBack); //��ȡ��̨ͼ��
	bool CanEditView()
	{
		return m_bCanEditView;
	}
	void SetEidtView(bool bCanEdit)
	{
		m_bCanEditView = bCanEdit;
	}
	void ShowImgFixSize();


private:
	Mat			m_matShowImg;
	Mat			m_matShowImgClone;
	QImage		m_imgShow;
	QRectF		m_rectShowImgRect;  //��ʾͼ��ľ��ο�
	int			m_nCols, m_nRows;
	//����ͼ�����Ų����ı���
	int			m_nCurRate;      //��ǰ���ʣ��Ŵ� ��С����
	double		m_dbShowPersent;  //��ǰ��ʾͼ��İٷֱ�
	QPoint		m_ptCoordinateOffset; //ͼ����ʾ������������Ͻǵ�ƫ����
	QPoint		m_ptPrev;			//����ƶ�ʱ��һ������
	bool		m_bCanEditView;		//�Ƿ���Զ�ͼ��������ţ��ƶ�����

public slots:
	
protected:
	void wheelEvent(QWheelEvent* event);  //��������Ϣ
	void paintEvent(QPaintEvent* event);  //������Ϣ
	void mouseMoveEvent(QMouseEvent* event);   //����ƶ���Ϣ
	void OnShowImgFixWindow(/*int nRows, int nCols*/);
//	void Enlarge(bool bEnlarge, QPoint ptCenter);
	void Enlarge(bool bEnlarge, QPointF ptCenter);
	void EnlargeCenter(bool bEnlarge);  //��ͼ�����ĵ�Ϊ��׼����
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:

	//������Դ��ɾ����Դ����
	bool Init();
	bool Init(int nRows, int nClos, int nChannels);
	bool Delete();
	//��Matת��ΪQImage
	
};

#endif // SHOWIMAGEWND_H
