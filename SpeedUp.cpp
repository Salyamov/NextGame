#include "SpeedUp.h"
#include "Player.h"

SpeedUp::SpeedUp() : PowerUp()
{
}

void SpeedUp::collision()
{
	//��� ���������� �������� ������ � �������� ��� ������
	std::cout << "SpeedUp \n";
	ThePlayer::Instance()->increaseMoveSpeed();
	m_bDead = true;
}
