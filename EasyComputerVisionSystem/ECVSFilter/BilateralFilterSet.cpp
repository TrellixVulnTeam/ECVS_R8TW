#include "stdafx.h"
/*#include "ShowImageWnd.h"*/
#include "FilterCommon.h"
#include "ECVSBase.h"
#include <QtWidgets/QPushButton>
#include "BilateralFilterSet.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <QtWidgets/QToolBox>
using namespace cv;
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QFileDialog>
#include <QDockWidget>
#include <QTextCodec>  
#
#include "BilateralFilter.h"
CBilateralFilterSet::CBilateralFilterSet(CBilateralFilter* pOwer, QWidget *parent)
: m_pOwerFilter(pOwer),QDialog(parent)
{

// 	QVBoxLayout *mainLayout = new QVBoxLayout(this);
// 	QToolBox *toolbox = new QToolBox();
// 	mainLayout->addWidget(toolbox);

	ui.setupUi(this);
	m_pShowImgWnd = new CShowImageWnd(ui.frame);


	ui.frame->setStyleSheet("border:1px solid black");
	ui.frame->setAutoFillBackground(true);
	
	
	QToolBar *toolBar = new QToolBar(this);
	ui.horizontalLayout_5->addWidget(toolBar);
	//��Ӵ�ͼƬ��ť
	QToolButton*pToolButtonOpenImgs = new QToolButton(this);
	pToolButtonOpenImgs->setText(QStringLiteral("��ͼƬ"));
	pToolButtonOpenImgs->setIcon(QPixmap(":/BilateralFilter/open.png"));
	pToolButtonOpenImgs->setIconSize(QPixmap(":/BilateralFilter/open.png").size());
	pToolButtonOpenImgs->setToolTip(QStringLiteral("��ͼƬ")); 
	toolBar->addWidget(pToolButtonOpenImgs);
	//�������ȡͼƬ
	QToolButton *pToolButtonGetImgs = new QToolButton(this);
	pToolButtonGetImgs->setText(QStringLiteral("����"));
	toolBar->addWidget(pToolButtonGetImgs);

	QToolButton*pToolButtonShowOrgImg = new QToolButton(this);
	pToolButtonShowOrgImg->setText(QStringLiteral("��ʾԭͼ"));
	toolBar->addWidget(pToolButtonShowOrgImg);

	QToolButton*pToolButtonShowFilterImg = new QToolButton(this);
	pToolButtonShowFilterImg->setText(QStringLiteral("����ͼ"));
	toolBar->addWidget(pToolButtonShowFilterImg);

	QToolButton*pToolButtonShowFixSize= new QToolButton(this);
	pToolButtonShowFixSize->setText(QStringLiteral("ͼ����Ӧ����"));
	toolBar->addWidget(pToolButtonShowFixSize);

	//connect()
	connect(pToolButtonOpenImgs, SIGNAL(clicked()), SLOT(OnOpenImg()));
	connect(pToolButtonShowFixSize, SIGNAL(clicked()), SLOT(OnShowFixSize()));
	connect(pToolButtonShowOrgImg, SIGNAL(clicked()), SLOT(OnShowOrgImg()));  //��ʾԭͼ
	connect(pToolButtonShowFilterImg, SIGNAL(clicked()), SLOT(OnShowFilterImg()));  //��ʾ����ͼ


	//�����С����ť
	Qt::WindowFlags flags = Qt::Window;
	setWindowFlags(flags);
	
	//���ò�����ȡֵ��Χ
	ui.horizontalSliderD->setRange(1, 20);  //D 1 ~ 20
	ui.horizontalSliderSigmaColor->setRange(1, 255); //SigmaColor 1~255
	ui.horizontalSliderSigmaSpace->setRange(1, 255); //SigmaSpace 1~255
	ui.spinBoxD->setRange(1, 20);  //D 1 ~ 20
	ui.spinBoxSigmaColor->setRange(1, 255); //SigmaColor 1~255
	ui.spinBoxSigmaSpace->setRange(1, 255); //SigmaSpace 1~255
	ui.spinBoxD->setValue(m_pOwerFilter->m_nDiameter);
	ui.spinBoxSigmaColor->setValue(m_pOwerFilter->m_dbSigmaColor);
	ui.spinBoxSigmaSpace->setValue(m_pOwerFilter->m_dbSigmaSpace);
	ui.horizontalSliderD->setValue(m_pOwerFilter->m_nDiameter);
	ui.horizontalSliderSigmaColor->setValue(m_pOwerFilter->m_dbSigmaColor);
	ui.horizontalSliderSigmaSpace->setValue(m_pOwerFilter->m_dbSigmaSpace);
	//�źźͲ۵�����
	connect(ui.horizontalSliderD, SIGNAL(valueChanged(int)), SLOT(OnSliderDChanged(int)));
	connect(ui.horizontalSliderSigmaColor, SIGNAL(valueChanged(int)), SLOT(OnSliderSigmaColorChanged(int)));
	connect(ui.horizontalSliderSigmaSpace, SIGNAL(valueChanged(int)), SLOT(OnSliderSigmaSpaceChanged(int)));
	connect(ui.spinBoxD, SIGNAL(valueChanged(int)), SLOT(OnSpinDChanged(int)));
	connect(ui.spinBoxSigmaColor, SIGNAL(valueChanged(int)), SLOT(OnSpinSigmaColorChanged(int)));
	connect(ui.spinBoxSigmaSpace, SIGNAL(valueChanged(int)), SLOT(OnSpinSigmaSpaceChanged(int)));

	connect(ui.OKBtn, SIGNAL(clicked()), SLOT(OnOkClicked()));
	connect(ui.CancelBtn, SIGNAL(clicked()), SLOT(OnCancelClicled()));

}

