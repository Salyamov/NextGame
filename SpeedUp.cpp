#include "SpeedUp.h"
#include "Player.h"

SpeedUp::SpeedUp() : PowerUp()
{
}

void SpeedUp::collision()
{
	//тут происходит апргрейд игрока и исчезает сам объект
	std::cout << "SpeedUp \n";
	ThePlayer::Instance()->increaseMoveSpeed();
	m_bDead = true;
}
