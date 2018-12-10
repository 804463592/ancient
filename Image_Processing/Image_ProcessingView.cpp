
// Image_ProcessingView.cpp : CImage_ProcessingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Image_Processing.h"
#endif

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
#include "LowGray.h"
#include "DownTimes.h"
#include "HistDraw.h"
#include "WarnDlg.h"
#include "PepperSalt.h"
#include "MeanFilter.h"
#include "math.h"
#include "MedianFilter.h"
#include <algorithm>
#include "HistDrawDialg.h"
#include "CplexNum.h"
#include "Fourier.h"
#include "MainFrm.h"
#include "GeometricMeanFilter.h"
#include "Slider.h"
#include <random>
#include "RGBSheet.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImage_ProcessingView

IMPLEMENT_DYNCREATE(CImage_ProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImage_ProcessingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImage_ProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CImage_ProcessingView::OnFileOpen)
	ON_COMMAND(IDM_Gray, &CImage_ProcessingView::OnGray)
	ON_COMMAND(ID_FILE_SAVE_AS, &CImage_ProcessingView::OnFileSaveAs)
	ON_COMMAND(IDM_SHOWRED, &CImage_ProcessingView::OnShowred)
//	ON_COMMAND(ID_VIEW_TOOLBAR, &CImage_ProcessingView::OnViewToolbar)
ON_COMMAND(ID_Image_Processing, &CImage_ProcessingView::OnImageProcessing)
ON_COMMAND(ID_DoubleImage, &CImage_ProcessingView::OnDoubleimage)
ON_COMMAND(ID_DownSample, &CImage_ProcessingView::OnDownsample)
ON_COMMAND(ID_DOWNGRAY, &CImage_ProcessingView::OnDowngray)
ON_COMMAND(ID_DoubleImage2, &CImage_ProcessingView::OnDoubleimage2)
ON_COMMAND(ID_Histogram, &CImage_ProcessingView::OnHistogram)
ON_COMMAND(ID_HistoGram2, &CImage_ProcessingView::OnHistogram2)
//ON_COMMAND(ID_HistBack, &CImage_ProcessingView::OnHistback)
ON_COMMAND(ID_HistMatch, &CImage_ProcessingView::OnHistmatch)
ON_COMMAND(ID_SALT, &CImage_ProcessingView::OnSalt)
ON_COMMAND(ID_MeanFilter, &CImage_ProcessingView::OnMeanfilter)
//ON_COMMAND(ID_MedianFilter, &CImage_ProcessingView::OnMedianfilter)
ON_COMMAND(ID_MedianF, &CImage_ProcessingView::OnMedianf)
//ON_WM_MOUSEHWHEEL()
//ON_WM_MOUSEHWHEEL()
ON_COMMAND(ID_Source, &CImage_ProcessingView::OnSource)
ON_COMMAND(ID_Fourier, &CImage_ProcessingView::OnFourier)
ON_COMMAND(ID_IFFT, &CImage_ProcessingView::OnIfft)
ON_COMMAND(ID_GeometricMeanFilter, &CImage_ProcessingView::OnGeometricmeanfilter)
ON_COMMAND(ID_HarmonicMeanFilter, &CImage_ProcessingView::OnHarmonicmeanfilter)
ON_COMMAND(ID_IHarmonicMeanFilter, &CImage_ProcessingView::OnIharmonicmeanfilter)
ON_COMMAND(ID_MaxFilter, &CImage_ProcessingView::OnMaxfilter)
ON_COMMAND(ID_MinFilter, &CImage_ProcessingView::OnMinfilter)
ON_COMMAND(ID_MidpointFilter, &CImage_ProcessingView::OnMidpointfilter)
ON_WM_VSCROLL()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_ERASEBKGND()
ON_COMMAND(ID_32834, &CImage_ProcessingView::On32834)
ON_COMMAND(ID_ShowOriginalImage, &CImage_ProcessingView::OnShoworiginalimage)
ON_COMMAND(ID_HideOriginalImage, &CImage_ProcessingView::OnHideoriginalimage)
ON_COMMAND(ID_FillZero, &CImage_ProcessingView::OnFillzero)
ON_COMMAND(ID_LowPass, &CImage_ProcessingView::OnLowpass)
ON_COMMAND(ID_BLPF, &CImage_ProcessingView::OnBlpf)
ON_COMMAND(ID_GLPF, &CImage_ProcessingView::OnGlpf)
ON_COMMAND(ID_SelfMedianFilter, &CImage_ProcessingView::OnSelfmedianfilter)
ON_COMMAND(ID_GaussianNoise, &CImage_ProcessingView::OnGaussiannoise)
ON_COMMAND(ID_ShowRGB, &CImage_ProcessingView::OnShowrgb)
ON_COMMAND(ID_ShowHSI, &CImage_ProcessingView::OnShowhsi)
ON_COMMAND(ID_RGBHistoGram, &CImage_ProcessingView::OnRgbhistogram)
ON_COMMAND(ID_IHistoGram, &CImage_ProcessingView::OnIhistogram)
ON_COMMAND(ID_RGBCut, &CImage_ProcessingView::OnRgbcut)
ON_WM_SETCURSOR()
ON_COMMAND(ID_32873, &CImage_ProcessingView::OnMyimg_PROCESSING)
//ON_COMMAND(32855, &CImage_ProcessingView::On32855)

//ON_COMMAND(32855, &CImage_ProcessingView::On32855)
END_MESSAGE_MAP()

// CImage_ProcessingView 构造/析构
//使用了github

CImage_ProcessingView::CImage_ProcessingView()
	: Times(1)
	, w(0)
	, h(0)
	, m_Scale(1.0f)
	//, Ftmp(NULL)
	, FTResult(NULL)
	, FftTime(0)
	, MouseX(0)
	, MouseY(0)
	, MouseFlag(0)
	, MouseFlag2(0)
	, MouseX2(0)
	, MouseY2(0)
{
	// TODO: 在此处添加构造代码

}

CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView 绘制
void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	/////////////////////////////////////////设置背景颜色
	CRect   rect1;    
	GetClientRect(rect1);
	if (m_Image.IsNull())
	{
		CRect   rect2;    
		rect2.left=rect1.right/3;
		rect2.top=rect1.bottom/4;
		rect2.right=rect1.right*2/3;
		rect2.bottom=rect1.bottom*3/4;
		pDC->FillSolidRect(rect1,RGB(128,128,128)); 
		pDC->FillSolidRect(rect2,RGB(169,169,169)); 
	}
	
	//////////////////////////////////////////画图
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!m_Image.IsNull())
	{
		//CRect rect;
		//GetClientRect(&rect);
		//m_Image.X=rect.right/2-w/2;
		//m_Image.Y=rect.bottom/2-h/2;//重画时调整位置

		if(m_Image.Flag==0)//FLAG为0
		{
				if (m_Image.GetWidth()>rect1.right)///////
				{
					rect1.right=m_Image.GetWidth();
				}
				if (m_Image.GetHeight()>rect1.bottom)
				{
					rect1.bottom=m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
				}
				pDC->FillSolidRect(rect1,RGB(128,128,128)); //重新设置背景颜色


				m_Image.Draw(pDC->m_hDC,m_Image.X,m_Image.Y);//xy显示
			
		}
		else if (m_Image.Flag==1)//FLAG显示源图
		{
			if (m_Image.GetWidth()>rect1.right)
			{
				rect1.right=m_Image.GetWidth();
			}
			if (m_Image.GetHeight()>rect1.bottom)
			{
				rect1.bottom=m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
			}
			pDC->FillSolidRect(rect1,RGB(128,128,128)); //重新设置背景颜色
			
			m_Imagecp.Draw(pDC->m_hDC,m_Imagecp.X,m_Imagecp.Y);//显示源图
			pDC->TextOut(m_Imagecp.X+m_Imagecp.GetWidth()/2,m_Imagecp.Y-30,"原始图");
			m_Image.Draw(pDC->m_hDC,m_Image.X,m_Image.Y);//xy显示
			pDC->TextOut(m_Image.X+m_Image.GetWidth()/2,m_Image.Y-30,"当前图");

		}
		else if(m_Image.Flag==2)//下采样图像
		{
			if (m_Image.GetWidth()>rect1.right)///////
			{
				rect1.right=m_Image.GetWidth();
			}
			if (m_Image.GetHeight()>rect1.bottom)
			{
				rect1.bottom=m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
			}
	
			pDC->FillSolidRect(rect1,RGB(128,128,128)); //重新设置背景颜色

			
			image2.Draw(pDC->m_hDC,m_Image.X,m_Image.Y);
		}
		else if (m_Image.Flag==3)//rgb分割前，取框中
		{
			if (m_Image.GetWidth()>rect1.right)///////
			{
				rect1.right=m_Image.GetWidth();
			}
			if (m_Image.GetHeight()>rect1.bottom)
			{
				rect1.bottom=m_Image.GetHeight();////如果图片比客户区大，扩大背景区域
			}
			pDC->FillSolidRect(rect1,RGB(169,169,169)); //重新设置背景颜色

			m_Image.Draw(pDC->m_hDC,m_Image.X,m_Image.Y);//xy显示

			CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush= pDC->SelectObject(pBrush);
			pDC->Rectangle(CRect(CPoint(MouseX,MouseY),CPoint(MouseX2,MouseY2)));
			pDC->SelectObject(pOldBrush);
			
		}
		
	}

	return;
}

void CImage_ProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImage_ProcessingView 打印


void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImage_ProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImage_ProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImage_ProcessingView 诊断

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImage_ProcessingView 消息处理程序


