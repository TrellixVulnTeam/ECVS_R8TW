#define  ECVS_BUILD_DLL

#include "ECVSBase.h"
#include "InputOutputInfo.h"
#include "ToolInput.h"
#include "ToolOutput.h"

#include <vector>
using std::vector;
#include "AlgrithmBase.h"


CAlgrithmBase::CAlgrithmBase()
{
	//������������� һ���Ǵ������ һ���Ǵ���ʱ��

	CToolOutput *pErrorCode = new CToolOutput(DataType::TYPE_INT); //�������
	CInputOutputInfo err(DataType::TYPE_INT);
	err.SetIntValue(ECVS_ERR_HAS_NO_EXECUTE);  //��ʼ��Ϊδִ�С�
	pErrorCode->SetValue(err);
	pErrorCode->SetStringInfo("�������");
	m_vectOutput.push_back(pErrorCode);
	//��ʼ��ʱ��Ϊ0
	CInputOutputInfo ti(DataType::TYPE_DOUBLE);
	ti.SetDoubleValue(0);

	CToolOutput* pProcessTime = new CToolOutput(DataType::TYPE_DOUBLE);
	pProcessTime->SetStringInfo("����ʱ��");
	pProcessTime->SetValue(ti);
	m_vectOutput.push_back(pProcessTime);

}


CAlgrithmBase::~CAlgrithmBase()
{
	DeleteMemory();
}

string CAlgrithmBase::GetShowText() //��ȡ��ʾ�ַ���
{
	return m_strShowText;
}
void CAlgrithmBase::SetShowText(string strText)//�޸���ʾ�ַ���
{
	m_strShowText = strText;
}
string CAlgrithmBase::GetAlgrithmName()  //��ȡ�㷨����
{
	return m_strAlgrithmName;
}
const CToolInput* CAlgrithmBase::GetInput(string strWitch)
{
	for (int i = 0; i < m_vectInput.size(); ++i)
	{
		if (m_vectInput[i]->GetStringInfo() == strWitch)
		{
			return m_vectInput[i];
		}
	}
	return NULL;
	
}
const CToolOutput* CAlgrithmBase::GetOutput(string strWitch)
{
	for (int i = 0; i < m_vectOutput.size(); ++i)
	{
		if (m_vectOutput[i]->GetStringInfo() == strWitch)
		{
			return m_vectOutput[i];
		}
	}
	return NULL;
}

const vector<CToolOutput*> CAlgrithmBase::GetOutput() //��ȡ���㷨�������������
{
	return m_vectOutput;
}
const vector<CToolInput*> CAlgrithmBase::GetInput() //��ȡ���㷨�������������
{
	return m_vectInput;
}

bool CAlgrithmBase::SetInputValue(string strWitch, const CInputOutputInfo& value)
{
	for (int i = 0; i < m_vectInput.size(); ++i)
	{
		if (m_vectInput[i]->GetStringInfo() == strWitch)
		{
			return m_vectInput[i]->SetValue(value);
			
		}
	}
	return false;
}
bool CAlgrithmBase::SetInputValue(int nIndedx, const CInputOutputInfo& value)
{
	if (nIndedx >= m_vectInput.size())
	{
		return false;
	}
	return m_vectInput[nIndedx]->SetValue(value);
}
CAlgrithmBase::CAlgrithmBase(const CAlgrithmBase& rhs)
{
	Clone(rhs);
}
CAlgrithmBase& CAlgrithmBase::operator= (const CAlgrithmBase &rhs)
{

	if (this != &rhs)
	{
		Clone(rhs);
	}
	

	return *this;
}
//���ڸ��ƹ��캯���͸�ֵ������ʹ��,ʵ�ֿ������г�Ա����
void CAlgrithmBase::Clone(const CAlgrithmBase& rhs)
{
	DeleteMemory();
	for (int i = 0; i < rhs.m_vectInput.size(); ++i)
	{
		CToolInput *pInput = new CToolInput(*rhs.m_vectInput[i]);
		m_vectInput.push_back(pInput);
	}
	for (int i = 0; i < rhs.m_vectOutput.size(); ++i)
	{
		CToolOutput* pOutput = new CToolOutput(*rhs.m_vectOutput[i]);
		m_vectOutput.push_back(pOutput);
	}
	m_strAlgrithmName = rhs.m_strAlgrithmName;
	m_strShowText = rhs.m_strShowText;
}
void CAlgrithmBase::DeleteMemory() // ɾ���ڴ�
{
	for (int i = 0; i < m_vectInput.size(); ++i)
	{
		delete m_vectInput[i];
		m_vectInput[i] = NULL;
	}
	m_vectInput.clear();

	for (int i = 0; i < m_vectOutput.size(); ++i)
	{
		delete m_vectOutput[i];
		m_vectOutput[i] = NULL;
	}
	m_vectOutput.clear();
	
}


//��ȡ�������������˵������CToolInput ��m_strInfo
vector<string> CAlgrithmBase::GetInputParamName()
{
	vector<string> inputVec;
	for (int i = 0; i < m_vectInput.size(); ++i)
	{
		inputVec.push_back(m_vectInput[i]->GetStringInfo());
	}
	
	return inputVec;
}
//��ȡ���������������˵������CToolOutput ��m_strInfo
vector<string> CAlgrithmBase::GetOutputParamName()
{
	vector<string> outVec;
	for (int i = 0; i < m_vectOutput.size(); ++i)
	{
		outVec.push_back(m_vectOutput[i]->GetStringInfo());
	}
	return outVec;
	
}

//Ĭ�ϻ�ȡ�������
string CAlgrithmBase::GetErrorMsg()
{
	const CInputOutputInfo & info = m_vectOutput[0]->GetValue();
	int nErr = 0;
	info.GetIntValue(nErr);
	return ::GetErrorMsg(nErr);
}