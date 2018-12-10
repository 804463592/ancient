#include "StdAfx.h"
#include "Fourier.h"
#include "FastFourierTran.h"
#include "MainFrm.h"

void Fourier(CplexNum *pTd,int wi,int he,CplexNum * pFd,CImage_ProcessingView *pv)
{
	int i,j;					//循环控制变量
	int wid = 1, hei = 1;		//进行傅立叶变换的宽度和高度
	int widpor=0,heipor=0;		//wid hei :2的幂次数

//////////计算可以参加傅里叶变换的宽度和高度（2的幂次方）///////////
	while (wid*2<=wi)
	{
		wid *= 2;
		widpor++;
	}
	while (hei*2<=he)
	{
		hei *= 2;
		heipor++;
	}

	/////////////X方向FFT////////////////
	for (i=0;i<hei;i++)
	{
		FastFourierTran(&pTd[wid*i],&pFd[wid*i],widpor);
		//设置进度条前50%
		double p;
		p=(double)i/(double)(hei);
		int k=p*50;
		pv->SetProgress(k);
	}

	///////////////矩阵转置///////////
	for(i=0;i<hei;i++)
		for(j=0;j<wid;j++)
			pTd[hei * j+i] =pFd[wid *i +j];

	/////////////Y方向一维FFT////////////////
	for (j=0;j<wid;j++)
	{
		FastFourierTran(&pTd[j*hei],&pFd[hei*j],heipor);

		//设置进度条后50%
		double p;
		p=(double)j/(double)(wid);
		int k=p*50;
		pv->SetProgress(k+50);
	}
	pv->SetProgress(0);//恢复进度条

	////////////pFd存储了俄日为傅立叶变换的结果，但需要转置回来存在pTd/////////
	for(i=0;i<hei;i++)
		for(j=0;j<wid;j++)
			pTd[wid *i + j] = pFd[hei *j + i];


}