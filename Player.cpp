#include "pch.h"
#include "Player.h"
#include "enemyManager.h"



Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init()
{
	CSound::Init();
	_slash = new CSound("BGM/slash.wav", false);

	ImageStorage();

	//�÷��̾� �ʱ����
	_player._playerImg = _IDLE;
	
	//�÷��̾� �ʱ���ġ
	_player._Px = 100;
	_player._Py = 600;

	//�÷��̾� �̵��� ����
	_player._playerSpeed = 6.0f;
	_player._graVity = 0;
	_player._jumpPower = 0;

	//�÷��̾� �ִϸ��̼ǿ����� �Ұ�
	_player._isDead = false;

	_player._isJump = false;

	_player._isWall = false;

	_player._isAttacking = false;

	_soundplayed = false;

	//�ִϸ��̼� ī��Ʈ
	_count = _index = 0;
	
	//�α��� ķ
	_camera.left = 100;
	_camera.right = WINSIZEX / 2;
	_camera.top = 400;
	_camera.bottom = WINSIZEY - 100;


	_camX = 0;
	_camY = -730;
	/// end;


	//�ȼ� �浹�� ��
	//_player._probeY = _player._playerHitRc.bottom;

	//�̹��� RC�� �������� ũ�⸸ŭ
	_player._playerImgRc = RectMakeCenter(_player._Px, _player._Py, _player._playerImg->getFrameWidth(), _player._playerImg->getFrameHeight());
	_player._playerHitRc = RectMakeCenter(_player._Px, _player._Py, 150, 160);
	
	_slashR = new effect;
	_slashR->init(IMAGEMANAGER->findImage("SLASHR"), 258, 126, 1, 5.0f);
	_slashL = new effect;
	_slashL->init(IMAGEMANAGER->findImage("SLASHL"), 258, 126, 1, 5.0f);
	
	_enemycount = 0;


	return S_OK;
}

void Player::release()
{
	CSound::Release();
}

void Player::update()
{
	PlayerAnimation();

	


	KeyControl();
	PixelCollGround();
	CameraMove(_camera);
	PixelCollWall();
	autochangeState();

	_player._playerImgRc = RectMakeCenter(_player._Px, _player._Py, _player._playerImg->getFrameWidth(), _player._playerImg->getFrameHeight());
	_player._playerHitRc = RectMakeCenter(_player._Px, _player._Py, 150, 130);
	_player._playeratkRc = RectMakeCenter(_player._Px, _player._Py, 500, 100);
	
	_slash->Update();
	EFFECTMANAGER->update();
	
}

void Player::render()
{


	//�α��� ����
	_BG->render(getMemDC(), _camX, _camY);
	
	_GROUND->render(getMemDC(), _camX, _camY);
	
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
	
		_COLL->render(getMemDC(), _camX, _camY);

		Rectangle(getMemDC(), _camera);
		//Rectangle(getMemDC(), _player._playeratkRc);
		//Rectangle(getMemDC(), _player._playerHitRc);
	}

	_player._playerImg->frameRender(getMemDC(), _player._playerImgRc.left, _player._playerImgRc.top);

	//���ӿ��̹���
	_AIM->render(getMemDC(), _ptMouse.x - _AIM->getWidth() / 2, _ptMouse.y - _AIM->getHeight() / 2);

	EFFECTMANAGER->render();



}

