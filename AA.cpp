#include "AA.h"
#include "Game.h"

AA::AA() : Enemy()
{
}

void AA::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
}

void AA::update()
{
	scroll(TheGame::Instance()->getScrollSpeed());

	Vector2D playerPos = ThePlayer::Instance()->getPosition();
	float x = playerPos.getX() - m_position.getX();
	float y = playerPos.getY() - m_position.getY();

	float delta = std::sqrt(x * x + y * y) * (1 / float(m_moveSpeed));

	//тут вычислить угол до игрока и в зависимости от угла поставить соответсвтующий кадр




	ShooterObject::update();
}

void AA::collision()
{
}
