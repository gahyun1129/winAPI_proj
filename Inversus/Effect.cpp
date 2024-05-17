#include "stdafx.h"

bool Effect::EffectCoolTime(float time)
{
	coolTime -= time;
	size.left -= 1;
	size.top -= 1;
	size.right += 1;
	size.bottom += 1;
	if (coolTime < 0) {
		return true;
	}
	return false;
}
