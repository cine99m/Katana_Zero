#include "pch.h"
#include "starScene.h"
#include "battle.h"

starScene::starScene()
{
}


starScene::~starScene()
{
}

HRESULT starScene::init()
{
	_battle = new battle;
	_battle->init("battle", WINSIZEX / 2, WINSIZEY / 2);

	return S_OK;
}

void starScene::release()
{
}

void starScene::update()
{
	_battle->update();
}

void starScene::render()
{
	IMAGEMANAGER->findImage("¹è°æ")->render(getMemDC());

	_battle->render();
}
