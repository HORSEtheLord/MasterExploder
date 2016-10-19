#include <ctime>
#include <memory>
#include <Windows.h>
#include <Windowsx.h>

#include "GameObject.h"
#include "Graphics.h"
#include "Logger.h"
#include "Terrain.h"
#include "Unit.h"
#include "Utils.h"
#include "Timer.h"
#include "Building.h"
#include "EnemyUnit.h"
#include "CollisionChecker.h"
#include <random>
#include "Obstacle.h"

std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects;
std::shared_ptr<Graphics> graphics;
std::shared_ptr<Terrain> terrain;
std::shared_ptr<Unit> unit;
std::shared_ptr<Building> building;
std::shared_ptr<Timer> timer;

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

	if (uMsg == WM_RBUTTONUP)
	{
		if (unit)
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			int newX = xPos / TILE_WIDTH;
			int newY = yPos / TILE_HEIGHT;

			//MKOS: dynamic_pointer_cast to kiepski pomys�
			std::shared_ptr<GameObject> target = CollisionChecker::GetInstance().At(newX, newY);
			std::shared_ptr<AttackableGameObject> attackableTarget;
			if (target != nullptr && (attackableTarget = std::dynamic_pointer_cast<AttackableGameObject>(target)))
			{
				unit->Attack(attackableTarget);
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

bool initGameObjects()
{
	for (auto it = gameObjects->cbegin(); it != gameObjects->cend(); ++it)
	{
		if (!(*it)->Init(graphics))
		{
			Logger::Log((*it)->GetName() + L" initialization failed.");
			return false;
		}
	}

	return true;
}

void updateGameObjects()
{
	for (auto it = gameObjects->cbegin(); it != gameObjects->cend(); ++it)
	{
		(*it)->Update();
	}
}

void drawGameObjects()
{
	for (auto it = gameObjects->cbegin(); it != gameObjects->cend(); ++it)
	{
		(*it)->Draw(graphics);
	}
}

void unitialize()
{
	gameObjects->clear();

	CollisionChecker::GetInstance().Unload();

	unit = nullptr;
	terrain = nullptr;
	graphics = nullptr;
	building = nullptr;
	timer = nullptr;

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
		return false;
	}

	gameObjects = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();

	if (!CollisionChecker::Init(TERRAIN_WIDTH, TERRAIN_HEIGHT, gameObjects))
	{
		Logger::Log(L"CollisionChecker initialization failed.");
		unitialize();
		return -1;
	}

	building = std::make_shared<Building>(39, 29, 300);
	gameObjects->push_back(building);

	unit = std::make_shared<Unit>(0, 0, 40, 200, 20, 10);
	gameObjects->push_back(unit);

	std::shared_ptr<EnemyUnit> enemyUnit = std::make_shared<EnemyUnit>(39, 28, 40, 300, 10);
	enemyUnit->Attack(unit);
	gameObjects->push_back(enemyUnit);

	enemyUnit = std::make_shared<EnemyUnit>(15, 20, 40, 300, 10);
	enemyUnit->Attack(unit);
	gameObjects->push_back(enemyUnit);
	enemyUnit = nullptr;

	std::default_random_engine engine(time(0));
	std::uniform_int_distribution<unsigned> distribution(0, 4);

	CollisionChecker::GetInstance().Update();

	for (int i = 0; i < TERRAIN_WIDTH * TERRAIN_HEIGHT; ++i)
	{
		if (!CollisionChecker::GetInstance().IsNodeOccupied(CALCULATE_X(i), CALCULATE_Y(i)))
		{
			if (!distribution(engine))
			{
				gameObjects->push_back(std::make_shared<Obstacle>(CALCULATE_X(i), CALCULATE_Y(i)));
			}
		}
	}

	if (!initGameObjects())
	{
		Logger::Log(L"GameObjects initialization failed.");
		unitialize();
		return -1;
	}

	if (!AStarAlgorithm::Init(TERRAIN_WIDTH, TERRAIN_HEIGHT))
	{
		Logger::Log(L"AStarAlgorithm initialization failed.");
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
				updateGameObjects();
				CollisionChecker::GetInstance().Update();
				lag -= MS_PER_UPDATE;
			}

			graphics->BeginDraw();
			terrain->Draw(graphics);
			drawGameObjects();
			graphics->EndDraw();
		}
	}

	unitialize();

	Logger::Log(L"Application ended.");
	return 0;
}