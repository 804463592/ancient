
// Image_ProcessingView.cpp : CImage_ProcessingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CImage_ProcessingView ����/����
//ʹ����github

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
	// TODO: �ڴ˴���ӹ������

}

CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView ����
void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	/////////////////////////////////////////���ñ�����ɫ
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
	
	//////////////////////////////////////////��ͼ
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!m_Image.IsNull())
	{
		//CRect rect;
		//GetClientRect(&rect);
		//m_Image.X=rect.right/2-w/2;
		//m_Image.Y=rect.bottom/2-h/2;//�ػ�ʱ����λ��

		if(m_Image.Flag==0)//FLAGΪ0
		{
				if (m_Image.GetWidth()>rect1.right)///////
				{
					rect1.right=m_Image.GetWidth();
				}
				if (m_Image.GetHeight()>rect1.bottom)
				{
					rect1.bottom=m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
				}
				pDC->FillSolidRect(rect1,RGB(128,128,128)); //�������ñ�����ɫ


				m_Image.Draw(pDC->m_hDC,m_Image.X,m_Image.Y);//xy��ʾ
			
		}
		else if (m_Image.Flag==1)//FLAG��ʾԴͼ
		{
			if (m_Image.GetWidth()>rect1.right)
			{
				rect1.right=m_Image.GetWidth();
			}
			if (m_Image.GetHeight()>rect1.bottom)
			{
				rect1.bottom=m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}
			pDC->FillSolidRect(rect1,RGB(128,128,128)); //�������ñ�����ɫ
			
			m_Imagecp.Draw(pDC->m_hDC,m_Imagecp.X,m_Imagecp.Y);//��ʾԴͼ
			pDC->TextOut(m_Imagecp.X+m_Imagecp.GetWidth()/2,m_Imagecp.Y-30,"ԭʼͼ");
			m_Image.Draw(pDC->m_hDC,m_Image.X,m_Image.Y);//xy��ʾ
			pDC->TextOut(m_Image.X+m_Image.GetWidth()/2,m_Image.Y-30,"��ǰͼ");

		}
		else if(m_Image.Flag==2)//�²���ͼ��
		{
			if (m_Image.GetWidth()>rect1.right)///////
			{
				rect1.right=m_Image.GetWidth();
			}
			if (m_Image.GetHeight()>rect1.bottom)
			{
				rect1.bottom=m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}
	
			pDC->FillSolidRect(rect1,RGB(128,128,128)); //�������ñ�����ɫ

			
			image2.Draw(pDC->m_hDC,m_Image.X,m_Image.Y);
		}
		else if (m_Image.Flag==3)//rgb�ָ�ǰ��ȡ����
		{
			if (m_Image.GetWidth()>rect1.right)///////
			{
				rect1.right=m_Image.GetWidth();
			}
			if (m_Image.GetHeight()>rect1.bottom)
			{
				rect1.bottom=m_Image.GetHeight();////���ͼƬ�ȿͻ��������󱳾�����
			}
			pDC->FillSolidRect(rect1,RGB(169,169,169)); //�������ñ�����ɫ

			m_Image.Draw(pDC->m_hDC,m_Image.X,m_Image.Y);//xy��ʾ

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
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImage_ProcessingView ��ӡ


void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CImage_ProcessingView ���

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImage_ProcessingView ��Ϣ�������


void CImage_ProcessingView::OnFileOpen()
{
	BOOL OpenFlage=1;//��¼�Ƿ�ɹ�����ͼƬ

	m_Image.Flag=0;//�ָ�����FLAG

	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if(IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if(!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		if(!m_Imagecp.IsNull()) m_Imagecp.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������

		while(S_FALSE ==m_Image.Load(dlg.GetPathName()))
		{
			MessageBox("�򿪵Ĳ���24λ���ɫͼ��");
			if(IDCANCEL == dlg.DoModal()) //���´�ͼƬ�����ȡ��������ѭ��   
			{
				OpenFlage=0;//û�д�ͼƬ������ѭ��
				break;
			}
		}//ȷ����24λ��ɫͼƬ
		m_Imagecp.Load(dlg.GetPathName());//��ԭʼͼƬ����


		//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
		if (1==OpenFlage)
		{
			CSize sizeTotal;
			w=m_Image.GetWidth();
			h=m_Image.GetHeight();


			CRect rect;
			GetClientRect(&rect);
			m_Image.X=max(0,rect.right/2-w/2);
			m_Image.Y=max(0,rect.bottom/2-h/2);//������ʾͼƬ�����Ͻ�λ��
			m_Imagecp.X=max(0,rect.right/2-w/2);
			m_Imagecp.Y=max(0,rect.bottom/2-h/2);//������ʾͼƬ�����Ͻ�λ��
			
			sizeTotal.cx =w;
			sizeTotal.cy =h;
			SetScrollSizes(MM_TEXT, sizeTotal);
		}

		//Window_Image_w=m_Image.GetWidth();//���ͼƬ�ĳ�ʼ��С��Ϊ�Ŵ���С������׼��
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //ǿ�Ƶ���ONDRAW����
	}
}


void CImage_ProcessingView::OnGray()
{
	// TODO: �ڴ���������������
	if(m_Image.IsNull()) 
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;//�ָ�����FLAG
	
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

	//((CMainFrame *)GetParent())->m_progress.SetPos(50);//���ý���������

	Invalidate(1); //ǿ�Ƶ���ONDRAW����
}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) {
		MessageBox(_T("�㻹û�д�һ��Ҫ�����ͼ���ļ���"));
		return;
	}
	CString strFilter;
	strFilter ="BMP λͼ�ļ�|*.bmp|JPEG ͼ���ļ�|*.jpg|GIF ͼ���ļ�|*.gif|PNG ͼ���ļ�|*.png||";  
	
	//	strFilter ="�����ļ�|*.*||";   

	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if ( IDOK != dlg.DoModal()) 
		return;
	// ����û�û��ָ���ļ���չ������Ϊ�����һ��
	CString strFileName;
	CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;   //  ����ļ���
	//if(dlg.m_ofn.nFileExtension == 0)     //����ļ���չ��
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
	// ͼ�񱣴�
	HRESULT hResult;
	if (1==m_Image.Flag)
	{
		hResult = image2.Save(strFileName);//�����²�����ͼƬ
	}
	else
	{
		hResult = m_Image.Save(strFileName);//����ԭʼͼƬ
	}
	if (FAILED(hResult))
	{
		MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;//�ָ�����FLAG

	int w=m_Image.GetWidth();//���ͼ��Ŀ��
	int h=m_Image.GetHeight();//���ͼ��ĸ߶�
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			m_Image.m_pBits[0][j][k]=0;//B   ��ѭ������ͼ�������ֵ����������ɫ��������ɫ������Ϊ0��ͼ���ֻʣ�º�ɫ������
			m_Image.m_pBits[1][j][k]=0;//G


		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}



void CImage_ProcessingView::OnImageProcessing()
{
	// TODO: �ڴ���������������
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		MessageBox(_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;//�ָ�����FLAG

	int w=m_Image.GetWidth();//���ͼ��Ŀ��
	int h=m_Image.GetHeight();//���ͼ��ĸ߶�
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			m_Image.m_pBits[0][j][k]=0;//B   ��ѭ������ͼ�������ֵ����������ɫ����/��ɫ����/��ɫ������Ϊ0�����ͼ����ɴ���ɫ
			m_Image.m_pBits[1][j][k]=0;//G
			m_Image.m_pBits[2][j][k]=0;//R


		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}

//ͼƬ���
void CImage_ProcessingView::OnDoubleimage()
{
	Times++;
	float k=Times;
	//k=(k-1)/k;
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
			//_T("���ȴ�һ��ͼ��"));
		 return;
	}

	m_Image.Flag=0;//�ָ�����FLAG
	w=m_Image.GetWidth();//��õ�һ��ͼ��Ŀ��
	h=m_Image.GetHeight();//���ͼ��ĸ߶�

	MyImage_ Image_Second;
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if(IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if(!Image_Second.IsNull()) Image_Second.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������

		Image_Second.Load(dlg.GetPathName());//���öԻ����GetPathName���ͼƬ��λ�ã����ҵ���Load����ͼƬ


		if(Image_Second.IsNull()) return;
		if (w!=Image_Second.GetWidth()||h!=Image_Second.GetHeight())//�ж�����ͼ���С�Ƿ�һ��
		{
			MessageBox(_T("����ͼ���С��һ�£�"));
			return;
		}
		for (int j=0; j<h; j++)
		{
			for (int i=0; i<w; i++)//����ͼ��������Ӳ���
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

//��ͼƬ�²��������ͷֱ���
void CImage_ProcessingView::OnDownsample()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if(!image2.IsNull())//���ǰ���Ѿ��²������ˣ�������پɵ��²��������ͼƬ
	{
		image2.Destroy();
	}
	
	w=m_Image.GetWidth();//���ͼ��Ŀ��
	h=m_Image.GetHeight();//���ͼ��ĸ߶�

	DownTimes dlg;//�����Ի������
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

		while(dlg.m_downtimes<=0||pow((double)2,(int)dlg.m_downtimes)>w||pow((double)2,(int)dlg.m_downtimes)>h)//�ж��Ƿ�������Ч������
		{
			MessageBox("	  ������Ч\n������������Ч���²�������");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		m_Image.Flag=2;//��¼FLAG

		int T=pow((double)2,(int)dlg.m_downtimes);//�²�������*2


		//CImage image2;
		image2.Create(w/T,h/T,24);//ȫ�ֱ���Create����Ҫdelete

		int nrow=image2.GetPitch();//���CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
		BYTE *psrc=(BYTE *)image2.GetBits();//���CImage���һ�е����ص�ַ
		/*����ά���鸴�ƽ�m_CImage*/
		for (int j=0;j<h/T;j++)
		{
			for (int k=0;k<w/T;k++)
			{
				psrc[j*nrow+k*3]=m_Image.m_pBits[0][j*T][k*T];//B
				psrc[j*nrow+k*3+1]=m_Image.m_pBits[1][j*T][k*T];//G
				psrc[j*nrow+k*3+2]=m_Image.m_pBits[2][j*T][k*T];//R

			}
		}
	/*����ά���鸴�ƽ�image2*/
	Invalidate(1);//ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
	}
	
	
}


void CImage_ProcessingView::OnDowngray()
{
	if(m_Image.IsNull()) 
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;//�ָ�����FLAG

	///�ж��Ƿ�Ϊ��ɫͼƬ�������򵯳����ʾ���///
	if(!(m_Image.m_pBits[0][0][0]==m_Image.m_pBits[1][0][0]&&m_Image.m_pBits[1][0][0]==m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL==warn.DoModal())
		{
			return;
		}
	}

	OnGray();//����ǲ�ɫͼ����ת��Ϊ�Ҷ�ͼ

	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();


	CLowGray dlg;
	if (IDOK==dlg.DoModal())
	{
		UpdateData();
		while (dlg.LowGray<=0||dlg.LowGray>256)
		{
			MessageBox("�Ҷȼ���Ч������������Ҷȼ���");
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
		int Time=256/dlg.LowGray;//�ж��²�������  (������ӽ��ĻҶȼ�)

			for (int j=0;j<h;j++)
				{
					for (int k=0;k<w;k++)
						{
							BYTE b=m_Image.m_pBits[0][j][k];
							BYTE g=m_Image.m_pBits[1][j][k];
							BYTE r=m_Image.m_pBits[2][j][k];

			//////////
			int ave=(b+g+r)/3;//���Ž��ʹ������ӣ����ϸı�Ҷ�ֵ
			////ave������int����////

			if(ave>255/2)//���лҶȱ任�㷨
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
			Invalidate(1); //ǿ�Ƶ���ONDRAW����
	}
	//Times=1;//�ָ�Timees��ֵ��ͼƬ���Ҫ�ã�
	
}

//���
void CImage_ProcessingView::OnDoubleimage2()
{
	// TODO: �ڴ���������������
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;//�ָ�����FLAG
	int w=m_Image.GetWidth();//��õ�һ��ͼ��Ŀ��
	int h=m_Image.GetHeight();//���ͼ��ĸ߶�

	MyImage_ Image_Second;
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if(IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if(!Image_Second.IsNull()) Image_Second.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������

		Image_Second.Load(dlg.GetPathName());//���öԻ����GetPathName���ͼƬ��λ�ã����ҵ���Load����ͼƬ


		if(Image_Second.IsNull()) return;
		if (w!=Image_Second.GetWidth()||h!=Image_Second.GetHeight())//�ж�����ͼ���С�Ƿ�һ��
		{
			MessageBox(_T("����ͼ���С��һ�£�"));
			return;
		}
		for (int j=0; j<h; j++)
			for (int i=0; i<w; i++)//����ͼ��������Ӳ���
			{
				m_Image.m_pBits[0][j][i]=m_Image.m_pBits[0][j][i]-Image_Second.m_pBits[0][j][i];
				m_Image.m_pBits[1][j][i]=m_Image.m_pBits[1][j][i]-Image_Second.m_pBits[1][j][i];
				m_Image.m_pBits[2][j][i]=m_Image.m_pBits[2][j][i]-Image_Second.m_pBits[2][j][i];
			}
			Invalidate(1);
	}
	// TODO: �ڴ���������������
}

//============================================
//ֱ��ͼͳ��
//��������� ��
//����ֵ��	�ޣ�ȫ�ֱ��� float *probability ��ʾ�ֲ������ܶȣ�
//===============================================
void CImage_ProcessingView::OnHistogram()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
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
	OnGray();//����ǲ�ɫͼ����ת��Ϊ�Ҷ�ͼ

	m_Image.GetHistgran();//���ó�Ա����,ͳ��ֱ��ͼ

	//Dialg��ͼ
	HistDrawDialg dlg(this);
	dlg.DoModal();

	//ȡ������HISTDRAW������Dialg
	//m_Image.Flag=2;//����FLAG
	Invalidate(1);	
}

//====================================================
//�������ܣ�ֱ��ͼ���⻯
//������� ����  ����Ӧ����
//ֱ�ӽ�Դͼ���ݸ���
//====================================================
void CImage_ProcessingView::OnHistogram2()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	///�ж��Ƿ�Ϊ��ɫͼƬ�������򵯳����ʾ���///
	if(!(m_Image.m_pBits[0][0][0]==m_Image.m_pBits[1][0][0]&&m_Image.m_pBits[1][0][0]==m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL==warn.DoModal())
		{
			return;
		}
	}
	OnGray();//����ǲ�ɫͼ����ת��Ϊ�Ҷ�ͼ
	m_Image.GetHistgran();//��ȡ����ֱ��ͼ
	BYTE *lpNewDIBBits;

	long i,j;		//ѭ������
	BYTE pixel;		//����ֵ
	//float fPro[256];	//Դͼ�����ܶȱ���probability
	float temp[256];
	int   nRst[256];//ӳ���
	int nrow=m_Image.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	
	//BYTE *lpDIBBits=(BYTE *)m_Image.m_CImage.GetBits();//���Դͼ����ʼλ��

	w=m_Image.GetWidth();
	h=m_Image.GetHeight();

	//hNewDIBBits=LocalAlloc(LHND,w*h);//һά���飬���ֵ������������
	CImage image3;			//����ͼ
	image3.Create(w,h,24);	//Create����Ҫdelete
	lpNewDIBBits=(BYTE *)image3.GetBits();//���image3���һ�е����ص�ַ

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
			lpNewDIBBits[j*nrow+i*3]=(BYTE)(nRst[pixel]);//��ת��ûʲô��
			

			m_Image.m_pBits[0][j][i]=lpNewDIBBits[j*nrow+i*3];//ע����ʹ��m_pBits
			m_Image.m_pBits[1][j][i]=lpNewDIBBits[j*nrow+i*3];//��ʹ��CImage��Getbits
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
//	int nrow=m_Image.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
//	BYTE *psrc=(BYTE *)m_Image.m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ
//	/*������ά���鲢��m_CImage���ƽ���ά����*/
//
//	/*���������ά����*/
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
//	// TODO: �ڴ���������������
//	}
//	Invalidate();
//}


//ֱ��ͼ�涨��
void CImage_ProcessingView::OnHistmatch()
{
	BOOL OpenFlage=1;//��¼�Ƿ�ɹ�����ͼƬ

	//��ȡĿ��ֱ��ͼ
	MyImage_  MatchImage;
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if(IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if(!MatchImage.IsNull()) MatchImage.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������

		while(S_FALSE ==MatchImage.Load(dlg.GetPathName()))
		{
			MessageBox("�򿪵Ĳ���24λ���ɫͼ��");
			if(IDCANCEL == dlg.DoModal()) //���´�ͼƬ�����ȡ��������ѭ��   
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
	MatchImage.GetHistgran();//��ȡMatch����ֱ��ͼ




	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	//�ж��Ƿ�Ϊ��ɫͼƬ�������򵯳����ʾ���//
	if(!(m_Image.m_pBits[0][0][0]==m_Image.m_pBits[1][0][0]&&m_Image.m_pBits[1][0][0]==m_Image.m_pBits[2][0][0]))
	{
		WarnDlg warn;
		if (IDCANCEL==warn.DoModal())
		{
			return;
		}
	}

	m_Image.GetHistgran();//��ȡ����ֱ��ͼ
	OnGray();//����ǲ�ɫͼ����ת��Ϊ�Ҷ�ͼ

	



	float temp[256];
	long i,j;		//ѭ������
	BYTE pixel;		//����ֵ
	int   nMap[256];//����ӳ���
	int   npMap[256];//�涨ֱ��ͼ�ľ��⻯��ӳ���
	float fpPro[256];
	float  k=1.0f/256;
	for (i=0;i<256;i++)
	{
		fpPro[i]=MatchImage.probability[i];//�涨���ĸ���
	}
	int bGray=256;//�涨���ĻҶȼ�

	w=m_Image.GetWidth();
	h=m_Image.GetHeight();


	//����Դͼ�ۼ�ֱ��ͼ m_Image.probability
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

	//����涨����ۼ�ֱ��ͼ
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

	//����涨������ �����⻯��ӳ���npMap
	for(i=0;i<bGray;i++)
	{
		npMap[i]=(int)((bGray-1) * fpPro[i] + 0.5f);//�����1��
	}

	//����ӳ���ϵ
	for (i=0;i<256;i++)
	{
		int m=0;
		float min_value=1.0f;//float����С��ֵ
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
				m=j;//��¼��Сֵλ��
				min_value=now_value;//���ϸ�����С��ֵ
			}
		}
		nMap[i]=npMap[m];//�����Ҷ�ӳ���
	}

	//�Ը����ؽ���ֱ��ͼ�涨��ӳ�䴦��
	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			pixel = m_Image.m_pBits[0][j][i];

			m_Image.m_pBits[0][j][i]=(BYTE)(nMap[pixel]);//ע����ʹ��m_pBits
			m_Image.m_pBits[1][j][i]=(BYTE)(nMap[pixel]);//��ʹ��CImage��Getbits
			m_Image.m_pBits[2][j][i]=(BYTE)(nMap[pixel]);
		}
	}
	Invalidate(1);
}

//====================================================
//�������ܣ����ָ�����ʵĽ�������
//������� ��pepper��salt����
//ֱ�ӽ�Դͼ���ݸ���
//====================================================
void CImage_ProcessingView::OnSalt()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	PepperSalt dlg;//�����Ի������
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_pepper<0||dlg.m_pepper>1||dlg.m_salt<0||dlg.m_salt>1||
						(dlg.m_salt+dlg.m_pepper)>1)
		{
			MessageBox("	 ������Ч\n������������Ч����������");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	float p_a=dlg.m_pepper;//��ȡ������ĸ���,p_a(��),p_b���ף�
	float p_b=dlg.m_salt;


	float P_Sum=p_a+p_b;
	float xishu=1/P_Sum;
	float p_a_1=p_a*xishu;
	for (int i = 0; i <w; i++)
		for (int j = 0; j <h; j++)
		{
			if(rand()/32767.0<P_Sum)//ָ������rand()��������Ľ���1-32767����
			{
				if(rand()/32767.0<p_a_1)
					{	m_Image.m_pBits[0][j][i]=1;         //�����ص���ʾΪ��ɫ
						m_Image.m_pBits[1][j][i]=1;       
						m_Image.m_pBits[2][j][i]=1; 

				}
				else
				{
					m_Image.m_pBits[0][j][i]=255;         //�����ص���ʾΪ��ɫ
					m_Image.m_pBits[1][j][i]=255;       
					m_Image.m_pBits[2][j][i]=255;
				}

			}
		}
		Invalidate(1);
	}
	
}

//������ֵ�˲�
void CImage_ProcessingView::OnMeanfilter()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	GeometricMeanFilter dlg;//ͳһʹ�ü��ξ�ֵ�˲�ģ��DLG
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

	long B=0,G=0,R=0;//�ۼӴ洢��ֻBYTE���ͻ�������

	//��������ά���飬�����ݴ���ͼ����û�г�ʼ����
	BYTE *** NewPicture;
	NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
	for(int i=0;i<3;i++)  
	{ 
		NewPicture[i] = new  BYTE*[h];   //��H
	}   
	for(int i=0;i<3;i++)   
	{          
		for   (int j=0;j<h;j++)         
		{   
			NewPicture[i][j]=new BYTE[w];   //��W
		}
	}


		//��ֵ�˲�
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				R=0,G=0,B=0;//Ϊ��ģ������
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//ģ����ѭ��
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B+=m_Image.m_pBits[0][j+k][i+kk];//�ۼ����
						G+=m_Image.m_pBits[1][j+k][i+kk];//�ۼ����
						R+=m_Image.m_pBits[2][j+k][i+kk];//�ۼ����
					}
				}
				NewPicture[0][j][i]=B/(dlg.m_FileterSize*dlg.m_FileterSize);
				NewPicture[1][j][i]=G/(dlg.m_FileterSize*dlg.m_FileterSize);
				NewPicture[2][j][i]=R/(dlg.m_FileterSize*dlg.m_FileterSize);
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;
			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//���ý���������

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