void Player::KeyControl() // Ű ��Ʈ�Ѱ� �ִϸ��̼��� �����Ѵ�
{

	if (KEYMANAGER->isStayKeyDown('A') && !_player._isAttacking && !_player._isDead)
	{
		_player._playerImg = _RUN;
		_player._playerImg->setFrameY(1);
		_player._Pstate = RUN;
		_player._Dir = LEFT;
		_player._Px -= _player._playerSpeed;
	
	}

	if (KEYMANAGER->isStayKeyDown('D') && !_player._isAttacking&&!_player._isDead)
	{
		
		_player._playerImg = _RUN;
		_player._playerImg->setFrameY(0);
		_player._Pstate = RUN;
		_player._Dir = RIGHT;
		
		_player._Px += _player._playerSpeed;
	
	}

	if (KEYMANAGER->isOnceKeyUp('A') && !_player._isDead)
	{
		if (!_player._isJump) 
		{
			_player._playerImg = _IDLE;
			_player._playerImg->setFrameY(1);
			_player._Pstate = IDLE;
		
		}
	}

	if (KEYMANAGER->isOnceKeyUp('D') && !_player._isDead)
	{
		if (!_player._isJump)
		{
			_player._playerImg = _IDLE;
			_player._playerImg->setFrameY(0);
			_player._Pstate = IDLE;

		}
	}

	//����Ű�� ������ ��
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)&&!_player._isJump && !_player._isDead)
	{
		_player._isJump = true;
	
		if (_player._Dir == LEFT)
		{
			_player._playerImg = _JUMP;
			_player._Pstate = JUMP;
			_player._playerImg->setFrameY(1);
			
			_player._jumpPower = 6.0f;
			_player._Py -= _player._jumpPower;
		
		}
	    if (_player._Dir == RIGHT)
		{
			_player._playerImg = _JUMP;
			_player._Pstate = JUMP;
			_player._playerImg->setFrameY(0);

			_player._jumpPower = 6.0f;
			_player._Py -= _player._jumpPower;
			
		}
	}
	

	//���ݿ�
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_player._isDead) //&& !_player._isAttacking)
	{
		

		_player._isAttacking = true;
		
		if (_ptMouse.x > _player._Px)
		{
			_player._playerImg = _ATTACK;
			_player._Pstate = ATTACK;
			_player._playerImg->setFrameY(0);
			_player._Dir = RIGHT;

			_player._Px += 100.0f;
			EFFECTMANAGER->play("SLASHR", _player._Px + 50, _player._Py);
		}
		else if (_ptMouse.x < _player._Px)
		{
			_player._playerImg = _ATTACK;
			_player._Pstate = ATTACK;
			_player._playerImg->setFrameY(1);
			_player._Dir = LEFT;
			_player._Px -= 100.0f;
			EFFECTMANAGER->play("SLASHL", _player._Px - 50, _player._Py);
		}
		EnemysetDie();
		_slash->play();
	}

}

void Player::PlayerAnimation()
{
	_count++;

	_player._playerImg->setFrameX(_index);

	if (_count % 5 == 0)
	{
		switch (_player._Pstate)
		{
		case IDLE:

			if (_player._Dir == RIGHT)
			{
				_index++;

				if (_index > _player._playerImg->getMaxFrameX()) _index = 0;
				break;
			}
			else if (_player._Dir == LEFT)
			{
				_index--;

				if (_index < 0) _index = _player._playerImg->getMaxFrameX();
				break;
			}
		case RUN:

			if (_player._Dir == RIGHT)
			{
				_index++;

				if (_index > _player._playerImg->getMaxFrameX()) _index = 0;
				break;
			}
			else if (_player._Dir == LEFT)
			{
				_index--;

				if (_index < 0) _index = _player._playerImg->getMaxFrameX();
				break;
			}
		case JUMP:

			if (_player._Dir == RIGHT)
			{
				_index++;

				if (_index > _player._playerImg->getMaxFrameX()) _index = 0;
				break;
			}
			else if (_player._Dir == LEFT)
			{
				_index--;

				if (_index < 0) _index = _player._playerImg->getMaxFrameX();
				break;
			}
		
		case FALL:

			if (_player._Dir == RIGHT)
			{
				_index++;

				if (_index > _player._playerImg->getMaxFrameX()) _index = 0;
				break;
			}
			else if (_player._Dir == LEFT)
			{
				_index--;

				if (_index < 0) _index = _player._playerImg->getMaxFrameX();
				break;
			}
		
		case ROLL:

			if (_player._Dir == RIGHT)
			{
				_index++;

				if (_index > _player._playerImg->getMaxFrameX()) _index = 0;
				break;
			}
			else if (_player._Dir == LEFT)
			{
				_index--;

				if (_index < 0) _index = _player._playerImg->getMaxFrameX();
				break;
			}
		
		case WALL:

			if (_player._Dir == RIGHT)
			{
				_index++;

				if (_index > _player._playerImg->getMaxFrameX()) _index = 0;
				break;
			}
			else if (_player._Dir == LEFT)
			{
				_index--;

				if (_index < 0) _index = _player._playerImg->getMaxFrameX();
				break;
			}
		
		case DIE:
			
			if (_player._Dir == LEFT)
			{
			
				_index++;
			
				if (_index > _player._playerImg->getMaxFrameX())
				{
					
					_index = 11;
					
				}
				
			
				break;
			}
			else if (_player._Dir == RIGHT)
			{
				_index--;
			
				if (_index < 2)
				{
					_index = 1;
				
				}
			
				break;

			}
		
		case ATTACK:

			if (_player._Dir == RIGHT)
			{
				_index++;
	
				int currentX = _player._playerImg->getFrameX();

				if (currentX >= _player._playerImg->getMaxFrameX())
				{
					_player._Pstate = IDLE;
					_player._playerImg = _IDLE;
					_player._Dir = RIGHT;
					_player._playerImg->setFrameY(0);
					_player._isAttacking = false;
				}
				if (_index > _player._playerImg->getMaxFrameX()) _index = 0;
				break;
			}

			else if (_player._Dir == LEFT)
			{
				_index--;

				int currentX = _player._playerImg->getFrameX();

				if (currentX <= 0)
				{
					_player._Pstate = IDLE;
					_player._playerImg = _IDLE;
					_player._Dir = LEFT;
					_player._playerImg->setFrameY(1);
					_player._isAttacking = false;
				}

				if (_index < 0) _index = _player._playerImg->getMaxFrameX();
				break;
			}
	

		default:
			break;
		}
		_count = 0; 
	
	}
}

