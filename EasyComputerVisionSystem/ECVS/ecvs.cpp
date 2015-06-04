#include "ecvs.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <QDockWidget>
#include <QtWidgets/QtWidgets>
#include <QTreeWidget>
#include <QFileDialog>
#include <QDialog>
#include <BilateralFilter.h>
#include <Qpoint>
ECVS::ECVS(QWidget *parent)
: QMainWindow(parent)
{
	m_bChangeToolText = false;
	ui.setupUi(this);
	m_pShowImgWnd = new CShowImageWnd(this);
	setCentralWidget(m_pShowImgWnd);
	createDockWindows();
	createMenu();
	setUnifiedTitleAndToolBarOnMac(true);
}

ECVS::~ECVS()
{

}

void ECVS::resizeEvent(QResizeEvent *e)
{
	QMainWindow::resizeEvent(e);


	QRect qRect = m_objList->rect();
	m_objList->setColumnWidth(0, qRect.width());

}
void ECVS::createDockWindows()
{

	QDockWidget *dock;

	dock = new QDockWidget(QStringLiteral("�����б�"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_objList = new QTableView(dock);
	m_objList->horizontalHeader()->hide();
	m_objList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_objList->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	m_objList->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	m_objList->setContextMenuPolicy(Qt::CustomContextMenu);
	//�Ҽ��˵�
	connect(m_objList, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(SetFlow(const QPoint&)));
	//���˫��
	connect(m_objList, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(OnDoubleClicked(const QModelIndex &)));
	

	m_modelFlow = new QStandardItemModel();


	//�ı���Ϣ�ı�
	connect(m_modelFlow, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)), this, SLOT(ToolTextChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)));
	
	m_objList->setModel(m_modelFlow);
	m_objList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	dock->setWidget(m_objList);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	ui.menuView->addAction(dock->toggleViewAction());

	dock = new QDockWidget(QStringLiteral("������"), this);
	InitObjSet();
	dock->setWidget(m_objSet);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	ui.menuView->addAction(dock->toggleViewAction());


	dock = new QDockWidget(QStringLiteral("����"), this);
	addDockWidget(Qt::BottomDockWidgetArea, dock);
	m_pDebugTest = new QTextEdit(dock);
	dock->setWidget(m_pDebugTest);
	ui.menuView->addAction(dock->toggleViewAction());
}

//�Ҽ���ݲ˵�
void ECVS::SetFlow(const QPoint& ptPos)
{
	QModelIndex index = m_objList->currentIndex();
	
	if (index.row() >= 0 && index.row() < m_modelFlow->rowCount())
	{
		m_pMenuSetFlowMenu->exec(QCursor::pos());
	}
}

//���˫��
void ECVS::OnDoubleClicked(const QModelIndex & index)
{
	SetAlgrithm(index.row());
}
void ECVS::ToolTextChanged(const QModelIndex &lt, const QModelIndex &rb, const QVector<int> &roles)
{
//	m_modelFlow->item()
	if (m_bChangeToolText)  //�����ǰ�������㷨��ʾ�ַ�����
	{
		m_bChangeToolText = false;  //��־λ��תΪfalse
		for (int i = lt.row(); i <= rb.row(); ++i)
		{
			QStandardItem* pItem = m_modelFlow->item(i);
			QString str = pItem->text();
			std::string strName = str.toLocal8Bit().toStdString();
			//���������㷨��ʾ���֣��ò���ʱ������redo undo����  6-4��� redo undo����
			m_flowProcess[m_nCurIndex].SetAlgrithmName(i,strName);
		}
	}

}

void ECVS::SetTools()
{
	int nSelectedIndex = m_objList->currentIndex().row();
	SetAlgrithm(nSelectedIndex);

}
void ECVS::SetToolsFlow()
{

}
void ECVS::ChangeToolName()
{
	//m_objList->setEditTriggers(QAbstractItemView::CurrentChanged);
	m_objList->edit(m_objList->currentIndex());
	m_bChangeToolText = true;  //��ǰ�������㷨��ʾ�ַ�����
	//m_objLis
	
}

void ECVS::contextMenuEvent(QContextMenuEvent *e)
{

}

//��ʼ�����߼���
void ECVS::InitObjSet()
{
	m_objSet = new QTreeWidget(this);
	m_objSet->setHeaderHidden(true);


	//ͼ���ȡ����
	QTreeWidgetItem* pGetImg = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("ͼ���ȡ")));

	//ͼ��Ԥ������
	QTreeWidgetItem* pPreImg = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("ͼ��Ԥ����")));
	QTreeWidgetItem*pTreeWidgetTemp = new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("˫���˲�")));
	CBilateralFilter biFilter;
	string strName = biFilter.GetAlgrithmClassName();
	pTreeWidgetTemp->setData(0, Qt::UserRole, QVariant(strName.c_str()));


	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("��˹ģ��")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("��ֵģ��")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("Sobel�任")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("Canny��Ե")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("����")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("��ʴ")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("������")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("������")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("������")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("��һ��")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("�Աȶ���ǿ")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("��ֵ��")));




	//����
	QTreeWidgetItem* pMeasure = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("����")));

	//ģ�嶨λ
	QTreeWidgetItem* pMatchModel = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("��λ")));

	//��ѧ����
	QTreeWidgetItem* pMathCalc = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("��ѧ����")));


	//���빤��
	QTreeWidgetItem* pCode = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("���빤��")));



	//�������
	QTreeWidgetItem* pPlugins = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("���")));

	//void itemDoubleClicked(QTreeWidgetItem *item, int column);
	//�ź�����

	connect(m_objSet, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(OnAddTools(QTreeWidgetItem *, int)));


}


