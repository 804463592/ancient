#pragma once

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
// PropB 对话框

class PropB : public CPropertyPage
{
	DECLARE_DYNAMIC(PropB)

public:
	PropB();
	virtual ~PropB();

// 对话框数据
	enum { IDD = IDD_PROP3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CWnd* pWnd;
	CDC* pDC;
	CImage_ProcessingView* pv;
	int TypeFlag;
};
