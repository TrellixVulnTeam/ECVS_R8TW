#pragma once
/*
* AlgrithmBase.h
*
* ������ 2015-5-12  ���
*
* CAlgrithmBase ��Ϊ�����㷨���߹��ߵĻ��࣬���̴�����Ҳ����ֻ��Ҫʹ�ø���
*
*/

class ECVS_EXPORT CAlgrithmBase
{
public:
	CAlgrithmBase();
	virtual ~CAlgrithmBase();
	virtual void Run() = 0;  //ִ���㷨��
	virtual string GetErrorMsg() = 0; // ��ȡ�㷨ִ�д����ַ���
	
	virtual const vector<CToolOutput>& GetOutput() = 0; //��ȡ���㷨�������������
	//����ĳһ���������ֵ��������ô���������̿��ƣ�
	virtual bool SetInputValue(string strWitch, const CInputOutputInfo& value) = 0;
	virtual bool SetInputValue(int nIndedx, const CInputOutputInfo& value) = 0;
	//��ȡ�������������˵������CToolInput ��m_strInfo
	virtual vector<string> GetInputParamName() = 0;
	//��ȡ���������������˵������CToolOutput ��m_strInfo
	virtual vector<string> GetOutputParamName() = 0;
protected:
	//ֻ���������������Ƕ��⿪�ŵ�
 	vector<CToolInput>  m_vectInput;  //���е��������
 	vector<CToolOutput> m_vectOutput;  //���е��������
};

