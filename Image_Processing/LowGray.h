#pragma once


// CLowGray 灰度级降低 对话框

class CLowGray : public CDialogEx
{
	DECLARE_DYNAMIC(CLowGray)

public:
	CLowGray(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLowGray();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	int LowGray;
	int LowGray;
};
