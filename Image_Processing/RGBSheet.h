#pragma once
#include "PropR.h"
#include "PropG.h"
#include "PropB.h"


// RGBSheet

class RGBSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(RGBSheet)

public:
	RGBSheet(CImage_ProcessingView*,UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	RGBSheet(CImage_ProcessingView*,int type,LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~RGBSheet();


	

protected:
	DECLARE_MESSAGE_MAP()
public:
	// point to Viewclass
	CImage_ProcessingView* pv;
	PropR m_prop1;
	PropG m_prop2;
	PropB m_prop3;
	// flagÅÐ¶ÏË­ÔÚµ÷ÓÃ
	int TypeFlag;
};


