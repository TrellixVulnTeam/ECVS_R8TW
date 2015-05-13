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
using std::string;
using std::vector;
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
	bool IsSameType(const CInputOutputInfo& rhs); //�ж����������Ƿ���ͬһ���������� ͬһ����������(int == int || vector<int> == int)
	bool IsSameType(const CInputOutputInfo& rhs) const;

	//����һϵ�к���Ϊ���úͻ�ȡ����ֵ�ĺ�����������Ի�ȡ�����ò�ͬ���͵�ֵ��ô����false
	bool GetIntValue(int& nValue);
	bool GetDoubleValue(double& dbValue);
	bool GetStringValue(string& strValue);
	bool GetVectIntValue(vector<int>& vecInt);
	bool GetVectDoubleValue(vector<double>& vecDouble);
	bool GetVecStrValue(vector<string>& strValue);
	bool SetIntValue(const int& nValue);
	bool SetDoubleValue(const double& dbValue);
	bool SetStringValue(const string& strValue);
	bool SetVectIntValue(const vector<int>& vecInt);
	bool SetVectDoubleValue(const vector<double>& vecDouble);
	bool SetVecStrValue(const vector<string>& strValue);
	//opencv��û���룬��ʱֻʵ�ֱ�׼��������

private:
	DataType	m_dataType;  //�ö������������




	int			m_nIntValue; //ΪTYPE_INTʱ��ֵ
	double		m_dbValue;   //ΪTYPE_DOUBLE��ֵ
	string		m_strValue;	 //ΪTYPE_STRINGʱ��ֵ
	//���±�������˼��������
// 	Point		m_ptValue;   
// 	PointF		m_ptFValue;
// 	Mat			m_Image;

	vector<int>		m_vecIntValue;
	vector<double>	m_vecDoubleValue;
	vector<string>	m_vecStrValue;
// 	vector<Point>	m_vecPTValue;
// 	vector<PointF>	m_vecPTFValue;
// 	vector<Mat>		m_vecImage;

	//˽�з���
private:
	void CopyValue(const CInputOutputInfo& rhs); //��rhs��ֵ���Ƶ��ö���

};