void CImage_ProcessingView::OnFileOpen()
{
	BOOL OpenFlage=1;//记录是否成功打开了图片

	m_Image.Flag=0;//恢复设置FLAG

	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if(IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if(!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
		if(!m_Imagecp.IsNull()) m_Imagecp.Destroy();//判断是否已经有图片，有的话进行清除

		while(S_FALSE ==m_Image.Load(dlg.GetPathName()))
		{
			MessageBox("打开的不是24位真彩色图！");
			if(IDCANCEL == dlg.DoModal()) //重新打开图片；点击取消则跳出循环   
			{
				OpenFlage=0;//没有打开图片就跳出循环
				break;
			}
		}//确保是24位彩色图片
		m_Imagecp.Load(dlg.GetPathName());//对原始图片备份


		//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
		if (1==OpenFlage)
		{
			CSize sizeTotal;
			w=m_Image.GetWidth();
			h=m_Image.GetHeight();


			CRect rect;
			GetClientRect(&rect);
			m_Image.X=max(0,rect.right/2-w/2);
			m_Image.Y=max(0,rect.bottom/2-h/2);//设置显示图片的左上角位置
			m_Imagecp.X=max(0,rect.right/2-w/2);
			m_Imagecp.Y=max(0,rect.bottom/2-h/2);//设置显示图片的左上角位置
			
			sizeTotal.cx =w;
			sizeTotal.cy =h;
			SetScrollSizes(MM_TEXT, sizeTotal);
		}

		//Window_Image_w=m_Image.GetWidth();//获得图片的初始大小，为放大缩小功能做准备
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //强制调用ONDRAW函数
	}
}


void CImage_ProcessingView::OnGray()
{
	// TODO: 在此添加命令处理程序代码
	if(m_Image.IsNull()) 
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;//恢复设置FLAG
	
	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			int b=(int)m_Image.m_pBits[0][j][k];//B   
			int g=(int)m_Image.m_pBits[1][j][k];//G
			int r=(int)m_Image.m_pBits[2][j][k];//R
			int ave=(b*11+g*59+r*30)/100;
			//int ave =r;
			m_Image.m_pBits[0][j][k]=(BYTE)ave;
			m_Image.m_pBits[1][j][k]=(BYTE)ave;
			m_Image.m_pBits[2][j][k]=(BYTE)ave;


		}
	}

	//((CMainFrame *)GetParent())->m_progress.SetPos(50);//设置进度条！！

	Invalidate(1); //强制调用ONDRAW函数
}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {
		MessageBox(_T("你还没有打开一个要保存的图像文件！"));
		return;
	}
	CString strFilter;
	strFilter ="BMP 位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";  
	
	//	strFilter ="所有文件|*.*||";   

	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if ( IDOK != dlg.DoModal()) 
		return;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;   //  获得文件名
	//if(dlg.m_ofn.nFileExtension == 0)     //获得文件扩展名
	//{
	switch (dlg.m_ofn.nFilterIndex)
	{
	case 1:
		strExtension = "bmp"; break;
	case 2:
		strExtension = "jpg"; break;
	case 3:
		strExtension = "gif"; break;
	case 4:
		strExtension = "png"; break;
	default:
		break;
	}
	strFileName = strFileName + _T(".") + strExtension;
	//	//strFileName="C:\\Users\\Lenovo\\Desktop\\QSanguosha-Qingming\\abc.bmp";
	//}
	// 图像保存
	HRESULT hResult;
	if (1==m_Image.Flag)
	{
		hResult = image2.Save(strFileName);//保存下采样的图片
	}
	else
	{
		hResult = m_Image.Save(strFileName);//保存原始图片
	}
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;//恢复设置FLAG

	int w=m_Image.GetWidth();//获得图像的宽度
	int h=m_Image.GetHeight();//获得图像的高度
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			m_Image.m_pBits[0][j][k]=0;//B   用循环访问图像的像素值，将它的绿色分量和蓝色分量置为0，图像就只剩下红色分量了
			m_Image.m_pBits[1][j][k]=0;//G


		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}



void CImage_ProcessingView::OnImageProcessing()
{
	// TODO: 在此添加命令处理程序代码
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		MessageBox(_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;//恢复设置FLAG

	int w=m_Image.GetWidth();//获得图像的宽度
	int h=m_Image.GetHeight();//获得图像的高度
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			m_Image.m_pBits[0][j][k]=0;//B   用循环访问图像的像素值，将它的蓝色分量/绿色分量/红色分量置为0，因此图像会变成纯黑色
			m_Image.m_pBits[1][j][k]=0;//G
			m_Image.m_pBits[2][j][k]=0;//R


		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}

//图片相加
void CImage_ProcessingView::OnDoubleimage()
{
	Times++;
	float k=Times;
	//k=(k-1)/k;
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
			//_T("请先打开一幅图像！"));
		 return;
	}

	m_Image.Flag=0;//恢复设置FLAG
	w=m_Image.GetWidth();//获得第一幅图像的宽度
	h=m_Image.GetHeight();//获得图像的高度

	MyImage_ Image_Second;
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if(IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if(!Image_Second.IsNull()) Image_Second.Destroy();//判断是否已经有图片，有的话进行清除

		Image_Second.Load(dlg.GetPathName());//调用对话框的GetPathName获得图片的位置，并且调用Load加载图片


		if(Image_Second.IsNull()) return;
		if (w!=Image_Second.GetWidth()||h!=Image_Second.GetHeight())//判断两幅图像大小是否一致
		{
			MessageBox(_T("两幅图像大小不一致！"));
			return;
		}
		for (int j=0; j<h; j++)
		{
			for (int i=0; i<w; i++)//两幅图像做简单相加操作
			{
				int tt=m_Image.m_pBits[0][j][i];
				m_Image.m_pBits[0][j][i]=m_Image.m_pBits[0][j][i]*((k-1)/k)+Image_Second.m_pBits[0][j][i]*(1/k);
				m_Image.m_pBits[1][j][i]=m_Image.m_pBits[1][j][i]*((k-1)/k)+Image_Second.m_pBits[1][j][i]*(1/k);
				m_Image.m_pBits[2][j][i]=m_Image.m_pBits[2][j][i]*((k-1)/k)+Image_Second.m_pBits[2][j][i]*(1/k);
				tt=m_Image.m_pBits[0][j][i];
			}
		}
		Invalidate(1);
	}
}

//对图片下采样，降低分辨率
void CImage_ProcessingView::OnDownsample()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if(!image2.IsNull())//如果前面已经下采样过了，则此销毁旧的下采样保存的图片
	{
		image2.Destroy();
	}
	
	w=m_Image.GetWidth();//获得图像的宽度
	h=m_Image.GetHeight();//获得图像的高度

	DownTimes dlg;//建立对话框对象
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

		while(dlg.m_downtimes<=0||pow((double)2,(int)dlg.m_downtimes)>w||pow((double)2,(int)dlg.m_downtimes)>h)//判断是否输入有效的数字
		{
			MessageBox("	  输入无效\n请重新输入有效的下采样次数");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		m_Image.Flag=2;//记录FLAG

		int T=pow((double)2,(int)dlg.m_downtimes);//下采样次数*2


		//CImage image2;
		image2.Create(w/T,h/T,24);//全局变量Create后需要delete

		int nrow=image2.GetPitch();//获得CImage每一行像素的RGB所占用的存储空间的大小
		BYTE *psrc=(BYTE *)image2.GetBits();//获得CImage最后一行的像素地址
		/*将三维数组复制进m_CImage*/
		for (int j=0;j<h/T;j++)
		{
			for (int k=0;k<w/T;k++)
			{
				psrc[j*nrow+k*3]=m_Image.m_pBits[0][j*T][k*T];//B
				psrc[j*nrow+k*3+1]=m_Image.m_pBits[1][j*T][k*T];//G
				psrc[j*nrow+k*3+2]=m_Image.m_pBits[2][j*T][k*T];//R

			}
		}
	/*将三维数组复制进image2*/
	Invalidate(1);//强制调用ONDRAW函数，ONDRAW会绘制图像
	}
	
	
}


void CImage_ProcessingView::OnDowngray()
{
	if(m_Image.IsNull()) 
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;//恢复设置FLAG

	///判断是否为彩色图片，若是则弹出降质警告///
	if(!(m_Image.m_pBits[0][0][0]==m_Image.m_pBits[1][0][0]&&m_Image.m_pBits[1][0][0]==m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL==warn.DoModal())
		{
			return;
		}
	}

	OnGray();//如果是彩色图：先转化为灰度图

	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();


	CLowGray dlg;
	if (IDOK==dlg.DoModal())
	{
		UpdateData();
		while (dlg.LowGray<=0||dlg.LowGray>256)
		{
			MessageBox("灰度级无效，请重新输入灰度级！");
			//dlg.DoModal();
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}
		int Time=256/dlg.LowGray;//判断下采样次数  (采用最接近的灰度级)

			for (int j=0;j<h;j++)
				{
					for (int k=0;k<w;k++)
						{
							BYTE b=m_Image.m_pBits[0][j][k];
							BYTE g=m_Image.m_pBits[1][j][k];
							BYTE r=m_Image.m_pBits[2][j][k];

			//////////
			int ave=(b+g+r)/3;//随着降低次数增加，不断改变灰度值
			////ave必须是int类型////

			if(ave>255/2)//进行灰度变换算法
			{
				ave=(ave/Time+1)*Time;
				if (ave>255)
					ave=255;
			}
			else
			{
				ave=(ave/Time)*Time;
				if (ave<0)
					ave=0;
			}

			m_Image.m_pBits[0][j][k]=ave;
			m_Image.m_pBits[1][j][k]=ave;
			m_Image.m_pBits[2][j][k]=ave;
			}
			}
			Invalidate(1); //强制调用ONDRAW函数
	}
	//Times=1;//恢复Timees初值，图片相加要用！
	
}

//差分
void CImage_ProcessingView::OnDoubleimage2()
{
	// TODO: 在此添加命令处理程序代码
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;//恢复设置FLAG
	int w=m_Image.GetWidth();//获得第一幅图像的宽度
	int h=m_Image.GetHeight();//获得图像的高度

	MyImage_ Image_Second;
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if(IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if(!Image_Second.IsNull()) Image_Second.Destroy();//判断是否已经有图片，有的话进行清除

		Image_Second.Load(dlg.GetPathName());//调用对话框的GetPathName获得图片的位置，并且调用Load加载图片


		if(Image_Second.IsNull()) return;
		if (w!=Image_Second.GetWidth()||h!=Image_Second.GetHeight())//判断两幅图像大小是否一致
		{
			MessageBox(_T("两幅图像大小不一致！"));
			return;
		}
		for (int j=0; j<h; j++)
			for (int i=0; i<w; i++)//两幅图像做简单相加操作
			{
				m_Image.m_pBits[0][j][i]=m_Image.m_pBits[0][j][i]-Image_Second.m_pBits[0][j][i];
				m_Image.m_pBits[1][j][i]=m_Image.m_pBits[1][j][i]-Image_Second.m_pBits[1][j][i];
				m_Image.m_pBits[2][j][i]=m_Image.m_pBits[2][j][i]-Image_Second.m_pBits[2][j][i];
			}
			Invalidate(1);
	}
	// TODO: 在此添加命令处理程序代码
}

//============================================
//直方图统计
//输入参数： 无
//返回值：	无（全局变量 float *probability 表示分布概率密度）
//===============================================
void CImage_ProcessingView::OnHistogram()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	if(!(m_Image.m_pBits[0][0][0]==m_Image.m_pBits[1][0][0]&&m_Image.m_pBits[1][0][0]==m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL==warn.DoModal())
		{
			return;
		}
	}
	OnGray();//如果是彩色图：先转化为灰度图

	m_Image.GetHistgran();//调用成员函数,统计直方图

	//Dialg绘图
	HistDrawDialg dlg(this);
	dlg.DoModal();

	//取消调用HISTDRAW，改用Dialg
	//m_Image.Flag=2;//设置FLAG
	Invalidate(1);	
}

