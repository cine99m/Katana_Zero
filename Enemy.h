#pragma once
#include "gameNode.h" 
#include "Player.h"

enum ENEMYTYPE
{
	NORMAL,
	BOSS,
};

enum ENEMYSTATE
{
	E_IDLE,
	E_IDLE_TO_FIGHT,
	E_WALK,
	E_ATTACK,
	E_DIE,
};

enum ENEMYDIR
{
	E_LEFT,
	E_RIGHT,
};

struct ENEMYS
{
	ENEMYTYPE _ETYPE;
	ENEMYSTATE _ESTATE;
	ENEMYDIR _EDIR;


	image* _EnemyImg;

	float _Ex, _Ey;

	RECT _EnemyRc;
	RECT _enemyattackRc;

	int _EnemyRange;
	int _EnemyAttackRange;

	int _currentFrameX;
	int _currentFrameY;

	float _Espeed;


	int _count;
	int _index;
	int _atkCount;

	bool _isAlive;
	bool _isBattleMode;
	bool _isdied;

	int _randomMoveinterval;

	int _fadeout;
	int _fadein;

	//적의 타입을 결정해줄 변수

};

class Enemy : public gameNode
{

protected:
	ENEMYS _ENEMYS;

private:
	Player* _player;

	
	int _probeEy;
	

public:

	Enemy();
	~Enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void EnemyPixelcol();

	void EnemyAnimation();

	void EnemyAi();

	ENEMYS getENEMY() { return _ENEMYS; } 

	void setEnemyDie(bool isalive) { _ENEMYS._isAlive = isalive; }

	void setENEMY(ENEMYTYPE type) { _ENEMYS._ETYPE = type; }

	void setEnemyAddressMemoryLink(Player* player) { _player = player; }


};

