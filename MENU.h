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

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�
};

