#pragma once
#include "gameNode.h"

#include "Player.h"
#include "enemyManager.h"
#include "progressBar.h"
#include "ending.h"

/// �Ҹ�
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


	//���ο� ��ǿ�
	int _allSlow;
	int _varslow;



	int _nowVal;
	int _MaxVal;
	int _Minval;

	bool _iskeyDown;
	bool _isWait;





	//���÷��̿� count ���͹�
	int _countRep;
public:

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�


	void Replay();

};