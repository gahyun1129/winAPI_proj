#pragma once
class Effect
{
public:
	RECT size;
	POINT pos;
	float coolTime = 2.f;
	int r, g, b;

	bool EffectCoolTime(float time);
};

