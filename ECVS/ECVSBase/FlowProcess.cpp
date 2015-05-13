#include "ECVSBase.h"
#include "InputOutputInfo.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include <vector>
#include "AlgrithmBase.h"
#include "FlowProcess.h"
using std::vector;

CFlowProcess::CFlowProcess()
{
}


CFlowProcess::~CFlowProcess()
{
}

//��������Ƿ��д�
bool CFlowProcess::ComplierFlow(string& strError)
{

	int nErrorCount = 0; //����ĸ���
	//ÿ�����μ���Ƿ�Ϸ�
	for (int i = 0; i < m_pAlgrithms.size(); ++i)
	{
		//const vector<CToolInput*> inputParam = m_pAlgrithms[i]->GetInput();
		//ÿ���㷨��ÿ���������
		for (int j = 0; j < m_vecRalationSheep[i].size(); ++j)
		{
			//���ȼ���Ƿ��������㷨���Ϻ�����㷨������ǵĻ�������������һ��
			//���кŲ��Ե����
			char strIndex[128];  //������ʽ�����ַ���
			if (m_vecRalationSheep[i][j]->nIndex >= m_pAlgrithms.size())
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "�����ߵ����볬���˼��ϳ���:";
				sprintf(strIndex, "%d", m_vecRalationSheep[i][j]->nIndex);
				strError += strIndex + string(" ����Ϊ :");
				sprintf(strIndex, "%d", m_pAlgrithms.size());
				strError += strIndex + '\r\n';
				++nErrorCount;

				
				continue;
			}
			else if (m_vecRalationSheep[i][j]->nIndex >= i)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "�����߲�������������㷨:";
				sprintf(strIndex, "%d", m_vecRalationSheep[i][j]->nIndex);
				strError += strIndex + string(" ") + m_pAlgrithms[m_vecRalationSheep[i][j]->nIndex]->GetShowText();
			
				++nErrorCount;
				continue;
			}
			const CToolInput* pInput  = m_pAlgrithms[i]->GetInput(m_vecRalationSheep[i][j]->m_strWitchParam);
			const CToolOutput* pOutput = m_pAlgrithms[m_vecRalationSheep[i][j]->nIndex]->GetOutput(m_vecRalationSheep[i][j]->m_strDestParam);
			//���������ڵ����
			if (pInput == NULL)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "�����߲�����:" + m_vecRalationSheep[i][j]->m_strWitchParam + " ����\r\n";
				++nErrorCount;
				continue;
			}
			if (pOutput == NULL)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "����������������" + m_pAlgrithms[m_vecRalationSheep[i][j]->nIndex]->GetShowText() + " ����������:" + m_vecRalationSheep[i][j]->m_strDestParam + " ����\r\n";
				++nErrorCount;
				continue;
			}
			
			//�������ж��Ƿ���ͬһ�����;�OK

		
			if (!pInput->GetValue().IsSameType(pOutput->GetValue()))
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "����������������" + m_pAlgrithms[m_vecRalationSheep[i][j]->nIndex]->GetShowText() + " ���Ͳ�ƥ��\r\n";
				++nErrorCount;
				continue;
			}

		}

	}

	return (nErrorCount <= 0);
}

//�����㷨
bool  CFlowProcess::Run()
{
	string strError;
	//������붼��ͨ����ôֱ�ӷ��ش���
	if (!ComplierFlow(strError))
	{
		return false;
	}
	int nIndex = 0;
	while (nIndex >= 0 && nIndex < m_pAlgrithms.size())
	{
		 SetInputParam(nIndex);
		 m_pAlgrithms[nIndex]->Run();
		 m_pOutput[nIndex] = m_pAlgrithms[nIndex]->GetOutput();
	}
}

void CFlowProcess::SetInputParam(int nIndex)
{
	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //�㷨����໥��ϵ

	for (int i = 0; i < m_vecRalationSheep[nIndex].size(); ++i)
	{
		
		vector<CToolOutput*> pOutput = m_pOutput[m_vecRalationSheep[nIndex][i]->nIndex];
		CInputOutputInfo inOut;
		m_pAlgrithms[nIndex]->SetInputValue(m_vecRalationSheep[nIndex][i].m_strWitchParam, inOut);
	}


}