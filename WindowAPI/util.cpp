#include "stdafx.h"
#include "util.h"

float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float MY_UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	float distance = sqrtf(x * x + y * y);
	float angle = acosf(x / distance);
	if (endY > startY)
	{
		angle = PI2 - angle;
	}
	return angle;
}

void MY_UTIL::showTitle(HDC hdc, const char * title, int x, int y, COLORREF color)
{
	SetTextColor(hdc, color);
	TextOut(hdc, x, y, title, strlen(title));
}
