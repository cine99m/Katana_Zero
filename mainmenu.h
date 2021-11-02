#pragma once
#include "gameNode.h"
class mainmenu : public gameNode
{
private:
	image* _mainMenu;

	int _fadeIn;
	int _fadeOut;

	bool _isFadeInOut;

public:
	mainmenu();
	~mainmenu();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

};