void Player::ImageStorage()
{
//������ �̹���
	_BG = IMAGEMANAGER->addImage("BG", "BG/newBg.bmp", 2500, 1500, true, RGB(255, 0, 255));
	_COLL = IMAGEMANAGER->addImage("COLL", "BG/newColl.bmp", 2500, 1500, true, RGB(255, 0, 255));
	_GROUND = IMAGEMANAGER->addImage("GROUND", "BG/newGround.bmp", 2500, 1500, true, RGB(255, 0, 255));

//�÷��̾� ���� �̹���
// 
	 //�÷��̾�  ����  �̹���
	_IDLE = IMAGEMANAGER->addFrameImage("PLAYER_IDLE", "PLAYER/idle!/idle.bmp", 1584, 280, 11, 2, true, RGB(255, 0, 255));
	_RUN = IMAGEMANAGER->addFrameImage("PLAYER_RUN", "PLAYER/run!/run.bmp", 1720, 264, 10, 2, true, RGB(255, 0, 255));
	_JUMP = IMAGEMANAGER->addFrameImage("PLAYER_JUMP", "PLAYER/jump!/jump.bmp", 512, 336, 4, 2, true, RGB(255, 0, 255));
	_FALL = IMAGEMANAGER->addFrameImage("PLAYER_FALL", "PLAYER/fall!/fall.bmp", 672, 384, 4, 2, true, RGB(255, 0, 255));
	_WALL = IMAGEMANAGER->addFrameImage("PLAYER_WALL", "PLAYER/wall!/wall.bmp", 312, 336, 2, 2, true, RGB(255, 0, 255));
	_ROLL = IMAGEMANAGER->addFrameImage("PLAYER_ROLL", "PLAYER/roll!/roll.bmp", 1334, 262, 7, 2, true, RGB(255, 0, 255));
	_ATTACK = IMAGEMANAGER->addFrameImage("PLAYER_ATK", "PLAYER/attack!/attack.bmp", 1736, 336, 7, 2, true, RGB(255, 0, 255));
	_DIE = IMAGEMANAGER->addFrameImage("PLAYER_DIE", "PLAYER/die!/die.bmp", 2736, 344, 12, 2, true, RGB(255, 0, 255));

	//����
	_AIM = IMAGEMANAGER->addImage("PLAYER_AIM", "PLAYER/player_aim.bmp", 62, 58, true, RGB(255, 0, 255));

	//��������Ʈ
	 EFFECTMANAGER->addEffect("SLASHR", "EFFECT/katanaslash/katanaslashR.bmp", 1806, 126, 258, 126, 1, 5.0f, 10);
	 EFFECTMANAGER->addEffect("SLASHL", "EFFECT/katanaslash/katanaslashL.bmp", 1806, 126, 258, 126, 1, 5.0f, 10);
}