//����ָ��
//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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

//��ֵ�˲�
void CImage_ProcessingView::OnMedianf()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG
	GeometricMeanFilter dlg;//ͳһʹ�ü��ξ�ֵ�˲�ģ��DLG
	//dlg.DoModal();
	
	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//��������ά���飬�����ݴ���ͼ��
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //��H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //��W
			}
		}

		//�ݴ����飬��ȡ��ֵ
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//�����±�

		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				sz=0;
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//ģ����ѭ��
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B[sz]=m_Image.m_pBits[0][j+k][i+kk];
						G[sz]=m_Image.m_pBits[1][j+k][i+kk];
						R[sz]=m_Image.m_pBits[2][j+k][i+kk];
						sz++;
					}
				}
				std::sort(B,B+dlg.m_FileterSize*dlg.m_FileterSize);//sort����
				std::sort(G,G+dlg.m_FileterSize*dlg.m_FileterSize);
				std::sort(R,R+dlg.m_FileterSize*dlg.m_FileterSize);
				NewPicture[0][j][i]=B[(dlg.m_FileterSize*dlg.m_FileterSize-1)/2+1];
				NewPicture[1][j][i]=G[(dlg.m_FileterSize*dlg.m_FileterSize-1)/2+1];
				NewPicture[2][j][i]=R[(dlg.m_FileterSize*dlg.m_FileterSize-1)/2+1];
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		   ((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

//����ָ��
//////////////////////////////////////////////////////////////////////////
	
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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



//�ָ�Դͼ
void CImage_ProcessingView::OnSource()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG
/////////////���ͼƬ������,���٣�����copy////////////////////
	if (w!=m_Imagecp.GetWidth())
	{
		for(int i=0;i<3;i++)   //����m_pBits
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
		int nrow=m_Image.m_CImage.GetPitch();//���CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
		BYTE *psrc2=(BYTE *)m_Image.m_CImage.GetBits();//���CImage���һ�е����ص�ַ
		BYTE *psrc=(BYTE *)m_Imagecp.m_CImage.GetBits();//���CImage���һ�е����ص�ַ

		for (int j=0;j<w;j++)
		{
			for (int k=0;k<h;k++)
			{
				psrc2[j*nrow+k*3  ]=psrc[j*nrow+k*3  ];//B
				psrc2[j*nrow+k*3+1]=psrc[j*nrow+k*3+1];//G
				psrc2[j*nrow+k*3+2]=psrc[j*nrow+k*3+2];//R
			}
		}


		m_Image.m_pBits= new  BYTE **[3];//3��ά�ȣ����·����ڴ�  
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

//////////////////////////��ά���ٸ���Ҷ�任/////////////////////////////////////////////
void CImage_ProcessingView::OnFourier()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();


	long i,j;					//i:��ѭ������ ,j:��ѭ������
	double dTmp;				//��ʱ����
	//w��h��
	long wid =1,hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int widpor=0,heipor=0;		//wid hei :2���ݴ���

	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*w*h];//Ϊָ��ʱ���ָ������ڴ�
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*w*h];//Ϊָ��Ƶ���ָ������ڴ�

		
//////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
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

/////////��ʼ��pTd//////////////
	for(i=0;i<hei;i++)
	{
		for(j =0;j<wid;j++)
		{
			pTd[i*wid + j].re = 0;
			pTd[i*wid + j].im = 0;
		}
	}

/////////ͼ����pTdָ��////////////////////////////
		for (int j=0;j<hei;j++)
		{
			for (int i=0;i<wid;i++)
			{
				pTd[j*wid + i].re = pow((double)-1,(double)(i+j))*m_Image.m_pBits[0][j][i];//��-1)^i+j�ƶ��任����
			}
		}
		++FftTime;

	

	if (FTResult)
	{
		delete []FTResult;								//����任���ָ����Ч��ɾ���ڴ�
	}
	 FTResult = new CplexNum[sizeof(CplexNum)*w*h];	//Ϊ�任������·����ڴ�
//////////���ø���Ҷ�仯����Fourier////////////////////
	Fourier(pTd, w,h,pFd,this);

/////////////������/////////////
	
	for(i=0;i<hei;i++)
		for(j=0;j<wid;j++)
		{
			FTResult[wid *i + j]=pTd[wid *i + j];
		}


////////////�����任����ʾ���/////////////////////////
	int **Ftmp;			//�ݴ��ά����wid*hei -> ��i����j��
						//��ά����  ��hei*wid -> ��j����i��

//////////////�����ڴ�/////////////////////
	Ftmp=new int *[wid]; 
	double maxF(1);//�任������ϵ��
	int s(1);	//�����任ϵ��
	for (i=0;i<wid;i++)
	{
		Ftmp[i]=new int [hei];
	}

//////////////�����ݴ��ά����///////////////
	for (int j=0;j<hei;j++)
	{
		for (int i=0;i<wid;i++)
		{
			dTmp=pTd[j*wid + i].re*pTd[j*wid + i].re+pTd[j*wid + i].im*pTd[j*wid + i].im;
			dTmp=sqrt(dTmp)/100;
			if (maxF<dTmp)
			{
				maxF=dTmp;//�������ֵ
			}
			Ftmp[i][j]=dTmp;		
		}
	}
	double maxx=0;
	double v=2;//����
///////////////�����任///////////////////
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
	double pq=255/maxx;//ռ����
///////////////////������Դͼ////////////////
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

//////////////////�����ݴ�����ָ��////////////////
	for (i=0;i<wid;i++)
	{
		delete []Ftmp[i];
	}
	delete []Ftmp;

	delete []pTd;
	delete []pFd;
	Invalidate(TRUE);


}

