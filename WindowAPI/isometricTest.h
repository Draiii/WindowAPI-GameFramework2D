#pragma once
#include "gameNode.h"

//타일갯수
#define TILEX 5
#define TILEY 5
//타일크기
#define TILESIZEX 200
#define TILESIZEY (TILESIZEX / 2)
//타일반크기
#define TILESIZEX_HALF (TILESIZEX / 2)
#define TILESIZEY_HALF (TILESIZEY / 2)
//아이소타일 시작좌표(0, 0)
#define STARTX (WINSIZEX / 2)
#define STARTY 100

//타일 구조체
struct tagCell
{
	int x, y;
	RECT rc;
};

class isometricTest : public gameNode
{
private:
	tagCell _tile[TILEX][TILEY];  //타일구조체 총 25개
	POINT _index;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	isometricTest() {}
	~isometricTest() {}
};

