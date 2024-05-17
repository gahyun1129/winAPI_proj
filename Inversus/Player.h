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

	bool isDead = false;

	float coolTime = 3.f;

	int health = 3;

	int comboStack = 0;

	float comboCoolTime = 3.f;

public:
	Player();
	void DrawBullet(HDC hDC, POINT boardPos);
	void ReviveCoolTime(float time);
	void ComboCoolTime(float time);
};

