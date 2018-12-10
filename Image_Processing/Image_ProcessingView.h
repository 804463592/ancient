
// Image_ProcessingView.h : CImage_ProcessingView 类的接口
//

#pragma once
#include "MyImage_.h"
#include "atlimage.h"
#include "Image_ProcessingDoc.h"
#include "CplexNum.h"
//#include "Warning.h"

class CImage_ProcessingView : public CScrollView
{
protected: // 仅从序列化创建
	CImage_ProcessingView();
	DECLARE_DYNCREATE(CImage_ProcessingView)

// 特性
public:
	CImage_ProcessingDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CImage_ProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
public:
	MyImage_ m_Image;
	MyImage_ m_Imagecp;//用于复原图像

	afx_msg void OnGray();
	afx_msg void OnFileSaveAs();
	afx_msg void OnShowred();
//	afx_msg void OnViewToolbar();
	afx_msg void OnImageProcessing();
	afx_msg void OnDoubleimage();////图片相加
	afx_msg void OnDownsample();//对图片下采样，降低分辨率
	afx_msg void OnDowngray();//降低图片灰度级
private:
	// 记录次数
	int Times;
public:
	afx_msg void OnDoubleimage2();////图片相差
//	int Flag;
	CImage image2;//CImage新对象，用于保存下采样数据
	int w;//图像尺寸
	int h;//图像尺寸
//	float probability[256];

	//============================================
	//直方图统计
	//输入参数： 无
	//返回值：	无（全局变量 float *probability 表示分布概率密度）
	//===============================================
	afx_msg void OnHistogram();


	//====================================================
	//函数功能：直方图均衡化
	//输入输出 ：无  ：响应函数
	//直接将源图数据更改
	//====================================================
	afx_msg void OnHistogram2();

	//====================================================
	//函数功能：直方图规定化
	//输入输出 ：无  ：响应函数
	//直接将源图数据更改
	//====================================================
	afx_msg void OnHistmatch();

	//====================================================
	//函数功能：添加指定概率的椒盐噪声
	//输入输出 ：无  ：响应函数
	//直接将源图数据更改
	//====================================================
	afx_msg void OnSalt();

	//均值滤波
	afx_msg void OnMeanfilter();
//	afx_msg void OnMedianfilter();
	//中指滤波
	afx_msg void OnMedianf();
//	afx_msg BOOL OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	float m_Scale;
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSource();
	afx_msg void OnFourier();//傅立叶变换
	//int **Ftmp;
	CplexNum *FTResult;//傅立叶变换结果
	afx_msg void OnIfft();//二维傅立叶反变换
	void SetProgress(int);//设置进度条
	// 傅立叶变换的次数
	int FftTime;
	afx_msg void OnGeometricmeanfilter();//几何均值滤波
	afx_msg void OnHarmonicmeanfilter();//谐波均值滤波
	afx_msg void OnIharmonicmeanfilter();//逆谐波均值滤波
	afx_msg void OnMaxfilter();//最大值滤波
	afx_msg void OnMinfilter();//最小值滤波
	afx_msg void OnMidpointfilter();//中点滤波
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// 记录鼠标x坐标
	int MouseX;
	// 记录鼠标Y坐标
	int MouseY;
	// 鼠标按下FLAG
	int MouseFlag;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void On32834();
	afx_msg void OnShoworiginalimage();
	afx_msg void OnHideoriginalimage();
	// //源图鼠标点击FLAG
	int MouseFlag2;
	afx_msg void OnFillzero();

	afx_msg void OnLowpass();//理想低通滤波
	afx_msg void OnBlpf();//布特沃斯滤波器
	afx_msg void OnGlpf();
	afx_msg void OnSelfmedianfilter();//自适应中值滤波
	afx_msg void OnGaussiannoise();//添加高斯噪声
	afx_msg void OnShowrgb();//显示RGB分量
	afx_msg void OnShowhsi();//显示HSI分量
	afx_msg void OnRgbhistogram();//RGB均衡化
	afx_msg void OnIhistogram();//I分量均衡化
	afx_msg void OnRgbcut();//图像分割
	// 保存框框第二个点
	int MouseX2;
	// 保存框框第二个点
	int MouseY2;
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMyimg_PROCESSING();
//	afx_msg void On32855();

};

#ifndef _DEBUG  // Image_ProcessingView.cpp 中的调试版本
inline CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const
   { return reinterpret_cast<CImage_ProcessingDoc*>(m_pDocument); }
#endif