//====================================================
//函数功能：直方图均衡化
//输入输出 ：无  ：响应函数
//直接将源图数据更改
//====================================================
void CImage_ProcessingView::OnHistogram2()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	///判断是否为彩色图片，若是则弹出降质警告///
	if(!(m_Image.m_pBits[0][0][0]==m_Image.m_pBits[1][0][0]&&m_Image.m_pBits[1][0][0]==m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL==warn.DoModal())
		{
			return;
		}
	}
	OnGray();//如果是彩色图：先转化为灰度图
	m_Image.GetHistgran();//获取概率直方图
	BYTE *lpNewDIBBits;

	long i,j;		//循环计数
	BYTE pixel;		//像素值
	//float fPro[256];	//源图概率密度变量probability
	float temp[256];
	int   nRst[256];//映射表
	int nrow=m_Image.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	
	//BYTE *lpDIBBits=(BYTE *)m_Image.m_CImage.GetBits();//获得源图像起始位置

	w=m_Image.GetWidth();
	h=m_Image.GetHeight();

	//hNewDIBBits=LocalAlloc(LHND,w*h);//一维数组，最后赋值到三个数组中
	CImage image3;			//缓存图
	image3.Create(w,h,24);	//Create后需要delete
	lpNewDIBBits=(BYTE *)image3.GetBits();//获得image3最后一行的像素地址

	for (i=0;i<256;i++)
	{
		if(0==i)
		{
			temp[0]=m_Image.probability[0];
		}
		else
		{
			temp[i]=temp[i-1]+m_Image.probability[i];
		}
	}

	for(i=0;i<256;i++)
	{
		nRst[i]=(int)(255.0f * temp[i] + 0.5f);
	}


	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			pixel = m_Image.m_pBits[0][j][i];
			lpNewDIBBits[j*nrow+i*3]=(BYTE)(nRst[pixel]);//中转，没什么用
			

			m_Image.m_pBits[0][j][i]=lpNewDIBBits[j*nrow+i*3];//注意是使用m_pBits
			m_Image.m_pBits[1][j][i]=lpNewDIBBits[j*nrow+i*3];//不使用CImage的Getbits
			m_Image.m_pBits[2][j][i]=lpNewDIBBits[j*nrow+i*3];
		}
	}
	Invalidate(1);


}


//void CImage_ProcessingView::OnHistback()
//{
//	if(m_Image.m_CImage.IsNull())
//	{
//		int w=m_Image.m_CImage.GetWidth();
//	int h=m_Image.m_CImage.GetHeight();
//	int nrow=m_Image.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
//	BYTE *psrc=(BYTE *)m_Image.m_CImage.GetBits();//获得m_CImage最后一行的像素地址
//	/*创建三维数组并将m_CImage复制进三维数组*/
//
//	/*创建完成三维数组*/
//
//	for (int j=0;j<h;j++)
//	{
//		for (int k=0;k<w;k++)
//		{
//			m_Image.m_pBits[0][j][k]=psrc[j*nrow+k*3];//B
//			m_Image.m_pBits[1][j][k]=psrc[j*nrow+k*3+1];//G
//			m_Image.m_pBits[2][j][k]=psrc[j*nrow+k*3+2];//R
//		}
//	}
//	// TODO: 在此添加命令处理程序代码
//	}
//	Invalidate();
//}


//直方图规定化
void CImage_ProcessingView::OnHistmatch()
{
	BOOL OpenFlage=1;//记录是否成功打开了图片

	//获取目标直方图
	MyImage_  MatchImage;
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if(IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if(!MatchImage.IsNull()) MatchImage.Destroy();//判断是否已经有图片，有的话进行清除

		while(S_FALSE ==MatchImage.Load(dlg.GetPathName()))
		{
			MessageBox("打开的不是24位真彩色图！");
			if(IDCANCEL == dlg.DoModal()) //重新打开图片；点击取消则跳出循环   
			{
				OpenFlage=0;
				return;
			}
		}
	}
	else
	{
		return;
	}
	MatchImage.GetHistgran();//获取Match概率直方图




	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	//判断是否为彩色图片，若是则弹出降质警告//
	if(!(m_Image.m_pBits[0][0][0]==m_Image.m_pBits[1][0][0]&&m_Image.m_pBits[1][0][0]==m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL==warn.DoModal())
		{
			return;
		}
	}

	m_Image.GetHistgran();//获取概率直方图
	OnGray();//如果是彩色图：先转化为灰度图

	



	float temp[256];
	long i,j;		//循环计数
	BYTE pixel;		//像素值
	int   nMap[256];//待求映射表
	int   npMap[256];//规定直方图的均衡化的映射表
	float fpPro[256];
	float  k=1.0f/256;
	for (i=0;i<256;i++)
	{
		fpPro[i]=MatchImage.probability[i];//规定化的概率
	}
	int bGray=256;//规定化的灰度级

	w=m_Image.GetWidth();
	h=m_Image.GetHeight();


	//计算源图累计直方图 m_Image.probability
	for (i=0;i<256;i++)
	{
		if(0==i)
		{
			temp[0]=m_Image.probability[0];
		}
		else
		{
			temp[i]=temp[i-1]+m_Image.probability[i];
		}
		m_Image.probability[i]=temp[i];
	}

	//计算规定后的累计直方图
	for (i=0;i<bGray;i++)
	{
		if (i==0)
		{
			temp[0]=fpPro[0];
		}
		else
		{
			temp[i]=temp[i-1]+fpPro[i];
		}
		fpPro[i]=temp[i];
	}

	//计算规定化概率 经均衡化的映射表：npMap
	for(i=0;i<bGray;i++)
	{
		npMap[i]=(int)((bGray-1) * fpPro[i] + 0.5f);//必须减1！
	}

	//建立映射关系
	for (i=0;i<256;i++)
	{
		int m=0;
		float min_value=1.0f;//float型最小差值
		for(j=0;j<bGray;j++)
		{
			float now_value=0.0f;
			if (m_Image.probability[i]-fpPro[j]>=0.0f)
			{
				now_value=m_Image.probability[i]-fpPro[j];
			}
			else
			{
				now_value=fpPro[j]-m_Image.probability[i];
			}
			if (now_value<min_value)
			{
				m=j;//记录最小值位置
				min_value=now_value;//不断更新最小差值
			}
		}
		nMap[i]=npMap[m];//建立灰度映射表
	}

	//对个像素进行直方图规定化映射处理
	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			pixel = m_Image.m_pBits[0][j][i];

			m_Image.m_pBits[0][j][i]=(BYTE)(nMap[pixel]);//注意是使用m_pBits
			m_Image.m_pBits[1][j][i]=(BYTE)(nMap[pixel]);//不使用CImage的Getbits
			m_Image.m_pBits[2][j][i]=(BYTE)(nMap[pixel]);
		}
	}
	Invalidate(1);
}

//====================================================
//函数功能：添加指定概率的椒盐噪声
//输入输出 ：pepper、salt概率
//直接将源图数据更改
//====================================================
void CImage_ProcessingView::OnSalt()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	PepperSalt dlg;//建立对话框对象
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_pepper<0||dlg.m_pepper>1||dlg.m_salt<0||dlg.m_salt>1||
						(dlg.m_salt+dlg.m_pepper)>1)
		{
			MessageBox("	 输入无效\n请重新输入有效的噪声概率");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	float p_a=dlg.m_pepper;//获取噪声点的概率,p_a(黑),p_b（白）
	float p_b=dlg.m_salt;


	float P_Sum=p_a+p_b;
	float xishu=1/P_Sum;
	float p_a_1=p_a*xishu;
	for (int i = 0; i <w; i++)
		for (int j = 0; j <h; j++)
		{
			if(rand()/32767.0<P_Sum)//指定概率rand()产生随机的介于1-32767的数
			{
				if(rand()/32767.0<p_a_1)
					{	m_Image.m_pBits[0][j][i]=1;         //该像素点显示为黑色
						m_Image.m_pBits[1][j][i]=1;       
						m_Image.m_pBits[2][j][i]=1; 

				}
				else
				{
					m_Image.m_pBits[0][j][i]=255;         //该像素点显示为白色
					m_Image.m_pBits[1][j][i]=255;       
					m_Image.m_pBits[2][j][i]=255;
				}

			}
		}
		Invalidate(1);
	}
	
}

//算术均值滤波
void CImage_ProcessingView::OnMeanfilter()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	GeometricMeanFilter dlg;//统一使用几何均值滤波模板DLG
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

	long B=0,G=0,R=0;//累加存储，只BYTE类型会产生溢出

	//创建新三维数组，用于暂存新图、、没有初始化！
	BYTE *** NewPicture;
	NewPicture= new  BYTE **[3];//3个维度；分配内存  
	for(int i=0;i<3;i++)  
	{ 
		NewPicture[i] = new  BYTE*[h];   //先H
	}   
	for(int i=0;i<3;i++)   
	{          
		for   (int j=0;j<h;j++)         
		{   
			NewPicture[i][j]=new BYTE[w];   //后W
		}
	}


		//均值滤波
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				R=0,G=0,B=0;//为新模板清零
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//模板内循环
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B+=m_Image.m_pBits[0][j+k][i+kk];//累加求和
						G+=m_Image.m_pBits[1][j+k][i+kk];//累加求和
						R+=m_Image.m_pBits[2][j+k][i+kk];//累加求和
					}
				}
				NewPicture[0][j][i]=B/(dlg.m_FileterSize*dlg.m_FileterSize);
				NewPicture[1][j][i]=G/(dlg.m_FileterSize*dlg.m_FileterSize);
				NewPicture[2][j][i]=R/(dlg.m_FileterSize*dlg.m_FileterSize);
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;
			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//设置进度条！！

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

//回收指针
//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

//////////////////////////////////////////////////////////////////////////
		Invalidate(1);
	}
}

