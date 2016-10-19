#include "EnemyUnit.h"
#include "Logger.h"
#include "Utils.h"
#include "ImageLoader.h"

EnemyUnit::EnemyUnit(int locationX, int locationY, int damage, unsigned int hp, unsigned int attackSpeed)
	: AttackableGameObject(L"EnemyUnit", locationX, locationY, hp, hp), m_damage(damage), m_attackSpeed(attackSpeed)
{
	if (m_attackSpeed > MAX_ATTACK_SPEED)
	{
		m_attackSpeed = MAX_ATTACK_SPEED;
	}
	else if (m_attackSpeed == 0)
	{
		m_attackSpeed = 1;
	}

	m_millisecondsPerAttack = DEFAULT_SPEED / m_attackSpeed;
}

EnemyUnit::~EnemyUnit()
{
	if (m_bmp)
		m_bmp->Release();
	if (m_bmpDead)
		m_bmpDead->Release();
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
	m_timeSinceLastAttack += MS_PER_UPDATE;

	if (m_timeSinceLastAttack >= m_millisecondsPerAttack)
	{
		m_timeSinceLastAttack -= m_millisecondsPerAttack;
		//bool isAdjacent = CollisionChecker::CheckAdjacency(m_locationX, m_locationY, m_attackTarget->GetLocationX(), m_attackTarget->GetLocationY());
		if(m_attackTarget != nullptr && CollisionChecker::CheckAdjacency(m_locationX, m_locationY,
				m_attackTarget->GetLocationX(), m_attackTarget->GetLocationY()))
		{
			if (m_attackTarget->ReceiveDamage(m_damage))
				m_attackTarget = nullptr;
		}
	}
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

void EnemyUnit::Attack(std::shared_ptr<AttackableGameObject> attackTarget)
{
	m_attackTarget = attackTarget;
}
