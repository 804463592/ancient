// PropG.cpp : G S ����
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "PropG.h"
#include "afxdialogex.h"

#include <vector>
#include <math.h>
using namespace std;
// PropG �Ի���

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


// PropG ��Ϣ�������


BOOL PropG::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	pWnd =GetDlgItem(IDC_STATIC);//��̬�ı���ľ��

	pDC = pWnd->GetDC();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void PropG::OnPaint()
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
				psrc[j*nrow+i*3+1]=pv->m_Image.m_pBits[1][(int)(j*rate)][(int)(i*rate)];
				psrc[j*nrow+i*3+2]=0;
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));
	}
	else
	{
		vector<vector<double>> S;//H����
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
				psrc[j*nrow+i*3]=S[(int)(i*rate)][(int)(j*rate)]*255;
				psrc[j*nrow+i*3+1]=S[(int)(i*rate)][(int)(j*rate)]*255;
				psrc[j*nrow+i*3+2]=S[(int)(i*rate)][(int)(j*rate)]*255;
			}
		}

		image.Draw(pDC->m_hDC,CPoint(X,Y));

	}
	
}
