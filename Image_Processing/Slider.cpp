// Slider.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Slider.h"
#include "afxdialogex.h"


// Slider �Ի���

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


// Slider ��Ϣ�������


void Slider::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	CString str;
	if (TypeFlag==0)//��г���˲�
	{
		Q=((double)m_slider.GetPos()-(double)50)/10.0;
	}
	else 
		if (TypeFlag==1)//�����ͨ�˲�
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
		else if (TypeFlag==2)//������˹��ͨ�˲���
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
		else if (TypeFlag==3)//��˹��ͨ�˲���
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
		else if (TypeFlag==4)//��Ӹ�˹����
		{
			Q=(double)m_slider.GetPos();
		}



	
		if (TypeFlag==0)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("��г����ֵ�˲�������");
		}else if (TypeFlag==1)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("�����ͨ��ֹƵ�ʣ�");
		}else if (TypeFlag==2)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("������˹��ͨ��ֹƵ�ʣ�");
		}
		else if (TypeFlag==3)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("��˹��ͨ��ֹƵ�ʣ�");
		}
		else if (TypeFlag==4)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("��˹������׼�");
		}





	str.Format("%lf",Q);
	GetDlgItem(IDC_VALUE)->SetWindowText(str);    
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


BOOL Slider::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	GetWindowRect(&rect);

	MoveWindow(rect.left+300,rect.top,rect.right,rect.bottom);//���õ���λ��
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
