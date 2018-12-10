// GeometricMeanFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "GeometricMeanFilter.h"
#include "afxdialogex.h"


// GeometricMeanFilter 对话框

IMPLEMENT_DYNAMIC(GeometricMeanFilter, CDialogEx)

GeometricMeanFilter::GeometricMeanFilter(int n,CWnd* pParent /*=NULL*/)
	: CDialogEx(GeometricMeanFilter::IDD, pParent)
	, m_str(_T(""))
	, m_FileterSize(0)
	, TypeFlag(n)
{

}

GeometricMeanFilter::~GeometricMeanFilter()
{
}

void GeometricMeanFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GeometricMeanFilter, CDialogEx)
END_MESSAGE_MAP()


// GeometricMeanFilter 消息处理程序


BOOL GeometricMeanFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (TypeFlag==0||TypeFlag==2)//获取模板大小
	{
		if (TypeFlag==0)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("请选择均值滤波模板大小：");
		}if (TypeFlag==2)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("自适应中值滤波最大模板尺寸：");
		}
		
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     3*3     ");
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     5*5     ");
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     7*7     ");
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     9*9     ");
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                    11*11     ");
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                    13*13     ");
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                    15*15     ");
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	}else{ 
		if(TypeFlag==1)//获取阶数
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("请选择滤波器阶数大小：");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     1阶     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     2阶     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     3阶     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     4阶     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     5阶     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     6阶     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     7阶     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(1);
		}
	}
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("                     1*1     ");


	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void GeometricMeanFilter::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	int index;
	index = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

	if (TypeFlag==0||TypeFlag==2)
	{
		m_FileterSize=3+2*index;//模板尺寸
	}
	else
	{
		if (TypeFlag==1)
		{
			m_FileterSize=index+1;//阶数大小
		}
	}
	
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(index,m_str);
	CDialogEx::OnOK();
}
