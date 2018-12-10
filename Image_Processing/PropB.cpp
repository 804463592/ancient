// PropB.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "PropB.h"
#include "afxdialogex.h"

#include <vector>
#include <math.h>
using namespace std;
// PropB 对话框

IMPLEMENT_DYNAMIC(PropB, CPropertyPage)

PropB::PropB()
	: CPropertyPage(PropB::IDD)
	, pWnd(NULL)
	, pDC(NULL)
	, pv(NULL)
	, TypeFlag(0)
{

}

PropB::~PropB()
{
}

void PropB::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PropB, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// PropB 消息处理程序


void PropB::OnPaint()
{
	CRect   rect1;    
	GetClientRect(rect1);
	CPaintDC dc(this); // device context for painting
	pWnd->Invalidate();
	//更新窗口, 此时才真正向系统发送重绘消息, 
	pWnd->UpdateWindow();
	pDC->FillSolidRect(rect1,RGB(128,128,128)); 

	auto w=pv->w;
	auto h=pv->h;//源图尺寸

	if (TypeFlag==0)
	{
		int newh,neww; //求临时新图尺寸
		neww = w>rect1.right  ? rect1.right  : w ;
		newh = h>rect1.bottom ? rect1.bottom : h ;



		double rate;//放缩比例

		double Wrate,Hrate;//横竖放缩比例,取较大值为准
		Wrate=(double)w/(double)neww;
		Hrate=(double)h/(double)newh;
		rate=max(Wrate,Hrate);
		if (Wrate>Hrate)
		{
			newh=h/rate;
		}else
		{
			neww=w/rate;
		}

		int X=rect1.right/2-neww/2;
		int Y=rect1.bottom/2-newh/2;//图片的显示位置
		CImage image;//临时建立的新图
		image.Create(neww,newh,24);
		int nrow=image.GetPitch();//获得CImage每一行像素的RGB所占用的存储空间的大小
		BYTE *psrc=(BYTE *)image.GetBits();//获得image最后一行的像素地址

		for (int i = 0; i <neww; i++)
		{
			for (int j = 0; j <newh; j++)
			{
				psrc[j*nrow+i*3]=pv->m_Image.m_pBits[0][(int)(j*rate)][(int)(i*rate)];
				psrc[j*nrow+i*3+1]=0;
				psrc[j*nrow+i*3+2]=0;
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));
	}
	else 
	{
		vector<vector<double>> I;//H分量
		for (int i = 0; i <w; i++)
		{
			vector<double> vec;
			I.push_back(vec);
			for (int j = 0; j <h; j++)
			{
				double tmpI;
				int R=pv->m_Image.m_pBits[2][j][i];
				int G=pv->m_Image.m_pBits[1][j][i];
				int B=pv->m_Image.m_pBits[0][j][i];

				tmpI=(R+G+B)/3;

				I[i].push_back(tmpI);
			}
		}
		int newh,neww; //求临时新图尺寸
		neww = w>rect1.right  ? rect1.right  : w ;
		newh = h>rect1.bottom ? rect1.bottom : h ;

		double rate;//放缩比例

		double Wrate,Hrate;//横竖放缩比例,取较大值为准
		Wrate=(double)w/(double)neww;
		Hrate=(double)h/(double)newh;
		rate=max(Wrate,Hrate);
		if (Wrate>Hrate)
		{
			newh=h/rate;
		}else
		{
			neww=w/rate;
		}

		int X=rect1.right/2-neww/2;
		int Y=rect1.bottom/2-newh/2;//图片的显示位置
		CImage image;//临时建立的新图
		image.Create(neww,newh,24);
		int nrow=image.GetPitch();//获得CImage每一行像素的RGB所占用的存储空间的大小
		BYTE *psrc=(BYTE *)image.GetBits();//获得image最后一行的像素地址

		for (int i = 0; i <neww; i++)
		{
			for (int j = 0; j <newh; j++)
			{
				psrc[j*nrow+i*3]=I[(int)(i*rate)][(int)(j*rate)];
				psrc[j*nrow+i*3+1]=I[(int)(i*rate)][(int)(j*rate)];
				psrc[j*nrow+i*3+2]=I[(int)(i*rate)][(int)(j*rate)];
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));
	}
	
}


BOOL PropB::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	pWnd =GetDlgItem(IDC_STATIC);//静态文本框的句柄

	pDC = pWnd->GetDC();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
