
/*
* ToolInput.h
*
* ������ 2015-5-12  ���
*
* ʵ��CToolInput
*
*/
#define  ECVS_BUILD_DLL
#include "ToolInput.h"

CToolInput::CToolInput(DataType dataType, string strInfo /*= ""*/) :m_Value(dataType), m_strInfo(strInfo)
{
}

CToolInput::CToolInput(const CToolInput &rhs) : m_Value(rhs.m_Value), m_strInfo(rhs.m_strInfo)
{

}


CToolInput& CToolInput::operator = (const CToolInput& rhs)
{
	if (this != &rhs)
	{
		m_strInfo = rhs.m_strInfo; 
		m_Value = rhs.m_Value;
	}
	return *this;
}

CToolInput::~CToolInput()
{
}


//����ֵ
bool CToolInput::SetInputValue(const CInputOutputInfo&rhs)
{

	//����һ��ȷ���þͲ��ܸ���
	if (rhs.GetDataType() == m_Value.GetDataType())
	{
		this->m_Value = rhs;
		return true;
	}
	return false;

}

const CInputOutputInfo& CToolInput::GetValue()
{
	return m_Value;
}
//���úͻ�ȡ˵������
void CToolInput::SetStringInfo(string strInfo)
{
	m_strInfo = strInfo;
}
string CToolInput::GetStringInfo()
{
	return m_strInfo;
}
