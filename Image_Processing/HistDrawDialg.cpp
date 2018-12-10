// HistDrawDialg.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"

#include "afxdialogex.h"
#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
#include "HistDrawDialg.h"//注意H文件顺序
// HistDrawDialg 对话框

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


// HistDrawDialg 消息处理程序


BOOL HistDrawDialg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pWnd =GetDlgItem(IDC_STATIC);//静态文本框的句柄

	pDC = pWnd->GetDC();//获取DC

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void HistDrawDialg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	if( pv->m_Image.IsNull()) return;
	int w=pv->m_Image.GetWidth();
	int h=pv->m_Image.GetHeight();

	//使static控件区域无效
	pWnd->Invalidate();
	//更新窗口, 此时才真正向系统发送重绘消息, 
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
	N=350/M;//归一化：将最大值归一到坐标显示的最大值

	CPen pen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);//选择自定义颜色画笔

	pDC->MoveTo(110/2,700/2);
	pDC->LineTo(1200/2,700/2);//绘制横坐标轴

	pDC->MoveTo(1170/2,685/2);
	pDC->LineTo(1200/2,700/2);
	pDC->MoveTo(1170/2,715/2);
	pDC->LineTo(1200/2,700/2);//绘制箭头

	char ch[5];
	CString ch2="";//不能重复定义
	for(int i=0;i<256;i+=20)
	{
		itoa(i, ch, 10);
		ch2=ch;
		pDC->TextOutA(110/2+i*2,710/2,ch2);//绘制横坐标标尺
	}

	CString str("灰度值");
	pDC->TextOutA(1120/2,710/2,str);//横坐标文字标志

	pDC->MoveTo(110/2,700/2);
	pDC->LineTo(110/2,0);//绘制纵坐标轴

	pDC->MoveTo(110/2,0);
	pDC->LineTo((385-290)/2,30/2);
	pDC->MoveTo((400-290)/2,0);
	pDC->LineTo((415-290)/2,30/2);//绘制箭头

	float ii=1;
	CString ch3;
	for(int i=0;i<700/2;i+=80/2)
	{
		ii=i/N ;
		ch3.Format("%.5f",ii); 
		if(i!=0)
		{
			pDC->TextOutA(30/2,700/2-i,ch3);//绘制纵坐标标尺
		}
	}

	str="概率";
	pDC->TextOutA(40/2,20/2,str);//纵坐标文字标志

	pDC->SelectObject(pOldPen);//恢复颜色选择
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
