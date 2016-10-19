#pragma once
#include "GameObject.h"

class Obstacle : public GameObject
{
private:
	ID2D1Bitmap *m_bmp = nullptr;
public:
	Obstacle(int locationX, int locationY);
	Obstacle(const Obstacle&) = delete;
	virtual ~Obstacle();

	void operator=(const Obstacle&) = delete;

	bool Init(std::shared_ptr<Graphics> graphics) override;
	void Update() override;
	void Draw(std::shared_ptr<Graphics> graphics) const override;
};
