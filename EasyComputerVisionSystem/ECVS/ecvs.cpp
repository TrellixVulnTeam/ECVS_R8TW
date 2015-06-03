#include "ecvs.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <QDockWidget>
#include <QtWidgets/QtWidgets>
#include <QTreeWidget>
#include <QFileDialog>
#include <QDialog>
#include <BilateralFilter.h>
ECVS::ECVS(QWidget *parent)
	: QMainWindow(parent)
{
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
// 	QRect rect = ui.dockWidgetObjList->geometry();
// 	int nW = rect.width();
// 	int nH = rect.height();
// 	rect.setLeft(0);
// 	rect.setTop(0);
// 	rect.setWidth(nW);
// 	rect.setHeight(nH);
//	ui.listViewObjList->setGeometry(rect);
}
void ECVS::createDockWindows()
{

	QDockWidget *dock;

	dock = new QDockWidget(QStringLiteral("�����б�"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_objList = new QListWidget(dock);



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
	
	connect(m_objSet, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int )), this, SLOT(OnAddTools(QTreeWidgetItem *, int )));


}


void ECVS::createMenu()
{
	//ui.menuFile

	m_actOpenImg = new QAction(QStringLiteral("&��ͼƬ"), this);
	//m_actOpenImg->setShortcuts(QKeySequence::Save);
	m_actOpenImg->setStatusTip(tr("��ͼƬ"));
	connect(m_actOpenImg, SIGNAL(triggered()), this, SLOT(OpenImg()));

	ui.menuFile->addAction(m_actOpenImg);
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

}