//////////////////////////��ά���ٸ���Ҷ���任///////////////////////////////////////////
void CImage_ProcessingView::OnIfft()
{

	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	if(!FftTime) //�ж�ͼ���Ƿ�Ϊ��
	{
		MessageBox("���ȸ���Ҷ�任��");
		return;
	}

	m_Image.Flag=0;	//�ָ�FLAG
	--FftTime;

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();


	double dTmp;				//��ʱ����
	long i,j;					//i:��ѭ������ ,j:��ѭ������
	//w��h��
	long wid =1,hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int widpor=0,heipor=0;		//wid hei :2���ݴ���

	CplexNum *pTd = new CplexNum[sizeof(CplexNum)*w*h];//Ϊָ��ʱ���ָ������ڴ�
	CplexNum *pFd = new CplexNum[sizeof(CplexNum)*w*h];//Ϊָ��Ƶ���ָ������ڴ�

//////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
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

	/////////��ʼ��pTd//////////////
	for(i=0;i<hei;i++)
	{
		for(j =0;j<wid;j++)
		{
			pTd[i*wid + j].re = FTResult[i*wid + j].re;
			pTd[i*wid + j].im = -FTResult[i*wid + j].im;//����
		}
	}


	//////////���ø���Ҷ�仯����Fourier////////////////////
	Fourier(pTd, w,h,pFd,this);


	for(i=0;i<hei;i++)
	{
		for(j =0;j<wid;j++)
		{
			dTmp=pTd[i*wid + j].re;
			dTmp=pTd[i*wid + j].im;
			pTd[i*wid + j].re = pTd[i*wid + j].re/(double)(wid*hei) ;
			pTd[i*wid + j].im = -pTd[i*wid + j].im/(double)(wid*hei) ;//����
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

	///////////����ָ���ڴ�/////////////
	delete []pTd;
	delete []pFd;


	Invalidate(TRUE);
}

////////////���ý�����//////////////
void CImage_ProcessingView::SetProgress(int k)
{
	((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
}

///////////////////���ξ�ֵ�˲���///////////////////////
void CImage_ProcessingView::OnGeometricmeanfilter()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();
	//////////////////////////////////////
	GeometricMeanFilter dlg;
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		long double B=1,G=1,R=1;//�ۼӴ洢��ֻBYTE���ͻ�������

		//��������ά���飬�����ݴ���ͼ������ע�⣬û�г�ʼ����
		BYTE *** NewPicture;
		NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //��H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //��W
			}
		}


///////////////���ξ�ֵ�˲�///////////////////
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				R=1,G=1,B=1;//Ϊ��ģ������
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//ģ����ѭ��
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B *=pow((double)m_Image.m_pBits[0][j+k][i+kk],(double)1.0/(double)(dlg.m_FileterSize*dlg.m_FileterSize));//�۳����
						G *=pow((double)m_Image.m_pBits[1][j+k][i+kk],(double)1.0/(double)(dlg.m_FileterSize*dlg.m_FileterSize));//�۳����
						R *=pow((double)m_Image.m_pBits[2][j+k][i+kk],(double)1.0/(double)(dlg.m_FileterSize*dlg.m_FileterSize));//�۳����
					}
				}
				NewPicture[0][j][i]=B;
				NewPicture[1][j][i]=G;
				NewPicture[2][j][i]=R;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;
			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//����ָ��
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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
	// TODO: �ڴ���������������
}


