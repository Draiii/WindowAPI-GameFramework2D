#pragma once
#include "gameNode.h"
/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ϸ� ���ΰ��ӿ� �߰��ϱ�*/
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

//��������
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

