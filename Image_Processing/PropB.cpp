// PropB.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "PropB.h"
#include "afxdialogex.h"

#include <vector>
#include <math.h>
using namespace std;
// PropB �Ի���

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


// PropB ��Ϣ�������


void PropB::OnPaint()
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
				psrc[j*nrow+i*3]=pv->m_Image.m_pBits[0][(int)(j*rate)][(int)(i*rate)];
				psrc[j*nrow+i*3+1]=0;
				psrc[j*nrow+i*3+2]=0;
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));
	}
	else 
	{
		vector<vector<double>> I;//H����
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

	pWnd =GetDlgItem(IDC_STATIC);//��̬�ı���ľ��

	pDC = pWnd->GetDC();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
