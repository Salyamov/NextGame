#ifndef SHOTGLIDER_H
#define SHOTGLIDER_H
#include "Glider.h"

class ShotGlider : public Glider
{
public:
	ShotGlider();
	virtual ~ShotGlider();

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void update();

private:


};

class ShotGliderCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new ShotGlider();
	}
};




















#endif
