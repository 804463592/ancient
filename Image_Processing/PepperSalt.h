#pragma once


// PepperSalt �Ի���  ���������Ի���

class PepperSalt : public CDialogEx
{
	DECLARE_DYNAMIC(PepperSalt)

public:
	PepperSalt(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PepperSalt();

// �Ի�������
	enum { IDD = IDD_PepperSalt };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_pepper;
	float m_salt;
};
