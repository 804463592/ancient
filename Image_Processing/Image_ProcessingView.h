
// Image_ProcessingView.h : CImage_ProcessingView ��Ľӿ�
//

#pragma once
#include "MyImage_.h"
#include "atlimage.h"
#include "Image_ProcessingDoc.h"
#include "CplexNum.h"
//#include "Warning.h"

class CImage_ProcessingView : public CScrollView
{
protected: // �������л�����
	CImage_ProcessingView();
	DECLARE_DYNCREATE(CImage_ProcessingView)

// ����
public:
	CImage_ProcessingDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImage_ProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
public:
	MyImage_ m_Image;
	MyImage_ m_Imagecp;//���ڸ�ԭͼ��

	afx_msg void OnGray();
	afx_msg void OnFileSaveAs();
	afx_msg void OnShowred();
//	afx_msg void OnViewToolbar();
	afx_msg void OnImageProcessing();
	afx_msg void OnDoubleimage();////ͼƬ���
	afx_msg void OnDownsample();//��ͼƬ�²��������ͷֱ���
	afx_msg void OnDowngray();//����ͼƬ�Ҷȼ�
private:
	// ��¼����
	int Times;
public:
	afx_msg void OnDoubleimage2();////ͼƬ���
//	int Flag;
	CImage image2;//CImage�¶������ڱ����²�������
	int w;//ͼ��ߴ�
	int h;//ͼ��ߴ�
//	float probability[256];

	//============================================
	//ֱ��ͼͳ��
	//��������� ��
	//����ֵ��	�ޣ�ȫ�ֱ��� float *probability ��ʾ�ֲ������ܶȣ�
	//===============================================
	afx_msg void OnHistogram();


	//====================================================
	//�������ܣ�ֱ��ͼ���⻯
	//������� ����  ����Ӧ����
	//ֱ�ӽ�Դͼ���ݸ���
	//====================================================
	afx_msg void OnHistogram2();

	//====================================================
	//�������ܣ�ֱ��ͼ�涨��
	//������� ����  ����Ӧ����
	//ֱ�ӽ�Դͼ���ݸ���
	//====================================================
	afx_msg void OnHistmatch();

	//====================================================
	//�������ܣ����ָ�����ʵĽ�������
	//������� ����  ����Ӧ����
	//ֱ�ӽ�Դͼ���ݸ���
	//====================================================
	afx_msg void OnSalt();

	//��ֵ�˲�
	afx_msg void OnMeanfilter();
//	afx_msg void OnMedianfilter();
	//��ָ�˲�
	afx_msg void OnMedianf();
//	afx_msg BOOL OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	float m_Scale;
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSource();
	afx_msg void OnFourier();//����Ҷ�任
	//int **Ftmp;
	CplexNum *FTResult;//����Ҷ�任���
	afx_msg void OnIfft();//��ά����Ҷ���任
	void SetProgress(int);//���ý�����
	// ����Ҷ�任�Ĵ���
	int FftTime;
	afx_msg void OnGeometricmeanfilter();//���ξ�ֵ�˲�
	afx_msg void OnHarmonicmeanfilter();//г����ֵ�˲�
	afx_msg void OnIharmonicmeanfilter();//��г����ֵ�˲�
	afx_msg void OnMaxfilter();//���ֵ�˲�
	afx_msg void OnMinfilter();//��Сֵ�˲�
	afx_msg void OnMidpointfilter();//�е��˲�
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// ��¼���x����
	int MouseX;
	// ��¼���Y����
	int MouseY;
	// ��갴��FLAG
	int MouseFlag;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void On32834();
	afx_msg void OnShoworiginalimage();
	afx_msg void OnHideoriginalimage();
	// //Դͼ�����FLAG
	int MouseFlag2;
	afx_msg void OnFillzero();

	afx_msg void OnLowpass();//�����ͨ�˲�
	afx_msg void OnBlpf();//������˹�˲���
	afx_msg void OnGlpf();
	afx_msg void OnSelfmedianfilter();//����Ӧ��ֵ�˲�
	afx_msg void OnGaussiannoise();//��Ӹ�˹����
	afx_msg void OnShowrgb();//��ʾRGB����
	afx_msg void OnShowhsi();//��ʾHSI����
	afx_msg void OnRgbhistogram();//RGB���⻯
	afx_msg void OnIhistogram();//I�������⻯
	afx_msg void OnRgbcut();//ͼ��ָ�
	// ������ڶ�����
	int MouseX2;
	// ������ڶ�����
	int MouseY2;
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMyimg_PROCESSING();
//	afx_msg void On32855();

};

#ifndef _DEBUG  // Image_ProcessingView.cpp �еĵ��԰汾
inline CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const
   { return reinterpret_cast<CImage_ProcessingDoc*>(m_pDocument); }
#endif

