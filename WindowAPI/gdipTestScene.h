#pragma once
#include "gameNode.h"

class gdipTestScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	gdipTestScene() {}
	~gdipTestScene() {}
};