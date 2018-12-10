// PropG.cpp : G S 分量
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "PropG.h"
#include "afxdialogex.h"

#include <vector>
#include <math.h>
using namespace std;
// PropG 对话框

IMPLEMENT_DYNAMIC(PropG, CPropertyPage)

PropG::PropG()
	: CPropertyPage(PropG::IDD)
	, pWnd(NULL)
	, pDC(NULL)
	, pv(NULL)
	, TypeFlag(0)
{

}

PropG::~PropG()
{
}

void PropG::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PropG, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// PropG 消息处理程序


BOOL PropG::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	pWnd =GetDlgItem(IDC_STATIC);//静态文本框的句柄

	pDC = pWnd->GetDC();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void PropG::OnPaint()
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
				psrc[j*nrow+i*3]=0;
				psrc[j*nrow+i*3+1]=pv->m_Image.m_pBits[1][(int)(j*rate)][(int)(i*rate)];
				psrc[j*nrow+i*3+2]=0;
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));
	}
	else
	{
		vector<vector<double>> S;//H分量
		for (int i = 0; i <w; i++)
		{
			vector<double> vec;
			S.push_back(vec);
			for (int j = 0; j <h; j++)
			{
				double tmpS;
				int R=pv->m_Image.m_pBits[2][j][i];
				int G=pv->m_Image.m_pBits[1][j][i];
				int B=pv->m_Image.m_pBits[0][j][i];

				tmpS=(double)1 - ((double)3*(double)min(R,G,B)) / (double)(R+G+B);

				S[i].push_back(tmpS);
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
				psrc[j*nrow+i*3]=S[(int)(i*rate)][(int)(j*rate)]*255;
				psrc[j*nrow+i*3+1]=S[(int)(i*rate)][(int)(j*rate)]*255;
				psrc[j*nrow+i*3+2]=S[(int)(i*rate)][(int)(j*rate)]*255;
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));

	}
	
}
