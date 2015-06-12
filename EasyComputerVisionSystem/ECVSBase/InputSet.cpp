#include "InputSet.h"
/*#include "ecvs.h"*/
CInputSet::CInputSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

/*	m_pParent = (ECVS*)parent;*/

// 	int  nIndex = m_pParent->m_objList->currentIndex().row();
// 	m_pParent->m_flowProcess[m_pParent->]
	m_pModelInputParam = new QStandardItemModel(0, 2);
	m_pPreAlgrithm = new QStandardItemModel();
	m_pModelInputParam->setHorizontalHeaderItem(0, new QStandardItem(QStringLiteral("��������")));
	m_pModelInputParam->setHorizontalHeaderItem(1, new QStandardItem(QStringLiteral("˵��")));
/*	ui.tableViewInputParam->setFont(QFont(QStringLiteral("����"),9));*/
	
	// 	QStandardItem*pCol1 = new QStandardItem(QStringLiteral("��������"));
// 	QStandardItem*pCol2 = new QStandardItem(QStringLiteral("��������"));

// 	QList<QStandardItem*> listItem;
// 	listItem.append(pCol1);
// 	listItem.append(pCol2);
// 	m_pModelInputParam->insertColumn(0, listItem);
// 	m_pModelInputParam->appendColumn(listItem);
	ui.tableViewInputParam->setModel(m_pModelInputParam);
	ui.tableViewSelectedObj->setModel(m_pPreAlgrithm);
	ui.tableViewInputParam->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableViewInputParam->setEditTriggers(QAbstractItemView::NoEditTriggers);
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