#include "StdAfx.h"
#include "MyImage_.h"
#include "MainFrm.h"
#include "Image_ProcessingView.h"

MyImage_::MyImage_(void)
	: X(0)
	, Y(0)
{
	m_pBits=NULL;
	Flag=0;
	memset(probability, 0, sizeof(probability));
	//PV=GetActiveView();
}


MyImage_::~MyImage_(void)
{

	if ( m_pBits!=NULL)
	{
		int h=m_CImage.GetHeight();
		for   (int   i=0;   i<2;   i++)   
		{          
			for   (int   j=0;   j<h;   j++)         
			{   

				delete[] m_pBits[i][j];   
				m_pBits[i][j]=NULL;
			}
		}
		for (int   i=0;   i<2;   i++)
		{
			delete[] m_pBits[i];  
			m_pBits[i]=NULL;
		}
		delete[]  m_pBits;
		m_pBits=NULL;
	}
}

HRESULT MyImage_::Load(_In_z_ LPCTSTR pszFileName) 
{
	m_CImage.Load(pszFileName);
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ
	/*������ά���鲢��m_CImage���ƽ���ά����*/
	

	if (abs(nrow)!=3*w)
	{
		m_CImage.Destroy();
		return(S_FALSE );//��ֹ���ط�24λ�Ĳ�ɫͼ

	}
	//����������

	m_pBits= new  BYTE **[3];//3��ά�ȣ������ڴ�  
	for(int i=0;i<3;i++)  
	{ 
		m_pBits[i] = /*(BYTE**)*/new  BYTE*[h];   
	}   


	for(int i=0;i<3;i++)   
	{          
		for   (int j=0;j<h;j++)         
		{   
			m_pBits[i][j]=new BYTE[w];   
		}
	}

	/*���������ά����*/
		for (int j=0;j<h;j++)
		{
			for (int k=0;k<w;k++)
			{
				m_pBits[0][j][k]=psrc[j*nrow+k*3];//B
				m_pBits[1][j][k]=psrc[j*nrow+k*3+1];//G
				m_pBits[2][j][k]=psrc[j*nrow+k*3+2];//R
			}
		}
	/*������ά���鲢��m_CImage���ƽ���ά����*/
	return( S_OK );//Ϊ����CImge���Load��������ֵ��ͬ
}



BOOL  MyImage_::Draw(
	_In_ HDC hDestDC,
	_In_ int xDest,
	_In_ int yDest,
	_In_ int nDestWidth,
	_In_ int nDestHeight) const 
{
	//if(Flag==1)  return 0;
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ
	/*����ά���鸴�ƽ�m_CImage*/
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			psrc[j*nrow+k*3]=m_pBits[0][j][k];//B
			psrc[j*nrow+k*3+1]=m_pBits[1][j][k];//G
			psrc[j*nrow+k*3+2]=m_pBits[2][j][k];//R

		}
	}
	/*����ά���鸴�ƽ�m_CImage*/

	return m_CImage.Draw(hDestDC,xDest, yDest,nDestWidth, nDestHeight);//����CImage��Draw;
}
bool MyImage_::IsNull() const 
{
	return m_CImage.IsNull();
}

void MyImage_::Destroy() 
{
	m_CImage.Destroy();
}

int MyImage_::GetWidth() const 
{
	return m_CImage.GetWidth();
}
int MyImage_::GetHeight() const
{
	return m_CImage.GetHeight();
}




////draw�ᵼ��ԭʼ���ݸ���////
BOOL  MyImage_::Draw(
	_In_ HDC hDestDC,
	_In_ int xDest,
	_In_ int yDest) const
{
	//if(Flag==1)  return 0;
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ
	/*����ά���鸴�ƽ�m_CImage*/

	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			psrc[j*nrow+k*3]=m_pBits[0][j][k];//B
			psrc[j*nrow+k*3+1]=m_pBits[1][j][k];//G
			psrc[j*nrow+k*3+2]=m_pBits[2][j][k];//R

		}
	}
	/*����ά���鸴�ƽ�m_CImage*/
	//////
	//CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
 //   CImage_ProcessingView* pView = (CImage_ProcessingView*)pFrame->GetActiveView();
	////////��ȡviewָ��
	//if(pView->m_Image.Flag==1)
	//{
	//	return pView->image2.Draw(hDestDC,xDest,yDest);
	//}
	
	return m_CImage.Draw(hDestDC,xDest,yDest);
}

HRESULT MyImage_::Save(
	_In_z_ LPCTSTR pszFileName,
	_In_ REFGUID guidFileType) const
{
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ��ͼ����ʼ��ַ
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			psrc[j*nrow+k*3]=m_pBits[0][j][k];//B
			psrc[j*nrow+k*3+1]=m_pBits[1][j][k];//G
			psrc[j*nrow+k*3+2]=m_pBits[2][j][k];//R

		}
	}
	return m_CImage.Save(pszFileName,guidFileType);

}



//==============================
//�������ܣ�ͳ��ֱ��ͼ
//�����������ֱ��ͨ��probability����
//======================
void MyImage_::GetHistgran(void)
{
	BYTE *lpSrc;	//ָ��Դͼ��ָ��
	long i,j;		//ѭ������
	int w=GetWidth();
	int h=GetHeight();
	int gray[256];	//�Ҷȼ���
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	//float probability[256];
	BYTE pixel;		//����ֵ
	//BYTE *lpDIBBits=(BYTE *)m_CImage.GetBits();//���Դͼ����ʼλ��
	memset(gray,0,sizeof(gray));//��ʼ��

	for(j=0;j<h;j++)

	{
		for(i=0;i<w;i++)
		{
			pixel = m_pBits[0][j][i];
			gray[pixel]++;
		}
	}
	for(i=0;i<256;i++)
	{
		probability[i]=gray[i]/(w*h*1.0f);
	}
}
