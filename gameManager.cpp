#include "pch.h"
#include "gameManager.h"


HRESULT gameManager::init()
{
	CSound::Init();

	BGM = new CSound("BGM/Meat Grinder.mp3", true);
	BGM->play();

	

	_player = new Player;
	_player->init();

	_em = new enemyManager;
	_em->init();




	_em->setNormal();
	_em->setBoss();


	//Normal 벡터 안에 있는 값을 플레이어 에게 알려줄려고하는 ㅁ구문
	for (int i = 0; i < _em->getVNormal().size(); i++)
	{
		_em->getVNormal()[i]->setEnemyAddressMemoryLink(_player);
	}

	//구에에엑
		//슬로우모션 관련 변수
	_slowmo = new progressBar;
	_slowmo->init(20, 20, 376, 44);

	_MaxVal = _nowVal = 1000;
	_Minval = 10;

	_slowmo->setGauge(_nowVal, _MaxVal);

	_varslow = 1;

	//키가눌렸는지 확인하는 문구
	_iskeyDown = false;

	_isWait = false;
	
	return S_OK;
}

void gameManager::release()
{
	CSound::Release();
}

void gameManager::update()
{
	BGM->Update();

		
	
	_slowmo->setGauge(_nowVal, _MaxVal);
	_slowmo->update();

	_player->setEmMemoryAddressLink(_em);
	_em->setPlayerAddressMemoryLink(_player);



	_allSlow++;

	if (_allSlow % _varslow == 0)
	{

		_player->update();
		_em->update();


	}

	_nowVal += 1;

	// 게이지 바 제한
	if (_nowVal > _MaxVal)
	{
		_nowVal = _MaxVal;
	}
	//10
	if (_nowVal <= _Minval)
	{
		_Minval = 200;
	}
	//300
	else if (_nowVal > _Minval)
	{
		_Minval = 10;

		if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			_nowVal -= 10;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			_varslow = 2;
		}
		if (_nowVal < 10)
		{
			_varslow = 1;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_varslow = 1;
	}




	if (_em->getVNormal().empty())
	{
		BGM->stop();
		BGM->release();
		release();
		SCENEMANAGER->changeScene("ENDING");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
	
		BGM->stop();
		BGM->release();
		init();
	}



	Replay();
}

void gameManager::render()
{

	_player->render();

	_em->render();
	_slowmo->render();
}

void gameManager::Replay()
{
	if (_player->getPlayerAlive() == true)
	{

		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			BGM->stop();
			init();
			
		}	
	}
}
