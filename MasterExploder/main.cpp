#include <ctime>
#include <Windows.h>
#include <Windowsx.h>

#include "Graphics.h"
#include "Logger.h"
#include "Terrain.h"
#include "Unit.h"
#include "Utils.h"

Graphics *graphics;
Terrain *terrain;
Unit *unit;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	if (uMsg == WM_LBUTTONUP)
	{
		if (unit)
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			int newX = xPos / TILE_WIDTH;
			int newY = yPos / TILE_HEIGHT;

			unit->Move(newX, newY);
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND createWindow(HINSTANCE hInstance)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Master Exploder", WS_OVERLAPPEDWINDOW, 100, 100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	return windowHandle;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	Logger::Clear();
	Logger::Log(L"Application started.");

	HWND windowHandle = createWindow(hInstance);

	if (!windowHandle)
	{
		Logger::Log(L"Window creation failed.");
		return -1;
	}

	graphics = new Graphics();

	if (!graphics->Init(windowHandle))
	{
		Logger::Log(L"Graphics initialization failed.");
		delete graphics;
		return -1;
	}

	terrain = new Terrain(TERRAIN_WIDTH, TERRAIN_HEIGHT, true);

	if (!AStarAlgorithm::Init(TERRAIN_WIDTH, TERRAIN_HEIGHT, terrain->GetMap()))
	{
		Logger::Log(L"AStarAlgorithm initialization failed.");
		delete terrain;
		delete graphics;
		return -1;
	}

	unit = new Unit(0, 0);

	ShowWindow(windowHandle, nCmdShow);

	if (!terrain->Init(graphics))
	{
		Logger::Log(L"Terrain initialization failed.");
		delete unit;
		delete terrain;
		delete graphics;
		return -1;
	}

	if (!unit->Init(graphics))
	{
		Logger::Log(L"Unit initialization failed.");
		delete unit;
		delete terrain;
		delete graphics;
		return -1;
	}

	LARGE_INTEGER t;

	QueryPerformanceFrequency(&t);
	long long frequency = t.QuadPart;

	QueryPerformanceCounter(&t);
	long long previousTime = t.QuadPart;
	double lag = 0.0;

	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_DESTROY)
			{
				delete unit;
				delete terrain;
			}

			DispatchMessage(&message);
		}
		else
		{
			QueryPerformanceCounter(&t);
			long long currentTime = t.QuadPart;
			double elapsedTime = currentTime - previousTime;
			previousTime = currentTime;
			lag += 1000 * elapsedTime / frequency;

			while (lag >= MS_PER_UPDATE)
			{
				unit->Update();
				lag -= MS_PER_UPDATE;
			}

			graphics->BeginDraw();
			terrain->Draw(graphics);
			unit->Draw(graphics);
			graphics->EndDraw();
		}
	}

	delete graphics;

	Logger::Log(L"Application ended.");
	return 0;
}