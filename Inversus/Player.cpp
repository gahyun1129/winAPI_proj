#include "stdafx.h"

Player::Player()
{
	for (int i = 0; i < 6; ++i) {
		bullets[i].pos = { (long)(((i + 1) * 60.0) / 180.0 * PI), (long)(((i + 1) * 60.0) / 180.0 * PI) };
	}
}

void Player::DrawBullet(HDC hDC, POINT boardPos)
{
	POINT center = { boardPos.x + pos.x + rectSize / 2 , boardPos.y + pos.y + rectSize / 2 };
	HBRUSH hBrush, oldBrush;
	for (int i = 0; i < 6; ++i) {
		POINT bulletPos = { center.x + cos(bullets[i].pos.x + radian) * 20, center.y + sin(bullets[i].pos.y + radian) * 20 };
		if ( i < bulletNum)
		{
			Ellipse(hDC, bulletPos.x - 5, bulletPos.y - 5, bulletPos.x + 15, bulletPos.y + 15);
		}
	}
}

void Player::ReviveCoolTime(float time)
{
	coolTime -= time;
	if (coolTime < 0) {
		isDead = false;
		coolTime = 3.f;
	}
}

void Player::ComboCoolTime(float time)
{
	comboCoolTime -= time;
	if (comboCoolTime < 0) {
		comboStack = 0;
		comboCoolTime = 3.f;
	}
}
