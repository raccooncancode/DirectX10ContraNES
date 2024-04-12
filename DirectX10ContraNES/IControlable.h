#pragma once
#ifndef __ICONTROLABLE_H__
#define __ICONTROLABLE_H__
#include <Windows.h>

class IControlable
{
protected:

public:
	//virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

#endif // !__ICONTROLABLE_H__
