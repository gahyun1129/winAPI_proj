#pragma once
class Player
{
public:
	RECT size;
	POINT pos;
	int rectSize;
	int bulletNum = 6;

	float radian = 0.0f;

	Bullet bullets[6];

public:
	Player();
	void DrawBullet(HDC hDC, POINT boardPos);
};

