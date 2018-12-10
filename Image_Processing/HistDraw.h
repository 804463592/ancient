#include "Image_ProcessingDoc.h"
#include "stdafx.h"
#include "stdlib.h"
//========================
//�Ӻ�������ֱ��ͼ
//C++�����ں����ж��庯��
//========================
void HistDraw(CImage_ProcessingDoc* pDoc,CDC* pDC,float *probability)
{
	float M=0,N;
	for (int i=0;i<256;i++)
	{
		if (probability[i]>M)
		{
			M=probability[i];
		}
	}
	N=700/M;//��һ���������ֵ��һ��������ʾ�����ֵ

	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);//ѡ���Զ�����ɫ����

	pDC->MoveTo(400,800);
	pDC->LineTo(1500,800);//���ƺ�������

	pDC->MoveTo(1470,785);
	pDC->LineTo(1500,800);
	pDC->MoveTo(1470,815);
	pDC->LineTo(1500,800);//���Ƽ�ͷ

	char ch[5];
	CString ch2="";//�����ظ�����
	for(int i=0;i<256;i+=20)
	{
		itoa(i, ch, 10);
		ch2=ch;
		pDC->TextOutA(400+i*4,810,ch2);//���ƺ�������
	}

	CString str("�Ҷ�ֵ");
	pDC->TextOutA(1400,810,str);//���������ֱ�־




	pDC->MoveTo(400,800);
	pDC->LineTo(400,100);//������������

	pDC->MoveTo(400,100);
	pDC->LineTo(385,130);
	pDC->MoveTo(400,100);
	pDC->LineTo(415,130);//���Ƽ�ͷ

	float ii=1;
	CString ch3;
	for(int i=0;i<700;i+=80)
	{
		ii=i/N ;
		ch3.Format("%.5f",ii); 
		if(i!=0)
		{
			pDC->TextOutA(320,800-i,ch3);//������������
		}
	}

	str="����";
	pDC->TextOutA(330,120,str);//���������ֱ�־

	pDC->SelectObject(pOldPen);//�ָ���ɫѡ��
	for(int i=0;i<256;i++)
	{
		pDC->MoveTo(i*4+400,800);
		pDC->LineTo(i*4+400,800-N*probability[i]);

	}
			//m_Image.Flag=0;//��������FLAG
	
}
