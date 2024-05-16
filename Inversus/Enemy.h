#pragma once
class Enemy
{
public:
	RECT size;
	POINT pos;
	int rectSize;

	int coolTime = 0;
	DIREC dir = (DIREC)(rand() % 4);
};

