#include "pch.h"
#include "MENU.h"

MENU::MENU()
{
}

MENU::~MENU()
{
}

HRESULT MENU::init()
{
	CSound::Init();

	 STARTSOUND = new CSound("BGM/select.wav", false);
	 menubgm = new CSound("BGM/Rain On Brick.mp3",true);

	_mainmenuexit = IMAGEMANAGER->addImage("MAINEXIT", "BG/end.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_mainmenu = IMAGEMANAGER->addImage("MAIN", "BG/new.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_blackback = IMAGEMANAGER->addImage("BLACKB", "BG/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_nowimage = _mainmenu;
	_fadeIn2 = 0;
	_fadeIn = 0;
	_fadeOut = 255;
	_isFadeInOut = true;
	iskeydownd = false;

	menubgm->play();

	return S_OK;
}

void MENU::release()
{
	CSound::Release();
}

void MENU::update()
{
	if (_isFadeInOut)
	{
	

		_fadeIn++;
		_fadeOut--;


		if (_fadeIn > 254) _isFadeInOut = false;
	}

	if (!_isFadeInOut)
	{
		_fadeIn2++;
		if (_fadeIn2 > 254)
		{
			_fadeIn2 = 255;
		}
	}


	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!iskeydownd)
		{
			STARTSOUND->play();


			menubgm->stop();

			SCENEMANAGER->changeScene("GAME");
			release();
		}
		else
		{
			STARTSOUND->play();
			
			return exit(1);
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		STARTSOUND->play();
		_nowimage = _mainmenuexit;
		iskeydownd = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		STARTSOUND->play();
		_nowimage = _mainmenu;
		iskeydownd= false;
	}
	



	menubgm->Update();
	STARTSOUND->Update();
}

void MENU::render()
{
	
	_mainmenu->alphaRender(getMemDC(), _fadeIn);

	_nowimage->render(getMemDC(), 0, 0);
	
	_blackback->alphaRender(getMemDC(), _fadeOut);
}
