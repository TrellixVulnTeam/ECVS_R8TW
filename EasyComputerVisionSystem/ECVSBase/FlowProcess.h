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
	friend class CInputSet;
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
		~AlgrithmRelateship()
		{
			DeleteMemory();
		}
		AlgrithmRelateship(const AlgrithmRelateship& rhs)
		{
			Copy(rhs);
		}
		const AlgrithmRelateship&operator = (const AlgrithmRelateship& rhs)
		{
			if (this != &rhs)
			{
				Copy(rhs);
			}
			return *this;
		}
	private:
		void DeleteMemory()
		{
			for (int i = m_relationShip.size() - 1; i >= 0; --i)
			{
				delete m_relationShip[i];
				m_relationShip[i] = NULL;
				m_relationShip.pop_back();
			}
		}
		void Copy(const AlgrithmRelateship& rhs)
		{
			DeleteMemory();
			m_FalidProcess = rhs.m_FalidProcess;
			m_nStep2Index = rhs.m_nStep2Index;
		}

	};
	

public:
	CFlowProcess();
	CFlowProcess(const CFlowProcess& rhs);
	const CFlowProcess& operator=(const CFlowProcess& rhs);
	~CFlowProcess();
	bool AddAlgrithm(CAlgrithmBase* pAlgrithm); //������������һ���㷨
	bool SetAlgrithm(int nIndex); //��ĳһ���㷨�������ã�
	bool SetAlgrithmName(int nIndex, std::string strName); //�����㷨��ʾ����
	bool InsertAlgirthm(CAlgrithmBase* pAlgrithm, int nIndex); //����һ���㷨��nIndex�������������Χ ,����false��ʲô������
	bool ExchangeAlgrithmIndex(int nIndex1, int nIndex2); //��nIndex1��nIndex2���㷨�໥����,�±겻�ڷ�Χ����false
	bool ChangeAlgrithmIndex(int nIndex, int nChangedIndex); //��nIndex���㷨�ŵ�nChangedIndex�� ֮����㷨�������ȥ,�±�Ƿ����ش���
	bool DelAlgrithm(int nIndex); //ɾ��nIndex����Algorithm,����±�Ƿ��򷵻�false

	bool ComplierFlow(string& strError);  //�����㷨�����Ƿ�Ϸ������ݽ����ĺϷ���,strError�������еĴ���
	bool  Run();  //��ʼִ������
	int  GetAlgrithmNumber()
	{
		return m_pAlgrithms.size();
	}
	bool SetInput(int nIndex);
	
private: 
	vector<CAlgrithmBase*> m_pAlgrithms;   // �����е��㷨����
	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //�㷨����໥��ϵ
	vector<AlgrithmRelateship*> m_vecRalationSheep;  //�㷨����໥��ϵ
	vector< vector<CToolOutput*> >  m_pOutput; // ִ�й�����ÿ���㷨�����ֵ



private:
	//���õ�nIndex�㷨���������
	void SetInputParam(int nIndex);

	//ɾ�������ڴ�
	void DeleteMemory();
	void Copy(const CFlowProcess& rhs);

};

