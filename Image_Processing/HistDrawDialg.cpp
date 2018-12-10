// HistDrawDialg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"

#include "afxdialogex.h"
#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
#include "HistDrawDialg.h"//ע��H�ļ�˳��
// HistDrawDialg �Ի���

IMPLEMENT_DYNAMIC(HistDrawDialg, CDialogEx)

HistDrawDialg::HistDrawDialg(CImage_ProcessingView* pParent /*=NULL*/)
	: CDialogEx(HistDrawDialg::IDD, pParent)
	, pWnd(NULL)
	, pDC(NULL)
	, pv(NULL)
{
	pv=pParent;
}

HistDrawDialg::~HistDrawDialg()
{
}

void HistDrawDialg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HistDrawDialg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// HistDrawDialg ��Ϣ�������


BOOL HistDrawDialg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pWnd =GetDlgItem(IDC_STATIC);//��̬�ı���ľ��

	pDC = pWnd->GetDC();//��ȡDC

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void HistDrawDialg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	if( pv->m_Image.IsNull()) return;
	int w=pv->m_Image.GetWidth();
	int h=pv->m_Image.GetHeight();

	//ʹstatic�ؼ�������Ч
	pWnd->Invalidate();
	//���´���, ��ʱ��������ϵͳ�����ػ���Ϣ, 
	pWnd->UpdateWindow();
	pDC->Rectangle(0, 0, 1250/2,750/2); 



	/////////////////////////////
	float M=0,N;
	for (int i=0;i<256;i++)
	{
		if (pv->m_Image.probability[i]>M)
		{
			M=pv->m_Image.probability[i];
		}
	}
	N=350/M;//��һ���������ֵ��һ��������ʾ�����ֵ

	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);//ѡ���Զ�����ɫ����

	pDC->MoveTo(110/2,700/2);
	pDC->LineTo(1200/2,700/2);//���ƺ�������

	pDC->MoveTo(1170/2,685/2);
	pDC->LineTo(1200/2,700/2);
	pDC->MoveTo(1170/2,715/2);
	pDC->LineTo(1200/2,700/2);//���Ƽ�ͷ

	char ch[5];
	CString ch2="";//�����ظ�����
	for(int i=0;i<256;i+=20)
	{
		itoa(i, ch, 10);
		ch2=ch;
		pDC->TextOutA(110/2+i*2,710/2,ch2);//���ƺ�������
	}

	CString str("�Ҷ�ֵ");
	pDC->TextOutA(1120/2,710/2,str);//���������ֱ�־

	pDC->MoveTo(110/2,700/2);
	pDC->LineTo(110/2,0);//������������

	pDC->MoveTo(110/2,0);
	pDC->LineTo((385-290)/2,30/2);
	pDC->MoveTo((400-290)/2,0);
	pDC->LineTo((415-290)/2,30/2);//���Ƽ�ͷ

	float ii=1;
	CString ch3;
	for(int i=0;i<700/2;i+=80/2)
	{
		ii=i/N ;
		ch3.Format("%.5f",ii); 
		if(i!=0)
		{
			pDC->TextOutA(30/2,700/2-i,ch3);//������������
		}
	}

	str="����";
	pDC->TextOutA(40/2,20/2,str);//���������ֱ�־

	pDC->SelectObject(pOldPen);//�ָ���ɫѡ��
	for(int i=0;i<256;i++)
	{
		pDC->MoveTo(i*2+110/2,700/2);
		pDC->LineTo(i*2+110/2,700/2-N*pv->m_Image.probability[i]);
		pDC->MoveTo(i*2+1+110/2,700/2);
		pDC->LineTo(i*2+1+110/2,700/2-N*pv->m_Image.probability[i]);
		/*pDC->MoveTo(i*2+2+110/2,700/2);
		pDC->LineTo(i*2+2+110/2,700/2-N*pv->m_Image.probability[i]);
		pDC->MoveTo(i*2+3+110/2,700/2);
		pDC->LineTo(i*2+3+110/2,700/2-N*pv->m_Image.probability[i]);*/
	}


}
