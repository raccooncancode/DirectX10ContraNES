#pragma once
#ifndef __OBJECTENUM_H__
#define __OBJECTENUM_H__

enum ObjectTag{
	Player,
	Bullet,
	Enemy,
	Flatform,
	Other
};
enum ObjectXDirection {
	Left = -1,
	Right = 1,
	NoneX=0,
};
enum ObjectYDirection {
	Up = 1,
	Down = -1,
	NoneY = 0
};
#endif // !__OBJECTENUM_H__