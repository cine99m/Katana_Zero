#include "pch.h"
#include "playGround.h"




playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기에다 해라!!!
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

//메모리 해제는 여기다 해라!!!!
void playGround::release()
{
	gameNode::release();
	CSound::Release();
	


}

//연산처리는 여기다가!
void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
	
		init();
	}






}

//여기다 그려줘라!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============위에는 제발 건드리지 마라 ============
	



	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());

	//=============== 밑에도 건들지마라 ================
	_backBuffer->render(getHDC(), 0, 0);

}

