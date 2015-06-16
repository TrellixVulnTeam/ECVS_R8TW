/*
* ToolInput.h
*
* ������ 2015-5-12  ���
*
* ʵ��CToolOutput
*
*/
#include "stdafx.h"
#include "ToolOutput.h"

#include "ToolInput.h"
CToolOutput::CToolOutput(DataType dataType, string strInfo/* = ""*/) :m_Value(dataType), m_strInfo(strInfo)
{
}

CToolOutput::CToolOutput(const CToolOutput &rhs) : m_Value(rhs.m_Value), m_strInfo(rhs.m_strInfo)
{

}

CToolOutput::~CToolOutput()
{
}



//����ֵ
bool CToolOutput::SetValue(const CInputOutputInfo&rhs)
{

	//����һ��ȷ���þͲ��ܸ���
	if (rhs.GetDataType() == m_Value.GetDataType())
	{
		this->m_Value = rhs;
		return true;
	}
	return false;

}


const CInputOutputInfo& CToolOutput::GetValue() const
{
	return m_Value;
}

const CInputOutputInfo& CToolOutput::GetValue()
{
	return m_Value;
}
//���úͻ�ȡ˵������
void CToolOutput::SetStringInfo(string strInfo)
{
	m_strInfo = strInfo;
}
string CToolOutput::GetStringInfo()
{
	return m_strInfo;
}


bool CToolOutput::IsSameType(const CToolOutput &rhs)
{
	return m_Value.IsSameType(rhs.m_Value);
}
bool CToolOutput::IsSameType(const CToolInput& rhs)
{
	return m_Value.IsSameType(rhs.m_Value);
}

CToolOutput& CToolOutput::operator = (const CToolOutput& rhs)
{
	if (this != &rhs)
	{
		m_strInfo = rhs.m_strInfo;
		m_Value = rhs.m_Value;
	}
	return *this;
}
