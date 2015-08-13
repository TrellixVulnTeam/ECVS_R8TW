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
#include <QStandardItemModel>
#include "ui_ecvs.h"
class QTextEdit;
class QTreeWidget;
class QsciScintilla;
using std::vector;
class ECVS : public QMainWindow
{
	Q_OBJECT


	friend class CFlowSet;
public:
	ECVS(QWidget *parent = 0);
	~ECVS();
	void contextMenuEvent(QContextMenuEvent *);
protected:
	//�麯��

	void resizeEvent(QResizeEvent *); //���ڴ�С�����ı�
private:
	Ui::ECVSClass ui;
	QTableView *m_objList;  //���̹����б�
	QStandardItemModel *m_modelFlow;
	bool		m_bChangeToolText; //�Ƿ�Ϊ�����㷨����ʾ�ַ�
	QTreeWidget *m_objSet; //������
	CShowImageWnd *m_pShowImgWnd;  //��ʾͼ��Ĵ���

	QMenu *m_pMenuSetFlowMenu;
	QAction* m_pActSetTool; 
	QAction* m_pActSetFlows; 
	QAction* m_pActChangeToolName; 

	QTextEdit*		m_pDebugTest;
	QsciScintilla*  m_pCodeEdit;

	
	//˽�з���
private:
	void InitObjSet();
	void createDockWindows();
	void createMenu();
	void AddVisionTool(string strData);  //ͨ���㷨������������̴�����
	void AddAlgrithm(CAlgrithmBase* pAlgrithm); //����㷨����Ҫ��¼���� ����Redo UnDo, �Լ������������UI����
	void SetAlgrithm(int nIndex); //��ĳһ���㷨�������ã���Ҫ��¼���� ����Redo UnDo, �Լ������������UI����

	//�źźͲ�
public slots:
	void OpenImg();
	void OnAddTools(QTreeWidgetItem *item, int column);
	void SetFlow(const QPoint&);
	void SetTools();
	void SetToolsFlow();
	void ChangeToolName();
	void OnDoubleClicked(const QModelIndex &);
	void ToolTextChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &);
	void MoveObjIndex(int nWitch, int nAfter);
	void OnRun();
	void OnSetCamera(QAction *);  //�������
private:

	//����һ�����̵ļ��� ����redo undo ���� ��m_nCurIndex����
	vector<CFlowProcess>  m_flowProcess;
	int m_nCurIndex;

	QAction* m_actOpenImg;
	QAction* m_actSaveImg;
	QAction* m_pRunProcess;
	//�������Ļ�ȡͼ���
	QTreeWidgetItem* m_pGetImg;
	//˽�з���
private:
	void InitCamera();  //��ʼ���������
	void ExitCamera();  //�˳����
};

#endif // ECVS_H
