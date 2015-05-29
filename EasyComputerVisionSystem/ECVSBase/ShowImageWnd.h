#ifndef SHOWIMAGEWND_H
#define SHOWIMAGEWND_H
#include "ECVSBase.h"
#include <QGraphicsView>

#define  WM_SHOWIMGFIXWINDOW WM_USER + 5017  //�Զ�����Ϣ��������Ӧ������ʾͼƬ
#define NUMOFCANNEL 1
#define	MAXRATE	 80
#define	MINRATE	 -80
#define	ONEPERCENT  10
class ECVS_EXPORT CShowImageWnd : public QFrame
{
	Q_OBJECT
public:
	CShowImageWnd(QWidget *parent);
	~CShowImageWnd();
	
	void SetImage(Mat img); //������ʾͼ��

private:
	Mat m_matShowImg;
	Mat m_matShowImgClone;
	QImage	m_imgShow;
	QRect	m_rectShowImgRect;  //��ʾͼ��ľ��ο�
	int m_nCols, m_nRows;
	//����ͼ�����Ų����ı���
	int m_nCurRate;      //��ǰ���ʣ��Ŵ� ��С����
	double	m_dbShowPersent;  //��ǰ��ʾͼ��İٷֱ�
	QPoint		m_ptCoordinateOffset; //ͼ����ʾ������������Ͻǵ�ƫ����


public slots:
	
protected:
	void wheelEvent(QWheelEvent* event);
	void paintEvent(QPaintEvent* event);
	void OnShowImgFixWindow(/*int nRows, int nCols*/);
	void Enlarge(bool bEnlarge, QPoint ptCenter);
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
