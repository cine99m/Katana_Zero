#pragma once
#include "gameNode.h"
#include "gameManager.h"
#include "progressBar.h"
#include "MENU.h"
#include "ending.h"
#include "CSound.h"


class playGround : public gameNode
{
private:
	gameManager* _gm;

	progressBar* _slowmo;
	//슬로우 모션용
	int _allSlow;
	int _varslow;



	int _nowVal;
	int _MaxVal;
	int _Minval;

	bool _iskeyDown;
	bool _isWait;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

	
};

