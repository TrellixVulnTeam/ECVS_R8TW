#pragma once
#include "AlgrithmPlugin.h"
#include <vector>
#include <string>
using std::vector;
using std::string;
/*
* AlgrithmBase.h
*
* ������ 2015-6-9  ���
*
* CPluginManager �������еĲ��������װ�ز������ж�ز��
*
*/

// extern "C" __declspec(dllexport) HICON GetIcon(); //������ʾ��ͼ��;
// extern "C" __declspec(dllexport) const char* GetName();//��ȡ����
// extern "C" __declspec(dllexport) CAlgrithmBase* CreateAlgrithm();//�����㷨


// 
// extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam);

class ECVS_EXPORT CPluginManager
{
	
public:
	CPluginManager();
	~CPluginManager();
	vector<string> GetPluginsName();
	vector<string> GetPluginsInnerName();
	CAlgrithmBase* CreateAlgrithm(string strAlgrithm);

private:
	vector<CAlgrithmPlugin*> m_pPlugins;
	vector<string>		m_algrithmName;
	vector<string>		m_algrithmInnerName;
};

