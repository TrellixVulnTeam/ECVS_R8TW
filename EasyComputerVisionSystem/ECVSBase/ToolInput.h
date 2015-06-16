#pragma once
/*
* ToolInput.h
*
* ������ 2015-5-12  ���
*
* ��CInputOutputInfo�ķ�װ��ר����Input
*
*/

#include "InputOutputInfo.h"
class ECVS_EXPORT CToolInput
{
	friend class CToolOutput;
public:
	CToolInput(DataType dataType, string strInfo = "");
	//���ƹ��캯��
	CToolInput(const CToolInput &rhs);
	//��ֵ������
	CToolInput& operator=(const CToolInput&);
	~CToolInput();
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

