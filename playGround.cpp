#include "pch.h"
#include "playGround.h"




playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ���⿡�� �ض�!!!
HRESULT playGround::init()
{
	CSound::Init();
	gameNode::init(true);

	SCENEMANAGER->addScene("MENU", new MENU);
	SCENEMANAGER->addScene("GAME", new gameManager);
	SCENEMANAGER->addScene("ENDING", new ending);
	SCENEMANAGER->changeScene("MENU");


	return S_OK;
}

//�޸� ������ ����� �ض�!!!!
void playGround::release()
{
	gameNode::release();
	CSound::Release();
	


}

//����ó���� ����ٰ�!
void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
	
		init();
	}






}

//����� �׷����!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============������ ���� �ǵ帮�� ���� ============
	



	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());

	//=============== �ؿ��� �ǵ������� ================
	_backBuffer->render(getHDC(), 0, 0);

}