//中值滤波
void CImage_ProcessingView::OnMedianf()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG
	GeometricMeanFilter dlg;//统一使用几何均值滤波模板DLG
	//dlg.DoModal();
	
	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//创建新三维数组，用于暂存新图！
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //先H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //后W
			}
		}

		//暂存数组，求取中值
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//数组下标

		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				sz=0;
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//模板内循环
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B[sz]=m_Image.m_pBits[0][j+k][i+kk];
						G[sz]=m_Image.m_pBits[1][j+k][i+kk];
						R[sz]=m_Image.m_pBits[2][j+k][i+kk];
						sz++;
					}
				}
				std::sort(B,B+dlg.m_FileterSize*dlg.m_FileterSize);//sort排序
				std::sort(G,G+dlg.m_FileterSize*dlg.m_FileterSize);
				std::sort(R,R+dlg.m_FileterSize*dlg.m_FileterSize);
				NewPicture[0][j][i]=B[(dlg.m_FileterSize*dlg.m_FileterSize-1)/2+1];
				NewPicture[1][j][i]=G[(dlg.m_FileterSize*dlg.m_FileterSize-1)/2+1];
				NewPicture[2][j][i]=R[(dlg.m_FileterSize*dlg.m_FileterSize-1)/2+1];
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		   ((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

//回收指针
//////////////////////////////////////////////////////////////////////////
	
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

//////////////////////////////////////////////////////////////////////////
		Invalidate(1);
	}
}



//恢复源图
void CImage_ProcessingView::OnSource()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		return;
	}
	m_Image.Flag=0;	//恢复FLAG
/////////////如果图片填零了,销毁，重新copy////////////////////
	if (w!=m_Imagecp.GetWidth())
	{
		for(int i=0;i<3;i++)   //销毁m_pBits
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete []m_Image.m_pBits[i][j];
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete []m_Image.m_pBits[i];   
		}
		delete []m_Image.m_pBits;
		m_Image.Destroy();
		m_Image.m_CImage.Create(m_Imagecp.GetWidth(),m_Imagecp.GetHeight(),24);
		w=m_Image.m_CImage.GetWidth();
		h=m_Image.m_CImage.GetHeight();
		int nrow=m_Image.m_CImage.GetPitch();//获得CImage每一行像素的RGB所占用的存储空间的大小
		BYTE *psrc2=(BYTE *)m_Image.m_CImage.GetBits();//获得CImage最后一行的像素地址
		BYTE *psrc=(BYTE *)m_Imagecp.m_CImage.GetBits();//获得CImage最后一行的像素地址

		for (int j=0;j<w;j++)
		{
			for (int k=0;k<h;k++)
			{
				psrc2[j*nrow+k*3  ]=psrc[j*nrow+k*3  ];//B
				psrc2[j*nrow+k*3+1]=psrc[j*nrow+k*3+1];//G
				psrc2[j*nrow+k*3+2]=psrc[j*nrow+k*3+2];//R
			}
		}


		m_Image.m_pBits= new  BYTE **[3];//3个维度；重新分配内存  
		for(int i=0;i<3;i++)  
		{ 
			m_Image.m_pBits[i] = new  BYTE*[h];   
		}   
		for(int i=0;i<3;i++)  
		{          
			for   (int j=0;j<h;j++)         
			{   
				m_Image.m_pBits[i][j]=new BYTE[w];   
			}
		}

		for (int j=0;j<h;j++)
		{
			for (int k=0;k<w;k++)
			{
				m_Image.m_pBits[0][j][k]=psrc[j*nrow+k*3];//B
				m_Image.m_pBits[1][j][k]=psrc[j*nrow+k*3+1];//G
				m_Image.m_pBits[2][j][k]=psrc[j*nrow+k*3+2];//R
			}
		}
	}
	else
	{
		for (int j=0;j<h;j++)
		{
			for (int i=0;i<w;i++)
			{
				m_Image.m_pBits[0][j][i]=m_Imagecp.m_pBits[0][j][i];
				m_Image.m_pBits[1][j][i]=m_Imagecp.m_pBits[1][j][i];
				m_Image.m_pBits[2][j][i]=m_Imagecp.m_pBits[2][j][i];
			}
		}
	}



	CImage_ProcessingView::On32834();
	Invalidate(TRUE);
}

//////////////////////////二维快速傅立叶变换/////////////////////////////////////////////
void CImage_ProcessingView::OnFourier()
{
	if(m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();


	long i,j;					//i:行循环变量 ,j:列循环变量
	double dTmp;				//临时变量
	//w宽；h高
	long wid =1,hei = 1;		//进行傅立叶变换的宽度和高度
	int widpor=0,heipor=0;		//wid hei :2的幂次数

	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*w*h];//为指向时域的指针分配内存
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*w*h];//为指向频域的指针分配内存

		
//////////计算可以参加傅里叶变换的宽度和高度（2的幂次方）///////////
	while (wid*2<=w)
	{
		wid *= 2;
		widpor++;
	}
	while (hei*2<=h)
	{
		hei *= 2;
		heipor++;
	}

/////////初始化pTd//////////////
	for(i=0;i<hei;i++)
	{
		for(j =0;j<wid;j++)
		{
			pTd[i*wid + j].re = 0;
			pTd[i*wid + j].im = 0;
		}
	}

/////////图像赋予pTd指针////////////////////////////
		for (int j=0;j<hei;j++)
		{
			for (int i=0;i<wid;i++)
			{
				pTd[j*wid + i].re = pow((double)-1,(double)(i+j))*m_Image.m_pBits[0][j][i];//（-1)^i+j移动变换中心
			}
		}
		++FftTime;

	

	if (FTResult)
	{
		delete []FTResult;								//如果变换结果指针有效，删除内存
	}
	 FTResult = new CplexNum[sizeof(CplexNum)*w*h];	//为变换结果重新分配内存
//////////调用傅立叶变化函数Fourier////////////////////
	Fourier(pTd, w,h,pFd,this);

/////////////保存结果/////////////
	
	for(i=0;i<hei;i++)
		for(j=0;j<wid;j++)
		{
			FTResult[wid *i + j]=pTd[wid *i + j];
		}


////////////对数变换后显示结果/////////////////////////
	int **Ftmp;			//暂存二维数组wid*hei -> 【i】【j】
						//三维数组  是hei*wid -> 【j】【i】

//////////////分配内存/////////////////////
	Ftmp=new int *[wid]; 
	double maxF(1);//变换后最大的系数
	int s(1);	//对数变换系数
	for (i=0;i<wid;i++)
	{
		Ftmp[i]=new int [hei];
	}

//////////////导入暂存二维数组///////////////
	for (int j=0;j<hei;j++)
	{
		for (int i=0;i<wid;i++)
		{
			dTmp=pTd[j*wid + i].re*pTd[j*wid + i].re+pTd[j*wid + i].im*pTd[j*wid + i].im;
			dTmp=sqrt(dTmp)/100;
			if (maxF<dTmp)
			{
				maxF=dTmp;//保存最大值
			}
			Ftmp[i][j]=dTmp;		
		}
	}
	double maxx=0;
	double v=2;//底数
///////////////对数变换///////////////////
	for (int j=0;j<hei;j++)
	{
		for (int i=0;i<wid;i++)
		{
			long double p=Ftmp[i][j];
			//p=p/maxF;
			//p=(log(1+v*p)/log(v));
			Ftmp[i][j]=(log(1+p)/log(v));
			if (maxx<Ftmp[i][j])
			{
				maxx=Ftmp[i][j];
			}
		
		}
	}
	double pq=255/maxx;//占比例
///////////////////返回至源图////////////////
	for (int j=0;j<hei;j++)
	{
		for (int i=0;i<wid;i++)
		{
			double p=Ftmp[i][j];
			m_Image.m_pBits[2][j][i]=m_Image.m_pBits[1][j][i]=m_Image.m_pBits[0][j][i]=min(pq*Ftmp[i][j],255);
			//m_Image.m_pBits[1][j][i]=min(pq*Ftmp[i][j],255);
			//m_Image.m_pBits[2][j][i]=min(pq*Ftmp[i][j],255);
		}
	}

//////////////////回收暂存数组指针////////////////
	for (i=0;i<wid;i++)
	{
		delete []Ftmp[i];
	}
	delete []Ftmp;

	delete []pTd;
	delete []pFd;
	Invalidate(TRUE);


}

//////////////////////////二维快速傅立叶反变换///////////////////////////////////////////
void CImage_ProcessingView::OnIfft()
{

	if(m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	if(!FftTime) //判断图像是否为空
	{
		MessageBox("请先傅立叶变换！");
		return;
	}

	m_Image.Flag=0;	//恢复FLAG
	--FftTime;

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();


	double dTmp;				//临时变量
	long i,j;					//i:行循环变量 ,j:列循环变量
	//w宽；h高
	long wid =1,hei = 1;		//进行傅立叶变换的宽度和高度
	int widpor=0,heipor=0;		//wid hei :2的幂次数

	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*w*h];//为指向时域的指针分配内存
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*w*h];//为指向频域的指针分配内存

//////////计算可以参加傅里叶变换的宽度和高度（2的幂次方）///////////
	while (wid*2<=w)
	{
		wid *= 2;
		widpor++;
	}
	while (hei*2<=h)
	{
		hei *= 2;
		heipor++;
	}

	/////////初始化pTd//////////////
	for(i=0;i<hei;i++)
	{
		for(j =0;j<wid;j++)
		{
			pTd[i*wid + j].re = FTResult[i*wid + j].re;
			pTd[i*wid + j].im = -FTResult[i*wid + j].im;//共轭
		}
	}


	//////////调用傅立叶变化函数Fourier////////////////////
	Fourier(pTd, w,h,pFd,this);


	for(i=0;i<hei;i++)
	{
		for(j =0;j<wid;j++)
		{
			dTmp=pTd[i*wid + j].re;
			dTmp=pTd[i*wid + j].im;
			pTd[i*wid + j].re = pTd[i*wid + j].re/(double)(wid*hei) ;
			pTd[i*wid + j].im = -pTd[i*wid + j].im/(double)(wid*hei) ;//共轭
		}
	}


	for (int j=0;j<hei;j++)
	{
		for (int i=0;i<wid;i++)
		{
			
			m_Image.m_pBits[2][j][i]=m_Image.m_pBits[1][j][i]=m_Image.m_pBits[0][j][i]=pow((double)-1,(double)(i+j))*pTd[j*wid + i].re;
			//m_Image.m_pBits[1][j][i]=pow((double)-1,(double)(i+j))*pTd[j*wid + i].re;
			//m_Image.m_pBits[2][j][i]=pow((double)-1,(double)(i+j))*pTd[j*wid + i].re;
		}
	}

	///////////回收指针内存/////////////
	delete []pTd;
	delete []pFd;


	Invalidate(TRUE);
}