///////////////////////г����ֵ�˲�//////////////////////////
void CImage_ProcessingView::OnHarmonicmeanfilter()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();
	//////////////////////////////////////
	GeometricMeanFilter dlg;//ʹ�ü��ξ�ֵ�˲��װ�DLG
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		long double B=0,G=0,R=0;//�ۼӴ洢��ֻBYTE���ͻ�������

		//��������ά���飬�����ݴ���ͼ������ע�⣬û�г�ʼ����
		BYTE *** NewPicture;
		NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //��H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //��W
			}
		}


		///////////////г����ֵ�˲�///////////////////
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				R=0,G=0,B=0;//Ϊ��ģ������
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//ģ����ѭ��
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B +=(double)1.0/(double)m_Image.m_pBits[0][j+k][i+kk];//�۳����
						G +=(double)1.0/(double)m_Image.m_pBits[1][j+k][i+kk];//�۳����
						R +=(double)1.0/(double)m_Image.m_pBits[2][j+k][i+kk];//�۳����
					}
				}
				NewPicture[0][j][i]=(double)(dlg.m_FileterSize*dlg.m_FileterSize)/B;
				NewPicture[1][j][i]=(double)(dlg.m_FileterSize*dlg.m_FileterSize)/G;
				NewPicture[2][j][i]=(double)(dlg.m_FileterSize*dlg.m_FileterSize)/R;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;
			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//����ָ��
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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

