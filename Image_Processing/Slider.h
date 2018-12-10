#pragma once
#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Image_Processing.h"
#endif

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
// Slider 对话框

class Slider : public CDialogEx
{
	DECLARE_DYNAMIC(Slider)

public:
	Slider(int Type=0,CDC * p=NULL,CImage_ProcessingView * pp=NULL,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Slider();

// 对话框数据
	enum { IDD = IDD_SLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider;
	// //Q逆谐波均值滤波
	double Q;//获取值
	// 操作类型flag
	int TypeFlag;
	// 视类指针
	CDC *pDC;
	CImage_ProcessingView * pv;
	virtual BOOL OnInitDialog();
	double OldQ;
	double OldOldQ;
};
