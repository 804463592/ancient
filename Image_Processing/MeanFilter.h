#pragma once


// MeanFilter ��ֵ�˲� �Ի���

class MeanFilter : public CDialogEx
{
	DECLARE_DYNAMIC(MeanFilter)

public:
	MeanFilter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MeanFilter();

// �Ի�������
	enum { IDD = IDD_MeanFilter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_FileterSize;
};