//��г����ֵ�˲�
void CImage_ProcessingView::OnIharmonicmeanfilter()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();
	//////////////////////////////////////
	//ѡ��Qֵ
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
	GeometricMeanFilter dlg;//ʹ�ü��ξ�ֵ�˲�ģ��DLG
	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
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
		//�ۼӴ洢��ֻBYTE���ͻ�������

		//��������ά���飬�����ݴ���ͼ������ע�⣬û�г�ʼ����
		BYTE *** NewPicture;
		NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //��H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //��W
			}
		}

		///////////////��г����ֵ�˲�///////////////////
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				R1=0,G1=0,B1=0;//Ϊ��ģ������
				B2=0,G2=0,R2=0;//Ϊ��ģ������
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//ģ����ѭ��
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B1 +=pow((long double)m_Image.m_pBits[0][j+k][i+kk],(long double)(Q+1));
						B2 +=pow((long double)m_Image.m_pBits[0][j+k][i+kk],(long double)(Q));
						G1 +=pow((long double)m_Image.m_pBits[1][j+k][i+kk],(long double)(Q+1));
						G2 +=pow((long double)m_Image.m_pBits[1][j+k][i+kk],(long double)(Q));//�ۼ����
						R1 +=pow((long double)m_Image.m_pBits[2][j+k][i+kk],(long double)(Q+1));
						R2 +=pow((long double)m_Image.m_pBits[2][j+k][i+kk],(long double)(Q));//�ۼ����
					}
				}
				NewPicture[0][j][i]=B1/B2;
				NewPicture[1][j][i]=G1/G2;
				NewPicture[2][j][i]=R1/R2;
			}

			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;
			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//����ָ��
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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

//���ֵ�˲�
void CImage_ProcessingView::OnMaxfilter()
{

	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG
	GeometricMeanFilter dlg;//ͳһʹ�ü��ξ�ֵ�˲�ģ��DLG
	//dlg.DoModal();

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//��������ά���飬�����ݴ���ͼ��
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //��H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //��W
			}
		}

		//�ݴ����飬��ȡ��ֵ
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//�����±�

		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				sz=0;
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//ģ����ѭ��
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B[sz]=m_Image.m_pBits[0][j+k][i+kk];
						G[sz]=m_Image.m_pBits[1][j+k][i+kk];
						R[sz]=m_Image.m_pBits[2][j+k][i+kk];
						sz++;
					}
				}
				//�����㷨 ����pair   //ע��ڶ�������
				NewPicture[0][j][i]=*std::minmax_element(B,B+dlg.m_FileterSize*dlg.m_FileterSize).second;
				NewPicture[1][j][i]=*std::minmax_element(G,G+dlg.m_FileterSize*dlg.m_FileterSize).second;
				NewPicture[2][j][i]=*std::minmax_element(R,R+dlg.m_FileterSize*dlg.m_FileterSize).second;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//����ָ��
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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

//��Сֵ�˲�
void CImage_ProcessingView::OnMinfilter()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG
	GeometricMeanFilter dlg;//ͳһʹ�ü��ξ�ֵ�˲�ģ��DLG
	//dlg.DoModal();

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//��������ά���飬�����ݴ���ͼ��
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //��H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //��W
			}
		}

		//�ݴ����飬��ȡ��ֵ
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//�����±�

		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				sz=0;
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//ģ����ѭ��
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B[sz]=m_Image.m_pBits[0][j+k][i+kk];
						G[sz]=m_Image.m_pBits[1][j+k][i+kk];
						R[sz]=m_Image.m_pBits[2][j+k][i+kk];
						sz++;
					}
				}
				//�����㷨  ����pair
				NewPicture[0][j][i]=*std::minmax_element(B,B+dlg.m_FileterSize*dlg.m_FileterSize).first;
				NewPicture[1][j][i]=*std::minmax_element(G,G+dlg.m_FileterSize*dlg.m_FileterSize).first;
				NewPicture[2][j][i]=*std::minmax_element(R,R+dlg.m_FileterSize*dlg.m_FileterSize).first;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//����ָ��
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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

//�е��˲�
void CImage_ProcessingView::OnMidpointfilter()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG
	GeometricMeanFilter dlg;//ͳһʹ�ü��ξ�ֵ�˲�ģ��DLG
	//dlg.DoModal();

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//��������ά���飬�����ݴ���ͼ��
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //��H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //��W
			}
		}

		//�ݴ����飬��ȡ��ֵ
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//�����±�

		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				sz=0;
				for (int k=-((dlg.m_FileterSize-1)/2);k<(((dlg.m_FileterSize-1)/2)+1);k++)//ģ����ѭ��
				{
					for (int kk=-((dlg.m_FileterSize-1)/2);kk<(((dlg.m_FileterSize-1)/2)+1);kk++)
					{
						B[sz]=m_Image.m_pBits[0][j+k][i+kk];
						G[sz]=m_Image.m_pBits[1][j+k][i+kk];
						R[sz]=m_Image.m_pBits[2][j+k][i+kk];
						sz++;
					}
				}
				//�����㷨  ����pair
				NewPicture[0][j][i]=(*std::minmax_element(B,B+dlg.m_FileterSize*dlg.m_FileterSize).first+*std::minmax_element(B,B+dlg.m_FileterSize*dlg.m_FileterSize-1).second)/2;
				NewPicture[1][j][i]=(*std::minmax_element(G,G+dlg.m_FileterSize*dlg.m_FileterSize).first+*std::minmax_element(G,G+dlg.m_FileterSize*dlg.m_FileterSize-1).second)/2;
				NewPicture[2][j][i]=(*std::minmax_element(R,R+dlg.m_FileterSize*dlg.m_FileterSize).first+*std::minmax_element(R,R+dlg.m_FileterSize*dlg.m_FileterSize-1).second)/2;
			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//����ָ��
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

