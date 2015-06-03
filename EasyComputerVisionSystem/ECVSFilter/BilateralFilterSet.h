#ifndef BILATERALFILTERSET_H
#define BILATERALFILTERSET_H
#include "ecvsfilter_global.h"
#include "ECVSBase.h"
#include <QWidget>
#include <QDialog>
#include "ui_BilateralFilterSet.h"
#include "ShowImageWnd.h"
#include <QMainWindow>
#include <QGraphicsWidget>
class CBilateralFilter;
class  CBilateralFilterSet : public QDialog
{
	Q_OBJECT

public:
	CBilateralFilterSet(CBilateralFilter* pOwer,QWidget *parent = 0);
	~CBilateralFilterSet();

private:
	Ui::CBilateralFilterSet ui;
	CShowImageWnd *m_pShowImgWnd;

 	QPushButton* m_pButtonTest;
	CBilateralFilter*	m_pOwerFilter;  //���ĸ�Filter���õ�
	Mat m_imgProcessed;			//�������ͼ�񣬴��ļ���ȡ����������ȡ����
protected:
	void resizeEvent(QResizeEvent *);
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);  //����Windows��Ϣ

private slots:
	void OnOpenImg();
	void OnShowFixSize();
	void OnShowOrgImg();
	void OnShowFilterImg();
	void OnSliderDChanged(int nValue);
	void OnSliderSigmaColorChanged(int nValue);
	void OnSliderSigmaSpaceChanged(int nValue);

	void OnSpinDChanged(int nValue);
	void OnSpinSigmaColorChanged(int nValue);
	void OnSpinSigmaSpaceChanged(int nValue);
	void OnOkClicked();
	void OnCancelClicled();
private:
	void BilateralFilterParamChanged();  //��3�������κ�һ���ı�ʱ�����øú���
	void OnBilateralFilter();  //ʵ��ִ��BilateralFilter�ĺ���


	
};

#endif // BILATERALFILTERSET_H
