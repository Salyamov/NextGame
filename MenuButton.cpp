#include "MenuButton.h"
#include "InputHandler.h"

#include "TextureManager.h"

MenuButton::MenuButton() : ShooterObject(), m_callback(0), m_bReleased(true)
{
}

void MenuButton::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
	//m_currentRow = 1;
}


void MenuButton::draw()
{
	ShooterObject::draw();
	//std::cout << m_textureID  <<" size:" << m_width << " "<< m_height << " button is drawned \n";
	//TextureManager::Instance()->drawFrame("playbutton", 0, 0, 100, 50, 1, 1, Game::Instance()->getRenderer(), 0, 0);
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	//если находится над кнопкой
	if (pMousePos->getX() < (m_position.getX() + m_width) && pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height) && pMousePos->getY() > m_position.getY())
	{

		//если нажата, то вызываем каллбэк и картинка нажатия (флаг отпукания выкл )
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			if (m_callback != 0)
			{
				//call our callback functions
				m_callback();
				
			}
			m_bReleased = false;

		}
		//иначе картинка просто нахождения над кнопкой
		else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	//если не над кнопкой, то обычная картинка без подсветки
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	ShooterObject::clean();
}

