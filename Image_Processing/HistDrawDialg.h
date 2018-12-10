#pragma once


// HistDrawDialg 对话框

class HistDrawDialg : public CDialogEx
{
	DECLARE_DYNAMIC(HistDrawDialg)

public:
	HistDrawDialg(CImage_ProcessingView* pParent);   // 标准构造函数

	virtual ~HistDrawDialg();

// 对话框数据
	enum { IDD = IDD_HistDraw };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd* pWnd;
	CDC* pDC;
	CImage_ProcessingView* pv;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
