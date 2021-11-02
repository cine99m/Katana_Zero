#pragma once
#include "gameNode.h"
#include "CSound.h"


class MENU : public gameNode
{
private:
	gameNode* _MENU;



	image* _nowimage;
	image* _mainmenu;
	image* _mainmenuexit;

	image* _blackback;

	CSound* STARTSOUND;
	CSound* menubgm;

	int _fadeIn;
	int _fadeOut;
	int _fadeIn2;
	
	int count;

	bool _isFadeInOut;

	bool iskeydownd;

public:
	MENU();
	~MENU();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수
};

