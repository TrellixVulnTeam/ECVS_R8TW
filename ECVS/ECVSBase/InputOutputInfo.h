#pragma once

/*
* InputOutputInfo.h
*
* 创建于 2015-5-12  李春峰
*
* 该文件定义整个软件中交互的数据类型CInputOutputInfo 软件流程中都以该数据类型进行交互
* 
*/

#include "ECVSBase.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
//CInputOutputInfo 的数据类型







//代表输入输出的数据类型，里面包含大部分数据类型

class ECVS_EXPORT CInputOutputInfo
{
public:
	CInputOutputInfo(DataType type);
	CInputOutputInfo(const CInputOutputInfo& rhs); //复制构造函数
	~CInputOutputInfo();
	CInputOutputInfo& operator=(const CInputOutputInfo& rhs); //赋值操作符


	//以下两个函数为获取当前数据类型
	DataType GetDataType();
	const DataType GetDataType() const;
	//判断是否是列表类型
	bool  IsVector();
	bool IsSameType(const CInputOutputInfo& rhs); //判断两个对象是否是同一种数据类型 同一种数据类型(int == int || vector<int> == int)
	bool IsSameType(const CInputOutputInfo& rhs) const;

	//以下一系列函数为设置和获取数据值的函数，如果尝试获取或设置不同类型的值那么返回false
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
	//opencv还没导入，暂时只实现标准数据类型

private:
	DataType	m_dataType;  //该对象的数据类型




	int			m_nIntValue; //为TYPE_INT时的值
	double		m_dbValue;   //为TYPE_DOUBLE的值
	string		m_strValue;	 //为TYPE_STRING时的值
	//以下变量的意思依次类推
// 	Point		m_ptValue;   
// 	PointF		m_ptFValue;
// 	Mat			m_Image;

	vector<int>		m_vecIntValue;
	vector<double>	m_vecDoubleValue;
	vector<string>	m_vecStrValue;
// 	vector<Point>	m_vecPTValue;
// 	vector<PointF>	m_vecPTFValue;
// 	vector<Mat>		m_vecImage;

	//私有方法
private:
	void CopyValue(const CInputOutputInfo& rhs); //将rhs的值复制到该对象

};

