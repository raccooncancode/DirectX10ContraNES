#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <Windows.h>
#include <D3D10.h>
#include <D3DX10.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "debug.h"
#include "Texture.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "RectF.h"
#include "Camera.h"

#define MAX_FRAME_RATE 60
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

#define SCALING 2
/*
	Our simple game framework
*/
class CGame
{
	static CGame* __instance;
	HWND hWnd;

	int backBufferWidth = 0;
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;
	D3D10_VIEWPORT* viewPort;

	LPD3DX10SPRITE spriteObject;

	LPDIRECTINPUT8       di;
	LPDIRECTINPUTDEVICE8 didv;
	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	D3DXMATRIX projectionMatrix;
	D3DXMATRIX viewMatrix;

	HINSTANCE hInstance;

public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);


	// Draw a portion or ALL the texture at position (x,y) on the screen
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void DrawBound(float drawingX, float drawingY, float w, float h, LPTEXTURE tex);


	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	// Keyboard related functions 
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }
	D3D10_VIEWPORT* GetViewPort() { return this->viewPort; }
	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }

	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }
	D3DXMATRIX GetProjectionMatrix() { return this->projectionMatrix; }
	D3DXMATRIX GetViewMatrix() { return this->viewMatrix; }
	static CGame* GetInstance();

	~CGame();
};
#endif // !__GAME_H__