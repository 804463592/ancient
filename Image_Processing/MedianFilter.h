#pragma once


// MedianFilter �Ի���

class MedianFilter : public CDialogEx
{
	DECLARE_DYNAMIC(MedianFilter)

public:
	MedianFilter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MedianFilter();

// �Ի�������
	enum { IDD = IDD_MedianFilter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_FilterSize;
};
