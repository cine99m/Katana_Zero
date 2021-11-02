#pragma once
#include "gameNode.h"

#include "Player.h"
#include "enemyManager.h"
#include "progressBar.h"
#include "ending.h"

/// 소리
#include <list>
#include "CSound.h"


class gameManager : public gameNode
{
private:
	gameNode* _GM;

	CSound* BGM;


	Player* _player;
	enemyManager* _em;

	progressBar* _slowmo;


	//슬로우 모션용
	int _allSlow;
	int _varslow;



	int _nowVal;
	int _MaxVal;
	int _Minval;

	bool _iskeyDown;
	bool _isWait;





	//리플레이용 count 인터벌
	int _countRep;
public:

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수


	void Replay();

};