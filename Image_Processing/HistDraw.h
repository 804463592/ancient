#include "Image_ProcessingDoc.h"
#include "stdafx.h"
#include "stdlib.h"
//========================
//子函数：画直方图
//C++不能在函数中定义函数
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
	N=700/M;//归一化：将最大值归一到坐标显示的最大值

	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);//选择自定义颜色画笔

	pDC->MoveTo(400,800);
	pDC->LineTo(1500,800);//绘制横坐标轴

	pDC->MoveTo(1470,785);
	pDC->LineTo(1500,800);
	pDC->MoveTo(1470,815);
	pDC->LineTo(1500,800);//绘制箭头

	char ch[5];
	CString ch2="";//不能重复定义
	for(int i=0;i<256;i+=20)
	{
		itoa(i, ch, 10);
		ch2=ch;
		pDC->TextOutA(400+i*4,810,ch2);//绘制横坐标标尺
	}

	CString str("灰度值");
	pDC->TextOutA(1400,810,str);//横坐标文字标志




	pDC->MoveTo(400,800);
	pDC->LineTo(400,100);//绘制纵坐标轴

	pDC->MoveTo(400,100);
	pDC->LineTo(385,130);
	pDC->MoveTo(400,100);
	pDC->LineTo(415,130);//绘制箭头

	float ii=1;
	CString ch3;
	for(int i=0;i<700;i+=80)
	{
		ii=i/N ;
		ch3.Format("%.5f",ii); 
		if(i!=0)
		{
			pDC->TextOutA(320,800-i,ch3);//绘制纵坐标标尺
		}
	}

	str="概率";
	pDC->TextOutA(330,120,str);//纵坐标文字标志

	pDC->SelectObject(pOldPen);//恢复颜色选择
	for(int i=0;i<256;i++)
	{
		pDC->MoveTo(i*4+400,800);
		pDC->LineTo(i*4+400,800-N*probability[i]);

	}
			//m_Image.Flag=0;//重新设置FLAG
	
}
