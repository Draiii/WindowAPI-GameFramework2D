#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class sceneTest : public gameNode
{
private:
	player* _player;	//플레이어 클래스
	enemyManager* _enemyManager; //적매니져 클래스

public:
	HRESULT init();
	void release();
	void update();
	void render();

	sceneTest() {}
	~sceneTest() {}
};

