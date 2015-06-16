#ifndef QTABLEVIEWEX_H
#define QTABLEVIEWEX_H
//����϶������ܵ�TableView
#include <QTableView>



class QTableViewEx : public QTableView
{
	Q_OBJECT

public:
	QTableViewEx(QWidget *parent);
	~QTableViewEx();
	void setModel(QAbstractItemModel *model);
private:
	int m_nMouseDownIndex;
	int m_nMouseUpIndex;
	int m_nPreIndex; //����ƶ�ʱ����һ��Index
	QAbstractItemModel * m_pItemModel;
protected:
	virtual void	mouseMoveEvent(QMouseEvent * event);
	virtual void	mousePressEvent(QMouseEvent * event);
	virtual void	mouseReleaseEvent(QMouseEvent * event);
private:

public:
signals :
		void moveIndex(int , int );
};

#endif // QTABLEVIEWEX_H
