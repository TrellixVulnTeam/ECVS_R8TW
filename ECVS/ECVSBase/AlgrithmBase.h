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
	
	 string GetShowText(); //��ȡ��ʾ�ַ���
	 void SetShowText(string strText);//�޸���ʾ�ַ���
	 string GetAlgrithmName();  //��ȡ�㷨����

	 const vector<CToolOutput*> GetOutput() ; //��ȡ���㷨�������������
	 const vector<CToolInput*> GetInput() ; //��ȡ���㷨�������������

	virtual const CToolInput* GetInput(string strWitch) = 0; //��ȡĳָ���Ĳ���,��������ڷ���NULL
	virtual const CToolOutput* GetOutput(string strWitch) = 0; //��ȡĳָ���Ĳ���,��������ڷ���NULL

	//����ĳһ���������ֵ��������ô���������̿��ƣ�
	virtual bool SetInputValue(string strWitch, const CInputOutputInfo& value) = 0;
	virtual bool SetInputValue(int nIndedx, const CInputOutputInfo& value) = 0;
	//��ȡ�������������˵������CToolInput ��m_strInfo
	virtual vector<string> GetInputParamName() = 0;
	//��ȡ���������������˵������CToolOutput ��m_strInfo
	virtual vector<string> GetOutputParamName() = 0;
protected:
	//ֻ�����������������Լ��㷨��ʾ��������ַ�

	//2015-5-13 ��彫vector<CToolInput> vector<CToolOutput>  �޸�Ϊvector<CToolInput*>  vector<CToolOutput*> Ŀ���ǽ�Լ���ݽ���ʱ��ʱ����ռ�
 	vector<CToolInput*>  m_vectInput;  //���е��������

	//ע�⣬���е�Output���ٺ���������������һ������ִ�д�����룬Ϊ���ͣ��ڶ���Ϊ�㷨ִ��ʱ�䡣
 	vector<CToolOutput*> m_vectOutput;  //���е��������
	string				m_strShowText;  //Ĭ�Ϻ��㷨����һ��
	string				m_strAlgrithmName; //�㷨���֣����ⲻ�����޸� ���㷨�Լ��޸� 
};

