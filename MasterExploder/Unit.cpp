#include "Unit.h"
#include "Logger.h"
#include "Utils.h"
#include "ImageLoader.h"

Unit::Unit(int locationX, int locationY)
	: m_locationX(locationX), m_locationY(locationY)
{
}

Unit::~Unit()
{
	if (m_bmp)
		m_bmp->Release();
}

bool Unit::Init(Graphics *graphics)
{
	return ImageLoader::LoadSprite(graphics, L"unit1.png", &m_bmp);
}

void Unit::Draw(Graphics *graphics) const
{
	int width = TILE_WIDTH;
	int height = TILE_HEIGHT;

	int locationX = m_locationX * width;
	int locationY = m_locationY * height;

	graphics->GetRenderTarget()->DrawBitmap(
		m_bmp,
		D2D1::RectF(locationX, locationY, locationX + width, locationY + height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, m_bmp->GetSize().width, height = m_bmp->GetSize().height));
}

void Unit::Move(int locationX, int locationY)
{
	/*m_locationX = locationX;
	m_locationY = locationY;*/

	AStarAlgorithm algorithm(40, 30);
	m_path = algorithm.FindPath(AStarNode(m_locationX, m_locationY), AStarNode(locationX, locationY));
}

void Unit::Update()
{
	m_timeSinceLastMove += MS_PER_UPDATE;

	//MKOS: 1000 -> movement speed
	if (m_timeSinceLastMove >= 500)
	{
		m_timeSinceLastMove -= 500;
		if (!m_path.empty())
		{
			AStarNode &node = *m_path.begin();
			m_locationX = node.GetX();
			m_locationY = node.GetY();
			m_path.erase(m_path.begin());
		}
	}
}