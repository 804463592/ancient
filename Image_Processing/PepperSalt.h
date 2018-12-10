#pragma once


// PepperSalt 对话框  椒盐噪声对话框

class PepperSalt : public CDialogEx
{
	DECLARE_DYNAMIC(PepperSalt)

public:
	PepperSalt(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PepperSalt();

// 对话框数据
	enum { IDD = IDD_PepperSalt };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_pepper;
	float m_salt;
};
