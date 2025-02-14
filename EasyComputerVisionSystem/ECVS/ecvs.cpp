#include "ecvs.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <QDockWidget>
#include <QtWidgets/QtWidgets>
#include <QTreeWidget>
#include <QFileDialog>
#include <QDialog>
#include <BilateralFilter.h>
#include <Qpoint>
#include <Qsci/qsciscintilla.h>
#include "PluginManager.h"
#include "AlgrithmPlugin.h"
#include "PluginManager.h"
#include "QTableViewEx.h"
#include "ECVSReadImage.h"
#include "ECVSCamera.h"
extern void ECVSInitCameara();  //初始化内部集成相机
extern CAlgrithmBase* CreateAlgrithmGloble(string strName);
extern void ECVSExitCamera();  //退出内部集成相机
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
	CFlowProcess::SetShowImgWnd(m_pShowImgWnd);
	InitCamera();

	
}
void ECVS::InitCamera()
{

	//添加菜单项

	//先集成内部的相机
	ECVSInitCameara();
	
	connect(ui.menuCamera, SIGNAL(triggered(QAction *)), this, SLOT(OnSetCamera(QAction* )));

	for (int i = 0; i < CECVSCamera::m_pCameras.size(); ++i)
	{

		//添加菜单项
 		string strText = CECVSCamera::m_pCameras[i]->GetShowText();
		QString qStr = StdStr2QString(strText);
		QAction* acCamera = new QAction(qStr, this);
	
		acCamera->setStatusTip(qStr);

		ui.menuCamera->addAction(acCamera);

		//添加工具栏

		QTreeWidgetItem *pTempCamera = new QTreeWidgetItem(m_pGetImg, QStringList(qStr));
		char strName[128];
		sprintf(strName, "ECVS_Camera%d", i);
		//string strName = "ECVS_Camera" + i;
		pTempCamera->setData(0, Qt::UserRole, QVariant(strName));
	}

	//Plugin相机
}

void ECVS::OnSetCamera(QAction *pAction)
{
	QList<QAction*> acts = ui.menuCamera->actions();
	int nIndex = -1;
	//找到是哪一个Action被触发了
	for (int i = 0; i < acts.size(); ++i)
	{
		if (acts[i] == pAction)
		{
			nIndex = i;
			break;
		}
	}

	if (nIndex >= 0 && nIndex < CECVSCamera::m_pCameras.size())
	{
		CECVSCamera::m_pCameras[nIndex]->SetCameraParam();
	}

}

void ECVS::ExitCamera()
{
	//退出软件集成相机
	ECVSExitCamera();
	//Pligin相机
}
ECVS::~ECVS()
{
	//退出相机
	ExitCamera();
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

	dock = new QDockWidget(QStringLiteral("对象列表"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_objList = new QTableViewEx(dock);
	m_objList->horizontalHeader()->hide();
	m_objList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_objList->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	m_objList->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	m_objList->setContextMenuPolicy(Qt::CustomContextMenu);
	//右键菜单
	connect(m_objList, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(SetFlow(const QPoint&)));
	//鼠标双击
	connect(m_objList, SIGNAL(moveIndex(int, int)), this, SLOT(MoveObjIndex(int ,int )));
	connect(m_objList, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(OnDoubleClicked(const QModelIndex&)));
 //	connect(m_objList, SIGNAL(mouseMoveEvent(QMouseEvent* )), SLOT());
// 	connect(m_objList, SIGNAL(mouseMoveEvent(QMouseEvent*)), SLOT());
	m_modelFlow = new QStandardItemModel();


	//文本消息改变
	connect(m_modelFlow, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)), this, SLOT(ToolTextChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)));
	
	m_objList->setModel(m_modelFlow);
	m_objList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	dock->setWidget(m_objList);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	ui.menuView->addAction(dock->toggleViewAction());

	dock = new QDockWidget(QStringLiteral("工具箱"), this);
	InitObjSet();
	dock->setWidget(m_objSet);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	ui.menuView->addAction(dock->toggleViewAction());



	dock = new QDockWidget(QStringLiteral("调试"), this);
	addDockWidget(Qt::BottomDockWidgetArea, dock);
	m_pCodeEdit = new QsciScintilla(dock);
//	m_pDebugTest = new QTextEdit(dock);
	dock->setWidget(m_pCodeEdit);
	ui.menuView->addAction(dock->toggleViewAction());
}

//右键快捷菜单
void ECVS::SetFlow(const QPoint& ptPos)
{
	QModelIndex index = m_objList->currentIndex();
	
	if (index.row() >= 0 && index.row() < m_modelFlow->rowCount())
	{
		m_pMenuSetFlowMenu->exec(QCursor::pos());
	}
}

