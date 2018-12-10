// DownTimes.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "DownTimes.h"
#include "afxdialogex.h"


// DownTimes 对话框

IMPLEMENT_DYNAMIC(DownTimes, CDialogEx)

DownTimes::DownTimes(CWnd* pParent /*=NULL*/)
	: CDialogEx(DownTimes::IDD, pParent)
{

	m_downtimes = 0;
}

DownTimes::~DownTimes()
{
}

void DownTimes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIMES1, m_downtimes);
}


BEGIN_MESSAGE_MAP(DownTimes, CDialogEx)
END_MESSAGE_MAP()


// DownTimes 消息处理程序
