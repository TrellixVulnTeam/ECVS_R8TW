#pragma once
//////////////////////////////////////////////////////////////////////////
//
//	FlowProcess.h 2015-5-13 ��� 
//   CFlowProcess �����̴����࣬���е��߼����̶��ڸ����н���
//   ����ά�������㷨֮������ݽ���,��һ�汾��ʱֻ֧�ֵ������̣�
//   
//////////////////////////////////////////////////////////////////////////
class ECVS_EXPORT CFlowProcess
{ 
private:
	//�㷨���д����������
	enum RunFaildProcess
	{
		BREAK,   //ֱ��ֹͣ����
		IGNORED, //����
		STEPTO,  //��ת
	};
	//�㷨���������֮��Ĺ�ϵ
	struct InputOutputRelateship  
	{
		string m_strWitchParam; //Ϊ�㷨����һ�������Ĺ���ֵ
		int nIndex;				//Ϊ��������һ���㷨
		string m_strDestParam;  //ȡĿ���㷨����һ���ֶ�
		vector<int>	m_vecIndex;  //ȡĿ���㷨����Щֵ�����Ŀ��Ϊ��vector ��ֵΪ�գ���������а��ո�vectorȡֵ
	};

	struct  AlgrithmRelateship
	{
		vector<InputOutputRelateship*> m_relationShip;
		RunFaildProcess m_FalidProcess; //���д��������� Ĭ��ֹͣ����
		int m_nStep2Index;				//�������ת����ô��ת����һ��
		AlgrithmRelateship()
		{
			m_FalidProcess = RunFaildProcess::BREAK;
			m_nStep2Index = 0;
		}

	};
	

public:
	CFlowProcess();
	~CFlowProcess();
	bool AddAlgrithm(CAlgrithmBase* pAlgrithm); //������������һ���㷨
	bool InsertAlgirthm(CAlgrithmBase* pAlgrithm, int nIndex); //����һ���㷨��nIndex�������������Χ ,����false��ʲô������
	bool ExchangeAlgrithmIndex(int nIndex1, int nIndex2); //��nIndex1��nIndex2���㷨�໥����,�±겻�ڷ�Χ����false
	bool ChangeAlgrithmIndex(int nIndex, int nChangedIndex); //��nIndex���㷨�ŵ�nChangedIndex�� ֮����㷨�������ȥ,�±�Ƿ����ش���
	bool DelAlgrithm(int nIndex); //ɾ��nIndex����Algorithm,����±�Ƿ��򷵻�false

	bool ComplierFlow(string& strError);  //�����㷨�����Ƿ�Ϸ������ݽ����ĺϷ���,strError�������еĴ���
	bool  Run();  //��ʼִ������


private: 
	vector<CAlgrithmBase*> m_pAlgrithms;   // �����е��㷨����
	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //�㷨����໥��ϵ
	vector<AlgrithmRelateship*> m_vecRalationSheep;  //�㷨����໥��ϵ
	vector< vector<CToolOutput*> >  m_pOutput; // ִ�й�����ÿ���㷨�����ֵ



private:
	//���õ�nIndex�㷨���������
	void SetInputParam(int nIndex);



};

