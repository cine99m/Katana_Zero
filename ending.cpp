#include "pch.h"
#include "ending.h"



ending::ending()
{
}

ending::~ending()
{
}

HRESULT ending::init()
{
	CSound::Init();
	ENDSOUND = new CSound("BGM/ending.ogg", true);
	ENDSOUND->play();

	

	ENDING = IMAGEMANAGER->addImage("ENDING","BG/ending.bmp",WINSIZEX,WINSIZEY,true,RGB(255,0,255));
	ENDINGTITLE = IMAGEMANAGER->addImage("ENDINGTITLE", "BG/endtitle.bmp", 492, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BLACK", "BG/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_fadeIn2 = 0;
	_fadeIn = 0;
	_fadeOut = 255;
	_isFadeInOut = true;
	

	return S_OK;
}

void ending::release()
{
	CSound::Release();
}

void ending::update()
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

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("MENU");
		ENDSOUND->stop();
		ENDSOUND->Release();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		ENDSOUND->stop();
		ENDSOUND->Release();
		init();
		
	}
	ENDSOUND->Update();
}

void ending::render()
{
	//ENDING->render(getMemDC(), 0, 0);
	//ENDINGTITLE->render(getMemDC(), WINSIZEX / 2 -50 , WINSIZEY / 2- 50);
	
	ENDING->alphaRender(getMemDC(), _fadeIn);
	ENDINGTITLE->alphaRender(getMemDC(),_fadeIn2);
	IMAGEMANAGER->findImage("BLACK")->alphaRender(getMemDC(), _fadeOut);
	
}
