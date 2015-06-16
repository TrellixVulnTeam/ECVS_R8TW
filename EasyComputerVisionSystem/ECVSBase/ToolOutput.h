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
	friend class CToolInput; 
public:
	CToolOutput(DataType dataType, string strInfo = "");
	~CToolOutput();
	CToolOutput(const CToolOutput &rhs);
	CToolOutput& operator=(const CToolOutput&);
	//����ֵ
	bool SetValue(const CInputOutputInfo&rhs);
	bool IsSameType(const CToolOutput &rhs);
	bool IsSameType(const CToolInput& rhs);
	const CInputOutputInfo& GetValue();
	const CInputOutputInfo& GetValue() const;
	//���úͻ�ȡ˵������
	void SetStringInfo(string strInfo);
	string GetStringInfo();

private:
	CInputOutputInfo	m_Value;
	string				m_strInfo;   //���ڸ��ֶε�˵������, ���� ������ͼ�� ��"ƫ��X"

	
};

