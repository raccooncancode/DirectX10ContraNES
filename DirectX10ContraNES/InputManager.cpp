#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance() {
	if (instance == nullptr)
	{
		instance = new InputManager();
	}
	return instance;
}

void InputManager::RegisterListener(IControlable* object) {
	inputListeners.push(object);
}

void InputManager::UnRegisterCurrentListener()
{
	if (inputListeners.size() > 0)
		inputListeners.pop();
}
IControlable* InputManager::GetCurrentListener()
{
	if (inputListeners.size() > 0)
		return inputListeners.top();
	return NULL;
}

void InputManager::OnKeyDown(int keyCode)
{
	if (inputListeners.size() > 0)
		GetCurrentListener()->OnKeyDown(keyCode);
}
void InputManager::OnKeyUp(int keyCode)
{
	if (inputListeners.size() > 0)
		GetCurrentListener()->OnKeyUp(keyCode);
}
void InputManager::KeyState(BYTE* keyState)
{

}
