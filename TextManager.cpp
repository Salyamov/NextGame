#include "TextManager.h"
#include "Game.h"

TextManager* TextManager::s_pInstance = NULL;

TextManager::TextManager()
{
	m_textColor = { 255, 255, 255 };
	m_textSurface = NULL;
}


void TextManager::createTexture(std::string msg, std::string name, int x, int y, int w, int h, std::string font, Uint8 r, Uint8 g, Uint8 b)
{
	m_textColor.r = r;
	m_textColor.g = g;
	m_textColor.b = b;
	//SDL_Color color = { 120, 220, 255 };
	m_textSurface = TTF_RenderText_Solid(m_fonts[font], msg.c_str(), m_textColor);
	m_textures[name] = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), m_textSurface);
	m_textureParamsList[name] = new TextureParams;
	m_textureParamsList[name]->x = x;
	m_textureParamsList[name]->y = y;
	m_textureParamsList[name]->w = w;
	m_textureParamsList[name]->h = h;
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
	dstRect.x = m_textureParamsList[name]->x;
	dstRect.y = m_textureParamsList[name]->y;
	dstRect.w = m_textureParamsList[name]->w;
	dstRect.h = m_textureParamsList[name]->h;
	SDL_RenderCopy(TheGame::Instance()->getRenderer(), m_textures[name], &srcRect, &dstRect);
}

void TextManager::updateTexture(std::string msg, std::string name)
{
	/*
	int x = m_textureParamsList[name]->x;
	int y = m_textureParamsList[name]->y;
	int w = m_textureParamsList[name]->w;
	int h = m_textureParamsList[name]->h;
	std::string message = msg;
	SDL_Color color = m_textureParamsList[name]->color;
	m_textureParamsList.erase(name);

	m_textureParamsList[name] = new TextureParams;
	m_textureParamsList[name]->x = x;
	m_textureParamsList[name]->y = y;
	m_textureParamsList[name]->w = w;
	m_textureParamsList[name]->h = h;
	m_textureParamsList[name]->msg = message;
	m_textureParamsList[name]->color = color;
	*/
 
	//m_textureParamsList[name]->msg = msg;
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

