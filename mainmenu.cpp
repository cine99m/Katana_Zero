#include "pch.h"
#include "mainmenu.h"

mainmenu::mainmenu()
{
}

mainmenu::~mainmenu()
{
}

HRESULT mainmenu::init()
{
	IMAGEMANAGER->addImage("MAIN", "new.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_fadeOut = 255;
	_fadeIn = 0;

	_isFadeInOut = false;

	return S_OK;
}

void mainmenu::release()
{
}

void mainmenu::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!_isFadeInOut) _isFadeInOut = true;
	}

	if (_isFadeInOut)
	{
		_fadeIn++;
		_fadeOut--;

		if (_fadeIn > 254)
		{
			_isFadeInOut = false;
			SCENEMANAGER->changeScene("게임화면");
		}

	}

}

void mainmenu::render()
{
	IMAGEMANAGER->findImage("MAIN")->alphaRender(getMemDC(), _fadeOut);

}
