#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECFACTORYT_H
#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator {
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};


class GameObjectFactory
{
public:
	bool registerType(std::string typeID, BaseCreator* pCreator);
	GameObject* create(std::string typeID);
	GameObjectFactory* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new GameObjectFactory();
			return s_pInstance;
		}
		return s_pInstance;
	}
private:
	GameObjectFactory() {}
	std::map<std::string, BaseCreator*> m_creators;
	static GameObjectFactory* s_pInstance;
};



























#endif