void Player::PixelCollGround()
{
	_player._probeY = _player._Py + (_player._playerHitRc.bottom - _player._playerHitRc.top)/2;
	_player._probeYT = _player._Py - (_player._playerHitRc.bottom - _player._playerHitRc.top) / 2;

		//���� ���� �ϴ� ����
		for (int i = _player._probeY -15; i < _player._probeY + 5 ; ++i)
		{
			COLORREF color = GetPixel(_COLL->getMemDC(), _player._Px -_camX, i - _camY);

			int R = GetRValue(color);
			int G = GetGValue(color);
			int B = GetBValue(color);

			
			if ((R == 0 && G == 0 && B == 255))
			{
				_player._isJump = false;
				_player._isWall = false;
				_player._isNinja = false;
				_player._jumpPower = 0;
				_player._Py = i -  (_player._playerHitRc.bottom -_player._playerHitRc.top) / 2 - 2;
			
				if (_player._Dir == RIGHT && _player._Pstate == FALL)
				{
					_player._playerImg = _IDLE;
					_player._playerImg->setFrameY(0);
					_player._Pstate = IDLE;

				}
				else if (_player._Dir == LEFT && _player._Pstate == FALL)
				{
					_player._playerImg = _IDLE;
					_player._playerImg->setFrameY(1);
					_player._Pstate = IDLE;
				}
				break;
			}
		}

		//���� �ƴ����� �����ϴ� ����
		for (int i = _player._probeY + 7; i < _player._probeY + 8; ++i)
		{
			COLORREF color = GetPixel(_COLL->getMemDC(), _player._Px - _camX, i - _camY);

			int R = GetRValue(color);
			int G = GetGValue(color);
			int B = GetBValue(color);

			if ((R == 255 && G == 0 && B == 255))
			{
				_player._isJump = true;
				break;
			}
		}
		//�Ӹ��� �浹�ϴ� ����
		for (int i = _player._probeYT -30; i < _player._probeYT; ++i)
		{
			COLORREF color = GetPixel(_COLL->getMemDC(), _player._Px - _camX, i - _camY);

			int R = GetRValue(color);
			int G = GetGValue(color);
			int B = GetBValue(color);

			if ((R == 0 && G == 0 && B == 255))
			{
				
				//_player._Py = +500;
				_player._Py = i + 100;
				//_player._graVity = 0.5f;
				break;
			}
		}
		
}

