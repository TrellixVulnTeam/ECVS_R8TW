#pragma once

class ECVS_EXPORT CBilateralFilter :
	public CAlgrithmBase
{
public:
	CBilateralFilter();
	~CBilateralFilter();

	virtual void Run();		//ִ���㷨
	virtual void Set(){};  //�����㷨
	virtual string GetErrorMsg();
	//��д������������ʱδʵ�֣��ȵ�һ���㷨�ɹ�ʵ�ּ����̲��Գɹ�����ʵ��
	virtual void Read(){};
	virtual void Save() {};

//	virtual string GetErrorMsg(); // ��ȡ�㷨ִ�д����ַ���

private:
	//�㷨����ʱ˽�в���

// 
// 		m_nDiameter �C Diameter of each pixel neighborhood that is used during filtering.If it is non - positive, it
// 		is computed from sigmaSpace .
// 		m_dbSigmaColor �C Filter sigma in the color space.A larger value of the parameter means that
// 		farther colors within the pixel neighborhood(see sigmaSpace) will be mixed together,
// 		resulting in larger areas of semi - equal color.
// 		m_dbSigmaSpace �C Filter sigma in the coordinate space.A larger value of the parameter means
// 		that farther pixels will influence each other as long as their colors are close enough(see
// 		sigmaColor).When d > 0, it specifies the neighborhood size regardless of sigmaSpace .
// 		Otherwise, d is proportional to sigmaSpace .
	int		m_nDiameter;
	double	m_dbSigmaColor;
	double	m_dbSigmaSpace;


};

