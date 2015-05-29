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

#include <string>
#include <vector>
using std::vector;
using std::string;
#define  ECVSString string;

//���͵Ķ���

//��ͨ���ݵ���ʼ����
#define DATA_TYPE_BASE		0x0F00
//����������vector����ʼ����
#define DATA_TYPE_VEC_BASE	0xFF00

#define DATA_TYPE_INT		0x01
#define  DATA_TYPE_DOUBLE	0x02
#define DATA_TYPE_STRING	0x03
#define  DATA_TYPE_POINT	0x04
#define  DATA_TYPE_POINT2F  0x05
#define  DATA_TYPE_IMAGE	0x06
enum DataType
{
	TYPE_INT = DATA_TYPE_BASE + DATA_TYPE_INT,				//����
	TYPE_DOUBLE = DATA_TYPE_BASE + DATA_TYPE_DOUBLE,			//������
	TYPE_STRING = DATA_TYPE_BASE + DATA_TYPE_STRING,			//�ַ�������
	TYPE_POINT = DATA_TYPE_BASE + DATA_TYPE_POINT,				//CV::Point����
	TYPE_POINT2F = DATA_TYPE_BASE + DATA_TYPE_POINT2F,			//CV::Point2F����
	TYPE_IMAGE = DATA_TYPE_BASE + DATA_TYPE_IMAGE,				//CV::Mat ����
	//������ֶζ��������Vector����
	TYPE_INT_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_INT,
	TYPE_DOUBLE_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_DOUBLE,
	TYPE_STRING_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_STRING,
	TYPE_POINT_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_POINT,
	TYPE_POINT2F_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_POINT2F,
	TYPE_IMAGE_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_IMAGE,




};




//������
#define  ECVS_ERROR_NO_ERROR 0

//ϵͳ���ʱ�����д���


//�㷨��δִ��
#define ECVS_ERR_HAS_NO_EXECUTE 1
//��Ҫͼ��������㷨��û����������ͼ��
#define  ECVS_ERROR_HAS_NO_IMG_INPUT 2


//�Զ���������ʼλ ���в�����ش��� �ܸı��ֻ�к�16λ
#define  ECVS_ERROR_USER_MASK 0x00FF0000





bool IsVector(DataType dt); //�ж�dt�Ƿ���vector����
bool IsSameType(DataType dt1, DataType dt2);// �ж�dt1�� dt2�Ƿ�Ϊͬһ������ ����vector<int> ��int��ͬһ������
string GetErrorMsg(int nCode);