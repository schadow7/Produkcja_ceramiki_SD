#include "rPID.h"
using namespace std;

rPID::rPID()
{
	k = 1;
	Ti = 1;
	Td = 1;
	N = 1;
	b = 1;
	Ip = 0;
	Dp = 0;
	yp = 0;
}
rPID::rPID(float nk, float nTi, float nTd)
{
	k = nk;
	Ti = nTi;
	Td = nTd;
	N = 1;
	b = 1;
	Ip = 0;
	Dp = 0;
	yp = 0;
}
rPID::rPID(float nk, float nTi, float nTd, float nN, float nb)
{
	k = nk;
	Ti = nTi;
	Td = nTd;
	N = nN;
	b = nb;
	Ip = 0;
	Dp = 0;
	yp = 0;
}


rPID::~rPID()
{
}

float  rPID::ObliczSterowanie(float w, float y)
{
	float e, P, I, D, u;
	e = b*w - y;
	P = k*e;
	//anywindup
	I= ((u <= 0) || (u >= 1000))? 0.0 : Ip + k*Ti*e;
	//I = Ip + k*Ti*e;
	D = Td / (Td + N)*(Dp - k*N*(y - yp));
	Dp = D;
	Ip = I;
	u= P + I + D;
	//ograniczenie sterowania
	u = (u >= 1000) ? 1000 : u;
	u = (u < 0) ? 0 : u;
	return u;
}



float rPID::Getk()
{
	return k;
}


float rPID::GetTi()
{
	return Ti;
}


float rPID::GetTd()
{
	return Td;
}

void rPID::Setk(float w)
{
	k = w;
}
void rPID::SetTi(float w)
{
	Ti = w;
}
void rPID::SetTd(float w)
{
	Td= w;
}