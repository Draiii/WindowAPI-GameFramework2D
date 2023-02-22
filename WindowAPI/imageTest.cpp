#include "stdafx.h"
#include "imageTest.h"


HRESULT imageTest::init()
{
	_testImg = IMAGEMANAGER->addImage("테스트", "신세경.bmp", 500, 500);

	//1. 루프렌더
	//백그라운드 이미지 및 루프렌더 변수 초기화
	IMAGEMANAGER->addImage("백그라운드", "신세경.bmp", WINSIZEX, WINSIZEY);
	_loopX = _loopY = 0;


	//2. 스케일렌더
	//일반이미지, 프레임이미지 및 변수 초기화
	_img = IMAGEMANAGER->addImage("입술", "입술.bmp", 118, 67, true, RGB(255, 0, 255));
	_frameImg = IMAGEMANAGER->addFrameImage("호박", "호박.bmp", 400.f, 400.f, 800, 264, 8, 2);
	_index = _count = 0;

	//3. 로테이트렌더
	_angle = 0.0f;

	return S_OK;
}

void imageTest::release()
{
}

void imageTest::update()
{
	//1. 루프렌더
	//백그라운드 루프
	//_loopX++;
	_loopX += 3;
	//_loopY--;

	//2. 스케일렌더
	//프레임 이미지 애니메이션
	_count++;
	if (_count % 5 == 0)
	{
		_index++;
		if (_index > 7)
		{
			_index = 0;
		}
	}


	//3. 로테이트 렌더
	//각도를 화면 중점과 마우스 좌표로 구하기
	//_angle = getAngle(WINSIZEX / 2, WINSIZEY / 2, _ptMouse.x, _ptMouse.y);

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_angle += 0.05f;
	}

}

void imageTest::render()
{
	//1. 루프렌더
	//루프시킬 렉트의 영역 (화면 크기영역)
	RECT rc = RectMake(100, 100, WINSIZEX - 200, WINSIZEY - 200);
	//IMAGEMANAGER->loopRender("백그라운드", getMemDC(), &rc, _loopX, _loopY);

	//2. 스케일렌더
	_img->render(getMemDC(), 100, 100);
	_img->scaleRender(getMemDC(), 300, 100, 1.5f);
	//프레임 이미지
	//_frameImg->frameRender(getMemDC(), 100, 300, _index, 0);
	//_frameImg->scaleFrameRender(getMemDC(), 300, 300, _index, 0, 2.0f);

	//3. 로테이트렌더
	_img->rotateRender(getMemDC(), 600, 100, _angle);
	//프레임 이미지
	_frameImg->rotateFrameRender(getMemDC(), 600, 300, _index, 0, _angle);

	//_testImg->rotateRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, _angle);

}