////////////设置进度条//////////////
void CImage_ProcessingView::SetProgress(int k)
{
	((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
}

///////////////////几何均值滤波器///////////////////////
void CImage_ProcessingView::OnGeometricmeanfilter()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();
	//////////////////////////////////////
	GeometricMeanFilter dlg;
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		long double B=1,G=1,R=1;//累加存储，只BYTE类型会产生溢出

		//创建新三维数组，用于暂存新图、、、注意，没有初始化！
		BYTE *** NewPicture;
		NewPicture= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //先H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //后W
			}
		}


///////////////几何均值滤波///////////////////
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				R=1,G=1,B=1;//为新模板清零
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//模板内循环
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B *=pow((double)m_Image.m_pBits[0][j+k][i+kk],(double)1.0/(double)(dlg.m_FileterSize*dlg.m_FileterSize));//累乘求积
						G *=pow((double)m_Image.m_pBits[1][j+k][i+kk],(double)1.0/(double)(dlg.m_FileterSize*dlg.m_FileterSize));//累乘求积
						R *=pow((double)m_Image.m_pBits[2][j+k][i+kk],(double)1.0/(double)(dlg.m_FileterSize*dlg.m_FileterSize));//累乘求积
					}
				}
				NewPicture[0][j][i]=B;
				NewPicture[1][j][i]=G;
				NewPicture[2][j][i]=R;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;
			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//回收指针
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

		////////////////////////////////////////////////
		Invalidate(1);
	}
	// TODO: 在此添加命令处理程序代码
}


///////////////////////谐波均值滤波//////////////////////////
void CImage_ProcessingView::OnHarmonicmeanfilter()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();
	//////////////////////////////////////
	GeometricMeanFilter dlg;//使用几何均值滤波米板DLG
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		long double B=0,G=0,R=0;//累加存储，只BYTE类型会产生溢出

		//创建新三维数组，用于暂存新图、、、注意，没有初始化！
		BYTE *** NewPicture;
		NewPicture= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //先H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //后W
			}
		}


		///////////////谐波均值滤波///////////////////
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				R=0,G=0,B=0;//为新模板清零
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//模板内循环
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B +=(double)1.0/(double)m_Image.m_pBits[0][j+k][i+kk];//累乘求积
						G +=(double)1.0/(double)m_Image.m_pBits[1][j+k][i+kk];//累乘求积
						R +=(double)1.0/(double)m_Image.m_pBits[2][j+k][i+kk];//累乘求积
					}
				}
				NewPicture[0][j][i]=(double)(dlg.m_FileterSize*dlg.m_FileterSize)/B;
				NewPicture[1][j][i]=(double)(dlg.m_FileterSize*dlg.m_FileterSize)/G;
				NewPicture[2][j][i]=(double)(dlg.m_FileterSize*dlg.m_FileterSize)/R;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;
			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//回收指针
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

		////////////////////////////////////////////////
		Invalidate(1);
	}
}

//逆谐波均值滤波
void CImage_ProcessingView::OnIharmonicmeanfilter()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();
	//////////////////////////////////////
	//选择Q值
	Slider sliderdlg(0);
	double Q;
	if (IDOK==sliderdlg.DoModal())
	{
		Q=sliderdlg.Q;
	}else
	{
		return;
	}
	


	/////////////////////////////////////
	GeometricMeanFilter dlg;//使用几何均值滤波模板DLG
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		long double B1=0,G1=0,R1=0;
		long double B2=0,G2=0,R2=0;
		//累加存储，只BYTE类型会产生溢出

		//创建新三维数组，用于暂存新图、、、注意，没有初始化！
		BYTE *** NewPicture;
		NewPicture= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //先H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //后W
			}
		}

		///////////////逆谐波均值滤波///////////////////
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				R1=0,G1=0,B1=0;//为新模板清零
				B2=0,G2=0,R2=0;//为新模板清零
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//模板内循环
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B1 +=pow((long double)m_Image.m_pBits[0][j+k][i+kk],(long double)(Q+1));
						B2 +=pow((long double)m_Image.m_pBits[0][j+k][i+kk],(long double)(Q));
						G1 +=pow((long double)m_Image.m_pBits[1][j+k][i+kk],(long double)(Q+1));
						G2 +=pow((long double)m_Image.m_pBits[1][j+k][i+kk],(long double)(Q));//累加求和
						R1 +=pow((long double)m_Image.m_pBits[2][j+k][i+kk],(long double)(Q+1));
						R2 +=pow((long double)m_Image.m_pBits[2][j+k][i+kk],(long double)(Q));//累加求和
					}
				}
				NewPicture[0][j][i]=B1/B2;
				NewPicture[1][j][i]=G1/G2;
				NewPicture[2][j][i]=R1/R2;
			}

			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;
			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//回收指针
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

		////////////////////////////////////////////////
		Invalidate(1);
	}
}

//最大值滤波
void CImage_ProcessingView::OnMaxfilter()
{

	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG
	GeometricMeanFilter dlg;//统一使用几何均值滤波模板DLG
	//dlg.DoModal();

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//创建新三维数组，用于暂存新图！
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //先H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //后W
			}
		}

		//暂存数组，求取中值
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//数组下标

		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				sz=0;
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//模板内循环
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B[sz]=m_Image.m_pBits[0][j+k][i+kk];
						G[sz]=m_Image.m_pBits[1][j+k][i+kk];
						R[sz]=m_Image.m_pBits[2][j+k][i+kk];
						sz++;
					}
				}
				//泛型算法 返回pair   //注意第二个参数
				NewPicture[0][j][i]=*std::minmax_element(B,B+dlg.m_FileterSize*dlg.m_FileterSize).second;
				NewPicture[1][j][i]=*std::minmax_element(G,G+dlg.m_FileterSize*dlg.m_FileterSize).second;
				NewPicture[2][j][i]=*std::minmax_element(R,R+dlg.m_FileterSize*dlg.m_FileterSize).second;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//回收指针
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

		//////////////////////////////////////////////////////////////////////////
		Invalidate(1);
	}
}

//最小值滤波
void CImage_ProcessingView::OnMinfilter()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG
	GeometricMeanFilter dlg;//统一使用几何均值滤波模板DLG
	//dlg.DoModal();

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//创建新三维数组，用于暂存新图！
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //先H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //后W
			}
		}

		//暂存数组，求取中值
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//数组下标

		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				sz=0;
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//模板内循环
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B[sz]=m_Image.m_pBits[0][j+k][i+kk];
						G[sz]=m_Image.m_pBits[1][j+k][i+kk];
						R[sz]=m_Image.m_pBits[2][j+k][i+kk];
						sz++;
					}
				}
				//泛型算法  返回pair
				NewPicture[0][j][i]=*std::minmax_element(B,B+dlg.m_FileterSize*dlg.m_FileterSize).first;
				NewPicture[1][j][i]=*std::minmax_element(G,G+dlg.m_FileterSize*dlg.m_FileterSize).first;
				NewPicture[2][j][i]=*std::minmax_element(R,R+dlg.m_FileterSize*dlg.m_FileterSize).first;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//回收指针
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

		//////////////////////////////////////////////////////////////////////////
		Invalidate(1);
	}
}

//中点滤波
void CImage_ProcessingView::OnMidpointfilter()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG
	GeometricMeanFilter dlg;//统一使用几何均值滤波模板DLG
	//dlg.DoModal();

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//创建新三维数组，用于暂存新图！
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //先H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //后W
			}
		}

		//暂存数组，求取中值
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//数组下标

		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				sz=0;
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//模板内循环
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B[sz]=m_Image.m_pBits[0][j+k][i+kk];
						G[sz]=m_Image.m_pBits[1][j+k][i+kk];
						R[sz]=m_Image.m_pBits[2][j+k][i+kk];
						sz++;
					}
				}
				//泛型算法  返回pair
				NewPicture[0][j][i]=(*std::minmax_element(B,B+dlg.m_FileterSize*dlg.m_FileterSize).first+*std::minmax_element(B,B+dlg.m_FileterSize*dlg.m_FileterSize-1).second)/2;
				NewPicture[1][j][i]=(*std::minmax_element(G,G+dlg.m_FileterSize*dlg.m_FileterSize).first+*std::minmax_element(G,G+dlg.m_FileterSize*dlg.m_FileterSize-1).second)/2;
				NewPicture[2][j][i]=(*std::minmax_element(R,R+dlg.m_FileterSize*dlg.m_FileterSize).first+*std::minmax_element(R,R+dlg.m_FileterSize*dlg.m_FileterSize-1).second)/2;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//回收指针
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

		//////////////////////////////////////////////////////////////////////////
		Invalidate(1);
	}
}


void CImage_ProcessingView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

//根据鼠标点击位置设立flag
void CImage_ProcessingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	MouseX=point.x;
	MouseY=point.y;
	if (!m_Image.IsNull())//没有图片，不操作
	{
		if (m_Image.Flag==3)//处于RGB划框框状态
		{
			if (MouseX>=m_Image.X&&MouseY>m_Image.Y&&MouseX<(m_Image.X+m_Image.GetWidth())&&MouseY<(m_Image.Y+m_Image.GetHeight()))
			{
				MouseFlag=2;//如果鼠标按在图片区域，立鼠标按下FLAG
			}
		}
		else//移动图片状态
		{
					if (MouseX>=m_Image.X&&MouseY>m_Image.Y&&MouseX<(m_Image.X+m_Image.GetWidth())&&MouseY<(m_Image.Y+m_Image.GetHeight()))
				{
					MouseFlag=1;//如果鼠标按在图片区域，立鼠标按下FLAG
				}
				if (MouseX>=m_Imagecp.X&&MouseY>m_Imagecp.Y&&MouseX<(m_Imagecp.X+m_Imagecp.GetWidth())&&MouseY<(m_Imagecp.Y+m_Imagecp.GetHeight())&&m_Image.Flag==1)
				{
					MouseFlag2=1;//如果鼠标按在源图片区域且原始备份图片处于显示状态，立鼠标按下FLAG2
				}
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

//根据鼠标移动更新显示位置
void CImage_ProcessingView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_Image.Flag==3&&MouseFlag==2)
	{
		if (point.x>=m_Image.X&&point.y>m_Image.Y&&point.x<(m_Image.X+m_Image.GetWidth())&&point.y<(m_Image.Y+m_Image.GetHeight()))
		{
			MouseX2=point.x;
			MouseY2=point.y;
		}
		Invalidate();
	}
	if (MouseFlag==1)
	{
		m_Image.X=m_Image.X+(point.x-MouseX);
		m_Image.Y=m_Image.Y+(point.y-MouseY);
		Invalidate();
		MouseX=point.x;
		MouseY=point.y;
	}
	if (MouseFlag2==1)
	{
		m_Imagecp.X=m_Imagecp.X+(point.x-MouseX);
		m_Imagecp.Y=m_Imagecp.Y+(point.y-MouseY);
		Invalidate();
		MouseX=point.x;
		MouseY=point.y;
	}
	
	CScrollView::OnMouseMove(nFlags, point);
}


