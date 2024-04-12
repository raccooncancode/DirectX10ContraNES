#include "RectF.h"

RectF::RectF(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

float RectF::GetMiddleXOffset() { return x + (w / 2); }
float RectF::GetMiddleYOffset() { return y + (h / 2); }
bool RectF::IsOverlap(RectF* bound) {
	return !(bound->x + bound->w < x
		||
		bound->y + bound->h < y
		||
		bound->x > x + w
		||
		bound->y > y + h
		);
}
int RectF::IsOverlap(float xx,float yy, float ww, float hh) {
	return !(xx + ww < x
		||
		yy + hh < y
		||
		xx > x + w
		||
		yy > y + h
		);
}
bool RectF::IsContain(RectF* bound) {
	return (bound->x + bound->w <= x + w)
		&&
		(bound->x >= x)
		&&
		(bound->y >= y)
		&&
		(bound->y + bound->h <= y + h);
}
int RectF::IsContain(float xx, float yy, float ww, float hh) {
	return (xx + ww <= x + w)
		&&
		(xx >= x)
		&&
		(yy >= y)
		&&
		(yy + hh <= y + h);
}
void RectF::UpdateBoundSize(float w, float h) { this->w = w; this->h = h; }
void RectF::UpdateBoundLocation(float x, float y) { this->x = x; this->y = y; }
