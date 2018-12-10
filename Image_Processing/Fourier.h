#include "CplexNum.h"
#include "Image_ProcessingView.h"
/************************************************************************/
/* 函数名称：
			void Fourier(CplexNum *pTd,int wid,int hei,CplexNum * pFd);
   函数参数：
		   CplexNum * pTd		指向时域数组指针
		   int wid				图像宽度
		   int hei				图像高度
		   CplexNum * pFd		指向频域数组指针

	函数功能：二维FFT
	*/
/************************************************************************/
void Fourier(CplexNum *pTd,int wid,int hei,CplexNum * pFd,CImage_ProcessingView* p);