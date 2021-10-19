#include "TextManager.h"
#include "Game.h"

TextManager* TextManager::s_pInstance = NULL;

TextManager::TextManager()
{
	m_textColor = { 255, 255, 255 };
	m_textSurface = NULL;
}


void TextManager::createTexture(std::string msg, std::string name, int x, int y, int w, int h, std::string font, Uint8 r, Uint8 g, Uint8 b, border edge)
{
	m_textColor.r = r;
	m_textColor.g = g;
	m_textColor.b = b;
	//SDL_Color color = { 120, 220, 255 };
	m_textSurface = TTF_RenderText_Solid(m_fonts[font], msg.c_str(), m_textColor);
	m_textures[name] = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), m_textSurface);
	m_textureParamsList[name] = new TextureParams;

	TTF_SizeText(m_fonts[font], msg.c_str(), &m_textureParamsList[name]->w, &m_textureParamsList[name]->h);
	if (edge == LEFTBORDER)
	{
		m_textureParamsList[name]->x = x;
		m_textureParamsList[name]->y = y;
	}
	else if (edge == RIGHTBORDER)
	{
		m_textureParamsList[name]->x = x - m_textureParamsList[name]->w;//тут проблема (после второго захода в PLaystate
		m_textureParamsList[name]->y = y;                               // текст сдвигается влево на свою длину)
	}

	m_textureParamsList[name]->edge = edge;

	m_textureParamsList[name]->msg = msg;
	m_textureParamsList[name]->color = m_textColor;
	m_textureParamsList[name]->font = font;
	
	SDL_FreeSurface(m_textSurface);
	m_textSurface = NULL;
}

void TextManager::drawTexture(std::string name)
{
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_textureParamsList[name]->w;
	srcRect.h = m_textureParamsList[name]->h;
	SDL_Rect dstRect;
	/*
	dstRect.x = m_textureParamsList[name]->x;
	dstRect.y = m_textureParamsList[name]->y;
	*/
	dstRect.w = m_textureParamsList[name]->w;
	dstRect.h = m_textureParamsList[name]->h;

	if (m_textureParamsList[name]->edge == LEFTBORDER)
	{
		dstRect.x = m_textureParamsList[name]->x;
		dstRect.y = m_textureParamsList[name]->y;
	}
	else if (m_textureParamsList[name]->edge == RIGHTBORDER)
	{
		dstRect.x = m_textureParamsList[name]->x - m_textureParamsList[name]->w;
		dstRect.y = m_textureParamsList[name]->y;
	}

	SDL_RenderCopy(TheGame::Instance()->getRenderer(), m_textures[name], &srcRect, &dstRect);
}

void TextManager::updateTexture(std::string msg, std::string name)
{
	//new changes
	TTF_SizeText(m_fonts[m_textureParamsList[name]->font], msg.c_str(), &m_textureParamsList[name]->w, &m_textureParamsList[name]->h);

	m_textSurface = TTF_RenderText_Solid(m_fonts[m_textureParamsList[name]->font], msg.c_str(), m_textColor);
	m_textures[name] = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), m_textSurface);
	SDL_FreeSurface(m_textSurface);
	m_textSurface = NULL;

}

void TextManager::registerFont(std::string file, std::string name, int size)
{
	m_fonts[name] = TTF_OpenFont(file.c_str(), size);
	if (m_fonts[name] == NULL)
	{
		std::cout << "Failed to loaded Font" << TTF_GetError() << "\n";
	}
	else
	{
		std::cout << "font from: " << file << " is registered as: " << name << "\n";
	}
}

void TextManager::clearParams(std::string name)
{

}

