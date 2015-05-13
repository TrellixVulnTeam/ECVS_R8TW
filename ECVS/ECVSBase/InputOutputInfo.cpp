/*
* InputOutputInfo.cpp
*
* ������ 2015-5-12  ���
*
* ʵ��CInputOutputInfo��������
*
*/

#define  ECVS_BUILD_DLL
#include "InputOutputInfo.h"

//���캯��,����ָ������
CInputOutputInfo::CInputOutputInfo(DataType type) :m_dataType(type)
{
}


CInputOutputInfo::~CInputOutputInfo()
{
}

//��ֵ���캯��
CInputOutputInfo::CInputOutputInfo(const CInputOutputInfo& rhs) //���ƹ��캯��
{
	CopyValue(rhs);
}

//��ֵ������
CInputOutputInfo& CInputOutputInfo::operator = (const CInputOutputInfo& rhs)
{
	//�����������ֵ,��ô��ֵ
	if (this != &rhs)
	{
		CopyValue(rhs);
	}
	return *this;
}

//��rhs��ֵ���Ƶ��ö���
void CInputOutputInfo::CopyValue(const CInputOutputInfo& rhs)
{
	//����
	this->m_dataType = rhs.m_dataType;

	//ͨ����ͬ����������ֵ
	switch (m_dataType)
	{
	case TYPE_INT:
		m_nIntValue = rhs.m_nIntValue;
		break;
	case TYPE_DOUBLE:
		m_dbValue = rhs.m_dbValue;
		break;
	case TYPE_STRING:
		m_strValue = rhs.m_strValue;
		break;
	case TYPE_POINT:
		break;
	case TYPE_POINT2F:
		break;
	case TYPE_IMAGE:
		break;
	case TYPE_INT_VECTOR:
		m_vecIntValue = rhs.m_vecIntValue;
		break;
	case TYPE_DOUBLE_VECTOR:
		m_vecDoubleValue = rhs.m_vecDoubleValue;
		break;
	case TYPE_STRING_VECTOR:
		m_vecStrValue = rhs.m_vecStrValue;
		break;
	case TYPE_POINT_VECTOR:
		break;
	case TYPE_POINT2F_VECTOR:
		break;
	case TYPE_IMAGE_VECTOR:
		break;
	default:
		break;
	}

}


//��ȡ�ö��������,����DataTyoe
DataType CInputOutputInfo::GetDataType()
{
	return m_dataType;
}
const DataType CInputOutputInfo::GetDataType() const
{
	return m_dataType;
}


//�ж����������Ƿ���Vector��������Ƿ���true������false
bool  CInputOutputInfo::IsVector()
{
	if ( (m_dataType & DATA_TYPE_VEC_BASE) == DATA_TYPE_VEC_BASE)
	{
		return true;
	}
	return false;
}

bool CInputOutputInfo::IsSameType(const CInputOutputInfo& rhs) const
{
	return ::IsSameType(m_dataType, rhs.m_dataType);
}

bool CInputOutputInfo::IsSameType(const CInputOutputInfo& rhs)
{
	return ::IsSameType(m_dataType, rhs.m_dataType);
}

//����һϵ�к���Ϊ���úͻ�ȡ����ֵ�ĺ�����������Ի�ȡ�����ò�ͬ���͵�ֵ��ô����false
bool CInputOutputInfo::GetIntValue(int& nValue)
{
	if (m_dataType == DataType::TYPE_INT)
	{
		nValue = m_nIntValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::GetDoubleValue(double& dbValue)
{
	if (m_dataType == DataType::TYPE_DOUBLE)
	{
		dbValue = m_dbValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::GetStringValue(string& strValue)
{
	if (m_dataType == DataType::TYPE_STRING)
	{
		strValue = m_strValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::GetVectIntValue(vector<int>& vecInt)
{
	if (m_dataType == DataType::TYPE_INT_VECTOR)
	{
		vecInt = m_vecIntValue;
	}
	return false;
}
bool CInputOutputInfo::GetVectDoubleValue(vector<double>& vecDouble)
{
	if (m_dataType == DataType::TYPE_DOUBLE_VECTOR)
	{
		vecDouble = m_vecDoubleValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::GetVecStrValue(vector<string>& strValue)
{
	if (m_dataType == DataType::TYPE_STRING_VECTOR)
	{
		strValue = m_vecStrValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetIntValue(const int& nValue)
{
	if (m_dataType == DataType::TYPE_INT)
	{
		m_dbValue = nValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetDoubleValue(const double& dbValue)
{
	if (m_dataType == DataType::TYPE_DOUBLE)
	{
		m_dbValue = dbValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetStringValue(const string& strValue)
{
	if (m_dataType == DataType::TYPE_STRING)
	{
		m_strValue = strValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetVectIntValue(const vector<int>& vecInt)
{
	if (m_dataType == DataType::TYPE_INT_VECTOR)
	{
		m_vecIntValue = vecInt;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetVectDoubleValue(const vector<double>& vecDouble)
{
	if (m_dataType == DataType::TYPE_DOUBLE_VECTOR)
	{
		m_vecDoubleValue = vecDouble;
	}
	return false;
}
bool CInputOutputInfo::SetVecStrValue(const vector<string>& strValue)
{
	if (m_dataType == DataType::TYPE_STRING_VECTOR)
	{
		m_vecStrValue = strValue;
		return true;
	}
	return false;
}


//����ȫ�ֺ���
bool IsVector(DataType dt) //�ж�dt�Ƿ���vector����
{
	return ((dt&DATA_TYPE_VEC_BASE) == DATA_TYPE_VEC_BASE);
}
bool IsSameType(DataType dt1, DataType dt2)// �ж�dt1�� dt2�Ƿ�Ϊͬһ������ ����vector<int> ��int��ͬһ������
{
	 return ( (dt1 ^ dt2) &0x00FF == 0);
}