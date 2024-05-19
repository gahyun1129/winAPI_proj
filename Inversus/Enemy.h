#pragma once
class Enemy
{
public:
	RECT size;
	POINT pos;
	int rectSize;

	float coolTime = 2.f;
	DIREC dir = (DIREC)(rand() % 4);
	ENEMYTYPE type = (ENEMYTYPE)(rand() % 2);
};

