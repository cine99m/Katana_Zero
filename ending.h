#pragma once
#include "gameNode.h"
#include "CSound.h"

class ending : public gameNode
{
private:
	gameNode* _END;

	image* ENDING;
	image* ENDINGTITLE;

	CSound* ENDSOUND;

	int _fadeIn;
	int _fadeOut;
	int _count;

	int _fadeIn2;
	bool _isFadeInOut;

public:

	ending();
	~ending();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수

};

