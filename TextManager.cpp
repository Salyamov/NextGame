#include "TextManager.h"
#include "Game.h"

void TextManager::createTexture(std::string msg, std::string name, int x, int y, int w, int h, std::string font, Uint8 r, Uint8 g, Uint8 b)
{
	m_textColor = SDL_Color{ r, g, b };
	m_textSurface = TTF_RenderText_Solid(m_fonts[name], msg.c_str(), m_textColor);
	m_textures[name] = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), m_textSurface);
	m_textureParamsList[name] = new TextureParams;
	m_textureParamsList[name]->x = x;
	m_textureParamsList[name]->y = y;
	m_textureParamsList[name]->w = w;
	m_textureParamsList[name]->h = h;
	m_textureParamsList[name]->msg = msg;
	m_textureParamsList[name]->color = m_textColor;
	
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
	dstRect.x = m_textureParamsList[name]->x;
	dstRect.y = m_textureParamsList[name]->y;
	dstRect.w = m_textureParamsList[name]->w;
	dstRect.h = m_textureParamsList[name]->h;
	SDL_RenderCopy(TheGame::Instance()->getRenderer(), m_textures[name], &srcRect, &dstRect);
}

void TextManager::updateTexture(std::string msg, std::string name)
{
	m_textureParamsList[name]->msg = msg;
}

void TextManager::registerFont(std::string file, std::string name, int size)
{
	m_fonts[name] = TTF_OpenFont(file.c_str(), size);
	
}
