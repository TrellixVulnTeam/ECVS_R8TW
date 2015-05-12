/*
* ToolInput.h
*
* ������ 2015-5-12  ���
*
* ʵ��CToolOutput
*
*/
#define  ECVS_BUILD_DLL
#include "ToolOutput.h"


CToolOutput::CToolOutput(DataType dataType, string strInfo = "") :m_Value(dataType), m_strInfo(strInfo)
{
}

CToolOutput::CToolOutput(const CToolOutput &rhs) : m_Value(rhs.m_Value), m_strInfo(rhs.m_strInfo)
{

}

CToolOutput::~CToolOutput()
{
}



//����ֵ
bool CToolOutput::SetInputValue(const CInputOutputInfo&rhs)
{

	//����һ��ȷ���þͲ��ܸ���
	if (rhs.GetDataType() == m_Value.GetDataType())
	{
		this->m_Value = rhs;
		return true;
	}
	return false;

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
