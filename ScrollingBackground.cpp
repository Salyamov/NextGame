#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground() : ShooterObject()
{
	count = 0;
	maxcount = 0;
}

ScrollingBackground::~ScrollingBackground()
{
}

void ScrollingBackground::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
	m_scrollSpeed = pParams->getAnimSpeed();

	m_scrollSpeed = 1;

	m_srcRect1.x = 0;

}

void ScrollingBackground::draw()
{
}

void ScrollingBackground::update()
{
	//make first rectangle smaller(src1 dst1)
	m_srcRect1.x += m_scrollSpeed;
	m_srcRect1.w -= m_scrollSpeed;
	m_destRect1.w -= m_scrollSpeed;

	//make secon rectangle bigger(src2 dst2)
	m_srcRect2.w += m_scrollSpeed;
	m_destRect2.x -= m_scrollSpeed;
	m_destRect2.w += m_scrollSpeed;


	//reset and start again
	if (m_destRect2.w >= m_width)
	{
		m_srcRect1.w = m_destRect1.w = m_srcRect1Width = m_dstRect1Width = m_width;
		m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_dstRect2Width = 0;

		m_srcRect1.x = 0;
		m_destRect1.x = m_position.getX();
		m_srcRect1.y = 0;
		m_destRect1.y = m_position.getY();
		
	}

}

void ScrollingBackground::clean()
{
}
