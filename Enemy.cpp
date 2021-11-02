#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

HRESULT Enemy::init()
{

	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position)
{
	_ENEMYS._currentFrameX = _ENEMYS._currentFrameY = 0;

	_ENEMYS._EnemyImg = IMAGEMANAGER->findImage(imageName);

	_ENEMYS._EnemyRc = RectMakeCenter(position.x, position.y,
	_ENEMYS._EnemyImg->getFrameWidth(), _ENEMYS._EnemyImg->getFrameHeight());

	_ENEMYS._Ex = position.x;
	_ENEMYS._Ey = position.y;

	_ENEMYS._isAlive = true;
	_ENEMYS._isBattleMode = false;
	_ENEMYS._isdied = false;
	
	_ENEMYS._EnemyRange = 400;

	_ENEMYS._EnemyAttackRange = 180;
	
	
	_ENEMYS._Espeed = 3.0f;

	_ENEMYS._fadein = 0;
	_ENEMYS._fadeout = 255;

	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
	EnemyAi();
	EnemyAnimation();

	_ENEMYS._EnemyRc = RectMakeCenter(_ENEMYS._Ex+_player->getCamX(), _ENEMYS._Ey+_player->getCamY(),
		_ENEMYS._EnemyImg->getFrameWidth(), _ENEMYS._EnemyImg->getFrameHeight());
	_ENEMYS._enemyattackRc = RectMakeCenter(_ENEMYS._Ex, _ENEMYS._Ey, 200, 100);

	
	EnemyPixelcol();
}

void Enemy::render()
{

		if (_ENEMYS._EDIR == E_LEFT)
		{
			_ENEMYS._EnemyImg->frameRender(getMemDC(), _ENEMYS._EnemyRc.left, _ENEMYS._EnemyRc.top
				, _ENEMYS._currentFrameX, 1);
		}
		else if (_ENEMYS._EDIR == E_RIGHT)
		{
			_ENEMYS._EnemyImg->frameRender(getMemDC(), _ENEMYS._EnemyRc.left, _ENEMYS._EnemyRc.top
				, _ENEMYS._currentFrameX, 0);
		}
	
}

void Enemy::EnemyPixelcol()
{
	//땅을 검출 하는 구문
	_probeEy = _ENEMYS._Ey - (_ENEMYS._EnemyRc.bottom - _ENEMYS._EnemyRc.top) / 2; 
	for (int i = _probeEy - 15; i < _probeEy + 5; ++i)
	{
		COLORREF color = GetPixel(_player->getcoll()->getMemDC(), _ENEMYS._Ex , i );

		int R = GetRValue(color);
		int G = GetGValue(color);
		int B = GetBValue(color);


		if ((R == 0 && G == 0 && B == 255))
		{
			
			_ENEMYS._Ey = i - (_ENEMYS._EnemyRc.bottom - _ENEMYS._EnemyRc.top) / 2;

			break;
		}
	}
}

