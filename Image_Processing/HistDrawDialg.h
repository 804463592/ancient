#pragma once


// HistDrawDialg �Ի���

class HistDrawDialg : public CDialogEx
{
	DECLARE_DYNAMIC(HistDrawDialg)

public:
	HistDrawDialg(CImage_ProcessingView* pParent);   // ��׼���캯��

	virtual ~HistDrawDialg();

// �Ի�������
	enum { IDD = IDD_HistDraw };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CWnd* pWnd;
	CDC* pDC;
	CImage_ProcessingView* pv;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
