#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>

class TextureManager
{
public:
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw(std::string id, int x, int y, int width, int height, 
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, 
		SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string id, int margin, int spacing, int x, int y, 
		int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer);
	void clearFromTextureMap(std::string id);

	//изменение цвета при попадании(если сразу не исчезает)
	void setColor(std::string id, Uint8 r, Uint8 g, Uint8 b);

	static TextureManager* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }

private:
	TextureManager() {}
	static TextureManager* s_pInstance;
	std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;




















#endif