void CImage_ProcessingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_Image.Flag==3&&MouseFlag==2)
	{
		m_Image.Flag=4;//为了调用响应,FLAG=0运行函数前半部分，flag为4时获取了两个点，运行程序后半部分
		CImage_ProcessingView::OnRgbcut();//flag为4时获取了两个点，调用程序后半部分
	}
	
	MouseFlag=0;
	MouseFlag2=0;//恢复mouseflag
	CScrollView::OnLButtonUp(nFlags, point);
	
}


BOOL CImage_ProcessingView::OnEraseBkgnd(CDC* pDC)
{
	if (MouseFlag==0&&MouseFlag2==0)
	{
		return CScrollView::OnEraseBkgnd(pDC);
	}
	return TRUE;


}

//恢复图片显示的位置
void CImage_ProcessingView::On32834()
{
	if (!m_Image.IsNull())
	{
		CRect rect;
		GetClientRect(&rect);
		m_Image.X=max(0,rect.right/2-w/2);
		m_Image.Y=max(0,rect.bottom/2-h/2);
		Invalidate(TRUE);
	}
}

//显示源图
void CImage_ProcessingView::OnShoworiginalimage()
{
	if (!m_Image.IsNull())
	{
		m_Image.Flag=1;//设置显示flag
		m_Image.X=m_Image.X+w/2;
		m_Imagecp.X=m_Image.X-w;
		m_Imagecp.Y=m_Image.Y;
	}
	Invalidate(TRUE);
}

//影藏源图
void CImage_ProcessingView::OnHideoriginalimage()
{
	if (!m_Image.IsNull())
	{
		m_Image.Flag=0;//设置显示flag
		
	}
	CImage_ProcessingView::On32834();
	Invalidate(TRUE);
	// TODO: 在此添加命令处理程序代码
}

//图像填零
void CImage_ProcessingView::OnFillzero()
{
	if(m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();


	long i,j;					//i:行循环变量 ,j:列循环变量
	double dTmp;				//临时变量
	//w宽；h高
	long wid =1,hei = 1;		//进行傅立叶变换的宽度和高度
	int widpor=0,heipor=0;		//wid hei :2的幂次数

	//////////计算填零的宽度和高度（2的幂次方）///////////
	while (wid<w)
	{
		wid *= 2;
		widpor++;
	}
	while (hei<h)
	{
		hei *= 2;
		heipor++;
	}
////////////////////////////////添零新Cimage//////////////////////////////////////////
		MyImage_ m_ImageFillZero;
		m_ImageFillZero.m_CImage.Create(wid,hei,24);//局部变量Create
		if(m_ImageFillZero.m_CImage.IsNull()) 
			return;
		int zerow=m_ImageFillZero.m_CImage.GetWidth();
		int zeroh=m_ImageFillZero.m_CImage.GetHeight();

		int nrow=m_ImageFillZero.m_CImage.GetPitch();//获得CImage每一行像素的RGB所占用的存储空间的大小
		BYTE *psrc=(BYTE *)m_ImageFillZero.m_CImage.GetBits();//获得CImage最后一行的像素地址
		/*将三维数组复制进m_CImage*/
		for (int j=0;j<zeroh;j++)
		{
			for (int k=0;k<zerow;k++)
			{
					if (j<h&&k<w)
					{
						psrc[j*nrow+k*3  ]=m_Image.m_pBits[0][j][k];//B
						psrc[j*nrow+k*3+1]=m_Image.m_pBits[1][j][k];//G
						psrc[j*nrow+k*3+2]=m_Image.m_pBits[2][j][k];//R
					}else
					{
						psrc[j*nrow+k*3  ]=0;//B
						psrc[j*nrow+k*3+1]=0;//G
						psrc[j*nrow+k*3+2]=0;//R

					}
			}
		}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////填零新MyImage_////////////////////////////

		int zeronrow=m_ImageFillZero.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
		BYTE *zeropsrc=(BYTE *)m_ImageFillZero.m_CImage.GetBits();//获得m_CImage最后一行的像素地址
		/*创建三维数组并将m_CImage复制进三维数组*/

		m_ImageFillZero.m_pBits= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			m_ImageFillZero.m_pBits[i] = /*(BYTE**)*/new  BYTE*[zeroh];   
		}   


		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<zeroh;j++)         
			{   
				m_ImageFillZero.m_pBits[i][j]=new BYTE[zerow];   
			}
		}


		

		/*创建完成三维数组*/
		for (int j=0;j<zeroh;j++)
		{
			for (int k=0;k<zerow;k++)
			{
				m_ImageFillZero.m_pBits[0][j][k]=zeropsrc[j*nrow+k*3];//B
				m_ImageFillZero.m_pBits[1][j][k]=zeropsrc[j*nrow+k*3+1];//G
				m_ImageFillZero.m_pBits[2][j][k]=zeropsrc[j*nrow+k*3+2];//R
			}
		}
		


//////////////////////////////////销毁源图，copy新图到源图//////////////////////////
		for(int i=0;i<3;i++)   //销毁m_pBits
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete []m_Image.m_pBits[i][j];
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete []m_Image.m_pBits[i];   
		}
		delete []m_Image.m_pBits;
		m_Image.Destroy();
		m_Image.m_CImage.Create(wid,hei,24);
		w=m_Image.m_CImage.GetWidth();//==zerow
		h=m_Image.m_CImage.GetHeight();//==zeroh
	//	int nrow2=m_Image.m_CImage.GetPitch();//==nrow获得CImage每一行像素的RGB所占用的存储空间的大小
		BYTE *psrc2=(BYTE *)m_Image.m_CImage.GetBits();//获得CImage最后一行的像素地址

		for (int j=0;j<zeroh;j++)
		{
			for (int k=0;k<zerow;k++)
			{
					psrc2[j*nrow+k*3  ]=psrc[j*nrow+k*3  ];//B
					psrc2[j*nrow+k*3+1]=psrc[j*nrow+k*3+1];//G
					psrc2[j*nrow+k*3+2]=psrc[j*nrow+k*3+2];//R
			}
		}
		m_Image.m_pBits= new  BYTE **[3];//3个维度；重新分配内存  
		for(int i=0;i<3;i++)  
		{ 
			m_Image.m_pBits[i] = new  BYTE*[zeroh];   
		}   
		for(int i=0;i<3;i++)  
		{          
			for   (int j=0;j<zeroh;j++)         
			{   
				m_Image.m_pBits[i][j]=new BYTE[zerow];   
			}
		}

		for (int j=0;j<zeroh;j++)
		{
			for (int k=0;k<zerow;k++)
			{
				m_Image.m_pBits[0][j][k]=zeropsrc[j*nrow+k*3];//B
				m_Image.m_pBits[1][j][k]=zeropsrc[j*nrow+k*3+1];//G
				m_Image.m_pBits[2][j][k]=zeropsrc[j*nrow+k*3+2];//R
			}
		}
		//回收m_ImageFillZero
		//MyImage_的局部变量不用destroy与回收，其析构函数会自动回收
		
		Invalidate(TRUE);
}

//理想低通滤波
void CImage_ProcessingView::OnLowpass()
{
	if(m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox("请先进行傅立叶变换！");
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();
	//制作模板
	double **modul;
	modul = new double* [w];
	for (int i=0;i<w;i++)
	{
		modul[i] = new double [h];
	}

	CDC *pDC=GetDC();
	Slider sliderdlg(1,pDC,this);//获取D值
	double D;
	if (IDOK==sliderdlg.DoModal())
	{
		D=sliderdlg.Q;
	}else
	{
		return;
	}

	for (int i=0;i<w;i++)
	{
		for (int j=0;j<h;j++)
		{
			if ((pow((double)(i-w/2),(double)2)+pow((double)(j-h/2),(double)2))<=D*D)
			{
				modul[i][j]=1;
			}else{
				modul[i][j]=0;
			}

		}
	}

	//理想低通滤波
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
			FTResult[w *i + j].im=modul[j][i]*FTResult[w *i + j].im;
			FTResult[w *i + j].re=modul[j][i]*FTResult[w *i + j].re;
		}

	//回收指针内存
	for (int i=0;i<w;i++)
	{
		delete []modul[i];
	}
	delete []modul;
	//调用IFFT
	CImage_ProcessingView::OnIfft();
}

//布特沃斯低通滤波
void CImage_ProcessingView::OnBlpf()
{
	if(m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox("请先进行傅立叶变换！");
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();
	//制作模板
	double **modul;
	modul = new double* [w];
	for (int i=0;i<w;i++)
	{
		modul[i] = new double [h];
	}


	CDC *pDC=GetDC();
	Slider sliderdlg(2,pDC,this);//获取D值
	double D;
	if (IDOK==sliderdlg.DoModal())
	{
		D=sliderdlg.Q;
	}else
	{
		return;
	}

	GeometricMeanFilter dlg2(1);//获取N值
	int n;
	if (IDOK==dlg2.DoModal())
	{
		n=dlg2.m_FileterSize;
	}else
	{
		return;
	}


	for (int i=0;i<w;i++)
	{
		for (int j=0;j<h;j++)
		{
			modul[i][j]=1.0/(pow((pow((pow((double)(i-w/2),(double)2)+pow((double)(j-h/2),(double)2)),0.5)/D),(double)2*n)+1);
	
		}
	}

	//低通滤波
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
			FTResult[w *i + j].im=modul[j][i]*FTResult[w *i + j].im;
			FTResult[w *i + j].re=modul[j][i]*FTResult[w *i + j].re;
		}



		//回收指针内存
		for (int i=0;i<w;i++)
		{
			delete []modul[i];
		}
		delete []modul;

		//调用IFFT
		CImage_ProcessingView::OnIfft();
}

//高斯低通
void CImage_ProcessingView::OnGlpf()
{
	if(m_Image.IsNull()) //判断图像是否为空
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}

	if (!FftTime)
	{
		MessageBox("请先进行傅立叶变换！");
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();
	//制作模板
	double **modul;
	modul = new double* [w];
	for (int i=0;i<w;i++)
	{
		modul[i] = new double [h];
	}


	CDC *pDC=GetDC();
	Slider sliderdlg(3,pDC,this);//获取D值
	double D;
	if (IDOK==sliderdlg.DoModal())
	{
		D=sliderdlg.Q;
	}else
	{
		return;
	}

	for (int i=0;i<w;i++)
	{
		for (int j=0;j<h;j++)
		{
			//=exp(-((pow((double)(i-w/2),(double)2)+pow((double)(j-h/2),(double)2))/(double)2*D*D));
			double o1 ,o2,o3;
			o1=(pow((double)(i-w/2),(double)2)+pow((double)(j-h/2),(double)2));
			o2=(double)2*D*D;
			o3=-o1/o2;	
			modul[i][j]=exp(o3);
			//o3=modul[i][j];
		
		}
	}

	//低通滤波
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
			FTResult[w *i + j].im=modul[j][i]*FTResult[w *i + j].im;
			FTResult[w *i + j].re=modul[j][i]*FTResult[w *i + j].re;
		}



		//回收指针内存
		for (int i=0;i<w;i++)
		{
			delete []modul[i];
		}
		delete []modul;

		//调用IFFT
		CImage_ProcessingView::OnIfft();
}

