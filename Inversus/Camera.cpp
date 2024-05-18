#include "stdafx.h"

void Camera::ShakeCam(float time)
{
	if (isShake) {
		pos.x += degree;
		if (abs(pos.x) > offset) {
			degree = -degree;
			num -= 1;
			if (num < 0) {
				isShake = false;
				num = 4;
				pos = { 0, 0 };
			}
		}
	}
}
