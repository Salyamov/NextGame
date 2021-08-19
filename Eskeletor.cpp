#include "Eskeletor.h"

Eskeletor::Eskeletor() : Enemy()
{
	m_dyingTime = 50;
	m_health = 3;
	m_moveSpeed = 3;
	m_bulletFiringSpeed = 50;
}

Eskeletor::~Eskeletor()
{
}

void Eskeletor::update()
{
}
