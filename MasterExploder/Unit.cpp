#include "Unit.h"
#include "Logger.h"
#include "Utils.h"
#include "ImageLoader.h"

Unit::Unit(int locationX, int locationY, int damage, unsigned int hp, unsigned int movementSpeed, unsigned int attackSpeed)
	: AttackableGameObject(L"Unit", locationX, locationY, hp, hp), m_damage(damage), 
	m_movementSpeed(movementSpeed), m_attackSpeed(attackSpeed)
{
	if (m_movementSpeed > MAX_MOVEMENT_SPEED)
	{
		m_movementSpeed = MAX_MOVEMENT_SPEED;
	}
	else if (m_movementSpeed == 0)
	{
		m_movementSpeed = 1;
	}

	if (m_attackSpeed > MAX_ATTACK_SPEED)
	{
		m_attackSpeed = MAX_ATTACK_SPEED;
	}
	else if (m_attackSpeed == 0)
	{
		m_attackSpeed = 1;
	}

	m_millisecondsPerMove = DEFAULT_SPEED / m_movementSpeed;
	m_millisecondsPerAttack = DEFAULT_SPEED / m_attackSpeed;
}

Unit::~Unit()
{
	if (m_bmp)
		m_bmp->Release();
	if (m_bmpDead)
		m_bmpDead->Release();
}

bool Unit::Init(std::shared_ptr<Graphics> graphics)
{
	wchar_t *filename = L"unit1.png";

	if (!ImageLoader::LoadSprite(graphics, filename, &m_bmp))
	{
		Logger::Log(L"Sprite loading failed. File: " + std::wstring(filename));
		return false;
	}

	wchar_t *filenameDestroyed = L"unit1_dead.png";

	if (!ImageLoader::LoadSprite(graphics, filenameDestroyed, &m_bmpDead))
	{
		Logger::Log(L"Enemy unit sprite loading failed. File: " + std::wstring(filenameDestroyed));
		return false;
	}

	return true;
}

void Unit::Draw(std::shared_ptr<Graphics> graphics) const
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

void Unit::Move(int locationX, int locationY)
{
	m_attackTarget = nullptr;

	std::vector<int> path = AStarAlgorithm::GetInstance().FindPath(
		CALCULATE_KEY(m_locationX, m_locationY),
		CALCULATE_KEY(locationX, locationY));

	if (!path.empty())
		m_path = path;
}

void Unit::Attack(std::shared_ptr<AttackableGameObject> attackTarget)
{
	m_attackTarget = nullptr;

	std::vector<int> path = AStarAlgorithm::GetInstance().FindPath(
		CALCULATE_KEY(m_locationX, m_locationY),
		CALCULATE_KEY(attackTarget->GetLocationX(), attackTarget->GetLocationY()),
		false);

	if (!path.empty())
	{
		m_path = path;
		m_attackTarget = attackTarget;
	}
}

void Unit::Update()
{
	m_timeSinceLastMove += MS_PER_UPDATE;
	m_timeSinceLastAttack += MS_PER_UPDATE;

	if (m_timeSinceLastMove >= m_millisecondsPerMove)
	{
		m_timeSinceLastMove -= m_millisecondsPerMove;
		if (!m_path.empty())
		{
			int node = *m_path.begin();
			m_locationX = CALCULATE_X(node);
			m_locationY = CALCULATE_Y(node);
			m_path.erase(m_path.begin());
		}
	}

	if (m_timeSinceLastAttack >= m_millisecondsPerAttack)
	{
		m_timeSinceLastAttack -= m_millisecondsPerAttack;
		if(m_path.empty() && m_attackTarget != nullptr)
		{
			if (m_attackTarget->ReceiveDamage(m_damage))
				m_attackTarget = nullptr;
		}
	}
}