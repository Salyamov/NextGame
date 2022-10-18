#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H
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

	static GameObjectFactory* Instance()
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
	~GameObjectFactory() {}
	static GameObjectFactory* s_pInstance;

	std::map<std::string, BaseCreator*> m_creators;
	
};

typedef GameObjectFactory TheGameObjectFactory;

























#endif
