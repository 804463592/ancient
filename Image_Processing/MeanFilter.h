#pragma once


// MeanFilter 均值滤波 对话框

class MeanFilter : public CDialogEx
{
	DECLARE_DYNAMIC(MeanFilter)

public:
	MeanFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MeanFilter();

// 对话框数据
	enum { IDD = IDD_MeanFilter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_FileterSize;
};
