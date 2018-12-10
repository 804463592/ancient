#pragma once
#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Image_Processing.h"
#endif

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
// Slider �Ի���

class Slider : public CDialogEx
{
	DECLARE_DYNAMIC(Slider)

public:
	Slider(int Type=0,CDC * p=NULL,CImage_ProcessingView * pp=NULL,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Slider();

// �Ի�������
	enum { IDD = IDD_SLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider;
	// //Q��г����ֵ�˲�
	double Q;//��ȡֵ
	// ��������flag
	int TypeFlag;
	// ����ָ��
	CDC *pDC;
	CImage_ProcessingView * pv;
	virtual BOOL OnInitDialog();
	double OldQ;
	double OldOldQ;
};
