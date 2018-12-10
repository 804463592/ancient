// LowGray.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "LowGray.h"
#include "afxdialogex.h"


// CLowGray 对话框

IMPLEMENT_DYNAMIC(CLowGray, CDialogEx)

CLowGray::CLowGray(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLowGray::IDD, pParent)
	, LowGray(0)
{

	LowGray = 0;
}

CLowGray::~CLowGray()
{
}

void CLowGray::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, LowGray);
	DDX_Text(pDX, IDC_EDIT1, LowGray);
}


BEGIN_MESSAGE_MAP(CLowGray, CDialogEx)
END_MESSAGE_MAP()


// CLowGray 消息处理程序
