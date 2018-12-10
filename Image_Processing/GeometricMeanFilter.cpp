// GeometricMeanFilter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "GeometricMeanFilter.h"
#include "afxdialogex.h"


// GeometricMeanFilter �Ի���

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


// GeometricMeanFilter ��Ϣ�������


BOOL GeometricMeanFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (TypeFlag==0||TypeFlag==2)//��ȡģ���С
	{
		if (TypeFlag==0)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("��ѡ���ֵ�˲�ģ���С��");
		}if (TypeFlag==2)
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("����Ӧ��ֵ�˲����ģ��ߴ磺");
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
		if(TypeFlag==1)//��ȡ����
		{
			GetDlgItem(IDC_STATIC)->SetWindowText("��ѡ���˲���������С��");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     1��     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     2��     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     3��     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     4��     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     5��     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     6��     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("	                     7��     ");
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(1);
		}
	}
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("                     1*1     ");


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void GeometricMeanFilter::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	int index;
	index = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

	if (TypeFlag==0||TypeFlag==2)
	{
		m_FileterSize=3+2*index;//ģ��ߴ�
	}
	else
	{
		if (TypeFlag==1)
		{
			m_FileterSize=index+1;//������С
		}
	}
	
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(index,m_str);
	CDialogEx::OnOK();
}
