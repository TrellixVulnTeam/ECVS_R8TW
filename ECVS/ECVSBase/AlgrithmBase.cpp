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
}


CAlgrithmBase::~CAlgrithmBase()
{
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


const vector<CToolOutput*> CAlgrithmBase::GetOutput() //��ȡ���㷨�������������
{
	return m_vectOutput;
}
const vector<CToolInput*> CAlgrithmBase::GetInput() //��ȡ���㷨�������������
{
	return m_vectInput;
}