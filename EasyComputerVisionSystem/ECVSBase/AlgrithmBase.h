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
	CAlgrithmBase(const CAlgrithmBase& rhs);
	CAlgrithmBase& operator= (const CAlgrithmBase &rhs);



	virtual ~CAlgrithmBase();
	virtual void Run() = 0;  //ִ���㷨
	virtual void Set() = 0;  //�����㷨
	//��д������������ʱδʵ�֣��ȵ�һ���㷨�ɹ�ʵ�ּ����̲��Գɹ�����ʵ��
	virtual void Read() = 0;  
	virtual void Save() = 0;
	
	virtual string GetErrorMsg(); // ��ȡ�㷨ִ�д����ַ���
	
	 string GetShowText(); //��ȡ��ʾ�ַ���
	 void SetShowText(string strText);//�޸���ʾ�ַ���
	 string GetAlgrithmName();  //��ȡ�㷨����

	 const vector<CToolOutput*> GetOutput() ; //��ȡ���㷨�������������
	 const vector<CToolInput*> GetInput() ; //��ȡ���㷨�������������

	 const CToolInput* GetInput(string strWitch) ; //��ȡĳָ���Ĳ���,��������ڷ���NULL
	 const CToolOutput* GetOutput(string strWitch); //��ȡĳָ���Ĳ���,��������ڷ���NULL

	//����ĳһ���������ֵ��������ô���������̿��ƣ�
	 bool SetInputValue(string strWitch, const CInputOutputInfo& value) ;
	 bool SetInputValue(int nIndedx, const CInputOutputInfo& value) ;
	//��ȡ�������������˵������CToolInput ��m_strInfo
	 vector<string> GetInputParamName() ;
	//��ȡ���������������˵������CToolOutput ��m_strInfo
	 vector<string> GetOutputParamName();
protected:
	//ֻ�����������������Լ��㷨��ʾ��������ַ�


	//Ϊ�˼򵥣�ֱ��ʹ����� ����ʹ������ָ��֮��ļ���
	//2015-5-13 ��彫vector<CToolInput> vector<CToolOutput>  �޸�Ϊvector<CToolInput*>  vector<CToolOutput*> Ŀ���ǽ�Լ���ݽ���ʱ��ʱ����ռ�
 	vector<CToolInput*>  m_vectInput;  //���е��������

	//ע�⣬���е�Output���ٺ���������������һ������ִ�д�����룬Ϊ���ͣ��ڶ���Ϊ�㷨ִ��ʱ�䡣
 	vector<CToolOutput*> m_vectOutput;  //���е��������,
	string				m_strShowText;  //Ĭ�Ϻ��㷨����һ��
	string				m_strAlgrithmName; //�㷨���֣����ⲻ�����޸� ���㷨�Լ��޸� 




protected:
	virtual void Clone(const CAlgrithmBase& rhs); //���ڸ��ƹ��캯���͸�ֵ������ʹ��
	virtual void DeleteMemory(); // ɾ���ڴ�
};

