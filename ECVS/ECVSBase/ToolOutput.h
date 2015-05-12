#pragma once
/*
* ToolInput.h
*
* ������ 2015-5-12  ���
*
* ��CInputOutputInfo�ķ�װ��ר����Ouput
*
*/
#include "InputOutputInfo.h"
class ECVS_EXPORT CToolOutput
{
public:
	CToolOutput(DataType dataType, string strInfo = "");
	~CToolOutput();
	CToolOutput(const CToolOutput &rhs);

	//����ֵ
	bool SetInputValue(const CInputOutputInfo&rhs);

	const CInputOutputInfo& GetValue();
	//���úͻ�ȡ˵������
	void SetStringInfo(string strInfo);
	string GetStringInfo();

private:
	CInputOutputInfo	m_Value;
	string				m_strInfo;   //���ڸ��ֶε�˵������, ���� ������ͼ�� ��"ƫ��X"

	CToolOutput& operator=(const CToolOutput&);
};
