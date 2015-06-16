#ifndef FLOWSET_H
#define FLOWSET_H

#include <QDialog>
#include "ui_InputSet.h"
#include <QStandardItemModel>

class CInputSet : public QDialog
{
	Q_OBJECT
	friend class CFlowProcess;
public:
	CInputSet(int nIndex, QWidget *parent = 0);
	~CInputSet();
	
	void AddSrcInput(QString strInputName, QString strInputType);
	void AddSelectedParam(QString strName, QString str);
	void ClearSelectedParam();
	void AddPreAlgrithms(QString strPreAlgrithm);
public slots:
	void SelectedAlgrithmChanged( QModelIndex );

Q_SIGNALS:
	//�����㷨�ı���,nIndexCurParam����һ�����������nCurInput��ѡ����һ�������Ϊ�������
	void InputIndexChange(int nIndexCurParam,int nCurInput);

private:
	Ui::CInputSet ui;
	QStandardItemModel *m_pModelInputParam;  //��Ҫ������Ĳ���
	QStandardItemModel *m_pPreAlgrithm;  // ǰ�����ߣ�
	QStandardItemModel *m_pCandidateParam;  //�� ѡ���������
	CFlowProcess*		m_pOwerProcess ;  //������һ��Process
	const int			m_nAlgrithmIndex;
	
};

#endif // FLOWSET_H
