#pragma once
#include "gameNode.h"
#include "CSound.h"

class ending : public gameNode
{
private:
	gameNode* _END;

	image* ENDING;
	image* ENDINGTITLE;

	CSound* ENDSOUND;

	int _fadeIn;
	int _fadeOut;
	int _count;

	int _fadeIn2;
	bool _isFadeInOut;

public:

	ending();
	~ending();

	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Խ�
	virtual void update();			//�����ϴ� �Լ�
	virtual void render();			//�׸��� �Լ�

};

