#include "RenderSystem.h"
#include "SpriteManager.h"

RenderSystem::RenderSystem(const std::vector<RenderComponent> &components)
	: m_components(components)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Draw(const Graphics& graphics) const
{
	int width = TILE_WIDTH;
	int height = TILE_HEIGHT;

	for (const RenderComponent &component : m_components)
	{
		int locationX = component.GetX() * width;
		int locationY = component.GetY() * height;

		ID2D1Bitmap *sprite = SpriteManager::GetInstance().GetSprite(component.GetSpriteId());

		graphics.GetRenderTarget()->DrawBitmap(
			sprite,
			D2D1::RectF(locationX, locationY, locationX + width, locationY + height),
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			D2D1::RectF(0.0f, 0.0f, sprite->GetSize().width, sprite->GetSize().height));
	}
}