//自适应中值滤波
void CImage_ProcessingView::OnSelfmedianfilter()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG
	GeometricMeanFilter dlg(2);//统一使用滤波模板DLG
	//dlg.DoModal();

	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据

		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误

		//判断是否输入有效的数字
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   输入模板尺寸无效\n请重新输入合适的正奇数值");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//创建新三维数组，用于暂存新图！
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3个维度；分配内存  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //先H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //后W
			}
		}

		//暂存数组，用于求取中值
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//数组下标
		
		
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//设定i，j合理的取值范围，防止超出图片范围
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				//B
				for (int FilterSize=3;FilterSize<=dlg.m_FileterSize;FilterSize++)
				{
								sz=0;
								for (int k=-((FilterSize-1)/2);k<(((FilterSize-1)/2)+1);k++)//模板内循环
								{
									for (int kk=-((FilterSize-1)/2);kk<(((FilterSize-1)/2)+1);kk++)
									{
										B[sz]=m_Image.m_pBits[0][j+k][i+kk];

										sz++;
									}
								}
								for (int i=0;i<9;i++)
								{
									sz=B[i];
								}
								std::sort(B,B+FilterSize*FilterSize);//sort排序,注意第二个参数！！！
								for (int i=0;i<9;i++)
								{
									sz=B[i];
								}

								NewPicture[0][j][i]=B[(FilterSize*FilterSize-1)/2+1];


								sz=B[(FilterSize*FilterSize-1)/2+1];
								sz=B[FilterSize*FilterSize-1];
								sz=B[0];
								if ((B[(FilterSize*FilterSize-1)/2+1]!=B[FilterSize*FilterSize-1])&&(B[(FilterSize*FilterSize-1)/2+1]!=B[0]) )//如果中值非噪声
								{
									if ((m_Image.m_pBits[0][j][i]!=B[FilterSize*FilterSize-1])&&(m_Image.m_pBits[0][j][i]!=B[0]))//如果中心非噪声
									{
										sz=m_Image.m_pBits[0][j][i];
										NewPicture[0][j][i]=m_Image.m_pBits[0][j][i];//输出原值
										
									}
								 	else
									{
										sz=B[(FilterSize*FilterSize-1)/2+1];
										NewPicture[0][j][i]=B[(FilterSize*FilterSize-1)/2+1];//输出中值
									}
									break;
								}
				}

				//G
				for (int FilterSize=3;FilterSize<=dlg.m_FileterSize;FilterSize++)
				{
					sz=0;
					for (int k=-((FilterSize-1)/2);k<(((FilterSize-1)/2)+1);k++)//模板内循环
					{
						for (int kk=-((FilterSize-1)/2);kk<(((FilterSize-1)/2)+1);kk++)
						{
							G[sz]=m_Image.m_pBits[1][j+k][i+kk];
							sz++;
						}
					}
					std::sort(G,G+FilterSize*FilterSize);
					NewPicture[1][j][i]=G[(FilterSize*FilterSize-1)/2+1];
					if ((G[(FilterSize*FilterSize-1)/2+1]!=G[FilterSize*FilterSize-1])&&(G[(FilterSize*FilterSize-1)/2+1]!=G[0]) )//如果中值非噪声
					{
						if ((m_Image.m_pBits[1][j][i]!=G[FilterSize*FilterSize-1])&&(m_Image.m_pBits[1][j][i]!=G[0]))//如果中心非噪声
						{
							NewPicture[1][j][i]=m_Image.m_pBits[1][j][i];//输出原值

						}
						else
						{
							NewPicture[1][j][i]=G[(FilterSize*FilterSize-1)/2+1];//输出中值
						}
						break;
					}
				}

				//R
				for (int FilterSize=3;FilterSize<=dlg.m_FileterSize;FilterSize++)
				{
					sz=0;
					for (int k=-((FilterSize-1)/2);k<(((FilterSize-1)/2)+1);k++)//模板内循环
					{
						for (int kk=-((FilterSize-1)/2);kk<(((FilterSize-1)/2)+1);kk++)
						{
							R[sz]=m_Image.m_pBits[2][j+k][i+kk];
							sz++;
						}
					}
					std::sort(R,R+FilterSize*FilterSize);
					NewPicture[2][j][i]=R[(FilterSize*FilterSize-1)/2+1];
					if ((R[(FilterSize*FilterSize-1)/2+1]!=R[FilterSize*FilterSize-1])&&(R[(FilterSize*FilterSize-1)/2+1]!=R[0]) )//如果中值非噪声
					{
						if ((m_Image.m_pBits[2][j][i]!=R[FilterSize*FilterSize-1])&&(m_Image.m_pBits[2][j][i]!=R[0]))//如果中心非噪声
						{
							NewPicture[2][j][i]=m_Image.m_pBits[2][j][i];//输出原值

						}
						else
						{
							NewPicture[2][j][i]=R[(FilterSize*FilterSize-1)/2+1];//输出中值
						}
						break;
					}
				}



			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//设置进度条！！
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！
	

		//将新图赋予源图
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//新图是没有初始化的!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//回收指针
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//回收内存
			}
		}
		for(int i=0;i<3;i++)  
		{ 
			delete[] NewPicture[i];
		}
		delete [] NewPicture;

		//////////////////////////////////////////////////////////////////////////
		Invalidate(1);
	}
}


void CImage_ProcessingView::OnGaussiannoise()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	Slider dlg(4);//获取标准差值
	double D;

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//获得编辑框用户输入的数据
		D=dlg.Q;
		if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误
	
		w=m_Image.GetWidth();//获取高度和宽度
		h=m_Image.GetHeight();

		std::normal_distribution<> gus_noise(0, D);//第一个参数为平均灰度级，第二个参数为标准差
		std::default_random_engine dre;//引擎
		int n;

		for (int i = 0; i <w; i++)
		{
			for (int j = 0; j <h; j++)
			{
				n=gus_noise(dre);
					if ((n+m_Image.m_pBits[0][j][i])>255)
					{
						m_Image.m_pBits[0][j][i]=255;
					}else
					if ((n+m_Image.m_pBits[0][j][i])<0)
					{
						m_Image.m_pBits[0][j][i]=0;
					}else
						{
							m_Image.m_pBits[0][j][i]+=n;
					}


					if ((n+m_Image.m_pBits[1][j][i])>255)
					{
						m_Image.m_pBits[1][j][i]=255;
					}else
					if ((n+m_Image.m_pBits[1][j][i])<0)
					{
						m_Image.m_pBits[1][j][i]=0;
					}else{
						m_Image.m_pBits[1][j][i]+=n;
					}


					if ((n+m_Image.m_pBits[2][j][i])>255)
					{
						m_Image.m_pBits[2][j][i]=255;
					}else
					if ((n+m_Image.m_pBits[2][j][i])<0)
					{
						m_Image.m_pBits[2][j][i]=0;
					}else{
							m_Image.m_pBits[2][j][i]+=n;
					}
			}
			}
			Invalidate(1);
	}
}

//显示RGB分量
void CImage_ProcessingView::OnShowrgb()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		return;
	}
	m_Image.Flag=0;	//恢复FLAG


	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	RGBSheet propSheet(this,0,"RGB表单");//pv,int flag,名称
	propSheet.DoModal();


}


void CImage_ProcessingView::OnShowhsi()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		return;
	}
	m_Image.Flag=0;	//恢复FLAG


	w=m_Image.GetWidth();//获取高度和宽度
	h=m_Image.GetHeight();

	RGBSheet propSheet(this,1,"HSI表单");//pv,int flag,名称
	propSheet.DoModal();

}

//RGB均衡化
void CImage_ProcessingView::OnRgbhistogram()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		return;
	}
	m_Image.Flag=0;	//恢复FLAG

	//B分量均衡化
	//////////////////////////////////////////////////////////////////////////////
	m_Image.GetHistgran();//获取概率直方图
	BYTE *lpNewDIBBits;

	long i,j;		//循环计数
	BYTE pixel;		//像素值
	//float fPro[256];	//源图概率密度变量probability
	float temp[256];
	int   nRst[256];//映射表
	int nrow=m_Image.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小

	w=m_Image.GetWidth();
	h=m_Image.GetHeight();
	CImage image3;			//缓存图
	image3.Create(w,h,24);	//Create后需要delete
	lpNewDIBBits=(BYTE *)image3.GetBits();//获得image3最后一行的像素地址

	for (i=0;i<256;i++)
	{
		if(0==i)
		{
			temp[0]=m_Image.probability[0];
		}
		else
		{
			temp[i]=temp[i-1]+m_Image.probability[i];
		}
	}

	for(i=0;i<256;i++)
	{
		nRst[i]=(int)(255.0f * temp[i] + 0.5f);
	}
	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			pixel = m_Image.m_pBits[0][j][i];
			lpNewDIBBits[j*nrow+i*3]=(BYTE)(nRst[pixel]);//中转，没什么用

			m_Image.m_pBits[0][j][i]=lpNewDIBBits[j*nrow+i*3];//注意是使用m_pBits
		}
	}
	//G分量均衡
	//////////////////////////////////////////////////////////////////////////
	auto tmp=m_Image.m_pBits[0];
	m_Image.m_pBits[0]=m_Image.m_pBits[1];
	m_Image.m_pBits[1]=tmp;  //交换G 、B指针

	m_Image.GetHistgran(); //获取概率直方图

	nrow=m_Image.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小

	for (i=0;i<256;i++)
	{
		if(0==i)
		{
			temp[0]=m_Image.probability[0];
		}
		else
		{
			temp[i]=temp[i-1]+m_Image.probability[i];
		}
	}

	for(i=0;i<256;i++)
	{
		nRst[i]=(int)(255.0f * temp[i] + 0.5f);
	}
	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			pixel = m_Image.m_pBits[0][j][i];
			lpNewDIBBits[j*nrow+i*3]=(BYTE)(nRst[pixel]);//中转，没什么用
			m_Image.m_pBits[0][j][i]=lpNewDIBBits[j*nrow+i*3];//注意是使用m_pBits
		}
	}

	tmp=m_Image.m_pBits[0];
	m_Image.m_pBits[0]=m_Image.m_pBits[1];
	m_Image.m_pBits[1]=tmp;  //交换回来G 、B指针

	//R分量均衡
	//////////////////////////////////////////////////////////////////////////
	tmp=m_Image.m_pBits[0];
	m_Image.m_pBits[0]=m_Image.m_pBits[2];
	m_Image.m_pBits[2]=tmp;  //交换R、B指针

	m_Image.GetHistgran(); //获取概率直方图
	nrow=m_Image.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小

	for (i=0;i<256;i++)
	{
		if(0==i)
		{
			temp[0]=m_Image.probability[0];
		}
		else
		{
			temp[i]=temp[i-1]+m_Image.probability[i];
		}
	}

	for(i=0;i<256;i++)
	{
		nRst[i]=(int)(255.0f * temp[i] + 0.5f);
	}
	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			pixel = m_Image.m_pBits[0][j][i];
			lpNewDIBBits[j*nrow+i*3]=(BYTE)(nRst[pixel]);//中转，没什么用
			m_Image.m_pBits[0][j][i]=lpNewDIBBits[j*nrow+i*3];//注意是使用m_pBits
		}
	}

	tmp=m_Image.m_pBits[0];
	m_Image.m_pBits[0]=m_Image.m_pBits[2];
	m_Image.m_pBits[2]=tmp;  //交换回来R 、B指针

	Invalidate(1);
}