void Player::PixelCollWall()
{
	//old �ڵ�
	/*{
	//if (_player._Dir == LEFT) {
	//	COLORREF colorL = GetPixel(_COLL->getMemDC(), _player._playerHitRc.left + 60 - _camX, _player._Py - _camY);

	//	int RL = GetRValue(colorL);
	//	int GL = GetGValue(colorL);
	//	int BL = GetBValue(colorL);

	//	if ((RL == 255 && GL == 0 && BL == 0))
	//	{
	//		_player._playerImg = _WALL;
	//		_player._Pstate = WALL;
	//		_player._Dir = RIGHT;
	//		_player._playerImg->setFrameY(1);

	//		_player._isJump = false;
	//		_player._isWall = true;
	//		_player._jumpPower = 0;
	//		_player._playerSpeed = 0;


	//		if (KEYMANAGER->isStayKeyDown('D'))
	//		{
	//			_player._playerSpeed = 6.0f;
	//		}
	//
	//	}
	//			else if (!(RL == 255 && GL == 0 && BL == 0))
	//			{
	//				_player._isWall = false;
	//			}

	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE) &&_player._isWall)
	//{
	//	_player._isWall = false;
	//	_player._Dir = RIGHT;
	//}



	//			COLORREF colorR = GetPixel(_COLL->getMemDC(), _player._playerHitRc.right - 60 - _camX, _player._Py - _camY);

	//			int RR = GetRValue(colorR);
	//			int GR = GetGValue(colorR);
	//			int BR = GetBValue(colorR);

	//			if ((RR == 255 && GR == 0 && BR == 0))
	//			{
	//				_player._playerImg = _WALL;
	//				_player._Pstate = WALL;
	//				_player._Dir = LEFT;
	//				_player._playerImg->setFrameY(0);

	//				_player._isJump = false;
	//				_player._isWall = true;
	//				_player._jumpPower = 0;
	//				_player._playerSpeed = 0;


	//				if (KEYMANAGER->isStayKeyDown('A'))
	//				{
	//					_player._playerSpeed = 6.0f;
	//				}
	//				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//				{
	//					_player._isWall = false;
	//					_player._Dir = LEFT;
	//				}

	//			}
				else if (!(RR == 255 && GR == 0 && BR == 0))
				{
					_player._isWall = false;
				}



				//���� ­���ڵ�
				//_player._probeXL = _player._Px + (_player._playerHitRc.bottom - _player._playerHitRc.top) / 2;
				//_player._probeXR = _player._Px - (_player._playerHitRc.bottom - _player._playerHitRc.top) / 2;
				}
	}*/
	
		for (int i = _player._playerHitRc.left +60 ; i > _player._playerHitRc.left  ; --i)
	{
		COLORREF color = GetPixel(_COLL->getMemDC(), i - _camX, _player._Py - _camY);

		int R = GetRValue(color);
		int G = GetGValue(color);
		int B = GetBValue(color);

		if ((R == 255 && G == 0 && B == 0))
		{
			_player._playerImg = _WALL;
			_player._Pstate = WALL;
			_player._Dir = RIGHT;
			_player._playerImg->setFrameY(1);

			_player._isJump = false;
 			_player._isWall = true;
			_player._isNinja = false;

			_player._jumpPower = 0;
			_player._playerSpeed = 0;


			if (KEYMANAGER->isStayKeyDown('D'))
			{
				_player._playerSpeed = 6.0f;
			}
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{

				_player._isNinja = true;
			}
		}

		break;
	}

	//������ �˻��ڵ�
	for (int i = _player._playerHitRc.right -60  ; i < _player._playerHitRc.right; ++i)
	{
		COLORREF color = GetPixel(_COLL->getMemDC(), i - _camX, _player._Py - _camY);

		int R = GetRValue(color);
		int G = GetGValue(color);
		int B = GetBValue(color);

		if ((R == 255 && G == 0 && B == 0))
		{
			_player._playerImg = _WALL;
			_player._Pstate = WALL;
			_player._Dir = LEFT;
			_player._playerImg->setFrameY(0);

			_player._isJump = false;
			_player._isWall = true;
			_player._isNinja = false;

			_player._jumpPower = 0;
			_player._playerSpeed = 0;


			if (KEYMANAGER->isStayKeyDown('A'))
			{
				_player._playerSpeed = 6.0f;
			}
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{

				_player._isNinja = true;


			}
		}
	
		break;
	}
}
	


void Player::autochangeState()
{
	//���� ���� �߷�
	if (_player._isJump)
	{
		_player._Py -= _player._jumpPower;
		_player._jumpPower -= _player._graVity;
		_player._graVity = 0.2f;
	}

	//�����ؼ� �ö󰡴� ��Ȳ
	if (_player._jumpPower >= _player._graVity && _player._isJump && !_player._isAttacking)
	{
		if (_player._Dir == RIGHT)
		{
			_player._playerImg = _JUMP;
			_player._Pstate = JUMP;

			_player._playerImg->setFrameY(0);
		}
		else if (_player._Dir == LEFT)
		{
			_player._playerImg = _JUMP;
			_player._Pstate = JUMP;

			_player._playerImg->setFrameY(1);
		}
	}

	//�������� ��Ȳ
	if (_player._graVity > _player._jumpPower && _player._isJump && !_player._isAttacking)
	{
		if (_player._Dir == RIGHT)
		{
			_player._playerImg = _FALL;
			_player._Pstate = FALL;

			_player._playerImg->setFrameY(0);
		}
		else if (_player._Dir == LEFT)
		{
			_player._playerImg = _FALL;
			_player._Pstate = FALL;

			_player._playerImg->setFrameY(1);

		}
	}

	//������
	if (_player._isNinja)
	{
		if (_player._Dir == RIGHT)
		{
			_player._Px += 6.0f;
			_player._Py -= 4.0f;
			
		}
		else if (_player._Dir == LEFT )
		{
			_player._Px -= 6.0f;
			_player._Py -= 4.0f;
		}
		if (_player._playerHitRc.top < _camera.top)
		{
				
				//_camY += 3;
				_player._Py += 6;
			
		}
	}
	if (_player._isDead)
	{
	
		_player._playerImg = _DIE;
		_player._Pstate = DIE;
		_player._Dir = LEFT;
		_player._playerImg->setFrameY(0);

	
	
	}
	



}