//���������λ������flag
void CImage_ProcessingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	MouseX=point.x;
	MouseY=point.y;
	if (!m_Image.IsNull())//û��ͼƬ��������
	{
		if (m_Image.Flag==3)//����RGB�����״̬
		{
			if (MouseX>=m_Image.X&&MouseY>m_Image.Y&&MouseX<(m_Image.X+m_Image.GetWidth())&&MouseY<(m_Image.Y+m_Image.GetHeight()))
			{
				MouseFlag=2;//�����갴��ͼƬ��������갴��FLAG
			}
		}
		else//�ƶ�ͼƬ״̬
		{
					if (MouseX>=m_Image.X&&MouseY>m_Image.Y&&MouseX<(m_Image.X+m_Image.GetWidth())&&MouseY<(m_Image.Y+m_Image.GetHeight()))
				{
					MouseFlag=1;//�����갴��ͼƬ��������갴��FLAG
				}
				if (MouseX>=m_Imagecp.X&&MouseY>m_Imagecp.Y&&MouseX<(m_Imagecp.X+m_Imagecp.GetWidth())&&MouseY<(m_Imagecp.Y+m_Imagecp.GetHeight())&&m_Image.Flag==1)
				{
					MouseFlag2=1;//�����갴��ԴͼƬ������ԭʼ����ͼƬ������ʾ״̬������갴��FLAG2
				}
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

//��������ƶ�������ʾλ��
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
		m_Image.Flag=4;//Ϊ�˵�����Ӧ,FLAG=0���к���ǰ�벿�֣�flagΪ4ʱ��ȡ�������㣬���г����벿��
		CImage_ProcessingView::OnRgbcut();//flagΪ4ʱ��ȡ�������㣬���ó����벿��
	}
	
	MouseFlag=0;
	MouseFlag2=0;//�ָ�mouseflag
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

//�ָ�ͼƬ��ʾ��λ��
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

//��ʾԴͼ
void CImage_ProcessingView::OnShoworiginalimage()
{
	if (!m_Image.IsNull())
	{
		m_Image.Flag=1;//������ʾflag
		m_Image.X=m_Image.X+w/2;
		m_Imagecp.X=m_Image.X-w;
		m_Imagecp.Y=m_Image.Y;
	}
	Invalidate(TRUE);
}

//Ӱ��Դͼ
void CImage_ProcessingView::OnHideoriginalimage()
{
	if (!m_Image.IsNull())
	{
		m_Image.Flag=0;//������ʾflag
		
	}
	CImage_ProcessingView::On32834();
	Invalidate(TRUE);
	// TODO: �ڴ���������������
}

//ͼ������
void CImage_ProcessingView::OnFillzero()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();


	long i,j;					//i:��ѭ������ ,j:��ѭ������
	double dTmp;				//��ʱ����
	//w��h��
	long wid =1,hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int widpor=0,heipor=0;		//wid hei :2���ݴ���

	//////////��������Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
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
////////////////////////////////������Cimage//////////////////////////////////////////
		MyImage_ m_ImageFillZero;
		m_ImageFillZero.m_CImage.Create(wid,hei,24);//�ֲ�����Create
		if(m_ImageFillZero.m_CImage.IsNull()) 
			return;
		int zerow=m_ImageFillZero.m_CImage.GetWidth();
		int zeroh=m_ImageFillZero.m_CImage.GetHeight();

		int nrow=m_ImageFillZero.m_CImage.GetPitch();//���CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
		BYTE *psrc=(BYTE *)m_ImageFillZero.m_CImage.GetBits();//���CImage���һ�е����ص�ַ
		/*����ά���鸴�ƽ�m_CImage*/
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
//////////////////////////////////������MyImage_////////////////////////////

		int zeronrow=m_ImageFillZero.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
		BYTE *zeropsrc=(BYTE *)m_ImageFillZero.m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ
		/*������ά���鲢��m_CImage���ƽ���ά����*/

		m_ImageFillZero.m_pBits= new  BYTE **[3];//3��ά�ȣ������ڴ�  
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


		

		/*���������ά����*/
		for (int j=0;j<zeroh;j++)
		{
			for (int k=0;k<zerow;k++)
			{
				m_ImageFillZero.m_pBits[0][j][k]=zeropsrc[j*nrow+k*3];//B
				m_ImageFillZero.m_pBits[1][j][k]=zeropsrc[j*nrow+k*3+1];//G
				m_ImageFillZero.m_pBits[2][j][k]=zeropsrc[j*nrow+k*3+2];//R
			}
		}
		


//////////////////////////////////����Դͼ��copy��ͼ��Դͼ//////////////////////////
		for(int i=0;i<3;i++)   //����m_pBits
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
	//	int nrow2=m_Image.m_CImage.GetPitch();//==nrow���CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
		BYTE *psrc2=(BYTE *)m_Image.m_CImage.GetBits();//���CImage���һ�е����ص�ַ

		for (int j=0;j<zeroh;j++)
		{
			for (int k=0;k<zerow;k++)
			{
					psrc2[j*nrow+k*3  ]=psrc[j*nrow+k*3  ];//B
					psrc2[j*nrow+k*3+1]=psrc[j*nrow+k*3+1];//G
					psrc2[j*nrow+k*3+2]=psrc[j*nrow+k*3+2];//R
			}
		}
		m_Image.m_pBits= new  BYTE **[3];//3��ά�ȣ����·����ڴ�  
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
		//����m_ImageFillZero
		//MyImage_�ľֲ���������destroy����գ��������������Զ�����
		
		Invalidate(TRUE);
}

//�����ͨ�˲�
void CImage_ProcessingView::OnLowpass()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox("���Ƚ��и���Ҷ�任��");
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();
	//����ģ��
	double **modul;
	modul = new double* [w];
	for (int i=0;i<w;i++)
	{
		modul[i] = new double [h];
	}

	CDC *pDC=GetDC();
	Slider sliderdlg(1,pDC,this);//��ȡDֵ
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

	//�����ͨ�˲�
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
			FTResult[w *i + j].im=modul[j][i]*FTResult[w *i + j].im;
			FTResult[w *i + j].re=modul[j][i]*FTResult[w *i + j].re;
		}

	//����ָ���ڴ�
	for (int i=0;i<w;i++)
	{
		delete []modul[i];
	}
	delete []modul;
	//����IFFT
	CImage_ProcessingView::OnIfft();
}

//������˹��ͨ�˲�
void CImage_ProcessingView::OnBlpf()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox("���Ƚ��и���Ҷ�任��");
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();
	//����ģ��
	double **modul;
	modul = new double* [w];
	for (int i=0;i<w;i++)
	{
		modul[i] = new double [h];
	}


	CDC *pDC=GetDC();
	Slider sliderdlg(2,pDC,this);//��ȡDֵ
	double D;
	if (IDOK==sliderdlg.DoModal())
	{
		D=sliderdlg.Q;
	}else
	{
		return;
	}

	GeometricMeanFilter dlg2(1);//��ȡNֵ
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

	//��ͨ�˲�
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
			FTResult[w *i + j].im=modul[j][i]*FTResult[w *i + j].im;
			FTResult[w *i + j].re=modul[j][i]*FTResult[w *i + j].re;
		}



		//����ָ���ڴ�
		for (int i=0;i<w;i++)
		{
			delete []modul[i];
		}
		delete []modul;

		//����IFFT
		CImage_ProcessingView::OnIfft();
}

