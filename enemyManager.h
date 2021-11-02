#pragma once
#include "gameNode.h"
#include "Boss.h"
#include "Normal.h"

#include <vector>

class Player;

class enemyManager : public gameNode
{
private:
	typedef vector<Enemy*>			  vEnemy;
	typedef vector<Enemy*>::iterator  viEnemy;

	Enemy* _Boss;

private:
	vEnemy	_vNormal;
	viEnemy _viNormal;



	Player* _player;

	Normal* _normal;
	Boss* _boss;

	




public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void setNormal();
	void setBoss();

	void removeNormal(int arrNum);


	void bossimageStorage();
	void normalimageStorage();


	vector<Enemy*> getVNormal() { return _vNormal; }
	vector<Enemy*>::iterator getViNormal() { return _viNormal; }




	void setPlayerAddressMemoryLink(Player* player) { _player = player; }




};
