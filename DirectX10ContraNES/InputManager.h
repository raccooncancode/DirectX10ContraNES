#pragma once
#ifndef __InputManager_H__
#define __InputManager_H__

#include "IControlable.h"
#include <stack>
#include "debug.h"
class InputManager
{
private:
	static InputManager* instance;
	std::stack<IControlable*> inputListeners;
	InputManager(){}
public:
	static InputManager* GetInstance();
	void RegisterListener(IControlable* object);
	void UnRegisterCurrentListener();
	IControlable* GetCurrentListener();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void KeyState(BYTE* keyState);
};


#endif // !__InputManager_H__
