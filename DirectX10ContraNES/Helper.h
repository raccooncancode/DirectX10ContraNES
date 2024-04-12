#pragma once
#ifndef __HELPER_H__
#define __HELPER_H__

#include <string>
#include <D3DX10.h>
#include <D3D10.h>
using namespace std;
class Helper {
public:
	static string aXToString(int ax) {
		if (ax == 1)
			return "Right";
		else if (ax == -1)
			return "Left";
		else
			return "";
	}
	static string angleToString(float angle) {
		if (angle == D3DX_PI)
			return "180";
		else if (angle == D3DX_PI / 2)
			return "90";
		else if (angle == D3DX_PI / 4)
			return "45";
		else if (angle == D3DX_PI / 2 + D3DX_PI / 4)
			return "135";
		else if (angle == D3DX_PI + D3DX_PI / 4)
			return "225";
		else if (angle == D3DX_PI + D3DX_PI / 2)
			return "270";
		else if (angle == D3DX_PI + D3DX_PI / 2 + D3DX_PI / 4)
			return "315";	
		return "0";
	}
};

#endif // !__HELPER_H__
