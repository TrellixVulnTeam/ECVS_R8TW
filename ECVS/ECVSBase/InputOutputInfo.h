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

//��ͨ���ݵ���ʼ����
#define DATA_TYPE_BASE  0x0F00
//����������vector����ʼ����
#define DATA_TYPE_VEC_BASE 0xFF00

enum DataType
{
	TYPE_INT		= DATA_TYPE_BASE,				//����
	TYPE_DOUBLE		= DATA_TYPE_BASE + 1,			//������
	TYPE_STRING		= DATA_TYPE_BASE + 2,			//�ַ�������
	TYPE_POINT		= DATA_TYPE_BASE + 3,				//CV::Point����
	TYPE_POINT2F	= DATA_TYPE_BASE + 4,			//CV::Point2F����
	TYPE_IMAGE		= DATA_TYPE_BASE + 5,				//CV::Mat ����
	//������ֶζ��������Vector����
	TYPE_INT_VECTOR		= DATA_TYPE_VEC_BASE,
	TYPE_DOUBLE_VECTOR	= DATA_TYPE_VEC_BASE + 1,
	TYPE_STRING_VECTOR	= DATA_TYPE_VEC_BASE + 2,
	TYPE_POINT_VECTOR	= DATA_TYPE_VEC_BASE + 3,
	TYPE_POINT2F_VECTOR = DATA_TYPE_VEC_BASE + 4,
	TYPE_IMAGE_VECTOR	= DATA_TYPE_VEC_BASE + 5


};

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

