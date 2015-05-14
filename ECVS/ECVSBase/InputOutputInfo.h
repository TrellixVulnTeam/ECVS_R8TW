#pragma once

/*
* InputOutputInfo.h
*
* ������ 2015-5-12  ���
*
* ���ļ�������������н�������������CInputOutputInfo ��������ж��Ը��������ͽ��н���
* 
*/

#include "ECVSBase.h"
#include <string>
#include <vector>
#include <cxcore.h>
using std::string;
using std::vector;
using cv::Mat;
using cv::Point;
using cv::Point2f;

//CInputOutputInfo ����������







//��������������������ͣ���������󲿷���������

class ECVS_EXPORT CInputOutputInfo
{
public:
	CInputOutputInfo(DataType type);
	CInputOutputInfo(const CInputOutputInfo& rhs); //���ƹ��캯��
	~CInputOutputInfo();
	CInputOutputInfo& operator=(const CInputOutputInfo& rhs); //��ֵ������


	//������������Ϊ��ȡ��ǰ��������
	DataType GetDataType();
	const DataType GetDataType() const;
	//�ж��Ƿ����б�����
	bool  IsVector();
	bool  IsVector() const;

	bool IsSameType(const CInputOutputInfo& rhs); //�ж����������Ƿ���ͬһ���������� ͬһ����������(int == int || vector<int> == int)
	bool IsSameType(const CInputOutputInfo& rhs) const;

	//����һϵ�к���Ϊ���úͻ�ȡ����ֵ�ĺ�����������Ի�ȡ�����ò�ͬ���͵�ֵ��ô����false
	bool GetIntValue(int& nValue);
	bool GetDoubleValue(double& dbValue);
	bool GetStringValue(string& strValue);
	bool GetVectIntValue(vector<int>& vecInt);
	bool GetVectDoubleValue(vector<double>& vecDouble);
	bool GetVecStrValue(vector<string>& strValue);
	//����const����
	bool GetIntValue(int& nValue) const;
	bool GetDoubleValue(double& dbValue) const;
	bool GetStringValue(string& strValue) const;
	bool GetVectIntValue(vector<int>& vecInt) const;
	bool GetVectDoubleValue(vector<double>& vecDouble) const;
	bool GetVecStrValue(vector<string>& strValue) const;

	//2015-5-14 ����OpenCV��������
	bool SetIntValue(const int& nValue);
	bool SetDoubleValue(const double& dbValue);
	bool SetStringValue(const string& strValue);
	bool SetVectIntValue(const vector<int>& vecInt);
	bool SetVectDoubleValue(const vector<double>& vecDouble);
	bool SetVecStrValue(const vector<string>& strValue);
	bool SetPointValue(const Point & ptPos);
	bool SetPointFValue(const Point2f& ptPos);
	bool SetImageValue(const Mat& mat);
	bool SetVecPointValue(const vector<Point>& vecPoint);
	bool SetVecPointFValue(const vector<Point2f>& vecPoint2f);
	bool SetVecImageValue(const vector<Mat>& vecImage);


	bool GetPointValue(Point& ptPos);
	bool GetPointValue(Point& ptPos) const;
	bool GetPointFValue(Point2f& ptPos) ;
	bool GetPointFValue(Point2f& ptPos)const;
	bool GetImageValue(Mat & img) ;
	bool GetImageValue(Mat & img)const;
	bool GetVecPointValue(vector<Point>& vecPts);
	bool GetVecPointValue(vector<Point>& vecPts)const;
	bool GetVecPointFValue(vector<Point2f>& vecPts);
	bool GetVecPointFValue(vector<Point2f>& vecPts) const;
	bool GetVecImageValue(vector<Mat>& vecImage);
	bool GetVecImageValue(vector<Mat>& vecImage) const;




private:
	DataType	m_dataType;  //�ö������������




	int			m_nIntValue; //ΪTYPE_INTʱ��ֵ
	double		m_dbValue;   //ΪTYPE_DOUBLE��ֵ
	string		m_strValue;	 //ΪTYPE_STRINGʱ��ֵ
	//���±�������˼��������
	Point		m_ptValue;   
	Point2f		m_ptFValue;
	Mat			m_Image;

	vector<int>		m_vecIntValue;
	vector<double>	m_vecDoubleValue;
	vector<string>	m_vecStrValue;
	vector<Point>	m_vecPTValue;
	vector<Point2f>	m_vecPTFValue;
	vector<Mat>		m_vecImage;

	//˽�з���
private:
	void CopyValue(const CInputOutputInfo& rhs); //��rhs��ֵ���Ƶ��ö���

};

