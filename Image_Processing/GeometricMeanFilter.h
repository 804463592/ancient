#pragma once


// GeometricMeanFilter �Ի���

class GeometricMeanFilter : public CDialogEx
{
	DECLARE_DYNAMIC(GeometricMeanFilter)

public:
	GeometricMeanFilter(int n=0,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GeometricMeanFilter();

// �Ի�������
	enum { IDD = IDD_GeometricMeanFilter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// //��ȡѡ��
	CString m_str;
	virtual void OnOK();
	// //ģ��ߴ�
	int m_FileterSize;
	// ����flag
	int TypeFlag;
};
