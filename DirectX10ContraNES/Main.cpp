#include <windows.h>

#include "debug.h"
#include "Game.h"
#include "TextureManager.h"
//#include "SceneManager.h"
#include "Map.h"
//#include "Soldier.h"
#include "Bill.h"
#include "TestObject.h"
#include "Camera.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Contra NES GAME"
#define WINDOW_ICON_PATH L"Icon\\contra.ico"


#define BACKGROUND_COLOR D3DXCOLOR(0.0f/255,0.0f/255,0.0f/255, 0.0f)

#define SCREEN_WIDTH 270
#define SCREEN_HEIGHT 240 
#define SCREEN_SCALING 2

#define MS_PER_UPDATE 1000.0f/60

HWND hWnd;

Map* gMap;
std::vector<GameObject*> objects;
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResources()
{
	TextureManager* textures = TextureManager::GetInstance();
	textures->Add(0, L"Textures\\Bill.png");
	textures->Add(-100, L"Textures\\Bound.png");
	textures->Add(-99, L"Textures\\BulletSmall.png");
	textures->Add(-98, L"Textures\\BulletBig.png");
	gMap = new Map(1,true);
}



void Update(DWORD dt)
{
	gMap->Update(dt);
	//bill->Update(dt);
	//bill->Update(dt);
	//soldier->Update(dt);
	//Camera::GetInstance()->Update(bill);
	//if (bill->GetBillData()->GetX() >= soldier->GetSoldierData()->GetX()-10
	//	&&
	//	bill->GetBillData()->GetX() <= soldier->GetSoldierData()->GetX()+10
	//	)
	//{
	//	timeIntersect++;
	//	DebugOut(L"\nIntersect: %d",timeIntersect);
	//}

}
void Render()
{
	if (GetActiveWindow() != hWnd)
		return;
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	//o1->Render();
	/*for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}*/
	//bg->Draw(3326, 240);
	//SceneManager::GetInstance()->Render();
	gMap->Render();
	//bill->Render();
	spriteHandler->Flush();
	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	__int64 updatePerSec = 0;

	QueryPerformanceFrequency((LARGE_INTEGER*)&updatePerSec);

	float secsPerUpdate = 1.0f / (float)updatePerSec;

	float lag = 0.0f;

	unsigned int nFrameCounts = 0;

	float timeCount = 0;

	__int64 currTimeStamp = 0;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	bool isRender;
	double elapsedInMilisecond;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		isRender = false;

		QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);

		elapsedInMilisecond = (double)(currTimeStamp - prevTimeStamp) * secsPerUpdate * 1000.0f; //to milisecond
		prevTimeStamp = currTimeStamp;

		lag += elapsedInMilisecond;
		timeCount += elapsedInMilisecond;



		if (timeCount >= (double)1000.0f)
		{
			//DebugOutTitle(L"[FPS]: %d", nFrameCounts);
			nFrameCounts = 0;
			timeCount = 0;
		}

		while (lag >= MS_PER_UPDATE)
		{
			isRender = true;
			Update(lag);
			CGame::GetInstance()->ProcessKeyboard();
			lag -= MS_PER_UPDATE;
		}
		if (isRender)
		{
			Render();
			nFrameCounts++;

		}

		
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);
	
	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);
	game->InitKeyboard();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * SCREEN_SCALING, SCREEN_HEIGHT * SCREEN_SCALING, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Camera::GetInstance()->UpdateCameraSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	LoadResources();

	Run();

	return 0;
}