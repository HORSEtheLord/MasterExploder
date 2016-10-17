#include <ctime>
#include <memory>
#include <Windows.h>
#include <Windowsx.h>

#include "Graphics.h"
#include "Logger.h"
#include "Terrain.h"
#include "Unit.h"
#include "Utils.h"
#include "Timer.h"
#include "Building.h"
#include "EnemyUnit.h"

std::shared_ptr<Graphics> graphics;
std::shared_ptr<Terrain> terrain;
std::shared_ptr<Unit> unit;
std::shared_ptr<Building> building;
std::shared_ptr<Timer> timer;
std::shared_ptr<EnemyUnit> enemyUnit;

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

			/*LARGE_INTEGER t;
			QueryPerformanceFrequency(&t);
			long long frequency = t.QuadPart;

			QueryPerformanceCounter(&t);
			long long previousTime = t.QuadPart;*/

			unit->Move(newX, newY);

			/*QueryPerformanceCounter(&t);
			long long currentTime = t.QuadPart;
			double elapsedTime = currentTime - previousTime;
			previousTime = currentTime;
			double milliseconds = 1000 * elapsedTime / frequency;
			milliseconds = 0;*/
		}
	}

	if (uMsg == WM_RBUTTONUP)
	{
		if (unit)
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			int newX = xPos / TILE_WIDTH;
			int newY = yPos / TILE_HEIGHT;

			/*if (building && building->GetLocationX() == newX && building->GetLocationY() == newY)
			{
				unit->Attack(building);
			}*/
			/*else */
			if (enemyUnit && enemyUnit->GetLocationX() == newX && enemyUnit->GetLocationY() == newY)
			{
				unit->Attack(enemyUnit);
			}
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

void unitialize()
{
	unit = nullptr;
	terrain = nullptr;
	graphics = nullptr;
	building = nullptr;
	timer = nullptr;
	enemyUnit = nullptr;

	CoUninitialize();
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
	
	HRESULT hr = CoInitialize(NULL);

	if (hr != S_OK)
	{
		Logger::Log(L"CoInitialize failed.");
		return -1;
	}

	graphics = std::make_shared<Graphics>();

	if (!graphics->Init(windowHandle))
	{
		Logger::Log(L"Graphics initialization failed.");
		unitialize();
		return -1;
	}

	terrain = std::make_shared<Terrain>(TERRAIN_WIDTH, TERRAIN_HEIGHT, true);

	if (!terrain->Init(graphics))
	{
		Logger::Log(L"Terrain initialization failed.");
		unitialize();
		return -1;
	}

	unit = std::make_shared<Unit>(0, 0, 40, 20, 10);

	if (!unit->Init(graphics))
	{
		Logger::Log(L"Unit initialization failed.");
		unitialize();
		return -1;
	}

	if (!AStarAlgorithm::Init(TERRAIN_WIDTH, TERRAIN_HEIGHT, terrain->GetCollisionMap()))
	{
		Logger::Log(L"AStarAlgorithm initialization failed.");
		unitialize();
		return -1;
	}

	building = std::make_shared<Building>(39, 29, 300);

	if (!building->Init(graphics))
	{
		Logger::Log(L"Building initialization failed.");
		unitialize();
		return -1;
	}

	enemyUnit = std::make_shared<EnemyUnit>(39, 28, 300);

	if (!enemyUnit->Init(graphics))
	{
		Logger::Log(L"EnemyUnit initialization failed.");
		unitialize();
		return -1;
	}

	ShowWindow(windowHandle, nCmdShow);

	timer = std::make_shared<Timer>();

	double lag = 0.0;

	MSG message;
	message.message = WM_NULL;
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}
		else
		{
			lag += timer->Tick();

			while (lag >= MS_PER_UPDATE)
			{
				unit->Update();
				lag -= MS_PER_UPDATE;
			}

			graphics->BeginDraw();
			terrain->Draw(graphics);
			building->Draw(graphics);
			unit->Draw(graphics);
			enemyUnit->Draw(graphics);
			graphics->EndDraw();
		}
	}

	unitialize();

	Logger::Log(L"Application ended.");
	return 0;
}