#include "pch.h"
#include "image.h"


#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0,0,0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//뭔가가 미리 정의되어있다면 메모리 해제 해주어라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	if (_imageInfo == nullptr)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC 영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}
	   	 
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC 영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != nullptr) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC 영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//모든 init함수에서 블렌드 이미지 세팅을 해뒀으니 
		//릴리즈에서도 해제해줘야한다
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_blendImage);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}


void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC
			0,					//복사될 좌표(left)
			0,					//복사될 좌표(top)
			_imageInfo->width,		//복사될 크기 (가로크기)
			_imageInfo->height,		//복사될 크기 (세로크기)
			_imageInfo->hMemDC,		//복사해올 DC
			0, 0,					//복사해올 시작좌표(left, top)
			_imageInfo->width,		//복사해올 크기(가로)
			_imageInfo->height,		// 			(세로)
			_transColor);			//복사할때 제외할 픽셀값
	}
	else
	{
		//BitBlt == DC영역간의 고속복사를 해주는 함수
		BitBlt(
			hdc,				//복사될 DC
			0,				//복사될 좌표 (left)
			0,				//복사될 좌표 (top)
			_imageInfo->width,	//복사될 크기
			_imageInfo->height,
			_imageInfo->hMemDC,//복사해올 DC
			0, 0,				//복사시작될 좌표(left, top)
			SRCCOPY);			//변형없이 복사한다
	}

}



void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC
			destX,					//복사될 좌표(left)
			destY,					//복사될 좌표(top)
			_imageInfo->width,		//복사될 크기 (가로크기)
			_imageInfo->height,		//복사될 크기 (세로크기)
			_imageInfo->hMemDC,		//복사해올 DC
			0, 0,					//복사해올 시작좌표(left, top)
			_imageInfo->width,		//복사해올 크기(가로)
			_imageInfo->height,		// 			(세로)
			_transColor	);			//복사할때 제외할 픽셀값
	}
	else
	{
		//BitBlt == DC영역간의 고속복사를 해주는 함수
		BitBlt(
			hdc,				//복사될 DC
			destX,				//복사될 좌표 (left)
			destY,				//복사될 좌표 (top)
			_imageInfo->width,	//복사될 크기
			_imageInfo->height,
			_imageInfo->hMemDC,//복사해올 DC
			0, 0,				//복사시작될 좌표(left, top)
			SRCCOPY);			//변형없이 복사한다
	}
	

}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의 DC
			destX,					//복사될 좌표(left)
			destY,					//복사될 좌표(top)
			sourWidth,				//복사될 크기 (가로크기)
			sourHeight,				//복사될 크기 (세로크기)
			_imageInfo->hMemDC,		//복사해올 DC
			sourX, sourY,					//복사해올 시작좌표(left, top)
			sourWidth,				//복사해올 크기(가로)
			sourHeight,				// 			(세로)
			_transColor);			//복사할때 제외할 픽셀값
	}
	else
	{
		//BitBlt == DC영역간의 고속복사를 해주는 함수
		BitBlt(
			hdc,				//복사될 DC
			destX,				//복사될 좌표 (left)
			destY,				//복사될 좌표 (top)
			sourWidth,			//복사될 크기
			sourHeight,
			_imageInfo->hMemDC,//복사해올 DC
			sourX, sourY,		//복사시작될 좌표(left, top)
			SRCCOPY);			//변형없이 복사한다
	}

}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의 DC
			destX,						//복사될 좌표(left)
			destY,						//복사될 좌표(top)
			_imageInfo->frameWidth,		//복사될 크기 (가로크기)
			_imageInfo->frameHeight,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,							//복사해올 시작좌표(left, top)
			_imageInfo->frameWidth,		//복사해올 크기(가로)
			_imageInfo->frameHeight,	// 			  (세로)
			_transColor);				//복사할때 제외할 픽셀값
	}
	else
	{
		//BitBlt == DC영역간의 고속복사를 해주는 함수
		BitBlt(
			hdc,						//복사될 DC
			destX,						//복사될 좌표 (left)
			destY,						//복사될 좌표 (top)
			_imageInfo->frameWidth,		//복사될 크기 (가로크기)
			_imageInfo->frameHeight,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);					//변형없이 복사한다
	}

}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의 DC
			destX,						//복사될 좌표(left)
			destY,						//복사될 좌표(top)
			_imageInfo->frameWidth,		//복사될 크기 (가로크기)
			_imageInfo->frameHeight,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,							//복사해올 시작좌표(left, top)
			_imageInfo->frameWidth,		//복사해올 크기(가로)
			_imageInfo->frameHeight,	// 			  (세로)
			_transColor);				//복사할때 제외할 픽셀값
	}
	else
	{
		//BitBlt == DC영역간의 고속복사를 해주는 함수
		BitBlt(
			hdc,						//복사될 DC
			destX,						//복사될 좌표 (left)
			destY,						//복사될 좌표 (top)
			_imageInfo->frameWidth,		//복사될 크기 (가로크기)
			_imageInfo->frameHeight,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);					//변형없이 복사한다
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//오프셋 영역 보정을 해봅시다 보정은 나머지 연산자를 이용하면 매우 깔끔하고 정확합니다
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//상하좌우 다 루프를 시켜야하니까 필요한 도구들
	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	//Y축 루프부터 처리해보자
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;


		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//계산 한 것을 실제로 렌더링 해주는 것은 이 함수
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의 DC
			destX,						//복사될 좌표(left)
			destY,						//복사될 좌표(top)
			_imageInfo->frameWidth,		//복사될 크기 (가로크기)
			_imageInfo->frameHeight,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,							//복사해올 시작좌표(left, top)
			_imageInfo->frameWidth,		//복사해올 크기(가로)
			_imageInfo->frameHeight,	// 			  (세로)
			_transColor);				//복사할때 제외할 픽셀값
	}
	else
	{
		//BitBlt == DC영역간의 고속복사를 해주는 함수
		BitBlt(
			hdc,						//복사될 DC
			destX,						//복사될 좌표 (left)
			destY,						//복사될 좌표 (top)
			_imageInfo->frameWidth,		//복사될 크기 (가로크기)
			_imageInfo->frameHeight,	//복사될 크기 (세로크기)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);					//변형없이 복사한다
	}

	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}


