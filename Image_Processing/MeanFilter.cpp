// MeanFilter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "MeanFilter.h"
#include "afxdialogex.h"


// MeanFilter �Ի���

IMPLEMENT_DYNAMIC(MeanFilter, CDialogEx)

MeanFilter::MeanFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(MeanFilter::IDD, pParent)
{

	m_FileterSize = 0;
}

MeanFilter::~MeanFilter()
{
}

void MeanFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_FilterSize);
	DDX_Text(pDX, IDC_EDIT1, m_FileterSize);
}


BEGIN_MESSAGE_MAP(MeanFilter, CDialogEx)
END_MESSAGE_MAP()


// MeanFilter ��Ϣ�������
