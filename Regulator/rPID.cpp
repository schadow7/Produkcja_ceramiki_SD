#include "rPID.h"
float k, Ti, Td, N, b;
float yp, Ip, Dp; 

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
rPID::rPID(float k, float Ti, float Td)
{
	N = 1;
	b = 1;
	Ip = 0;
	Dp = 0;
	yp = 0;
}
rPID::rPID(float k, float Ti, float Td, float N, float b)
{
	Ip = 0;
	Dp = 0;
	yp = 0;
}


rPID::~rPID()
{
}

float  rPID::ObliczSterowanie(float w, float y)
{
	float e, P, I, D;
	e = b*w - y;
	P = k*e;
	I = Ip + k*Ti*e;
	D = Td / (Td + N)*(Dp - k*N*(y - yp));
	Dp = D;
	Ip = I;
	return P + I + D;
}

