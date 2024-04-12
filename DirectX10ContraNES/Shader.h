#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include <D3D10.h>
#include <D3DX10.h>
#include <string>

#include "Game.h"

class Shader {
private:
	ID3D10Effect* effect;
public:
	Shader(std::string shaderFileName);

};

#endif // !__SHADER_H__
