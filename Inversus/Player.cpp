#include "stdafx.h"

Player::Player()
{
	for (int i = 0; i < 6; ++i) {
		bullets[i].pos = { (long)(((i + 1) * 60.0) / 180.0 * PI), (long)(((i + 1) * 60.0) / 180.0 * PI) };
		bullets[i].degree = 20;
	}
}

void Player::DrawBullet(HDC hDC, POINT boardPos)
{
	POINT center = { boardPos.x + pos.x + (rectSize) / 2 , boardPos.y + pos.y + (rectSize) / 2 };
	HBRUSH hBrush, oldBrush;
	for (int i = 0; i < 6; ++i) {
		POINT bulletPos = { center.x + cos(bullets[i].pos.x + radian) * bullets[i].degree, center.y + sin(bullets[i].pos.y + radian) * bullets[i].degree };
		if ( i < bulletNum)
		{
			hBrush = CreateSolidBrush(RGB(bullets[i].r, bullets[i].g, bullets[i].b));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Ellipse(hDC, bulletPos.x, bulletPos.y, bulletPos.x + bullets[i].degree, bulletPos.y + bullets[i].degree);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
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

void Player::HEROCoolTime(float time)
{
	heroCoolTime -= time;
	if (heroCoolTime <= 0) {
		heroCoolTime = 1.f;
		isHero = false;
	}
}

void Player::BulletCoolTime(float time)
{
	resetBulletCoolTime -= time;
	if (resetBulletCoolTime <= 0) {
		resetBulletCoolTime = 1.f;
		bulletNum += 1;
	}
}
