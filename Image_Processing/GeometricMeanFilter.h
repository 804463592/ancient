#pragma once


// GeometricMeanFilter 对话框

class GeometricMeanFilter : public CDialogEx
{
	DECLARE_DYNAMIC(GeometricMeanFilter)

public:
	GeometricMeanFilter(int n=0,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GeometricMeanFilter();

// 对话框数据
	enum { IDD = IDD_GeometricMeanFilter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// //获取选择
	CString m_str;
	virtual void OnOK();
	// //模板尺寸
	int m_FileterSize;
	// 类型flag
	int TypeFlag;
};
