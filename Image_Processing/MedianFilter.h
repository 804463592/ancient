#pragma once


// MedianFilter 对话框

class MedianFilter : public CDialogEx
{
	DECLARE_DYNAMIC(MedianFilter)

public:
	MedianFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MedianFilter();

// 对话框数据
	enum { IDD = IDD_MedianFilter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_FilterSize;
};
