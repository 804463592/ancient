// PropR.cpp : R H ����
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "afxdialogex.h"

#include "PropR.h"

#include <vector>
#include <math.h>
using namespace std;

// PropR �Ի���

IMPLEMENT_DYNAMIC(PropR, CPropertyPage)

PropR::PropR()
	: CPropertyPage(PropR::IDD)
	, pWnd(NULL)
	, pDC(NULL)
	, pv(NULL)
	, TypeFlag(0)
{
	
}

PropR::~PropR()
{
}

void PropR::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PropR, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// PropR ��Ϣ�������


BOOL PropR::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pWnd =GetDlgItem(IDC_STATIC);//��̬�ı���ľ��

	pDC = pWnd->GetDC();

	if (TypeFlag==1)//��������ҳ����
	{
		TC_ITEM tc;
		tc.mask = TCIF_TEXT;
		tc.pszText = _T("H����");
		((CPropertySheet*)GetParent())->GetTabControl()->SetItem(0,&tc);
		tc.pszText = _T("S����");
		((CPropertySheet*)GetParent())->GetTabControl()->SetItem(1,&tc);
		tc.pszText = _T("I����");
		((CPropertySheet*)GetParent())->GetTabControl()->SetItem(2,&tc);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void PropR::OnPaint()
{

	CRect   rect1;    
	GetClientRect(rect1);
	CPaintDC dc(this); // device context for painting
	pWnd->Invalidate();
	//���´���, ��ʱ��������ϵͳ�����ػ���Ϣ, 
	pWnd->UpdateWindow();
	pDC->FillSolidRect(rect1,RGB(128,128,128)); 

	auto w=pv->w;
	auto h=pv->h;//Դͼ�ߴ�


	if (TypeFlag==0)
	{
		int newh,neww; //����ʱ��ͼ�ߴ�
		neww = w>rect1.right  ? rect1.right  : w ;
		newh = h>rect1.bottom ? rect1.bottom : h ;

		double rate;//��������

		double Wrate,Hrate;//������������,ȡ�ϴ�ֵΪ׼
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
		int Y=rect1.bottom/2-newh/2;//ͼƬ����ʾλ��

		CImage image;//��ʱ��������ͼ
		image.Create(neww,newh,24);
		int nrow=image.GetPitch();//���CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
		BYTE *psrc=(BYTE *)image.GetBits();//���image���һ�е����ص�ַ

		for (int i = 0; i <neww; i++)
		{
			for (int j = 0; j <newh; j++)
			{
				psrc[j*nrow+i*3]=0;
				psrc[j*nrow+i*3+1]=0;
				psrc[j*nrow+i*3+2]=pv->m_Image.m_pBits[2][(int)(j*rate)][(int)(i*rate)];
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));

	}
	else if (TypeFlag==1)//HSI�任
	{
		vector<vector<int>> H;//H����
		for (int i = 0; i <w; i++)
		{
			vector<int> vec;
			H.push_back(vec);
			for (int j = 0; j <h; j++)
			{
				double tmpH;
				int R=pv->m_Image.m_pBits[2][j][i];
				int G=pv->m_Image.m_pBits[1][j][i];
				int B=pv->m_Image.m_pBits[0][j][i];
				tmpH=acos((double)(2*R-G-B) / ( 2*sqrt((double)(R-G)*(R-G) + (double)(R-B)*(G-B))));
				
				if (B<=G)
				{
					tmpH=tmpH*(double)180/(double)3.1415926;
				}else{
					tmpH=360-tmpH*(double)180/(double)3.1415926;
				}
				H[i].push_back(tmpH);
			}
		}
		int newh,neww; //����ʱ��ͼ�ߴ�
		neww = w>rect1.right  ? rect1.right  : w ;
		newh = h>rect1.bottom ? rect1.bottom : h ;

		double rate;//��������

		double Wrate,Hrate;//������������,ȡ�ϴ�ֵΪ׼
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
		int Y=rect1.bottom/2-newh/2;//ͼƬ����ʾλ��

		CImage image;//��ʱ��������ͼ
		image.Create(neww,newh,24);
		int nrow=image.GetPitch();//���CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
		BYTE *psrc=(BYTE *)image.GetBits();//���image���һ�е����ص�ַ

		for (int i = 0; i <neww; i++)
		{
			for (int j = 0; j <newh; j++)
			{
				psrc[j*nrow+i*3]=  H[(int)(i*rate)][(int)(j*rate)]*(double)255/(double)360;
				psrc[j*nrow+i*3+1]=H[(int)(i*rate)][(int)(j*rate)]*(double)255/(double)360;
				psrc[j*nrow+i*3+2]=H[(int)(i*rate)][(int)(j*rate)]*(double)255/(double)360;
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));


	}
	
	

}
