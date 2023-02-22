#include "stdafx.h"
#include "sceneTest.h"

HRESULT sceneTest::init()
{
	//백그라운드 이미지초기화
	IMAGEMANAGER->addImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY);
	//UFO 프레임 이미지초기화
	IMAGEMANAGER->addFrameImage("ufo", "ufo.bmp", 530, 32, 10, 1);
	//총알 이미지
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));


	//플레이어 클래스 초기화
	_player = new player;
	_player->init();

	//적매니져 클래스 초기화
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//상호참조 세팅하기
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void sceneTest::release()
{
	//플레이어 클래스 해제
	//_player->release();
	SAFE_DELETE(_player);

	//적매니져 클래스 해제
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void sceneTest::update()
{
	//플레이어 클래스 업데이트
	_player->update();

	//적매니져 클래스 업데이트
	_enemyManager->update();

	//씬변경
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->loadScene("테스트씬1");
	}
}

void sceneTest::render()
{
	//백그라운드 렌더
	IMAGEMANAGER->render("백그라운드", getMemDC());

	//플레이어 클래스 렌더
	_player->render();

	//적매니져 클래스 렌더
	_enemyManager->render();
}
