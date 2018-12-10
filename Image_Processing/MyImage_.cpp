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
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//获得m_CImage最后一行的像素地址
	/*创建三维数组并将m_CImage复制进三维数组*/
	

	if (abs(nrow)!=3*w)
	{
		m_CImage.Destroy();
		return(S_FALSE );//防止加载非24位的彩色图

	}
	//？？？？？

	m_pBits= new  BYTE **[3];//3个维度；分配内存  
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

	/*创建完成三维数组*/
		for (int j=0;j<h;j++)
		{
			for (int k=0;k<w;k++)
			{
				m_pBits[0][j][k]=psrc[j*nrow+k*3];//B
				m_pBits[1][j][k]=psrc[j*nrow+k*3+1];//G
				m_pBits[2][j][k]=psrc[j*nrow+k*3+2];//R
			}
		}
	/*创建三维数组并将m_CImage复制进三维数组*/
	return( S_OK );//为了与CImge类的Load函数返回值相同
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
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//获得m_CImage最后一行的像素地址
	/*将三维数组复制进m_CImage*/
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			psrc[j*nrow+k*3]=m_pBits[0][j][k];//B
			psrc[j*nrow+k*3+1]=m_pBits[1][j][k];//G
			psrc[j*nrow+k*3+2]=m_pBits[2][j][k];//R

		}
	}
	/*将三维数组复制进m_CImage*/

	return m_CImage.Draw(hDestDC,xDest, yDest,nDestWidth, nDestHeight);//调用CImage的Draw;
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




////draw会导致原始数据更改////
BOOL  MyImage_::Draw(
	_In_ HDC hDestDC,
	_In_ int xDest,
	_In_ int yDest) const
{
	//if(Flag==1)  return 0;
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//获得m_CImage最后一行的像素地址
	/*将三维数组复制进m_CImage*/

	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			psrc[j*nrow+k*3]=m_pBits[0][j][k];//B
			psrc[j*nrow+k*3+1]=m_pBits[1][j][k];//G
			psrc[j*nrow+k*3+2]=m_pBits[2][j][k];//R

		}
	}
	/*将三维数组复制进m_CImage*/
	//////
	//CMainFrame*   pFrame=(CMainFrame*)AfxGetMainWnd();   
 //   CImage_ProcessingView* pView = (CImage_ProcessingView*)pFrame->GetActiveView();
	////////获取view指针
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
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//获得m_CImage最后一行的像素地址即图像起始地址
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
//函数功能：统计直方图
//无输入输出，直接通过probability保存
//======================
void MyImage_::GetHistgran(void)
{
	BYTE *lpSrc;	//指向源图的指针
	long i,j;		//循环计数
	int w=GetWidth();
	int h=GetHeight();
	int gray[256];	//灰度计数
	int nrow=m_CImage.GetPitch();//获得m_CImage每一行像素的RGB所占用的存储空间的大小
	//float probability[256];
	BYTE pixel;		//像素值
	//BYTE *lpDIBBits=(BYTE *)m_CImage.GetBits();//获得源图像起始位置
	memset(gray,0,sizeof(gray));//初始化

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
