#pragma once
#include "gameNode.h"
#include "ship.h"

class battle;

class starScene : public gameNode
{
private:
	ship* _battle;

public:
	starScene();
	~starScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

