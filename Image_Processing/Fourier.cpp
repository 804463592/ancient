#include "StdAfx.h"
#include "Fourier.h"
#include "FastFourierTran.h"
#include "MainFrm.h"

void Fourier(CplexNum *pTd,int wi,int he,CplexNum * pFd,CImage_ProcessingView *pv)
{
	int i,j;					//ѭ�����Ʊ���
	int wid = 1, hei = 1;		//���и���Ҷ�任�Ŀ�Ⱥ͸߶�
	int widpor=0,heipor=0;		//wid hei :2���ݴ���

//////////������ԲμӸ���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2���ݴη���///////////
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

	/////////////X����FFT////////////////
	for (i=0;i<hei;i++)
	{
		FastFourierTran(&pTd[wid*i],&pFd[wid*i],widpor);
		//���ý�����ǰ50%
		double p;
		p=(double)i/(double)(hei);
		int k=p*50;
		pv->SetProgress(k);
	}

	///////////////����ת��///////////
	for(i=0;i<hei;i++)
		for(j=0;j<wid;j++)
			pTd[hei * j+i] =pFd[wid *i +j];

	/////////////Y����һάFFT////////////////
	for (j=0;j<wid;j++)
	{
		FastFourierTran(&pTd[j*hei],&pFd[hei*j],heipor);

		//���ý�������50%
		double p;
		p=(double)j/(double)(wid);
		int k=p*50;
		pv->SetProgress(k+50);
	}
	pv->SetProgress(0);//�ָ�������

	////////////pFd�洢�˶���Ϊ����Ҷ�任�Ľ��������Ҫת�û�������pTd/////////
	for(i=0;i<hei;i++)
		for(j=0;j<wid;j++)
			pTd[wid *i + j] = pFd[hei *j + i];


}