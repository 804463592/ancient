// RGBSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"

#include "RGBSheet.h"


// RGBSheet

IMPLEMENT_DYNAMIC(RGBSheet, CPropertySheet)

RGBSheet::RGBSheet(CImage_ProcessingView* p,UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
	, pv(p)
	, TypeFlag(0)
{
	m_prop1.pv=pv;
	m_prop2.pv=pv;
	m_prop3.pv=pv;
	AddPage(&m_prop1);
	AddPage(&m_prop2);
	AddPage(&m_prop3);
}

RGBSheet::RGBSheet(CImage_ProcessingView* p,int type,LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
	,pv(p)
	, TypeFlag(type)
{
	m_prop1.pv=pv;
	m_prop1.TypeFlag=TypeFlag;
	m_prop2.pv=pv;
	m_prop2.TypeFlag=TypeFlag;
	m_prop3.pv=pv;
	m_prop3.TypeFlag=TypeFlag;
	//m_prop1.pv=pv;
	AddPage(&m_prop1);
	AddPage(&m_prop2);
	AddPage(&m_prop3);
}

RGBSheet::~RGBSheet()
{
}


BEGIN_MESSAGE_MAP(RGBSheet, CPropertySheet)
END_MESSAGE_MAP()


// RGBSheet 消息处理程序