void Player::SetCamera(RECT& camera, int left, int top, int width, int height)
{
	camera.left = left;
	camera.right = _camera.left + width;
	camera.top = top;
	camera.bottom = _camera.top + height;
}

void Player::CameraMove(RECT& camera)
{
	SetCamera(camera, WINSIZEX / 2-200 , WINSIZEY / 2 - 230 , 400, 400);


	if (_COLL->getHeight() <= WINSIZEY - _camY || _camY == 0 ||
		_player._playerHitRc.bottom <  camera.bottom || _player._playerHitRc.top > camera.top)
	{
	/*	_player._Py -= _player._jumpPower;
		_player._jumpPower -= _player._graVity;*/
	
	}
	if (_camX >= 0 || _camX + WINSIZEX <= _COLL->getWidth())
	{
		_player._playerSpeed = 6.0f;
	}

	if (_player._Px <= camera.left + 75 && KEYMANAGER->isStayKeyDown('A'))
	{
		if (_camX < 0)
		{
			_camX += 6.0f;
			_player._playerSpeed = 0;
			_player._Px = _camera.left + 75;
			_player._Px += _player._playerSpeed;
		}
	}
	else if (_player._Px >= camera.right - 75 && KEYMANAGER->isStayKeyDown('D'))
	{
		if (_camX + _COLL->getWidth() >= WINSIZEX)
		{
			_camX -= _player._playerSpeed;
			_player._playerSpeed = 0;
			_player._Px = _camera.right - 75;
			_player._Px -= _player._playerSpeed;
		}
		if (_player._Py <= camera.top + 50 && !_player._isJump)
		{
			_camY += _player._playerSpeed;
			_player._Py = camera.top + 50;
		}
	}
	else
	{
		_player._playerSpeed = 6.0f;
	}

	if (_player._Py<= camera.top + 75 && _player._jumpPower > 0 )
	{
		if (_camY < 0)
		{
			//if (_player._isJump)
			//{
			_camY += _player._jumpPower;
			_player._playerHitRc.top = camera.top + 75;
		}
			
		//	else
		//	{
		//		_camY += _player._playerSpeed;
		//	}
		//	//_player._Py = _camera.top +75;
		//}
		
	}


	if (_player._Py >= camera.bottom - 75)
	{
		if (_COLL->getHeight() >= WINSIZEY - _camY)
		{
			_camY += _player._jumpPower;
			_player._Py = _camera.bottom - 75;
		}
	}

	if (_camera.top > _player._playerHitRc.top)
	{
		int height = _camera.bottom - _camera.top;
		int aa = _player._playerHitRc.top - _camera.top;
		int ca = _camY;


		//_camera.top = _player._playerHitRc.top;
		//_camera.bottom = _camera.top + height;
		
		if (_camera.top >= _player._playerHitRc.top && _camY < 0)
		{
			_camY += 4.0f;
			//_player._Py -= 6.0f;
		}
	}
}

void Player::EnemysetDie()
{

	for (int i = 0; i < _em->getVNormal().size(); i++)
	{
			RECT temp;
			RECT enemy = _em->getVNormal()[i]->getENEMY()._EnemyRc;
			if (IntersectRect(&temp, &_player._playeratkRc, &enemy))
			{
				_em->getVNormal()[i]->setEnemyDie(false);
				
				_em->removeNormal(i);
				
				_enemycount += 1;
			
			}
		
	}


}
