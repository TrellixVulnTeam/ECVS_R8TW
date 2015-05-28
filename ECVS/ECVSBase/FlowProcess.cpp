#include "stdafx.h"
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
		for (int j = 0; j < m_vecRalationSheep[i]->m_relationShip.size(); ++j)
		{
			//���ȼ���Ƿ��������㷨���Ϻ�����㷨������ǵĻ�������������һ��
			//���кŲ��Ե����
			char strIndex[128];  //������ʽ�����ַ���
			if (m_vecRalationSheep[i]->m_relationShip[j]->nIndex >= m_pAlgrithms.size())
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "�����ߵ����볬���˼��ϳ���:";
				sprintf(strIndex, "%d", m_vecRalationSheep[i]->m_relationShip[j]->nIndex);
				strError += strIndex + string(" ����Ϊ :");
				sprintf(strIndex, "%d", m_pAlgrithms.size());
				strError += strIndex + '\r\n';
				++nErrorCount;


				continue;
			}
			else if (m_vecRalationSheep[i]->m_relationShip[j]->nIndex >= i)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "�����߲�������������㷨:";
				sprintf(strIndex, "%d", m_vecRalationSheep[i]->m_relationShip[j]->nIndex);
				strError += strIndex + string(" ") + m_pAlgrithms[m_vecRalationSheep[i]->m_relationShip[j]->nIndex]->GetShowText();

				++nErrorCount;
				continue;
			}
			const CToolInput* pInput = m_pAlgrithms[i]->GetInput(m_vecRalationSheep[i]->m_relationShip[j]->m_strWitchParam);
			const CToolOutput* pOutput = m_pAlgrithms[m_vecRalationSheep[i]->m_relationShip[j]->nIndex]->GetOutput(m_vecRalationSheep[i]->m_relationShip[j]->m_strDestParam);
			//���������ڵ����
			if (pInput == NULL)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "�����߲�����:" + m_vecRalationSheep[i]->m_relationShip[j]->m_strWitchParam + " ����\r\n";
				++nErrorCount;
				continue;
			}
			if (pOutput == NULL)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "����������������" + m_pAlgrithms[m_vecRalationSheep[i]->m_relationShip[j]->nIndex]->GetShowText() + " ����������:" + m_vecRalationSheep[i]->m_relationShip[j]->m_strDestParam + " ����\r\n";
				++nErrorCount;
				continue;
			}

			//�������ж��Ƿ���ͬһ�����;�OK


			if (!pInput->GetValue().IsSameType(pOutput->GetValue()))
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("��") + strIndex + "����������������" + m_pAlgrithms[m_vecRalationSheep[i]->m_relationShip[j]->nIndex]->GetShowText() + " ���Ͳ�ƥ��\r\n";
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
		//ÿ�������Ҫ���� ��������롱��"����ʱ��"
		const CToolOutput* pOutErrorCode = m_pAlgrithms[nIndex]->GetOutput("�������");


		int nErrorCode;
		bool b = pOutErrorCode->GetValue().GetIntValue(nErrorCode);
		if (nErrorCode != ECVS_ERROR_NO_ERROR)
		{
			// �����Ĵ�������
			if (m_vecRalationSheep[nIndex]->m_FalidProcess == RunFaildProcess::BREAK)
			{
				break;
			}
			else if (m_vecRalationSheep[nIndex]->m_FalidProcess == RunFaildProcess::IGNORED)
			{
				continue;  //���� ��������
			}
			else if (m_vecRalationSheep[nIndex]->m_FalidProcess == RunFaildProcess::STEPTO)
			{
				nIndex = m_vecRalationSheep[nIndex]->m_nStep2Index;  //������ת
				continue;
			}
			else  //Ӧ�ò����ߵ�������ȥ����������߽�ȥ��ִֹͣ��
			{
				break;
			}
		}
	
	}
}


