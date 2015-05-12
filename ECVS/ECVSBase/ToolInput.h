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
public:
	CToolInput(DataType dataType, string strInfo = "");
	//���ƹ��캯��
	CToolInput(const CToolInput &rhs);
	~CToolInput();
	//����ֵ
	bool SetInputValue(const CInputOutputInfo&rhs);

	const CInputOutputInfo& GetValue();
	//���úͻ�ȡ˵������
	void SetStringInfo(string strInfo);
	string GetStringInfo();
private:
	CInputOutputInfo	m_Value;
	string				m_strInfo;   //���ڸ��ֶε�˵������, ���� ������ͼ�� ��"ƫ��X"

	CToolInput& operator=(const CToolInput&);

};
