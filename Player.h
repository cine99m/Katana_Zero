#pragma once
#include "gameNode.h"
#include "effect.h"
#include "CSound.h"

class enemyManager;

enum PLAYERSTATE
{
	IDLE,
	RUN,
	JUMP,
	FALL,
	ROLL,
	WALL,
	DIE,
	ATTACK,
};


enum DIRECTION
{
	RIGHT,
	LEFT,
};


struct  PLAYER
{
	//�÷��̾� �̹���
	image* _playerImg;

	PLAYERSTATE _Pstate;
	DIRECTION _Dir;

	RECT _playerImgRc;
	RECT _playerHitRc;
	RECT _playeratkRc;

	float _Px, _Py;
	float _probeXL,_probeXR, _probeY,_probeYT;


	float _playerSpeed;
	float _jumpPower, _graVity;

	

	bool _isJump;
	bool _isDead;
	bool _isWall;
	bool _isAttacking;
	bool _isNinja;



};


class Player : public gameNode
{
private:
	PLAYER _player;
	enemyManager* _em;

	CSound* _slash;


	//������ �̹���
	image* _BG;
	image* _COLL;
	image* _GROUND;

	effect* _slashR;
	effect* _slashL;


	//ī�޶�
	RECT _camera;
	int _camX, _camY;


	bool _soundplayed;
	//
	int _atkDistance;

	int _enemycount;

	//�÷��̾� ���º� �̹��� ����
	image* _IDLE;
	image* _RUN;
	image* _JUMP;
	image* _FALL;
	image* _ROLL;
	image* _WALL;
	image* _DIE;
	image* _ATTACK;
	image* _AIM;

	int _count, _index;
	

	//���������� Ȯ��
	int _currentFrameX, _currentFrameY;

	//�ȼ��浹 ������







public:
	Player();
	~Player();


	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();	//�׸��� �Լ�


	void KeyControl();

	void PlayerAnimation();

	void ImageStorage();

	void PixelCollGround();
	void PixelCollWall();

	void autochangeState();

	void SetCamera(RECT& camera, int left, int top, int width, int height);
	void CameraMove(RECT& camera);

	void EnemysetDie();




	inline PLAYER GetPlayer() { return _player; }
	
	int getCamX() { return _camX; }
	int getCamY() { return _camY; }

	bool getPlayerAlive() { return _player._isDead; }
	void setPlayer(bool isdead) { _player._isDead = isdead; }
	image* getcoll() { return _COLL; }

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }
	
	int getECount() { return _enemycount; }
};

