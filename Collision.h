#ifndef COLLISION_H
#define COLLISION_H
#include "SDL.h"
#include "Vector2D.h"

const static int s_buffer = 4;

static bool RectRect(SDL_Rect* A, SDL_Rect* B)
{
	int aHBuf = A->h / s_buffer;
	int aWBuf = A->w / s_buffer;

	int bHBuf = B->h / s_buffer;
	int bWBuf = B->w / s_buffer;

	if (A->y + aHBuf >= (B->y + B->h) - bHBuf) { return false; }
	if ((A->y + A->h) - aHBuf <= B->y + bHBuf) { return false; }
	if ((A->x + A->w) - aWBuf <= B->x + bWBuf) { return false; }
	if (A->x + aWBuf >= (B->x + B->w) - bWBuf) { return false; }

	return true;
}

























#endif
