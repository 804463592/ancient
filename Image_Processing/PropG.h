#pragma once

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
// PropG �Ի���

class PropG : public CPropertyPage
{
	DECLARE_DYNAMIC(PropG)

public:
	PropG();
	virtual ~PropG();

// �Ի�������
	enum { IDD = IDD_PROP2 };

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
