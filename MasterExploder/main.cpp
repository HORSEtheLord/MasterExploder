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
#include "EntityManager.h"
#include "SpriteManager.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "AStarSystem.h"

//std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects;
//std::shared_ptr<Graphics> graphics;
Graphics graphics;
std::shared_ptr<Terrain> terrain;
//std::shared_ptr<Unit> unit;
//std::shared_ptr<Building> building;
std::shared_ptr<Timer> timer;
EntityManager entityManager;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	if (uMsg == WM_LBUTTONUP)
	{
		std::reference_wrapper<AStarComponent> aStarComponent = entityManager.m_aStarComponents.GetComponent(0);
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);

		int newX = xPos / TILE_WIDTH;
		int newY = yPos / TILE_HEIGHT;

		aStarComponent.get().Activate(newX, newY);
	}

	//if (uMsg == WM_RBUTTONUP)
	//{
	//	if (unit)
	//	{
	//		int xPos = GET_X_LPARAM(lParam);
	//		int yPos = GET_Y_LPARAM(lParam);

	//		int newX = xPos / TILE_WIDTH;
	//		int newY = yPos / TILE_HEIGHT;

	//		//MKOS: dynamic_pointer_cast to kiepski pomys³
	//		std::shared_ptr<GameObject> target = CollisionChecker::GetInstance().At(newX, newY);
	//		std::shared_ptr<AttackableGameObject> attackableTarget;
	//		if (target != nullptr && (attackableTarget = std::dynamic_pointer_cast<AttackableGameObject>(target)))
	//		{
	//			unit->Attack(attackableTarget);
	//		}
	//	}
	//}

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

//bool initGameObjects()
//{
//	for (auto it = gameObjects->cbegin(); it != gameObjects->cend(); ++it)
//	{
//		if (!(*it)->Init(graphics))
//		{
//			Logger::Log((*it)->GetName() + L" initialization failed.");
//			return false;
//		}
//	}
//
//	return true;
//}

//void updateGameObjects()
//{
//	for (auto it = gameObjects->cbegin(); it != gameObjects->cend(); ++it)
//	{
//		(*it)->Update();
//	}
//}
//
//void drawGameObjects()
//{
//	for (auto it = gameObjects->cbegin(); it != gameObjects->cend(); ++it)
//	{
//		(*it)->Draw(graphics);
//	}
//}

void unitialize()
{
	//gameObjects->clear();

	//CollisionChecker::GetInstance().Unload();

	//unit = nullptr;
	terrain = nullptr;
	//building = nullptr;
	timer = nullptr;

	SpriteManager::GetInstance().Unload();

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

	if (!graphics.Init(windowHandle))
	{
		Logger::Log(L"Graphics initialization failed.");
		unitialize();
		return -1;
	}

	if (!SpriteManager::GetInstance().Load(graphics))
	{
		Logger::Log(L"SpriteManager initialization failed.");
		unitialize();
		return -1;
	}

	terrain = std::make_shared<Terrain>(TERRAIN_WIDTH, TERRAIN_HEIGHT, true);

	/*gameObjects = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();

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
	enemyUnit = nullptr;*/

	/*std::default_random_engine engine(time(0));
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
	}*/

	/*if (!initGameObjects())
	{
		Logger::Log(L"GameObjects initialization failed.");
		unitialize();
		return -1;
	}*/

	//EntityManager entityManager;

	MovementSystem movementSystem(entityManager.m_movementComponents.GetComponentsCollection());
	RenderSystem renderSystem(entityManager.m_renderComponents.GetComponentsCollection());
	AStarSystem aStarSystem(entityManager.m_aStarComponents.GetComponentsCollection());
	CollisionSystem collisionSystem(entityManager.m_collisionComponents.GetComponentsCollection());

	if (!AStarAlgorithm::Init(TERRAIN_WIDTH, TERRAIN_HEIGHT, &collisionSystem))
	{
		Logger::Log(L"AStarAlgorithm initialization failed.");
		unitialize();
		return -1;
	}

	EntityId entityId = EntityManager::GenerateEntityId();

	entityManager.m_positionComponents.Insert(entityId, 0, 0);
	entityManager.m_renderComponents.Insert(entityId, entityManager.m_positionComponents.GetComponent(entityId), 0);
	entityManager.m_movementComponents.Insert(entityId, entityManager.m_positionComponents.GetComponent(entityId), 10);
	entityManager.m_aStarComponents.Insert(entityId, entityManager.m_positionComponents.GetComponent(entityId), entityManager.m_movementComponents.GetComponent(entityId));
	entityManager.m_collisionComponents.Insert(entityId, entityManager.m_positionComponents.GetComponent(entityId));

	std::default_random_engine engine(time(nullptr));
	std::uniform_int_distribution<unsigned> distribution(0, 4);

	for (int i = 1; i < TERRAIN_WIDTH * TERRAIN_HEIGHT; ++i)
	{
		if (!distribution(engine))
		{
			entityId = EntityManager::GenerateEntityId();
			entityManager.m_positionComponents.Insert(entityId, CALCULATE_X(i), CALCULATE_Y(i));
			entityManager.m_renderComponents.Insert(entityId, entityManager.m_positionComponents.GetComponent(entityId), 2);
			entityManager.m_collisionComponents.Insert(entityId, entityManager.m_positionComponents.GetComponent(entityId));
		}
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
				//updateGameObjects();
				//CollisionChecker::GetInstance().Update();
				aStarSystem.Update();
				movementSystem.Update();
				lag -= MS_PER_UPDATE;
			}

			graphics.BeginDraw();
			terrain->Draw(graphics);
			renderSystem.Draw(graphics);
			//drawGameObjects();
			graphics.EndDraw();
		}
	}

	unitialize();

	Logger::Log(L"Application ended.");
	return 0;
}