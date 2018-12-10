#include"stdafx.h"
#include "Calculatt.h"

CplexNum FSAdd(CplexNum a,CplexNum b)
{
	a.re=a.re+b.re;
	a.im=a.im+b.im;
	return a;
}
CplexNum FSSub(CplexNum a,CplexNum b)
{
	a.re=a.re-b.re;
	a.im=a.im-b.im;
	return a;
}
CplexNum FSMul(CplexNum a,CplexNum b)
{
	CplexNum c;
	c.re=a.re*b.re-a.im*b.im;
	c.im=a.im*b.re+a.re*b.im;
	return c;
}