#pragma  once
/*
* ECVSBase.h
*
* ������ 2015-5-12  ���
* 
* ECVSBase���еĹ��ö��峣�����ڸ��ļ�����
* ������ȫ�ֺ���Ҳ�ڸ��ļ����� 
*/
#ifdef ECVS_BUILD_DLL
#define ECVS_EXPORT __declspec(dllexport)
#else
#define  ECVS_EXPORT
#endif
