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

	for (int i = 0; i < 6; ++i) {
		POINT bulletPos = { center.x + cos(bullets[i].pos.x + radian) * 15, center.y + sin(bullets[i].pos.y + radian) * 15 };
		if ( i < bulletNum)
		{
			Ellipse(hDC, bulletPos.x + 0, bulletPos.y + 0, bulletPos.x + 10, bulletPos.y + 10);
		}
	}
}
