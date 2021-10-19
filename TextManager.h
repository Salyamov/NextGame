#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H
#include <SDL_ttf.h>
#include <string>
#include <map>

enum border
{
	LEFTBORDER = 0,
	RIGHTBORDER = 1
};

struct TextureParams
{
	std::string msg;
	int x;
	int y;
	int w;
	int h;
	SDL_Color color;
	std::string font;
	border edge;
};

class TextManager
{
public:
	void createTexture(std::string msg, std::string name, int x, int y, int w, int h, std::string font, Uint8 r, Uint8 g, Uint8 b, border edge);
	void drawTexture(std::string name);
	void updateTexture(std::string msg, std::string name);
	void registerFont(std::string file, std::string name, int size);

	static TextManager* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new TextManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

private:

	TextManager();
	static TextManager* s_pInstance;

	//TTF_Font* testFont;
	SDL_Color m_textColor;
	//SDL_Texture* message;
	//SDL_Rect m_messageRect;
	SDL_Surface* m_textSurface;
	std::map <std::string, TTF_Font*> m_fonts;
	std::map <std::string, SDL_Texture*> m_textures;
	std::map <std::string, TextureParams*> m_textureParamsList;

};














#endif
typedef TextManager TheTextManager;

