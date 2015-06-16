#pragma once

/*
* AlgrithmBase.h
*
* ������ 2015-6-9  ���
*
* CAlgrithmPlugin ����������
*
*/
#include <string>
using std::string;
#include <windows.h>
class CAlgrithmBase;
typedef void(__stdcall * PFUNCRUN)();
typedef string(__stdcall * PFUNCGETNAME)();
typedef HICON(__stdcall * PFUNCGETICON)();
typedef CAlgrithmBase*(__stdcall * PFUNCCREATEALGRITHM)();
class ECVS_EXPORT CAlgrithmPlugin
{
	friend class CPluginManager;
public:
	CAlgrithmPlugin(string strInnerName);
	~CAlgrithmPlugin();
	string GetAlgrithmInnerName();
	//CAlgrithmBase* CreateAlgrithm();
	//PFUNCRUN m_pFuncRun;
	PFUNCGETNAME m_pFuncGetName;
	PFUNCGETICON m_pFuncGetICon;
	PFUNCCREATEALGRITHM m_pCreateFunc;
	//PFUNCCREATEALGRITHM m_pFuncGetErrorMsg;
private:
	HMODULE  m_hModuleHandle;
	const string	 m_strData;
};

