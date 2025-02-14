#include "InputSet.h"
#include "ToolOutput.h"
#include "ToolInput.h"
#include "ECVSBase.h"


#include "AlgrithmBase.h"

#include <string>
#include <vector>
#include "FlowProcess.h"
using namespace std;
/*#include "ecvs.h"*/
CInputSet::CInputSet(int nIndex,QWidget *parent): m_nAlgrithmIndex(nIndex),QDialog(parent)
{
	ui.setupUi(this);

/*	m_pParent = (ECVS*)parent;*/

// 	int  nIndex = m_pParent->m_objList->currentIndex().row();
// 	m_pParent->m_flowProcess[m_pParent->]
	m_pModelInputParam = new QStandardItemModel(0, 2);
	m_pPreAlgrithm = new QStandardItemModel();
	m_pCandidateParam = new QStandardItemModel(0,2);
	m_pModelInputParam->setHorizontalHeaderItem(0, new QStandardItem(QStringLiteral("输入名字")));
	m_pModelInputParam->setHorizontalHeaderItem(1, new QStandardItem(QStringLiteral("说明")));

	m_pCandidateParam->setHorizontalHeaderItem(0, new QStandardItem(QStringLiteral("输出参数")));
	m_pCandidateParam->setHorizontalHeaderItem(1, new QStandardItem(QStringLiteral("说明")));

	
/*	ui.tableViewInputParam->setFont(QFont(QStringLiteral("宋体"),9));*/
	
	// 	QStandardItem*pCol1 = new QStandardItem(QStringLiteral("输入名字"));
// 	QStandardItem*pCol2 = new QStandardItem(QStringLiteral("输入类型"));

// 	QList<QStandardItem*> listItem;
// 	listItem.append(pCol1);
// 	listItem.append(pCol2);
// 	m_pModelInputParam->insertColumn(0, listItem);
// 	m_pModelInputParam->appendColumn(listItem);
	ui.tableViewInputParam->setModel(m_pModelInputParam);

	ui.tableViewInputParam->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableViewInputParam->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui.tableViewSelectedObj->setModel(m_pPreAlgrithm);
	ui.tableViewSelectedObj->horizontalHeader()->hide();

	ui.tableViewSelectedParam->setModel(m_pCandidateParam);

//	connect(m_pPreAlgrithm, SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), SLOT(SelectedAlgrithmChanged(const QModelIndex &, const QModelIndex &)));
	connect(ui.tableViewSelectedObj, SIGNAL(clicked(QModelIndex)),
		this, SLOT(SelectedAlgrithmChanged(QModelIndex)));
//	m_pPreAlgrithm->r
//	AddSrcInput(QStringLiteral("asd"), QStringLiteral("asd"));
}

CInputSet::~CInputSet()
{

}
void CInputSet::AddSrcInput(QString strInputName, QString strInputType)
{
	QStandardItem*pCol1 = new QStandardItem(strInputName);
	QStandardItem*pCol2 = new QStandardItem(strInputType);
	QList<QStandardItem*> listItem;
	listItem.append(pCol1);
	listItem.append(pCol2);
	m_pModelInputParam->appendRow(listItem);
}

void CInputSet::AddPreAlgrithms(QString strPreAlgrithm)
{
	m_pPreAlgrithm->appendRow(new QStandardItem(strPreAlgrithm));
}

void CInputSet::SelectedAlgrithmChanged( QModelIndex index )
{
//	int nRow = item->row();
	int nIndexParam = ui.tableViewInputParam->currentIndex().row();
	//emit InputIndexChange(nIndexParam, index.row());

	ClearSelectedParam();
	int nSize = m_pOwerProcess->m_pOutput[index.row()].size();
	vector<string> strOutName = m_pOwerProcess->m_pAlgrithms[index.row()]->GetOutputParamName();
	vector<CToolInput*> pInputs = m_pOwerProcess->m_pAlgrithms[m_nAlgrithmIndex]->GetInput();
	for (int i = 0; i < nSize; ++i)
	{
	
		if (m_pOwerProcess->m_pOutput[index.row()][i]->IsSameType(*pInputs[nIndexParam]))
		{
			AddSelectedParam(StdStr2QString(strOutName[i]), StdStr2QString(m_pOwerProcess->m_pOutput[index.row()][i]->GetStringInfo()));
		}
	
	}

}

void CInputSet::AddSelectedParam(QString strName, QString str)
{
	QStandardItem*pCol1 = new QStandardItem(strName);
	QStandardItem*pCol2 = new QStandardItem(str);
	QList<QStandardItem*> listItem;
	listItem.append(pCol1);
	listItem.append(pCol2);
	m_pCandidateParam->appendRow(listItem);
}
void CInputSet::ClearSelectedParam()
{
	m_pCandidateParam->clear();
}