#include "CplexNum.h"
#include "Image_ProcessingView.h"
/************************************************************************/
/* �������ƣ�
			void Fourier(CplexNum *pTd,int wid,int hei,CplexNum * pFd);
   ����������
		   CplexNum * pTd		ָ��ʱ������ָ��
		   int wid				ͼ����
		   int hei				ͼ��߶�
		   CplexNum * pFd		ָ��Ƶ������ָ��

	�������ܣ���άFFT
	*/
/************************************************************************/
void Fourier(CplexNum *pTd,int wid,int hei,CplexNum * pFd,CImage_ProcessingView* p);