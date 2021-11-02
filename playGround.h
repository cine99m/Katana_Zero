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
	//���ο� ��ǿ�
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

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

	
};