void Enemy::EnemyAnimation()
{
	_ENEMYS._count++;

	_ENEMYS._EnemyImg->setFrameX(_ENEMYS._currentFrameX);

	if (_ENEMYS._count % 5 == 0)
	{
		switch (_ENEMYS._ESTATE)
		{
		case E_IDLE:

			if (_ENEMYS._EDIR == E_RIGHT)
			{
				if (_ENEMYS._currentFrameX > _ENEMYS._EnemyImg->getMaxFrameX()) _ENEMYS._currentFrameX = 0;

				_ENEMYS._currentFrameX++;
		
				_ENEMYS._count = 0;

				break;
			}
			else if (_ENEMYS._EDIR == E_LEFT)
			{
				_ENEMYS._currentFrameX--;

				if (_ENEMYS._currentFrameX < 0) _ENEMYS._currentFrameX = _ENEMYS._EnemyImg->getMaxFrameX();
				break;
			}

			break;

		case E_IDLE_TO_FIGHT:

			if (_ENEMYS._EDIR == E_RIGHT)
			{
				if (_ENEMYS._currentFrameX >= _ENEMYS._EnemyImg->getMaxFrameX()) _ENEMYS._currentFrameX = 0;

				_ENEMYS._currentFrameX++;

				_ENEMYS._count = 0;

				break;
			}
			else if (_ENEMYS._EDIR == E_LEFT)
			{
				_ENEMYS._currentFrameX--;

				if (_ENEMYS._currentFrameX <= 0) _ENEMYS._currentFrameX = _ENEMYS._EnemyImg->getMaxFrameX();
				break;
			}
			break;

		case E_WALK:

			if (_ENEMYS._EDIR == E_RIGHT)
			{
				if (_ENEMYS._currentFrameX >= _ENEMYS._EnemyImg->getMaxFrameX()) _ENEMYS._currentFrameX = 0;


				_ENEMYS._currentFrameX++;

				_ENEMYS._count = 0;

				break;
			}
			 if (_ENEMYS._EDIR == E_LEFT)
			{
		

				if (_ENEMYS._currentFrameX <= 0) _ENEMYS._currentFrameX = _ENEMYS._EnemyImg->getMaxFrameX();
				_ENEMYS._currentFrameX--;
			

				break;
			}
			break;

		case E_ATTACK:

			if (_ENEMYS._EDIR == E_RIGHT)
			{
				if (_ENEMYS._currentFrameX >= _ENEMYS._EnemyImg->getMaxFrameX()) _ENEMYS._currentFrameX = 0;

				_ENEMYS._currentFrameX++;
							
				_ENEMYS._count = 0;

				if (_ENEMYS._EnemyAttackRange >= getDistance(_player->GetPlayer()._Px - _player->getCamX(), _player->GetPlayer()._Py - _player->getCamY(), _ENEMYS._Ex, _ENEMYS._Ey))
				{
					if (_ENEMYS._EnemyImg->getFrameX() >= 11)
					{
						_player->setPlayer(true);
					}
					 
				}
				break;
			}
			else if (_ENEMYS._EDIR == E_LEFT)
			{
				_ENEMYS._currentFrameX--;

				if (_ENEMYS._currentFrameX <= 0) _ENEMYS._currentFrameX = _ENEMYS._EnemyImg->getMaxFrameX();
				if (_ENEMYS._EnemyAttackRange >= getDistance(_player->GetPlayer()._Px - _player->getCamX(), _player->GetPlayer()._Py - _player->getCamY(), _ENEMYS._Ex, _ENEMYS._Ey))
				{
					if (_ENEMYS._EnemyImg->getFrameX() <= 1)
					{
						_player->setPlayer(true);
					}

				}
				break;
			}
			break;

		case E_DIE:

			if (_ENEMYS._ETYPE == BOSS)
			{
				if (_ENEMYS._EDIR == E_RIGHT)
				{
					if (_ENEMYS._currentFrameX >= _ENEMYS._EnemyImg->getMaxFrameX()) _ENEMYS._currentFrameX = 6;

					_ENEMYS._currentFrameX++;

					_ENEMYS._count = 0;

					break;
				}
				else if (_ENEMYS._EDIR == E_LEFT)
				{
					_ENEMYS._currentFrameX--;

					if (_ENEMYS._currentFrameX <= 2) _ENEMYS._currentFrameX = 1;

					break;
				}

				break;
			}

			if (_ENEMYS._ETYPE == NORMAL)
			{
				if (_ENEMYS._EDIR == E_RIGHT)
				{
					if (_ENEMYS._currentFrameX >= 16) _ENEMYS._currentFrameX = 17;

					_ENEMYS._currentFrameX++;

					_ENEMYS._count = 0;

					break;
				}
			if (_ENEMYS._EDIR == E_LEFT)
				{
					_ENEMYS._currentFrameX--;

					if (_ENEMYS._currentFrameX <= 2) _ENEMYS._currentFrameX = 1;

					break;
				}

				break;
			}

		default:
			break;
		}
		_ENEMYS._count = 0;

	}
}