void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}



//오브젝트를 뿌려줄 좌표 x ,y, 플레이어의 x ,y , 배경 x축 최대, 최소, y축 최대,최소 좌표
void image::cameraRender(HDC hdc, int objectX, int objectY, int PlayerX, int PlayerY, int backGroundX, int backGroundx, int backGroundY, int backGroundy)
{
	if (PlayerX <= backGroundx && PlayerY <= backGroundy) 					render(hdc, objectX - backGroundx, objectY - backGroundy);
	else if (PlayerX <= backGroundx && PlayerY >= backGroundY - WINSIZEY)		render(hdc, objectX - backGroundx, WINSIZEY - backGroundY + objectY);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY <= backGroundy) 				    render(hdc, WINSIZEX - backGroundX + objectX, objectY - backGroundy);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY >= backGroundY - WINSIZEY)		render(hdc, WINSIZEX - backGroundX + objectX, WINSIZEY - backGroundY + objectY);


	else if (PlayerX <= backGroundx) 											render(hdc, objectX - backGroundx, objectY - PlayerY);
	else if (PlayerX >= backGroundX - WINSIZEX)									render(hdc, WINSIZEX - backGroundX + objectX, objectY - PlayerY);
	else if (PlayerY <= backGroundy) 											render(hdc, objectX - PlayerX, objectY - backGroundy);
	else if (PlayerY >= backGroundY - WINSIZEY)									render(hdc, objectX - PlayerX, WINSIZEY - backGroundY + objectY);

	else render(hdc, objectX - PlayerX, objectY - PlayerY);
}

//좌표 x ,y ,카메라 고정 값 x, y, 플레이어의 x ,y ,배경 x축 최대, 최소, y축 최대,최소 좌표
void image::cameraFrameRender(HDC hdc, int objectX, int objectY, int PlayerX, int PlayerY, int backGroundX, int backGroundx, int backGroundY, int backGroundy)
{
	if (PlayerX <= backGroundx && PlayerY <= backGroundy) 									frameRender(hdc, objectX - backGroundx, objectY - backGroundy);
	else if (PlayerX <= backGroundx && PlayerY >= backGroundY - WINSIZEY)					frameRender(hdc, objectX - backGroundx, WINSIZEY - backGroundY + objectY);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY <= backGroundy) 				    frameRender(hdc, WINSIZEX - backGroundX + objectX, objectY - backGroundy);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY >= backGroundY - WINSIZEY)		frameRender(hdc, WINSIZEX - backGroundX + objectX, WINSIZEY - backGroundY + objectY);


	else if (PlayerX <= backGroundx) 											frameRender(hdc, objectX - backGroundx, objectY - PlayerY);
	else if (PlayerX >= backGroundX - WINSIZEX)									frameRender(hdc, WINSIZEX - backGroundX + objectX, objectY - PlayerY);
	else if (PlayerY <= backGroundy) 											frameRender(hdc, objectX - PlayerX, objectY - backGroundy);
	else if (PlayerY >= backGroundY - WINSIZEY)									frameRender(hdc, objectX - PlayerX, WINSIZEY - backGroundY + objectY);

	else frameRender(hdc, objectX - PlayerX, objectY - PlayerY);

}


//좌표 x ,y ,카메라 고정 값 x, y, 배경 x축 최대, 최소, y축 최대,최소 좌표
void image::cameraPlayerRender(HDC hdc, int PlayerX, int PlayerY, int cameraPosX, int cameraPosY, int backGroundX, int backGroundx, int backGroundY, int backGroundy)

{
	if (PlayerX <= backGroundx && PlayerY <= backGroundy) 						frameRender(hdc, cameraPosX + PlayerX - backGroundx, cameraPosY + PlayerY - backGroundy);
	else if (PlayerX <= backGroundx && PlayerY >= backGroundY - WINSIZEY)						frameRender(hdc, cameraPosX + PlayerX - backGroundx, cameraPosY + PlayerY - backGroundY + WINSIZEY);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY <= backGroundy) 						frameRender(hdc, cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY + PlayerY - backGroundy);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY >= backGroundY - WINSIZEY)						frameRender(hdc, cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY + PlayerY - backGroundY + WINSIZEY);


	else if (PlayerX <= backGroundx) 								frameRender(hdc, cameraPosX + PlayerX - backGroundx, cameraPosY);
	else if (PlayerX >= backGroundX - WINSIZEX)						frameRender(hdc, cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY);
	else if (PlayerY <= backGroundy) 								frameRender(hdc, cameraPosX, cameraPosY + PlayerY - backGroundy);
	else if (PlayerY >= backGroundY - WINSIZEY)						frameRender(hdc, cameraPosX, cameraPosY + PlayerY - backGroundY + WINSIZEY);

	else	frameRender(hdc, cameraPosX, cameraPosY);
}


void image::cameraAniRender(HDC hdc, int objectX, int objectY, int PlayerX, int PlayerY, int backGroundX, int backGroundx, int backGroundY, int backGroundy, animation* ani)
{

	if (PlayerX <= backGroundx && PlayerY <= backGroundy) 									aniRender(hdc, objectX - backGroundx, objectY - backGroundy, ani);
	else if (PlayerX <= backGroundx && PlayerY >= backGroundY - WINSIZEY)					aniRender(hdc, objectX - backGroundx, WINSIZEY - backGroundY + objectY, ani);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY <= backGroundy) 				    aniRender(hdc, WINSIZEX - backGroundX + objectX, objectY - backGroundy, ani);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY >= backGroundY - WINSIZEY)		aniRender(hdc, WINSIZEX - backGroundX + objectX, WINSIZEY - backGroundY + objectY, ani);


	else if (PlayerX <= backGroundx) 											aniRender(hdc, objectX - backGroundx, objectY - PlayerY, ani);
	else if (PlayerX >= backGroundX - WINSIZEX)									aniRender(hdc, WINSIZEX - backGroundX + objectX, objectY - PlayerY, ani);
	else if (PlayerY <= backGroundy) 											aniRender(hdc, objectX - PlayerX, objectY - backGroundy, ani);
	else if (PlayerY >= backGroundY - WINSIZEY)									aniRender(hdc, objectX - PlayerX, WINSIZEY - backGroundY + objectY, ani);

	else aniRender(hdc, objectX - PlayerX, objectY - PlayerY, ani);
}

void image::cameraPlayerAniRender(HDC hdc, int PlayerX, int PlayerY, int cameraPosX, int cameraPosY, int backGroundX, int backGroundx, int backGroundY, int backGroundy, animation* ani)
{
	if (PlayerX <= backGroundx && PlayerY <= backGroundy) 						aniRender(hdc, cameraPosX + PlayerX - backGroundx, cameraPosY + PlayerY - backGroundy, ani);
	else if (PlayerX <= backGroundx && PlayerY >= backGroundY - WINSIZEY)						aniRender(hdc, cameraPosX + PlayerX - backGroundx, cameraPosY + PlayerY - backGroundY + WINSIZEY, ani);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY <= backGroundy) 						aniRender(hdc, cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY + PlayerY - backGroundy, ani);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY >= backGroundY - WINSIZEY)						aniRender(hdc, cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY + PlayerY - backGroundY + WINSIZEY, ani);


	else if (PlayerX <= backGroundx) 								aniRender(hdc, cameraPosX + PlayerX - backGroundx, cameraPosY, ani);
	else if (PlayerX >= backGroundX - WINSIZEX)						aniRender(hdc, cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY, ani);
	else if (PlayerY <= backGroundy) 								aniRender(hdc, cameraPosX, cameraPosY + PlayerY - backGroundy, ani);
	else if (PlayerY >= backGroundY - WINSIZEY)						aniRender(hdc, cameraPosX, cameraPosY + PlayerY - backGroundY + WINSIZEY, ani);

	else	aniRender(hdc, cameraPosX, cameraPosY, ani);
}
