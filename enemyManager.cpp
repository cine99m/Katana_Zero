#include "pch.h"
#include "enemyManager.h"
#include "Player.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	//이미지 초기화
	bossimageStorage();
	normalimageStorage();


	return S_OK;
}

void enemyManager::release()
{
}


void enemyManager::update()
{
	for (_viNormal = _vNormal.begin(); _viNormal != _vNormal.end(); ++_viNormal)
	{
		(*_viNormal)->update();

	}


}

void enemyManager::render()
{
	char str[128];
	int i = 0;
	for (_viNormal = _vNormal.begin(); _viNormal != _vNormal.end(); ++_viNormal)
	{
		(*_viNormal)->render();
	

	}

	
}


void enemyManager::setNormal()
{


	//Enemy* normal;
	//normal = new Normal;
	//normal->setENEMY(NORMAL);
	//normal->init("NOR_IDLE", PointMake(700, 960));
	//_vNormal.push_back(normal);
	//

	//normal = new Normal;
	//normal->setENEMY(NORMAL);
	//normal->init("NOR_IDLE", PointMake(1200, 960));
	//_vNormal.push_back(normal);


	//normal = new Normal;
	//normal->setENEMY(NORMAL);
	//normal->init("NOR_IDLE", PointMake(1600, 960));
	//_vNormal.push_back(normal);



	//normal = new Normal;
	//normal->setENEMY(NORMAL);
	//normal->init("NOR_IDLE", PointMake(700, 1400));
	//_vNormal.push_back(normal);


	//normal = new Normal;
	//normal->setENEMY(NORMAL);
	//normal->init("NOR_IDLE", PointMake(1200, 1400));
	//_vNormal.push_back(normal);

	//
	//normal = new Normal;
	//normal->setENEMY(NORMAL);
	//normal->init("NOR_IDLE", PointMake(1600, 1400));
	//_vNormal.push_back(normal);
	//
}

void enemyManager::setBoss()
{
	Enemy* boss;
	boss = new Boss;
	boss->setENEMY(BOSS);
	boss->init("BOSS_IDLE", PointMake(900, 500));
	_vNormal.push_back(boss);

	boss = new Boss;
	boss->setENEMY(BOSS);
	boss->init("BOSS_IDLE", PointMake(1500, 500));
	_vNormal.push_back(boss);

	boss = new Boss;
	boss->setENEMY(BOSS);
	boss->init("BOSS_IDLE", PointMake(1900, 500));
	_vNormal.push_back(boss);


}

void enemyManager::removeNormal(int arrNum)
{
	_vNormal.erase(_vNormal.begin() + arrNum);
}



void enemyManager::bossimageStorage()
{
	//IMAGEMANAGER->addFrameImage("BOSS_IDLE", "ENEMY/Boss/idle!/boss_idle.bmp", 1448, 294, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSS_IDLE", "ENEMY/Boss/idle!/boss_idle.bmp", 2449, 300, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSS_IDLE_to_FIGHT", "ENEMY/Boss/idle_fight!/idle_fight.bmp", 1431, 378, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSS_WALK", "ENEMY/Boss/walk!/boss_walk.bmp", 1170, 294, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSS_ATK", "ENEMY/Boss/attack!/boss_attack.bmp", 3852, 312, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSS_DIE", "ENEMY/Boss/hurt!/hurt.bmp", 1278, 258, 6, 2, true, RGB(255, 0, 255));

}

void enemyManager::normalimageStorage()
{
	IMAGEMANAGER->addFrameImage("NOR_IDLE", "ENEMY/normal/idle/normal_idle.bmp", 792, 252, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NOR_RUN", "ENEMY/normal/run/normal_run.bmp", 1048, 254, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NOR_ATK", "ENEMY/normal/attack/normal_attack.bmp",828, 258, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NOR_DIE", "ENEMY/normal/hurt/normal_die.bmp", 2591, 250, 17, 2, true, RGB(255, 0, 255));
}