void ECVS::createMenu()
{
	//ui.menuFile

	m_actOpenImg = new QAction(QStringLiteral("&��ͼƬ"), this);
	//m_actOpenImg->setShortcuts(QKeySequence::Save);
	m_actOpenImg->setStatusTip(tr("��ͼƬ"));
	connect(m_actOpenImg, SIGNAL(triggered()), this, SLOT(OpenImg()));

	ui.menuFile->addAction(m_actOpenImg);

	m_pMenuSetFlowMenu = new QMenu(m_objList->horizontalHeader());  //�������ò˵�
	 m_pActSetTool = m_pMenuSetFlowMenu->addAction(QStringLiteral("�����㷨"));  //�����㷨����ACTION
	 m_pActSetFlows = m_pMenuSetFlowMenu->addAction(QStringLiteral("��������")); //�������̼���㷨��ϵ
	 m_pActChangeToolName = m_pMenuSetFlowMenu->addAction(QStringLiteral("�޸�����")); //�޸��㷨��ʾ������
	 connect(m_pActSetTool, SIGNAL(triggered()), this, SLOT(SetTools()));
	 connect(m_pActSetFlows, SIGNAL(triggered()), this, SLOT(SetToolsFlow()));
	 connect(m_pActChangeToolName, SIGNAL(triggered()), this, SLOT(ChangeToolName()));
// 	QMenu *m_pMenuSetFlowMenu;  //�������ò˵�
// 	QAction* m_pActSetTool;  //�����㷨����ACTION
// 	QAction* m_pActSetFlows; //�������̼���㷨��ϵ
// 	QAction* m_pActChangeToolName; //�޸��㷨��ʾ������
	/*m_pMenuSetFlowMenu = new QMenu();*/
	//ui.menuFile->addAction(m_actSaveImg);
}

void ECVS::OpenImg()
{
	QFileDialog openImg(this);
	openImg.setWindowTitle(QStringLiteral("��ͼƬ"));
	openImg.setNameFilter(QStringLiteral("Image Files(*.jpg *.png *.bmp)"));
	if (openImg.exec() == QDialog::Accepted)
	{
		QString path = openImg.selectedFiles()[0];
		QByteArray byteArray = path.toLocal8Bit();
		string strPath = byteArray.toStdString();
		m_pShowImgWnd->SetImage(cv::imread(strPath.c_str()));
	}
}

//˫�����ߣ���ӹ���
void ECVS::OnAddTools(QTreeWidgetItem *item, int column)
{
	QString str = item->text(0);
	QVariant var = item->data(0, Qt::UserRole);
	if (var.isValid())
	{
		QString qstrData = var.toString();
		string strData = qstrData.toLocal8Bit().toStdString();
		AddVisionTool(strData);

	}

}
//ͨ����������������㷨���ߣ�������õ��㷨������Ҫͨ��if else ��
void ECVS::AddVisionTool(string strData)
{
	CAlgrithmBase *pAlgrithm = CAlgrithmBase::CreateAlgrithm(strData);
	//���õ��㷨
	if (pAlgrithm != NULL)
	{
		if (pAlgrithm->Set())
		{
			AddAlgrithm(pAlgrithm);
		}

		delete pAlgrithm;
		pAlgrithm = NULL;
	}
	else //�����㷨����û�й��ܣ���ôȥ������������ң�
	{

	}
}

void ECVS::AddAlgrithm(CAlgrithmBase* pAlgrithm)
{
	m_nCurIndex;
	m_flowProcess;
	//����㷨
	if (m_flowProcess.size() == 0)  //λ����Ϊ��ʱ
	{
		CFlowProcess pro;
		pro.AddAlgrithm(pAlgrithm);//AddAlgrithm �����Լ����·���洢�ռ䣬����Ŀռ���Ҫ�����ͷ�
		m_flowProcess.push_back(pro);
		m_nCurIndex = 0;
	}
	else //�����Ϊ��
	{
		CFlowProcess flow = m_flowProcess[m_nCurIndex];  //ȡ��ǰ������
		flow.AddAlgrithm(pAlgrithm);  //
		m_flowProcess.erase(m_flowProcess.begin() + m_nCurIndex + 1, m_flowProcess.end()); //ɾ��β��
		m_flowProcess.push_back(flow); //���
		m_nCurIndex = m_flowProcess.size() - 1; //���ñ��

	}
	std::string str = pAlgrithm->GetShowText();
	QByteArray byteArray;
	byteArray = QByteArray::fromStdString(str);
	QString strName;
	strName = QString::fromLocal8Bit(byteArray);
	QString strIndex = QString::number(m_flowProcess[m_nCurIndex].GetAlgrithmNumber()).sprintf("%d", m_flowProcess[m_nCurIndex].GetAlgrithmNumber());

	m_modelFlow->setItem(m_flowProcess[m_nCurIndex].GetAlgrithmNumber() - 1, 0, new QStandardItem(strName));
	/*	m_modelFlow->setItem(0, 1, new QStandardItem("20120202"));*/
	//m_objList->addItem(strName);
	//m_objList->addR
}

void ECVS::SetAlgrithm(int nIndex)
{
	//���óɹ���Ҫ��¼����
	CFlowProcess flow = m_flowProcess[m_nCurIndex];
	if (m_flowProcess[m_nCurIndex].SetAlgrithm(nIndex))
	{
		m_flowProcess.erase(m_flowProcess.begin() + m_nCurIndex + 1, m_flowProcess.end()); //ɾ��β��
		m_flowProcess.insert(m_flowProcess.end() - 1 , flow); //���뵽�����ڶ�ȥ
		m_nCurIndex = m_flowProcess.size() - 1; //���ñ��
	}
}