CBilateralFilterSet::~CBilateralFilterSet()
{

}

void CBilateralFilterSet::resizeEvent(QResizeEvent *e)
{
	QDialog::resizeEvent(e);
	QRect rect = ui.frame->geometry();
	int nW = rect.width();
	int nH = rect.height();
	rect.setLeft(0);
	rect.setTop(0);
	rect.setWidth(nW);
	rect.setHeight(nH);
	m_pShowImgWnd->setGeometry(rect);
}

void CBilateralFilterSet::OnOpenImg()
{


	//QString path = QFileDialog::getOpenFileName(this, QStringLiteral("��ͼƬ"), ".", QStringLiteral("Image Files(*.jpg *.png *.bmp)"));

 	QFileDialog openImg(this);
	openImg.setWindowTitle(QStringLiteral("��ͼƬ"));
	openImg.setNameFilter(QStringLiteral("Image Files(*.jpg *.png *.bmp)"));
	if (openImg.exec() == Accepted)
	{
		QString path = openImg.selectedFiles()[0];
		QByteArray byteArray = path.toLocal8Bit();
		string strPath =  byteArray.toStdString();
		m_imgProcessed = imread(strPath.c_str());
		//QImage qImg(path);
		
		BilateralFilterParamChanged(); //��ͼƬʱ��Ҫ����һ���˲�����
		
	}

}
void CBilateralFilterSet::OnShowFixSize()
{
	m_pShowImgWnd->ShowImgFixSize();
}
void CBilateralFilterSet::OnSliderDChanged(int nValue)
{

	if (ui.spinBoxD->value() != nValue)
	{
		ui.spinBoxD->setValue(nValue);
		BilateralFilterParamChanged();
	}
}


void CBilateralFilterSet::OnSliderSigmaColorChanged(int nValue)
{
	
	if (ui.spinBoxSigmaColor->value() != nValue)
	{
		ui.spinBoxSigmaColor->setValue(nValue);
		BilateralFilterParamChanged();
	}

}

void CBilateralFilterSet::OnSliderSigmaSpaceChanged(int nValue)
{
	if (ui.spinBoxSigmaSpace->value() != nValue)
	{
		ui.spinBoxSigmaSpace->setValue(nValue);
		BilateralFilterParamChanged();
	}
	

}

void CBilateralFilterSet::OnSpinDChanged(int nValue)
{
	if (ui.horizontalSliderD->value() != nValue)
	{
		ui.horizontalSliderD->setValue(nValue);
		BilateralFilterParamChanged();
	}
}
void CBilateralFilterSet::OnSpinSigmaColorChanged(int nValue)
{
	if (ui.horizontalSliderSigmaColor->value() != nValue)
	{
		ui.horizontalSliderSigmaColor->setValue(nValue);
		BilateralFilterParamChanged();
	}
}
void CBilateralFilterSet::OnSpinSigmaSpaceChanged(int nValue)
{
	if (ui.horizontalSliderSigmaSpace->value() != nValue)
	{
		ui.horizontalSliderSigmaSpace->setValue(nValue);
		BilateralFilterParamChanged();
	}
}

void CBilateralFilterSet::BilateralFilterParamChanged()
{
	if (m_imgProcessed.data != NULL) //����ͼ��ʱ�����д���
	{
		::PostMessage((HWND)this->winId(), BILATERAL_FILTER_PARAM_CHANGE, 0, 0);
	}
	
}

bool CBilateralFilterSet::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	if (eventType == "windows_generic_MSG")
	{
		PMSG msg = (PMSG)message;
		if (msg->message == BILATERAL_FILTER_PARAM_CHANGE)
		{

			OnBilateralFilter();
			return true;
		}
	}
	return __super::nativeEvent(eventType, message, result);
}

void CBilateralFilterSet::OnBilateralFilter()
{
	Mat imgProcessd;


	imgProcessd = m_pOwerFilter->Run(m_imgProcessed, ui.spinBoxD->value(), ui.spinBoxSigmaColor->value(), ui.spinBoxSigmaSpace->value()); //ִ��
	m_pShowImgWnd->SetImage(imgProcessd);
	
}

void CBilateralFilterSet::OnOkClicked()
{
	m_pOwerFilter->m_nDiameter = ui.spinBoxD->value();
	m_pOwerFilter->m_dbSigmaColor = ui.spinBoxSigmaColor->value();
	m_pOwerFilter->m_dbSigmaSpace = ui.spinBoxSigmaSpace->value();
	this->close();
	this->setResult(Accepted);
}
void CBilateralFilterSet::OnCancelClicled()
{
	
	this->close();
	this->setResult(Rejected);
}

//��ʾԭͼ
void CBilateralFilterSet::OnShowOrgImg()
{
	if (m_imgProcessed.data != NULL)
	{
		m_pShowImgWnd->SetImage(m_imgProcessed);
	}
}

//��ʾ����ͼ
void CBilateralFilterSet::OnShowFilterImg()
{
	BilateralFilterParamChanged();
}

//�鹹�캯��
