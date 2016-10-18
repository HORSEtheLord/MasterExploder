#include "EnemyUnit.h"
#include "Logger.h"
#include "Utils.h"
#include "ImageLoader.h"

EnemyUnit::EnemyUnit(int locationX, int locationY, unsigned int hp)
	: GameObject(L"EnemyUnit"), m_locationX(locationX), m_locationY(locationY), m_maxHitPoints(hp), m_currentHitPoints(hp)
{
}

EnemyUnit::~EnemyUnit()
{
	if (m_bmp)
		m_bmp->Release();
	if (m_bmpDead)
		m_bmpDead->Release();
}

bool EnemyUnit::ReceiveDamage(int damage)
{
	if (damage >= m_currentHitPoints)
	{
		m_currentHitPoints = 0;
		m_isDead = true;
	}
	else
	{
		m_currentHitPoints -= damage;
	}

	return m_isDead;
}

bool EnemyUnit::Init(std::shared_ptr<Graphics> graphics)
{
	wchar_t *filename = L"enemy_unit1.png";

	if (!ImageLoader::LoadSprite(graphics, filename, &m_bmp))
	{
		Logger::Log(L"Enemy unit sprite loading failed. File: " + std::wstring(filename));
		return false;
	}

	wchar_t *filenameDestroyed = L"enemy_unit1_dead.png";

	if (!ImageLoader::LoadSprite(graphics, filenameDestroyed, &m_bmpDead))
	{
		Logger::Log(L"Enemy unit sprite loading failed. File: " + std::wstring(filenameDestroyed));
		return false;
	}

	return true;
}

void EnemyUnit::Update()
{
}

void EnemyUnit::Draw(std::shared_ptr<Graphics> graphics) const
{
	int width = TILE_WIDTH;
	int height = TILE_HEIGHT;

	int locationX = m_locationX * width;
	int locationY = m_locationY * height;

	ID2D1Bitmap *bmp = m_isDead ? m_bmpDead : m_bmp;

	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(locationX, locationY, locationX + width, locationY + height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));
}