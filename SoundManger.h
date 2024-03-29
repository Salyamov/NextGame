#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SDL_mixer.h>
#include <map>
#include <string>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:

	static SoundManager* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, sound_type type);

	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);
	void stopMusic();

	std::map<std::string, Mix_Music*> getMusicFiles() { return m_music; }

private:

	static SoundManager* s_pInstance;

	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;

	SoundManager();
	~SoundManager();

};

typedef SoundManager TheSoundManager;


























#endif