//鼠标双击
void ECVS::OnDoubleClicked(const QModelIndex & index)
{
	SetAlgrithm(index.row());
}
void ECVS::ToolTextChanged(const QModelIndex &lt, const QModelIndex &rb, const QVector<int> &roles)
{
//	m_modelFlow->item()
	if (m_bChangeToolText)  //如果当前是设置算法显示字符串的
	{
		m_bChangeToolText = false;  //标志位反转为false
		for (int i = lt.row(); i <= rb.row(); ++i)
		{
			QStandardItem* pItem = m_modelFlow->item(i);
			QString str = pItem->text();
			std::string strName = str.toLocal8Bit().toStdString();
			//这里设置算法显示名字，该步暂时不加入redo undo功能  6-4添加 redo undo功能
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
// 	CFlowSet *pFlowSet = new CFlowSet(this);
 	int nIndex = m_objList->currentIndex().row();
	m_flowProcess[m_nCurIndex].SetInput(nIndex);
// 	CAlgrithmBase* pAlgrithm = m_flowProcess[m_nCurIndex].;
// 	pFlowSet->exec();
}

void ECVS::ChangeToolName()
{
	//m_objList->setEditTriggers(QAbstractItemView::CurrentChanged);
	m_objList->edit(m_objList->currentIndex());
	m_bChangeToolText = true;  //当前是设置算法显示字符串的
	//m_objLis
	
}

void ECVS::contextMenuEvent(QContextMenuEvent *e)
{

}

//初始化工具集合
void ECVS::InitObjSet()
{
	m_objSet = new QTreeWidget(this);
	m_objSet->setHeaderHidden(true);


	//图像获取工具
	m_pGetImg = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("图像获取")));
	QTreeWidgetItem*pGetImgFromFile = new QTreeWidgetItem(m_pGetImg, QStringList(QStringLiteral("从文件读取")));
	CECVSReadImage bRead;
	string strName = bRead.GetAlgrithmClassName();
	pGetImgFromFile->setData(0, Qt::UserRole, QVariant(strName.c_str()));


	//图像预处理工具
	QTreeWidgetItem* pPreImg = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("图像预处理")));
	QTreeWidgetItem*pTreeWidgetTemp = new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("双边滤波")));
	CBilateralFilter biFilter;
	 strName = biFilter.GetAlgrithmClassName();
	pTreeWidgetTemp->setData(0, Qt::UserRole, QVariant(strName.c_str()));


	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("高斯模糊")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("中值模糊")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("Sobel变换")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("Canny边缘")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("膨胀")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("腐蚀")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("开运算")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("闭运算")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("金字塔")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("归一化")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("对比度增强")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("二值化")));




	//测量
	QTreeWidgetItem* pMeasure = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("测量")));

	//模板定位
	QTreeWidgetItem* pMatchModel = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("定位")));

	//数学运算
	QTreeWidgetItem* pMathCalc = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("数学工具")));


	//代码工具
	QTreeWidgetItem* pCode = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("代码工具")));



	//插件功能
	QTreeWidgetItem* pPlugins = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("插件")));
	CPluginManager* pPluginsManager = GetPlugins();
	vector<string> strAlgrithmName = pPluginsManager->GetPluginsName();  //算法对外名字
	vector<string> strDataName = pPluginsManager->GetPluginsInnerName(); //算法内部名字
	for (int i = 0; i < strDataName.size(); ++i)
	{
		QByteArray byteArray;
		byteArray = QByteArray::fromStdString(strAlgrithmName[i]);
		QString qStrName;
		qStrName = QString::fromLocal8Bit(byteArray);
		QTreeWidgetItem*pTreeWidgetTemp = new QTreeWidgetItem(pPlugins, QStringList(qStrName));
		CBilateralFilter biFilter;
		string strName = strDataName[i];
		pTreeWidgetTemp->setData(0, Qt::UserRole, QVariant(strName.c_str()));
	}



	//void itemDoubleClicked(QTreeWidgetItem *item, int column);
	//信号连接

	connect(m_objSet, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(OnAddTools(QTreeWidgetItem *, int)));


}


void ECVS::createMenu()
{
	//ui.menuFile

	m_actOpenImg = new QAction(QStringLiteral("&打开图片"), this);
	//m_actOpenImg->setShortcuts(QKeySequence::Save);
	m_actOpenImg->setStatusTip(tr("打开图片"));
	connect(m_actOpenImg, SIGNAL(triggered()), this, SLOT(OpenImg()));
	m_pRunProcess = new QAction(QStringLiteral("&运行"), this);
	connect(m_pRunProcess, SIGNAL(triggered()), this, SLOT(OnRun()));

	ui.menuFile->addAction(m_actOpenImg);
	ui.menuFile->addAction(m_pRunProcess);

	m_pMenuSetFlowMenu = new QMenu(m_objList->horizontalHeader());  //流程设置菜单
	m_pActSetTool = m_pMenuSetFlowMenu->addAction(QStringLiteral("设置算法"));  //设置算法工具ACTION
	m_pActSetFlows = m_pMenuSetFlowMenu->addAction(QStringLiteral("输入设置")); //设置流程间的算法关系
	m_pActChangeToolName = m_pMenuSetFlowMenu->addAction(QStringLiteral("修改名字")); //修改算法显示的名字
	
	connect(m_pActSetTool, SIGNAL(triggered()), this, SLOT(SetTools()));
	connect(m_pActSetFlows, SIGNAL(triggered()), this, SLOT(SetToolsFlow()));
	connect(m_pActChangeToolName, SIGNAL(triggered()), this, SLOT(ChangeToolName()));
// 	QMenu *m_pMenuSetFlowMenu;  //流程设置菜单
// 	QAction* m_pActSetTool;  //设置算法工具ACTION
// 	QAction* m_pActSetFlows; //设置流程间的算法关系
// 	QAction* m_pActChangeToolName; //修改算法显示的名字
	/*m_pMenuSetFlowMenu = new QMenu();*/
	//ui.menuFile->addAction(m_actSaveImg);
}

