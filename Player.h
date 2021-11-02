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
	//플레이어 이미지
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


	//배경관련 이미지
	image* _BG;
	image* _COLL;
	image* _GROUND;

	effect* _slashR;
	effect* _slashL;


	//카메라
	RECT _camera;
	int _camX, _camY;


	bool _soundplayed;
	//
	int _atkDistance;

	int _enemycount;

	//플레이어 상태별 이미지 모음
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
	

	//프레임으로 확인
	int _currentFrameX, _currentFrameY;

	//픽셀충돌 디버깅용







public:
	Player();
	~Player();


	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();	//그리기 함수


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

