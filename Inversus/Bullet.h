#pragma once
class Bullet
{
public:
	RECT size;
	POINT pos;

	int degree;
	DIREC dir;

	int r = 255, g = 255, b = 255;

	POINT center;

	TYPE type = NONE;

	int num;

	float radian = 0;
public:
	void UpdateRadian(float time);
};

