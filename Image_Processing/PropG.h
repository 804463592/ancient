#pragma once

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
// PropG 对话框

class PropG : public CPropertyPage
{
	DECLARE_DYNAMIC(PropG)

public:
	PropG();
	virtual ~PropG();

// 对话框数据
	enum { IDD = IDD_PROP2 };

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
