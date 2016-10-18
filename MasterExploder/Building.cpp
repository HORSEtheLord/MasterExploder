#include "Building.h"
#include "ImageLoader.h"
#include "Logger.h"
#include "Utils.h"

Building::Building(int locationX, int locationY, unsigned int hp)
	: AttackableGameObject(L"Building", hp, hp), m_locationX(locationX), m_locationY(locationY)
{
}

Building::~Building()
{
	if (m_bmp)
		m_bmp->Release();
	if (m_bmpDestroyed)
		m_bmpDestroyed->Release();
}

bool Building::ReceiveDamage(int damage)
{
	if (damage >= GetCurrentHp())
	{
		SetCurrentHp(0);
		m_isDestroyed = true;
	}
	else
	{
		//zuka:
		//zapytac matiego jak lepiej
		unsigned int currentHp = GetCurrentHp();
		SetCurrentHp(currentHp - damage);
		//SetCurrentHp(GetCurrentHp() - damage);
	}

	return m_isDestroyed;
}

bool Building::Init(std::shared_ptr<Graphics> graphics)
{
	wchar_t *filename = L"building1.png";

	if (!ImageLoader::LoadSprite(graphics, filename, &m_bmp))
	{
		Logger::Log(L"Building sprite loading failed. File: " + std::wstring(filename));
		return false;
	}

	wchar_t *filenameDestroyed = L"building1_destroyed.png";

	if (!ImageLoader::LoadSprite(graphics, filenameDestroyed, &m_bmpDestroyed))
	{
		Logger::Log(L"Building sprite loading failed. File: " + std::wstring(filenameDestroyed));
		return false;
	}

	return true;
}

void Building::Update()
{
}

void Building::Draw(std::shared_ptr<Graphics> graphics) const
{
	int width = TILE_WIDTH;
	int height = TILE_HEIGHT;

	int locationX = m_locationX * width;
	int locationY = m_locationY * height;

	ID2D1Bitmap *bmp = m_isDestroyed ? m_bmpDestroyed : m_bmp;

	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(locationX, locationY, locationX + width, locationY + height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));
}
