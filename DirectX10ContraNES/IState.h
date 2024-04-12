#pragma once
#ifndef __ISTATE_H__
#define __ISTATE_H__
#include <string>
class IState {
protected:

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update(float dt) = 0;
	virtual void OnKeyDown(int keyCode) = 0;
	virtual void OnKeyUp(int keyCode) = 0;
	virtual std::string GetStateName() = 0;
};
#endif // !__ISTATE_H__
