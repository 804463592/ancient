#pragma once


// CLowGray �Ҷȼ����� �Ի���

class CLowGray : public CDialogEx
{
	DECLARE_DYNAMIC(CLowGray)

public:
	CLowGray(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLowGray();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	int LowGray;
	int LowGray;
};