void Enemy::EnemyAi()
{
//	보스일떄만
	if (_ENEMYS._ETYPE == BOSS)
	{

		if (_ENEMYS._EnemyRange > getDistance(_player->GetPlayer()._Px - _player->getCamX(), _player->GetPlayer()._Py-_player->getCamY(), _ENEMYS._Ex, _ENEMYS._Ey))
		{
			_ENEMYS._isBattleMode = true;
		}
		else
		{
			_ENEMYS._isBattleMode = false;
		}

		//죽었을 떄 움직임
		if (!_ENEMYS._isAlive)
		{
			if (_ENEMYS._ETYPE == BOSS) 
			{
				if (_ENEMYS._EDIR == E_LEFT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_DIE");
					_ENEMYS._ESTATE = E_DIE;
					_ENEMYS._EnemyImg->setFrameY(0);
				}
				else if (_ENEMYS._EDIR == E_RIGHT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_DIE");
					_ENEMYS._ESTATE = E_DIE;
					_ENEMYS._EnemyImg->setFrameY(1);
				}
			}
		}
	

		if (_ENEMYS._isBattleMode && _ENEMYS._isAlive)
		{
			//오른쪽으로 걸어오게 할때
			if (_ENEMYS._Ex < _player->GetPlayer()._Px - _player->getCamX())
			{
				_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_WALK");
				_ENEMYS._EDIR = E_RIGHT;
				_ENEMYS._ESTATE = E_WALK;
				_ENEMYS._EnemyImg->setFrameY(0);
				_ENEMYS._Ex += _ENEMYS._Espeed;
			}
			else if (_ENEMYS._Ex > _player->GetPlayer()._Px - _player->getCamX())
			{
				_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_WALK");
				_ENEMYS._EDIR = E_LEFT;
				_ENEMYS._ESTATE = E_WALK;
				_ENEMYS._EnemyImg->setFrameY(1);
				_ENEMYS._Ex -= _ENEMYS._Espeed;
			}
			//만약 공격거리내로 들어온다면 
			if (_ENEMYS._EnemyAttackRange >= getDistance(_player->GetPlayer()._Px - _player->getCamX(), 0, _ENEMYS._Ex, 0))
			{
				_ENEMYS._Espeed = 0;

				if (_ENEMYS._EDIR == E_LEFT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_ATK");
					_ENEMYS._EDIR = E_LEFT;
					_ENEMYS._ESTATE = E_ATTACK;
					_ENEMYS._EnemyImg->setFrameY(1);
					
				}

				else if (_ENEMYS._EDIR == E_RIGHT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_ATK");
					_ENEMYS._EDIR = E_RIGHT;
					_ENEMYS._ESTATE = E_ATTACK;
					_ENEMYS._EnemyImg->setFrameY(0);
				}

			}
			//공격 사거리 밖이라면 따라가게
			else
			{
				if (_ENEMYS._EDIR == E_RIGHT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_WALK");
					_ENEMYS._EDIR = E_RIGHT;
					_ENEMYS._ESTATE = E_WALK;
					_ENEMYS._EnemyImg->setFrameY(0);
				}
				else if (_ENEMYS._EDIR == E_LEFT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_WALK");
					_ENEMYS._EDIR = E_LEFT;
					_ENEMYS._ESTATE = E_WALK;
					_ENEMYS._EnemyImg->setFrameY(1);
				}
				_ENEMYS._Espeed = 3.0f;
			}
		}
		//가시거리 밖이라면 IDLE
		else if (!_ENEMYS._isBattleMode && _ENEMYS._isAlive)
		{
			if (_ENEMYS._EDIR == E_RIGHT)
			{
				_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_IDLE");
				_ENEMYS._EnemyImg->setFrameY(0);
			}
			else if (_ENEMYS._EDIR == E_LEFT)
			{
				_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("BOSS_IDLE");
				_ENEMYS._EnemyImg->setFrameY(1);
			}
		}

	}

	//	노멀일떄만
	if (_ENEMYS._ETYPE == NORMAL)
	{

		if (_ENEMYS._EnemyRange > getDistance(_player->GetPlayer()._Px - _player->getCamX(), _player->GetPlayer()._Py - _player->getCamY(), _ENEMYS._Ex, _ENEMYS._Ey))
		{
			_ENEMYS._isBattleMode = true;
		}
		else
		{
			_ENEMYS._isBattleMode = false;
		}

		//죽었을 떄 움직임
		if (!_ENEMYS._isAlive)
		{
			if (_ENEMYS._ETYPE == NORMAL)
			{
				if (_ENEMYS._EDIR == E_LEFT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_DIE");
					_ENEMYS._ESTATE = E_DIE;
					_ENEMYS._EnemyImg->setFrameY(0);
				}
				else if (_ENEMYS._EDIR == E_RIGHT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_DIE");
					_ENEMYS._ESTATE = E_DIE;
					_ENEMYS._EnemyImg->setFrameY(1);
				}
			}
		}


		if (_ENEMYS._isBattleMode && _ENEMYS._isAlive)
		{
			//오른쪽으로 걸어오게 할때
			if (_ENEMYS._Ex < _player->GetPlayer()._Px - _player->getCamX())
			{
				_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_RUN");
				_ENEMYS._EDIR = E_RIGHT;
				_ENEMYS._ESTATE = E_WALK;
				_ENEMYS._EnemyImg->setFrameY(0);
				_ENEMYS._Ex += _ENEMYS._Espeed;
			}
			else if (_ENEMYS._Ex > _player->GetPlayer()._Px - _player->getCamX())
			{
				_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_RUN");
				_ENEMYS._EDIR = E_LEFT;
				_ENEMYS._ESTATE = E_WALK;
				_ENEMYS._EnemyImg->setFrameY(1);
				_ENEMYS._Ex -= _ENEMYS._Espeed;
			}

			//만약 공격거리내로 들어온다면 
			if (_ENEMYS._EnemyAttackRange >= getDistance(_player->GetPlayer()._Px - _player->getCamX(), 0, _ENEMYS._Ex, 0))
			{
				_ENEMYS._Espeed = 0;

				if (_ENEMYS._EDIR == E_LEFT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_ATK");
					_ENEMYS._EDIR = E_LEFT;
					_ENEMYS._ESTATE = E_ATTACK;
					_ENEMYS._EnemyImg->setFrameY(1);

				}

				else if (_ENEMYS._EDIR == E_RIGHT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_ATK");
					_ENEMYS._EDIR = E_RIGHT;
					_ENEMYS._ESTATE = E_ATTACK;
					_ENEMYS._EnemyImg->setFrameY(0);
				}

			}

			//공격 사거리 밖이라면 따라가게
			else
			{
				if (_ENEMYS._EDIR == E_RIGHT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_RUN");
					_ENEMYS._EDIR = E_RIGHT;
					_ENEMYS._ESTATE = E_WALK;
					_ENEMYS._EnemyImg->setFrameY(0);
				}
				else if (_ENEMYS._EDIR == E_LEFT)
				{
					_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_RUN");
					_ENEMYS._EDIR = E_LEFT;
					_ENEMYS._ESTATE = E_WALK;
					_ENEMYS._EnemyImg->setFrameY(1);
				}
				_ENEMYS._Espeed = 3.0f;
			}
		}

		//가시거리 밖이라면 IDLE
		else if (!_ENEMYS._isBattleMode && _ENEMYS._isAlive)
		{
			if (_ENEMYS._EDIR == E_RIGHT)
			{
				_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_IDLE");
				_ENEMYS._EnemyImg->setFrameY(0);
			}
			else if (_ENEMYS._EDIR == E_LEFT)
			{
				_ENEMYS._EnemyImg = IMAGEMANAGER->findImage("NOR_IDLE");
				_ENEMYS._EnemyImg->setFrameY(1);
			}
		}

	}

}
