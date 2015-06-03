#ifndef ECVS_H
#define ECVS_H
#include <ECVSBaseHeader.h>
#include <ECVSBase.h>
#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <ShowImageWnd.h>
#include <vector>
#include <FlowProcess.h>
#include<QTreeWidget>
#include "ui_ecvs.h"
class QTextEdit;
class QTreeWidget;
using std::vector;
class ECVS : public QMainWindow
{
	Q_OBJECT

public:
	ECVS(QWidget *parent = 0);
	~ECVS();
	
protected:
	//�麯��

	void resizeEvent(QResizeEvent *); //���ڴ�С�����ı�
private:
	Ui::ECVSClass ui;
	QListWidget *m_objList;  //���̹����б�
	QTreeWidget *m_objSet; //������
	CShowImageWnd *m_pShowImgWnd;  //��ʾͼ��Ĵ���

	QTextEdit*		m_pDebugTest;
	
	//˽�з���
private:
	void InitObjSet();
	void createDockWindows();
	void createMenu();
	void AddVisionTool(string strData);  //ͨ���㷨������������̴�����
	void AddAlgrithm(CAlgrithmBase* pAlgrithm); //����㷨����Ҫ��¼���� ����Redo UnDo, �Լ������������UI����
	//�źźͲ�
public slots:
	void OpenImg();
	void OnAddTools(QTreeWidgetItem *item, int column);
private:

	//����һ�����̵ļ��� ����redo undo ���� ��m_nCurIndex����
	vector<CFlowProcess>  m_flowProcess;
	int m_nCurIndex;

	QAction* m_actOpenImg;
	QAction* m_actSaveImg;

};

#endif // ECVS_H