//��˹��ͨ
void CImage_ProcessingView::OnGlpf()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ��
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}

	if (!FftTime)
	{
		MessageBox("���Ƚ��и���Ҷ�任��");
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();
	//����ģ��
	double **modul;
	modul = new double* [w];
	for (int i=0;i<w;i++)
	{
		modul[i] = new double [h];
	}


	CDC *pDC=GetDC();
	Slider sliderdlg(3,pDC,this);//��ȡDֵ
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

	//��ͨ�˲�
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
			FTResult[w *i + j].im=modul[j][i]*FTResult[w *i + j].im;
			FTResult[w *i + j].re=modul[j][i]*FTResult[w *i + j].re;
		}



		//����ָ���ڴ�
		for (int i=0;i<w;i++)
		{
			delete []modul[i];
		}
		delete []modul;

		//����IFFT
		CImage_ProcessingView::OnIfft();
}

//����Ӧ��ֵ�˲�
void CImage_ProcessingView::OnSelfmedianfilter()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG
	GeometricMeanFilter dlg(2);//ͳһʹ���˲�ģ��DLG
	//dlg.DoModal();

	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������

		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���

		//�ж��Ƿ�������Ч������
		while(dlg.m_FileterSize%2==0||dlg.m_FileterSize<0||dlg.m_FileterSize>w||dlg.m_FileterSize>h)
		{
			MessageBox("   ����ģ��ߴ���Ч\n������������ʵ�������ֵ");
			if (IDOK==dlg.DoModal())
			{
				UpdateData();
			}
			else
			{
				return;
			}
		}

		//��������ά���飬�����ݴ���ͼ��
		BYTE *** NewPicture=nullptr;
		NewPicture= new  BYTE **[3];//3��ά�ȣ������ڴ�  
		for(int i=0;i<3;i++)  
		{ 
			NewPicture[i] = new  BYTE*[h];   //��H
		}   
		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				NewPicture[i][j]=new BYTE[w];   //��W
			}
		}

		//�ݴ����飬������ȡ��ֵ
		int *B,*G,*R;
		B= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		G= new int[dlg.m_FileterSize*dlg.m_FileterSize];
		R= new int[dlg.m_FileterSize*dlg.m_FileterSize];

		int sz;//�����±�
		
		
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//�趨i��j�����ȡֵ��Χ����ֹ����ͼƬ��Χ
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				//B
				for (int FilterSize=3;FilterSize<=dlg.m_FileterSize;FilterSize++)
				{
								sz=0;
								for (int k=-((FilterSize-1)/2);k<(((FilterSize-1)/2)+1);k++)//ģ����ѭ��
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
								std::sort(B,B+FilterSize*FilterSize);//sort����,ע��ڶ�������������
								for (int i=0;i<9;i++)
								{
									sz=B[i];
								}

								NewPicture[0][j][i]=B[(FilterSize*FilterSize-1)/2+1];


								sz=B[(FilterSize*FilterSize-1)/2+1];
								sz=B[FilterSize*FilterSize-1];
								sz=B[0];
								if ((B[(FilterSize*FilterSize-1)/2+1]!=B[FilterSize*FilterSize-1])&&(B[(FilterSize*FilterSize-1)/2+1]!=B[0]) )//�����ֵ������
								{
									if ((m_Image.m_pBits[0][j][i]!=B[FilterSize*FilterSize-1])&&(m_Image.m_pBits[0][j][i]!=B[0]))//������ķ�����
									{
										sz=m_Image.m_pBits[0][j][i];
										NewPicture[0][j][i]=m_Image.m_pBits[0][j][i];//���ԭֵ
										
									}
								 	else
									{
										sz=B[(FilterSize*FilterSize-1)/2+1];
										NewPicture[0][j][i]=B[(FilterSize*FilterSize-1)/2+1];//�����ֵ
									}
									break;
								}
				}

				//G
				for (int FilterSize=3;FilterSize<=dlg.m_FileterSize;FilterSize++)
				{
					sz=0;
					for (int k=-((FilterSize-1)/2);k<(((FilterSize-1)/2)+1);k++)//ģ����ѭ��
					{
						for (int kk=-((FilterSize-1)/2);kk<(((FilterSize-1)/2)+1);kk++)
						{
							G[sz]=m_Image.m_pBits[1][j+k][i+kk];
							sz++;
						}
					}
					std::sort(G,G+FilterSize*FilterSize);
					NewPicture[1][j][i]=G[(FilterSize*FilterSize-1)/2+1];
					if ((G[(FilterSize*FilterSize-1)/2+1]!=G[FilterSize*FilterSize-1])&&(G[(FilterSize*FilterSize-1)/2+1]!=G[0]) )//�����ֵ������
					{
						if ((m_Image.m_pBits[1][j][i]!=G[FilterSize*FilterSize-1])&&(m_Image.m_pBits[1][j][i]!=G[0]))//������ķ�����
						{
							NewPicture[1][j][i]=m_Image.m_pBits[1][j][i];//���ԭֵ

						}
						else
						{
							NewPicture[1][j][i]=G[(FilterSize*FilterSize-1)/2+1];//�����ֵ
						}
						break;
					}
				}

				//R
				for (int FilterSize=3;FilterSize<=dlg.m_FileterSize;FilterSize++)
				{
					sz=0;
					for (int k=-((FilterSize-1)/2);k<(((FilterSize-1)/2)+1);k++)//ģ����ѭ��
					{
						for (int kk=-((FilterSize-1)/2);kk<(((FilterSize-1)/2)+1);kk++)
						{
							R[sz]=m_Image.m_pBits[2][j+k][i+kk];
							sz++;
						}
					}
					std::sort(R,R+FilterSize*FilterSize);
					NewPicture[2][j][i]=R[(FilterSize*FilterSize-1)/2+1];
					if ((R[(FilterSize*FilterSize-1)/2+1]!=R[FilterSize*FilterSize-1])&&(R[(FilterSize*FilterSize-1)/2+1]!=R[0]) )//�����ֵ������
					{
						if ((m_Image.m_pBits[2][j][i]!=R[FilterSize*FilterSize-1])&&(m_Image.m_pBits[2][j][i]!=R[0]))//������ķ�����
						{
							NewPicture[2][j][i]=m_Image.m_pBits[2][j][i];//���ԭֵ

						}
						else
						{
							NewPicture[2][j][i]=R[(FilterSize*FilterSize-1)/2+1];//�����ֵ
						}
						break;
					}
				}



			}
			double p;
			p=(double)j/(double)(h-((dlg.m_FileterSize-1)/2));
			int k=p*100;

			((CMainFrame *)GetParent())->m_progress.SetPos(k);//���ý���������
		}
		((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������
	

		//����ͼ����Դͼ
		for (int j=((dlg.m_FileterSize-1)/2);j<h-((dlg.m_FileterSize-1)/2);j++)//��ͼ��û�г�ʼ����!
		{
			for (int i=((dlg.m_FileterSize-1)/2);i<w-((dlg.m_FileterSize-1)/2);i++)
			{
				m_Image.m_pBits[0][j][i]=NewPicture[0][j][i];
				m_Image.m_pBits[1][j][i]=NewPicture[1][j][i];
				m_Image.m_pBits[2][j][i]=NewPicture[2][j][i];
			}
		}

		//����ָ��
		//////////////////////////////////////////////////////////////////////////

		for(int i=0;i<3;i++)   
		{          
			for   (int j=0;j<h;j++)         
			{   
				delete[] NewPicture[i][j];//�����ڴ�
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
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	Slider dlg(4);//��ȡ��׼��ֵ
	double D;

	if (IDOK==dlg.DoModal())
	{
		UpdateData();//��ñ༭���û����������
		D=dlg.Q;
		if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���
	
		w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
		h=m_Image.GetHeight();

		std::normal_distribution<> gus_noise(0, D);//��һ������Ϊƽ���Ҷȼ����ڶ�������Ϊ��׼��
		std::default_random_engine dre;//����
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

//��ʾRGB����
void CImage_ProcessingView::OnShowrgb()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG


	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	RGBSheet propSheet(this,0,"RGB��");//pv,int flag,����
	propSheet.DoModal();


}


void CImage_ProcessingView::OnShowhsi()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG


	w=m_Image.GetWidth();//��ȡ�߶ȺͿ��
	h=m_Image.GetHeight();

	RGBSheet propSheet(this,1,"HSI��");//pv,int flag,����
	propSheet.DoModal();

}

//RGB���⻯
void CImage_ProcessingView::OnRgbhistogram()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG

	//B�������⻯
	//////////////////////////////////////////////////////////////////////////////
	m_Image.GetHistgran();//��ȡ����ֱ��ͼ
	BYTE *lpNewDIBBits;

	long i,j;		//ѭ������
	BYTE pixel;		//����ֵ
	//float fPro[256];	//Դͼ�����ܶȱ���probability
	float temp[256];
	int   nRst[256];//ӳ���
	int nrow=m_Image.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С

	w=m_Image.GetWidth();
	h=m_Image.GetHeight();
	CImage image3;			//����ͼ
	image3.Create(w,h,24);	//Create����Ҫdelete
	lpNewDIBBits=(BYTE *)image3.GetBits();//���image3���һ�е����ص�ַ

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
			lpNewDIBBits[j*nrow+i*3]=(BYTE)(nRst[pixel]);//��ת��ûʲô��

			m_Image.m_pBits[0][j][i]=lpNewDIBBits[j*nrow+i*3];//ע����ʹ��m_pBits
		}
	}
	//G��������
	//////////////////////////////////////////////////////////////////////////
	auto tmp=m_Image.m_pBits[0];
	m_Image.m_pBits[0]=m_Image.m_pBits[1];
	m_Image.m_pBits[1]=tmp;  //����G ��Bָ��

	m_Image.GetHistgran(); //��ȡ����ֱ��ͼ

	nrow=m_Image.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С

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
			lpNewDIBBits[j*nrow+i*3]=(BYTE)(nRst[pixel]);//��ת��ûʲô��
			m_Image.m_pBits[0][j][i]=lpNewDIBBits[j*nrow+i*3];//ע����ʹ��m_pBits
		}
	}

	tmp=m_Image.m_pBits[0];
	m_Image.m_pBits[0]=m_Image.m_pBits[1];
	m_Image.m_pBits[1]=tmp;  //��������G ��Bָ��

	//R��������
	//////////////////////////////////////////////////////////////////////////
	tmp=m_Image.m_pBits[0];
	m_Image.m_pBits[0]=m_Image.m_pBits[2];
	m_Image.m_pBits[2]=tmp;  //����R��Bָ��

	m_Image.GetHistgran(); //��ȡ����ֱ��ͼ
	nrow=m_Image.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С

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
			lpNewDIBBits[j*nrow+i*3]=(BYTE)(nRst[pixel]);//��ת��ûʲô��
			m_Image.m_pBits[0][j][i]=lpNewDIBBits[j*nrow+i*3];//ע����ʹ��m_pBits
		}
	}

	tmp=m_Image.m_pBits[0];
	m_Image.m_pBits[0]=m_Image.m_pBits[2];
	m_Image.m_pBits[2]=tmp;  //��������R ��Bָ��

	Invalidate(1);
}

