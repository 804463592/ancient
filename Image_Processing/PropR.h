#pragma once

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
// PropR �Ի���

class PropR : public CPropertyPage
{
	DECLARE_DYNAMIC(PropR)

public:
	PropR();
	virtual ~PropR();

// �Ի�������
	enum { IDD = IDD_PROP1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CWnd* pWnd;
	CDC* pDC;
	CImage_ProcessingView* pv;
	int TypeFlag;
};