//�������������nIndex���㷨���ϵĵڼ���,
//�ú��������߼��򵥣����Ǵ��뷱����������⣬�������ά��----2015-5-14
void CFlowProcess::SetInputParam(int nIndex)
{
	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //�㷨����໥��ϵ

	//�㷨��ÿ���ֶ���������������������˸ú������еļ�ⶼ������Բ������κμ�� ֻ�谴������ֵ����
	for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip.size(); ++i)
	{

		vector<CToolOutput*> pOutput = m_pOutput[m_vecRalationSheep[nIndex]->m_relationShip[i]->nIndex];
		CInputOutputInfo inOut(m_pAlgrithms[nIndex]->GetInput(m_vecRalationSheep[nIndex]->m_relationShip[i]->m_strWitchParam)->GetValue().GetDataType());
		DataType dtInput = inOut.GetDataType();  //���������
		//��ȡ���������Դ����
		const CToolOutput* pSrc = m_pAlgrithms[m_vecRalationSheep[nIndex]->m_relationShip[i]->nIndex]->GetOutput(m_vecRalationSheep[nIndex]->m_relationShip[i]->m_strDestParam);
		const CInputOutputInfo& valueSrc = pSrc->GetValue();
		//���������ֵ�����������ǹ��� CInputOutputInfo ��ֵ ������Ҫ������CInputOutputInfo��֧�ֵ����ͽ�������
		//����Ĵ���ȽϷ�����
		if (inOut.IsVector())  //�����������������
		{
			if (valueSrc.IsVector())  //�������ԴҲ������
			{
				//inOut  ��vector����
				switch (inOut.GetDataType())
				{
				case TYPE_INT_VECTOR:
				{
										vector<int> vecValue;
										vector<int> nValue;
										valueSrc.GetVectIntValue(nValue);
										for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //������ֵ
										{
											if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= nValue.size())
											{
												continue;
											}
											vecValue.push_back(nValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										}
										inOut.SetVectIntValue(vecValue);
										break;
				}

				case TYPE_DOUBLE_VECTOR:
				{

										   vector<double> vecValue;
										   vector<double> dbValue;
										   valueSrc.GetVectDoubleValue(dbValue);
										   for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //������ֵ
										   {
											   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= dbValue.size())
											   {
												   continue;
											   }
											   vecValue.push_back(dbValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										   }
										   inOut.SetVectDoubleValue(vecValue);
										   break;
				}


				case TYPE_STRING_VECTOR:

				{
										   vector<string> vecValue;
										   vector<string> strValue;
										   valueSrc.GetVecStrValue(strValue);
										   for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //������ֵ
										   {
											   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= strValue.size())
											   {
												   continue;
											   }
											   vecValue.push_back(strValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										   }
										   inOut.SetVecStrValue(strValue);
										   break;
				}

					break;
				case TYPE_POINT_VECTOR:
				{
										  vector<Point> vecValue;
										  vector<Point> ptValue;
										  valueSrc.GetVecPointValue(ptValue);
										  for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //������ֵ
										  {
											  if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= ptValue.size())
											  {
												  continue;
											  }
											  vecValue.push_back(ptValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										  }
										  inOut.SetVecPointValue(vecValue);
										  break;
				}

					
				case TYPE_POINT2F_VECTOR:
				{
											vector<Point2f> vecValue;
											vector<Point2f> ptValue;
											valueSrc.GetVecPointFValue(ptValue);
											for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //������ֵ
											{
												if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= ptValue.size())
												{
													continue;
												}
												vecValue.push_back(ptValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
											}
											inOut.SetVecPointFValue(vecValue);
											break;
				}
				
				case TYPE_IMAGE_VECTOR:
				{
										  vector<Mat> vecValue;
										  vector<Mat> ptValue;
										  valueSrc.GetVecImageValue(ptValue);
										  for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //������ֵ
										  {
											  if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= ptValue.size())
											  {
												  continue;
											  }
											  vecValue.push_back(ptValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										  }
										  inOut.SetVecImageValue(vecValue);
										  break;
				}
				
				default:
					break;
				}
			}
			else  // �������Դ�������У���ôֱ�ӽ�����������ӽ�����
			{

				//inOut  ����vector����
				switch (inOut.GetDataType())
				{
				case TYPE_INT_VECTOR:
				{
										vector<int> vecValue;
										int nValue;
										valueSrc.GetIntValue(nValue);
										vecValue.push_back(nValue);
										inOut.SetVectIntValue(vecValue);
										break;
				}

				case  TYPE_DOUBLE_VECTOR:
				{

											vector<double> vecValue;
											double dbValue;
											valueSrc.GetDoubleValue(dbValue);
											vecValue.push_back(dbValue);
											inOut.SetVectDoubleValue(vecValue);
											break;
				}


				case TYPE_STRING_VECTOR:

				{
										   vector<string> vecValue;
										   string strValue;
										   valueSrc.GetStringValue(strValue);
										   vecValue.push_back(strValue);
										   inOut.SetVecStrValue(vecValue);
				}

					break;
				case TYPE_POINT_VECTOR:
				{
										  vector<Point> vecValue;
										  Point ptValue;
										  valueSrc.GetPointValue(ptValue);
										  vecValue.push_back(ptValue);
										  inOut.SetVecPointValue(vecValue);
										
				}
					break;
				case TYPE_POINT2F_VECTOR:
				{
											vector<Point2f> vecValue;
											Point2f ptValue;
											valueSrc.GetPointFValue(ptValue);
											vecValue.push_back(ptValue);
											inOut.SetVecPointFValue(vecValue);

				}
					break;
				case TYPE_IMAGE_VECTOR:
				{
										  vector<Mat> vecValue;
										  Mat img;
										  valueSrc.GetImageValue(img);
										  vecValue.push_back(img);
										  inOut.SetVecImageValue(vecValue);

				}
					break;
				default:
					break;
				}






			}
		}
		else  //�����ǵ�������
		{
			if (valueSrc.IsVector())  //���Դ������vector
			{
				switch (inOut.GetDataType())
				{
				case TYPE_INT:
				{

								 vector<int> vecValue;
								 valueSrc.GetVectIntValue(vecValue);
								 if (vecValue.size() < 0)  //��������Ϊ�գ����������㷨����
								 {
									 break;
								 }
								 int nValue;
								 if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
								 {
									 nValue = vecValue[0];
								 }
								 else
								 {
									 ////�����ѡ��ֵ������Χ ֱ�ӷ��� ��ȥ���κδ���
									 if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
									 {
										 break;
									 }
									 nValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
								 }
								 inOut.SetIntValue(nValue);
								 break;
				}

				case TYPE_DOUBLE:
				{

									vector<double> vecValue;
									double dbValue;
									valueSrc.GetVectDoubleValue(vecValue);

									if (vecValue.size() < 0)  //��������Ϊ�գ����������㷨����
									{
										break;
									}
									if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
									{
										dbValue = vecValue[0];
									}
									else
									{
										////�����ѡ��ֵ������Χ ֱ�ӷ��� ��ȥ���κδ���
										if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
										{
											break;
										}
										dbValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
									}

									inOut.SetDoubleValue(dbValue);
									break;
				}


				case TYPE_STRING:

				{
									vector<string> vecValue;
									string strValue;
									valueSrc.GetVecStrValue(vecValue);

									if (vecValue.size() < 0)  //��������Ϊ�գ����������㷨����
									{
										break;
									}
									if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
									{
										strValue = vecValue[0];
									}
									else
									{
										////�����ѡ��ֵ������Χ ֱ�ӷ��� ��ȥ���κδ���
										if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
										{
											break;
										}
										strValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
									}

									inOut.SetStringValue(strValue);
									break;
				}

					break;
				case TYPE_POINT:

				{
								   vector<Point> vecValue;
								   Point strValue;
								   valueSrc.GetVecPointValue(vecValue);

								   if (vecValue.size() < 0)  //��������Ϊ�գ����������㷨����
								   {
									   break;
								   }
								   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
								   {
									   strValue = vecValue[0];
								   }
								   else
								   {
									   ////�����ѡ��ֵ������Χ ֱ�ӷ��� ��ȥ���κδ���
									   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
									   {
										   break;
									   }
									   strValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
								   }

								   inOut.SetPointValue(strValue);
								   break;
				}
					break;
				case TYPE_POINT2F:

				{
									 vector<Point2f> vecValue;
									 Point2f strValue;
									 valueSrc.GetVecPointFValue(vecValue);

									 if (vecValue.size() < 0)  //��������Ϊ�գ����������㷨����
									 {
										 break;
									 }
									 if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
									 {
										 strValue = vecValue[0];
									 }
									 else
									 {
										 ////�����ѡ��ֵ������Χ ֱ�ӷ��� ��ȥ���κδ���
										 if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
										 {
											 break;
										 }
										 strValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
									 }

									 inOut.SetPointFValue(strValue);
									 break;
				}
					break;
				case TYPE_IMAGE:

				{
								   vector<Mat> vecValue;
								   Mat strValue;
								   valueSrc.GetVecImageValue(vecValue);

								   if (vecValue.size() < 0)  //��������Ϊ�գ����������㷨����
								   {
									   break;
								   }
								   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
								   {
									   strValue = vecValue[0];
								   }
								   else
								   {
									   ////�����ѡ��ֵ������Χ ֱ�ӷ��� ��ȥ���κδ���
									   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
									   {
										   break;
									   }
									   strValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
								   }

								   inOut.SetImageValue(strValue);
								   break;
				}
					break;
				default:
					break;
				}
			}
			else //Դ����Ҳ�ǵ�������
			{
				//inOut  ����vector����
				switch (inOut.GetDataType())
				{
				case TYPE_INT:
				{
								 // vector<int> vecValue;
								 int nValue;
								 valueSrc.GetIntValue(nValue);
								 //vecValue.push_back(nValue);
								 inOut.SetIntValue(nValue);
								 break;
				}

				case  TYPE_DOUBLE:
				{


									 double dbValue;
									 valueSrc.GetDoubleValue(dbValue);

									 inOut.SetDoubleValue(dbValue);
									 break;
				}


				case TYPE_STRING:

				{

									string strValue;
									valueSrc.GetStringValue(strValue);
									inOut.SetStringValue(strValue);
				}

					break;
				case TYPE_POINT:
				{

								   Point ptPos;
								   valueSrc.GetPointValue(ptPos);
								   inOut.SetPointValue(ptPos);
				}
					break;
				case TYPE_POINT2F:
				{

									 Point2f ptPos;
									 valueSrc.GetPointFValue(ptPos);
									 inOut.SetPointFValue(ptPos);
				}
					break;
				case TYPE_IMAGE:
				{

								   Mat img;
								   valueSrc.GetImageValue(img);
								   inOut.SetImageValue(img);
				}
					break;
				default:
					break;
				}
			}


			m_pAlgrithms[nIndex]->SetInputValue(m_vecRalationSheep[nIndex]->m_relationShip[i]->m_strWitchParam, inOut);
		}


	}
}