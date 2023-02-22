#pragma once
#include "gameNode.h"
/*앞으로 메인게임은 각각의 씬들만 관리를 한다*/
/*헤더파일만 메인게임에 추가하기*/
#include "sceneTest.h"
#include "sceneTest1.h"
#include "pixcelCollisionScene.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "soundTestScene.h"
#include "isometricTest.h"
#include "maptoolScene.h"
#include "gdipTestScene.h"
//#include "Astar.h"

//포폴게임
#include "introSecen.h"
#include "dungeonSecen.h"
#include "optionUI.h"
#include "myPlayer.h"
#include "monster_1.h"
#include "myAstar.h"

class mainGame : public gameNode
{
	
public:

	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

