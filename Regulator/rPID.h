#pragma once
class rPID
{
public:
	rPID();
	rPID(float k, float Ti, float Td);
	rPID(float k, float Ti, float Td, float N, float b);
	float ObliczSterowanie(float w, float y);
	~rPID();
};

