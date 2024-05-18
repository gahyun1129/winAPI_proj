#pragma once
class Camera
{
public:
	POINT pos = { 0, 0 };
	int offset = 20;
	int degree = 10;

	bool isShake = false;

	int num = 4;

public:
	void ShakeCam(float time);
};

