#pragma once
class rPID
{
	float k, Ti, Td, N, b;
	float yp, Ip, Dp; 
public:
	rPID();
	rPID(float k, float Ti, float Td);
	rPID(float k, float Ti, float Td, float N, float b);
	float ObliczSterowanie(float w, float y);
	float Getk();
	float GetTi();
	float GetTd();
	void Setk(float w);
	void SetTi(float w);
	void SetTd(float w);
	~rPID();
};


