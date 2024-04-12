#pragma once
#ifndef __RECTF_H__
#define __RECTF_H__

class RectF {
public:
	float x, y, w, h;
	RectF(float x, float y, float w, float h);
	float GetMiddleXOffset();
	float GetMiddleYOffset();
	bool IsOverlap(RectF* bound);
	bool IsContain(RectF* bound);
	int IsOverlap(float xx,float yy,float ww,float hh);
	int IsContain(float xx,float yy,float ww,float hh);
	void UpdateBoundSize(float w, float h);
	void UpdateBoundLocation(float x, float y);
};
typedef RectF* Bound;

#endif // !__RECTF_H__