//I分量均衡化
void CImage_ProcessingView::OnIhistogram()
{

	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		return;
	}
	m_Image.Flag=0;	//恢复FLAG
	using namespace std;//使用容器
	//转换为HSI
	vector<vector<vector<double>>> HSI;
	vector<vector<double>> vec;
	HSI.push_back(vec);HSI.push_back(vec);HSI.push_back(vec);
	//////////////////////////////////
	for (int i = 0; i <w; i++)
	{
		vector<double> vec;      //覆盖vec
		HSI[0].push_back(vec);//H
		HSI[1].push_back(vec);//S
		HSI[2].push_back(vec);//I
		for (int j = 0; j <h; j++)
		{
			double tmp;
			int R=m_Image.m_pBits[2][j][i];
			int G=m_Image.m_pBits[1][j][i];
			int B=m_Image.m_pBits[0][j][i];

			tmp=acos((double)(2*R-G-B) / (0.001+ 2*sqrt((double)(R-G)*(R-G) + (double)(R-B)*(G-B))));//0.001人为添加，防止除数为零
			if (B<=G)
			{
				tmp=tmp;
			}else{
				tmp=2*3.141592654-tmp;
			}
			HSI[0][i].push_back(std::move(tmp));

			tmp=(double)1 - ((double)3*(double)min(R,G,B)) / (double)(R+G+B);
			HSI[1][i].push_back(std::move(tmp));

			tmp=(R+G+B)/3;
			HSI[2][i].push_back(std::move(tmp));
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//直方图均衡化
	for (int i = 0; i <w; i++)
	{
		for (int j = 0; j <h; j++)
		{
			m_Image.m_pBits[0][j][i]=HSI[2][i][j];//将vectorI分量赋值图片第一维度
		}
	}
	m_Image.GetHistgran();//获取概率直方图
	BYTE *lpNewDIBBits;

	long i,j;		//循环计数
	BYTE pixel;		//像素值
	double temp[256];
	double   nRst[256];//映射表
	int nrow=m_Image.m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小

	w=m_Image.GetWidth();
	h=m_Image.GetHeight();
	CImage image3;			//缓存图
	image3.Create(w,h,24);	//Create后需要delete
	lpNewDIBBits=(BYTE *)image3.GetBits();//获得image3最后一行的像素地址

	for (i=0;i<256;i++)
	{
		if(0==i)
		{
			temp[0]=m_Image.probability[0];
		}
		else
		{
			temp[i]=temp[i-1]+m_Image.probability[i];
		}
	}

	for(i=0;i<256;i++)
	{
		nRst[i]=(255.0f * temp[i] + 0.5f);
	}
	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			pixel = m_Image.m_pBits[0][j][i];
			HSI[2][i][j]=nRst[pixel];
		
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//转化为RGB
	double R,G,B;
	for (int i = 0; i <w; i++)
	{
		for (int j = 0; j <h; j++)
		{
			double tmp;
			double H=HSI[0][i][j];
			double S=HSI[1][i][j];
			double I=HSI[2][i][j];
			if (0<=H*(double)180/(double)3.1415926&&H*(double)180/(double)3.1415926<120)
			{
				B=I*(1-S);
				R=I*(1+(S*cos(H))/(cos(60*(double)3.1415926/(double)180-H)));
				G=3*I-(R+B);
			}else if (120<=H*(double)180/(double)3.1415926&&H*(double)180/(double)3.1415926<240)
			{
				H=H-120.*(double)3.1415926/(double)180;
				R=I*(1-S);
				G=I*(1+(S*cos(H))/(cos(60*(double)3.1415926/(double)180-H)));
				B=3*I-(R+G);
			
			}else if(240<=H*(double)180/(double)3.1415926&&H*(double)180/(double)3.1415926<360)
			{
				H=H-240.*(double)3.1415926/(double)180;
				G=I*(1-S);
				B=I*(1+(S*cos(H))/(cos(60*(double)3.1415926/(double)180-H)));
				R=3*I-(B+G);
			}
			
			m_Image.m_pBits[2][j][i]=R>255? 255 : R<0? 0:R;
			m_Image.m_pBits[1][j][i]=G>255? 255 : G<0? 0:G;
			m_Image.m_pBits[0][j][i]=B>255? 255 : B<0? 0:B;

		}
		((CMainFrame *)GetParent())->m_progress.SetPos(100*i/w);//设置进度条！！
	}
	((CMainFrame *)GetParent())->m_progress.SetPos(0);//恢复进度条！！

	Invalidate(1);
}

//RGB图像分割
void CImage_ProcessingView::OnRgbcut()
{
	if(m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		return;
	}

	if (m_Image.Flag==0)//前半段获取两点
	{
		m_Image.Flag=3;	//设立FLAG
		using namespace std;//使用容器
		MouseX =0;
		MouseY = 0;
		MouseX2 =0;
		MouseY2 =0;
		Invalidate(TRUE);
	}
	else if (m_Image.Flag==4)//后半段处理图片
	{
		auto minX=min(MouseX,MouseX2)-m_Image.X,maxX=max(MouseX,MouseX2)-m_Image.X;
		auto minY=min(MouseY,MouseY2)-m_Image.Y,maxY=max(MouseY,MouseY2)-m_Image.Y;

		double R(0),G(0),B(0);//值初始化
		double Rstand(0),Gstand(0),Bstand(0);
		double Rmin(0),Rmax(0),Gmin(0),Gmax(0),Bmin(0),Bmax(0);
		auto size=(maxX-minX+1)*(maxY-minY+1);//最下和最右列加入计算，可以处理单列或单行的极限情况
		for (int i =minX; i <=maxX; i++)
		{
			for (int j = minY; j <=maxY; j++)
			{
				R+=(double)m_Image.m_pBits[2][j][i]/(double)size;//防止溢出，直接除以size
				G+=(double)m_Image.m_pBits[1][j][i]/(double)size;
				B+=(double)m_Image.m_pBits[0][j][i]/(double)size;
			}
		}
		for (int i =minX; i <=maxX; i++)
		{
			for (int j = minY; j <=maxY; j++)
			{
				Rstand += ((double)m_Image.m_pBits[2][j][i]-R)*((double)m_Image.m_pBits[2][j][i]-R);
				Gstand += ((double)m_Image.m_pBits[1][j][i]-G)*((double)m_Image.m_pBits[1][j][i]-G);
				Bstand += ((double)m_Image.m_pBits[0][j][i]-B)*((double)m_Image.m_pBits[0][j][i]-B);
			}
		}
		Rstand = sqrt(Rstand/(double)size);//标准差
		Gstand = sqrt(Gstand/(double)size);
		Bstand = sqrt(Bstand/(double)size);
		//划定分割区域
		Rmin=R-1.5*Rstand;  Rmax=R+1.5*Rstand;
		Gmin=G-1.5*Gstand;  Gmax=G+1.5*Gstand;
		Bmin=B-1.5*Bstand;  Bmax=B+1.5*Bstand;

		//重用R G B变量
		for (int i = 0; i <w; i++)
		{
			for (int j = 0; j <h; j++)
			{
				R = (double)m_Image.m_pBits[2][j][i];
				G = (double)m_Image.m_pBits[1][j][i];
				B = (double)m_Image.m_pBits[0][j][i];

				if (R>=Rmin&&R<=Rmax&&G>=Gmin&&G<=Gmax&&B>=Bmin&&B<=Bmax)
				{
					;
				}else
				{
					m_Image.m_pBits[2][j][i]=169;
					m_Image.m_pBits[1][j][i]=169;
					m_Image.m_pBits[0][j][i]=169;
				}
			}
		}
		///设置黑色指示边框
		for (int i =minX; i <=maxX; i++)
		{
			m_Image.m_pBits[2][minY][i]=0;
			m_Image.m_pBits[1][minY][i]=0;
			m_Image.m_pBits[0][minY][i]=0;
			m_Image.m_pBits[2][maxY][i]=0;
			m_Image.m_pBits[1][maxY][i]=0;
			m_Image.m_pBits[0][maxY][i]=0;
		}
		for (int j = minY; j <=maxY; j++)
		{
			m_Image.m_pBits[2][j][minX]=0;
			m_Image.m_pBits[1][j][minX]=0;
			m_Image.m_pBits[0][j][minX]=0;
			m_Image.m_pBits[2][j][maxX]=0;
			m_Image.m_pBits[1][j][maxX]=0;
			m_Image.m_pBits[0][j][maxX]=0;
		}

		m_Image.Flag=0;//必须置0，和前半部分形成可循环状态
		CImage_ProcessingView::OnShoworiginalimage();//显示源图进行对比
		//Invalidate(1);
	}

}


BOOL CImage_ProcessingView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (m_Image.Flag==3)
	{
		HCURSOR hCur  =  LoadCursor( NULL  , IDC_CROSS ) ;
		::SetCursor(hCur);
	}else
	{
		return CScrollView::OnSetCursor(pWnd, nHitTest, message);
	}
	
}


void CImage_ProcessingView::OnMyimg_PROCESSING()
{
	// TODO: 在此添加命令处理程序代码

}



