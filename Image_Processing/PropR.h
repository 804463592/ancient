#pragma once

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
// PropR 对话框

class PropR : public CPropertyPage
{
	DECLARE_DYNAMIC(PropR)

public:
	PropR();
	virtual ~PropR();

// 对话框数据
	enum { IDD = IDD_PROP1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CWnd* pWnd;
	CDC* pDC;
	CImage_ProcessingView* pv;
	int TypeFlag;
};
