// PepperSalt.cpp : B I 分量
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "PepperSalt.h"
#include "afxdialogex.h"


// PepperSalt 对话框

IMPLEMENT_DYNAMIC(PepperSalt, CDialogEx)

PepperSalt::PepperSalt(CWnd* pParent /*=NULL*/)
	: CDialogEx(PepperSalt::IDD, pParent)
{

	m_pepper = 0.0f;
	m_salt = 0.0f;
}

PepperSalt::~PepperSalt()
{
}

void PepperSalt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_pepper);
	DDX_Text(pDX, IDC_EDIT2, m_salt);
}


BEGIN_MESSAGE_MAP(PepperSalt, CDialogEx)
END_MESSAGE_MAP()


// PepperSalt 消息处理程序