//I�������⻯
void CImage_ProcessingView::OnIhistogram()
{

	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		return;
	}
	m_Image.Flag=0;	//�ָ�FLAG
	using namespace std;//ʹ������
	//ת��ΪHSI
	vector<vector<vector<double>>> HSI;
	vector<vector<double>> vec;
	HSI.push_back(vec);HSI.push_back(vec);HSI.push_back(vec);
	//////////////////////////////////
	for (int i = 0; i <w; i++)
	{
		vector<double> vec;      //����vec
		HSI[0].push_back(vec);//H
		HSI[1].push_back(vec);//S
		HSI[2].push_back(vec);//I
		for (int j = 0; j <h; j++)
		{
			double tmp;
			int R=m_Image.m_pBits[2][j][i];
			int G=m_Image.m_pBits[1][j][i];
			int B=m_Image.m_pBits[0][j][i];

			tmp=acos((double)(2*R-G-B) / (0.001+ 2*sqrt((double)(R-G)*(R-G) + (double)(R-B)*(G-B))));//0.001��Ϊ��ӣ���ֹ����Ϊ��
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
	//ֱ��ͼ���⻯
	for (int i = 0; i <w; i++)
	{
		for (int j = 0; j <h; j++)
		{
			m_Image.m_pBits[0][j][i]=HSI[2][i][j];//��vectorI������ֵͼƬ��һά��
		}
	}
	m_Image.GetHistgran();//��ȡ����ֱ��ͼ
	BYTE *lpNewDIBBits;

	long i,j;		//ѭ������
	BYTE pixel;		//����ֵ
	double temp[256];
	double   nRst[256];//ӳ���
	int nrow=m_Image.m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С

	w=m_Image.GetWidth();
	h=m_Image.GetHeight();
	CImage image3;			//����ͼ
	image3.Create(w,h,24);	//Create����Ҫdelete
	lpNewDIBBits=(BYTE *)image3.GetBits();//���image3���һ�е����ص�ַ

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
	//ת��ΪRGB
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
		((CMainFrame *)GetParent())->m_progress.SetPos(100*i/w);//���ý���������
	}
	((CMainFrame *)GetParent())->m_progress.SetPos(0);//�ָ�����������

	Invalidate(1);
}

//RGBͼ��ָ�
void CImage_ProcessingView::OnRgbcut()
{
	if(m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		return;
	}

	if (m_Image.Flag==0)//ǰ��λ�ȡ����
	{
		m_Image.Flag=3;	//����FLAG
		using namespace std;//ʹ������
		MouseX =0;
		MouseY = 0;
		MouseX2 =0;
		MouseY2 =0;
		Invalidate(TRUE);
	}
	else if (m_Image.Flag==4)//���δ���ͼƬ
	{
		auto minX=min(MouseX,MouseX2)-m_Image.X,maxX=max(MouseX,MouseX2)-m_Image.X;
		auto minY=min(MouseY,MouseY2)-m_Image.Y,maxY=max(MouseY,MouseY2)-m_Image.Y;

		double R(0),G(0),B(0);//ֵ��ʼ��
		double Rstand(0),Gstand(0),Bstand(0);
		double Rmin(0),Rmax(0),Gmin(0),Gmax(0),Bmin(0),Bmax(0);
		auto size=(maxX-minX+1)*(maxY-minY+1);//���º������м�����㣬���Դ����л��еļ������
		for (int i =minX; i <=maxX; i++)
		{
			for (int j = minY; j <=maxY; j++)
			{
				R+=(double)m_Image.m_pBits[2][j][i]/(double)size;//��ֹ�����ֱ�ӳ���size
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
		Rstand = sqrt(Rstand/(double)size);//��׼��
		Gstand = sqrt(Gstand/(double)size);
		Bstand = sqrt(Bstand/(double)size);
		//�����ָ�����
		Rmin=R-1.5*Rstand;  Rmax=R+1.5*Rstand;
		Gmin=G-1.5*Gstand;  Gmax=G+1.5*Gstand;
		Bmin=B-1.5*Bstand;  Bmax=B+1.5*Bstand;

		//����R G B����
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
		///���ú�ɫָʾ�߿�
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

		m_Image.Flag=0;//������0����ǰ�벿���γɿ�ѭ��״̬
		CImage_ProcessingView::OnShoworiginalimage();//��ʾԴͼ���жԱ�
		//Invalidate(1);
	}

}


BOOL CImage_ProcessingView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ���������������

}



