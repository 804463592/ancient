// WarnDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "WarnDlg.h"
#include "afxdialogex.h"


// WarnDlg 对话框

IMPLEMENT_DYNAMIC(WarnDlg, CDialogEx)

WarnDlg::WarnDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(WarnDlg::IDD, pParent)
{

}

WarnDlg::~WarnDlg()
{
}

void WarnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WarnDlg, CDialogEx)
END_MESSAGE_MAP()


// WarnDlg 消息处理程序
