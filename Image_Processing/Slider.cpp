// Slider.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Slider.h"
#include "afxdialogex.h"


// Slider 对话框

IMPLEMENT_DYNAMIC(Slider, CDialogEx)

Slider::Slider(int type,CDC * p,CImage_ProcessingView *pp,CWnd* pParent /*=NULL*/)
	: CDialogEx(Slider::IDD, pParent)
	, Q(0)
	, TypeFlag(type)
	, pDC(p)
	, pv(pp)
	, OldQ(0)
	, OldOldQ(0)
{

}

Slider::~Slider()
{
}

void Slider::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}


BEGIN_MESSAGE_MAP(Slider, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &Slider::OnCustomdrawSlider1)
END_MESSAGE_MAP()


// Slider 消息处理程序


void Slider::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	CString str;
	if (TypeFlag==0)//逆谐波滤波
	{
		Q=((double)m_slider.GetPos()-(double)50)/10.0;
	}
	else 
		if (TypeFlag==1)//理想低通滤波
			{
				Q=(double)m_slider.GetPos()*15;
				OldQ++;
				if (OldQ==5)
				{
					OldQ=0;
					pv->Invalidate(TRUE);
				}
				
				CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				CBrush *pOldBrush= pDC->SelectObject(pBrush);
				pDC->Ellipse(pv->m_Image.X+pv->m_Image.GetWidth()/2-Q,pv->m_Image.Y+pv->m_Image.GetHeight()/2-Q, pv->m_Image.X+pv->m_Image.GetWidth()/2+Q, pv->m_Image.Y+pv->m_Image.GetHeight()/2+Q);
				pDC->SelectObject(pOldBrush);

			}
		else if (TypeFlag==2)//布特沃斯低通滤波器
		{

			Q=(double)m_slider.GetPos()*10;
			OldQ++;
			if (OldQ==5)
			{
				OldQ=0;
				pv->Invalidate(TRUE);
			}

	
			CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush= pDC->SelectObject(pBrush);
			pDC->Ellipse(pv->m_Image.X+pv->m_Image.GetWidth()/2-Q,pv->m_Image.Y+pv->m_Image.GetHeight()/2-Q, pv->m_Image.X+pv->m_Image.GetWidth()/2+Q, pv->m_Image.Y+pv->m_Image.GetHeight()/2+Q);
			pDC->SelectObject(pOldBrush);
		}
		else if (TypeFlag==3)//高斯低通滤波器
		{
			Q=(double)m_slider.GetPos()*10;
			OldQ++;
			if (OldQ==5)
			{
				OldQ=0;
				pv->Invalidate(TRUE);
			}

			CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush= pDC->SelectObject(pBrush);
			pDC->Ellipse(pv->m_Image.X+pv->m_Image.GetWidth()/2-Q,pv->m_Image.Y+pv->m_Image.GetHeight()/2-Q, pv->m_Image.X+pv->m_Image.GetWidth()/2+Q, pv->m_Image.Y+pv->m_Image.GetHeight()/2+Q);
			pDC->SelectObject(pOldBrush);
		}
		else if (TypeFlag==4)//添加高斯噪声
		{
			Q=(double)m_slider.GetPos();
		}



	
		if (TypeFlag==0)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("逆谐波均值滤波阶数：");
		}else if (TypeFlag==1)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("理想低通截止频率：");
		}else if (TypeFlag==2)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("布特沃斯低通截止频率：");
		}
		else if (TypeFlag==3)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("高斯低通截止频率：");
		}
		else if (TypeFlag==4)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("高斯噪声标准差：");
		}





	str.Format("%lf",Q);
	GetDlgItem(IDC_VALUE)->SetWindowText(str);    
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL Slider::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	GetWindowRect(&rect);

	MoveWindow(rect.left+300,rect.top,rect.right,rect.bottom);//设置弹出位置
	// TODO:  在此添加额外的初始化
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