void ECVS::OnRun()
{
	//for (int i = 0; i < 100; ++i)
	{
		m_flowProcess[m_nCurIndex].Run();
		//Sleep(1);
	}
	
}


void ECVS::OpenImg()
{
	QFileDialog openImg(this);
	openImg.setWindowTitle(QStringLiteral("打开图片"));
	openImg.setNameFilter(QStringLiteral("Image Files(*.jpg *.png *.bmp)"));
	if (openImg.exec() == QDialog::Accepted)
	{
		QString path = openImg.selectedFiles()[0];
		QByteArray byteArray = path.toLocal8Bit();
		string strPath = byteArray.toStdString();
		m_pShowImgWnd->SetImage(cv::imread(strPath.c_str(), cv::IMREAD_UNCHANGED));
	}
}

//双击工具，添加工具
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
//通过流程名字来添加算法工具，软件内置的算法还是需要通过if else 来
void ECVS::AddVisionTool(string strData)
{
	CAlgrithmBase *pAlgrithm = CAlgrithmBase::CreateAlgrithm(strData);
	//内置的算法
	if (pAlgrithm != NULL)
	{
		if (pAlgrithm->Set())
		{
			AddAlgrithm(pAlgrithm);
		}

		if (pAlgrithm->NeedClear())
		{
			delete pAlgrithm;
			pAlgrithm = NULL;
		}
	
	}
	else if (pAlgrithm = GetPlugins()->CreateAlgrithm(strData), pAlgrithm != NULL)//内置算法里面没有功能，那么去插件功能里面找，
	{
		//;
	
			if (pAlgrithm != NULL)
			{
				if (pAlgrithm->Set())
				{
					AddAlgrithm(pAlgrithm);
				}
				if (pAlgrithm->NeedClear())
				{
					delete pAlgrithm;
					pAlgrithm = NULL;
				}
			}
		

		

	}
	else  //如果插件还是没找到，丢给全局的CreateAlgrithm
	{

		pAlgrithm = CreateAlgrithmGloble(strData);
		if (pAlgrithm != NULL)
		{
			if (pAlgrithm->Set())
			{
				AddAlgrithm(pAlgrithm);
			}
			if (pAlgrithm->NeedClear())
			{
				delete pAlgrithm;
				pAlgrithm = NULL;
			}
		}
	}
}

void ECVS::AddAlgrithm(CAlgrithmBase* pAlgrithm)
{
	m_nCurIndex;
	m_flowProcess;
	//添加算法
	if (m_flowProcess.size() == 0)  //位流程为空时
	{
		CFlowProcess pro;
		pro.AddAlgrithm(pAlgrithm);//AddAlgrithm 里面自己重新分配存储空间，外面的空间需要外面释放
		m_flowProcess.push_back(pro);
		m_nCurIndex = 0;
	}
	else //如果不为空
	{
		CFlowProcess flow = m_flowProcess[m_nCurIndex];  //取当前的流程
		flow.AddAlgrithm(pAlgrithm);  //
		m_flowProcess.erase(m_flowProcess.begin() + m_nCurIndex + 1, m_flowProcess.end()); //删除尾巴
	
		m_flowProcess.push_back(flow); //添加
		m_nCurIndex = m_flowProcess.size() - 1; //设置标号

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
	//设置成功需要记录操作
	CFlowProcess flow = m_flowProcess[m_nCurIndex];
	if (m_flowProcess[m_nCurIndex].SetAlgrithm(nIndex))
	{
		m_flowProcess.erase(m_flowProcess.begin() + m_nCurIndex + 1, m_flowProcess.end()); //删除尾巴
		m_flowProcess.insert(m_flowProcess.end() - 1 , flow); //插入到倒数第二去
		m_nCurIndex = m_flowProcess.size() - 1; //设置标号
	}
}

void ECVS::MoveObjIndex(int nWitch, int nAfter)
{

	//m_flowProcess[m_nCurIndex]
	CFlowProcess flow = m_flowProcess[m_nCurIndex];
	if (m_flowProcess[m_nCurIndex].ChangeAlgrithmIndex(nWitch, nAfter))
	{
		m_flowProcess.erase(m_flowProcess.begin() + m_nCurIndex + 1, m_flowProcess.end()); //删除尾巴
		m_flowProcess.insert(m_flowProcess.end() - 1, flow); //插入到倒数第二去
		m_nCurIndex = m_flowProcess.size() - 1; //设置标号
	}
}
