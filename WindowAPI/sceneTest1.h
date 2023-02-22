#pragma once
#include "gameNode.h"

class sceneTest1 : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	sceneTest1() {}
	~sceneTest1() {}
};

