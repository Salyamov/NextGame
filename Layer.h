#ifndef LAYER_H
#define LAYER_H

class Level;

class Layer
{
public:
	virtual void render() = 0;
	virtual void update(Level* pLevel) = 0;
	virtual ~Layer() {}

};



























#endif