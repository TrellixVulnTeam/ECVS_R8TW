#pragma once
/*
* AlgrithmBase.h
*
* ������ 2015-5-12  ���
*
* CAlgrithmBase ��Ϊ�����㷨���߹��ߵĻ��࣬���̴�����Ҳ����ֻ��Ҫʹ�ø���
*
*/
#include <string >
#include <map>
#include "ECVSBase.h"
#include "InputOutputInfo.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include "ECVSBase.h"
using std::string;
class CAlgrithmBase;
using std::map;


//ʵ�����Ʒ���ļ���������ͨ�������������ʵ����CAlgrithmBase ������������Ƕ���������꣬����MFC���Ƕ��
//�ұ����ֶ�ʵ��CreateAlgrithm ����
#define DEF_REFLECT_CLASS(class_name) public:\
	static void RegistClass();

#define IML_REFLECT_CLASS(class_name)  void class_name::RegistClass()\
{\
	CAlgrithmBase::m_mapCreatedFucn.insert(std::make_pair(#class_name, class_name::CreateAlgrithm));\
}



class ECVS_EXPORT CAlgrithmBase
{
public:
	typedef CAlgrithmBase* ( *CreateFunction)();
public:
	CAlgrithmBase();
	CAlgrithmBase(const CAlgrithmBase& rhs);
	CAlgrithmBase& operator= (const CAlgrithmBase &rhs);
	


	virtual ~CAlgrithmBase();

	virtual CAlgrithmBase* Clone() = 0; // �鹹�캯��
	virtual void Run() = 0;  //ִ���㷨
	virtual bool Set() = 0;  //�����㷨,���óɹ�����true�� ʧ�ܷ���false
	//��д������������ʱδʵ�֣��ȵ�һ���㷨�ɹ�ʵ�ּ����̲��Գɹ�����ʵ��
	virtual void Read() = 0;  
	virtual void Save() = 0;
	//�������Ƿ���Ҫ����ô洢�ռ�,Ĭ�϶�����Ҫ��,��ĳ����ʵ��Ϊ����ģʽʱ �򷵻�false������Camera��(�����������ʵ�ּ���ʵ��)
	virtual bool NeedClear()
	{
		return true;
	}
	virtual string GetErrorMsg(); // ��ȡ�㷨ִ�д����ַ���
	
	 string GetShowText(); //��ȡ��ʾ�ַ���
	 void SetShowText(string strText);//�޸���ʾ�ַ���
	 string GetAlgrithmName();  //��ȡ�㷨����
	 string GetAlgrithmClassName();  //��ȡ�㷨������
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
	string				m_strClassName; //�㷨���������ڲ�ʹ�ã�������̬��������



protected:
	virtual void Clone(const CAlgrithmBase& rhs); //���ڸ��ƹ��캯���͸�ֵ������ʹ��
	virtual void DeleteMemory(); // ɾ���ڴ�



	
public:

protected:
	static map<string, CreateFunction> m_mapCreatedFucn;
public:
	static CAlgrithmBase* CreateAlgrithm(string strClassName);
};

