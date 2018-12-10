// MedianFilter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "MedianFilter.h"
#include "afxdialogex.h"


// MedianFilter �Ի���

IMPLEMENT_DYNAMIC(MedianFilter, CDialogEx)

MedianFilter::MedianFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(MedianFilter::IDD, pParent)
{

	m_FilterSize = 0;
}

MedianFilter::~MedianFilter()
{
}

void MedianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_FilterSize);
}


BEGIN_MESSAGE_MAP(MedianFilter, CDialogEx)
END_MESSAGE_MAP()


// MedianFilter ��Ϣ�������
