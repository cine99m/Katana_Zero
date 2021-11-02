#pragma once

//선 그려주는 함수    (뿌려줄 DC, 시작점 X, Y, 끝점 X, Y)
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}


//렉트관련 매크로
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width /2 ), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//사각형 그려주는 매크로함수 (뿌려줄DC, 시작점 X(left), 시작점Y(top), 가로크기, 세로크기)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//사각형 그려주는 매크로함수 (뿌려줄DC, 중점X(left), 중점Y(top), 가로크기, 세로크기)
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//원 그려주는 매크로함수 (뿌려줄DC, 시작점 X(left), 시작점Y(top), 가로크기, 세로크기)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//원 그려주는 매크로함수 (뿌려줄DC, 중점X(left), 중점Y(top), 가로크기, 세로크기)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
//장애물 전용
inline RECT cameraRectMake(int objectX, int objectY, int PlayerX, int PlayerY, int backGroundX, int backGroundx, int backGroundY, int backGroundy, int width, int height, int WINSIZEX, int WINSIZEY)
{
	RECT rc;

	if (PlayerX <= backGroundx && PlayerY <= backGroundy) 									rc = RectMake(objectX - backGroundx, objectY - backGroundy, width, height);
	else if (PlayerX <= backGroundx && PlayerY >= backGroundY - WINSIZEY)					rc = RectMake(objectX - backGroundx, WINSIZEY - backGroundY + objectY, width, height);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY <= backGroundy) 				    rc = RectMake(WINSIZEX - backGroundX + objectX, objectY - backGroundy, width, height);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY >= backGroundY - WINSIZEY)		rc = RectMake(WINSIZEX - backGroundX + objectX, WINSIZEY - backGroundY + objectY, width, height);


	else if (PlayerX <= backGroundx) 											rc = RectMake(objectX - backGroundx, objectY - PlayerY, width, height);
	else if (PlayerX >= backGroundX - WINSIZEX)									rc = RectMake(WINSIZEX - backGroundX + objectX, objectY - PlayerY, width, height);
	else if (PlayerY <= backGroundy) 											rc = RectMake(objectX - PlayerX, objectY - backGroundy, width, height);
	else if (PlayerY >= backGroundY - WINSIZEY)									rc = RectMake(objectX - PlayerX, WINSIZEY - backGroundY + objectY, width, height);

	else rc = RectMake(objectX - PlayerX, objectY - PlayerY, width, height);

	return rc;

}

//카메라 전용
inline RECT cameraPlayerRectMake(int PlayerX, int PlayerY, int cameraPosX, int cameraPosY, int backGroundX, int backGroundx, int backGroundY, int backGroundy, int width, int height, int  WINSIZEX, int WINSIZEY)
{

	RECT rc;

	if (PlayerX <= backGroundx && PlayerY <= backGroundy) 						rc = RectMake(cameraPosX + PlayerX - backGroundx, cameraPosY + PlayerY - backGroundy, width, height);
	else if (PlayerX <= backGroundx && PlayerY >= backGroundY - WINSIZEY)						rc = RectMake(cameraPosX + PlayerX - backGroundx, cameraPosY + PlayerY - backGroundY + WINSIZEY, width, height);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY <= backGroundy) 						rc = RectMake(cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY + PlayerY - backGroundy, width, height);
	else if (PlayerX >= backGroundX - WINSIZEX && PlayerY >= backGroundY - WINSIZEY)						rc = RectMake(cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY + PlayerY - backGroundY + WINSIZEY, width, height);


	else if (PlayerX <= backGroundx) 								rc = RectMake(cameraPosX + PlayerX - backGroundx, cameraPosY, width, height);
	else if (PlayerX >= backGroundX - WINSIZEX)						rc = RectMake(cameraPosX + PlayerX - backGroundX + WINSIZEX, cameraPosY, width, height);
	else if (PlayerY <= backGroundy) 								rc = RectMake(cameraPosX, cameraPosY + PlayerY - backGroundy, width, height);
	else if (PlayerY >= backGroundY - WINSIZEY)						rc = RectMake(cameraPosX, cameraPosY + PlayerY - backGroundY + WINSIZEY, width, height);

	else	rc = RectMake(cameraPosX, cameraPosY, width, height);

	return rc;

}