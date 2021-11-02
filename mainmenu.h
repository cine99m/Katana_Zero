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

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

};

