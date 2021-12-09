#ifndef AA_H
#define AA_H
#include "Enemy.h"

class AA : public Enemy
{
public:
	AA();
	virtual ~AA() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();
	virtual void collision();

private:


};

class AACreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new AA();
	}
};












#endif