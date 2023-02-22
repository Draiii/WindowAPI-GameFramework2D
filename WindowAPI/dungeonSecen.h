#pragma once
#include "gameNode.h"
#define TILE_WIDTH 52
#define TILE_HEIGHT 52
#define FOG_TILE_WIDTH 60
#define FOG_TILE_HEIGHT 60
#define TILE_X_EA 27
#define TILE_Y_EA 15

#define MOVE_SPEED 6.5f
#define ATTACK_SPEED 19.5f

enum MAPMOVEDIRECTION
{
	HOLD, MOVE_LEFT, MOVE_TOP, MOVE_RIGHT, MOVE_BOTTOM,
	MOVE_LEFT_TOP, MOVE_RIGHT_TOP, MOVE_RIGHT_BOTTOM, MOVE_LEFT_BOTTOM,
	ATTACK_LEFT, ATTACK_TOP, ATTACK_RIGHT, ATTACK_BOTTOM,
	ATTACK_LEFT_TOP, ATTACK_RIGHT_TOP, ATTACK_RIGHT_BOTTOM, ATTACK_LEFT_BOTTOM,

};

enum TILEFOG
{
	DARKNESS, CLOUDY, BRIGHT 
};
//캐릭 범위 렉트
struct tagRangeRc
{
	RECT rc;
	float x, y;
};

//타일
struct tagMainTile
{
	image* Img;
	RECT rc;
	float x, y;	
};

//클래스 전방선언 / 상호참조
//플레이어
class myPlayer;
//몬스터 
class monster_1;
//astar
class myAstar;

class dungeonSecen :	public gameNode
{
private:
	//클래스 전방선언 / 상호참조
	myPlayer* myPlayerCss;
	monster_1* myMonsterCss;
	myAstar* myAstarCss;

	tagMainTile mainTile[TILE_Y_EA][TILE_X_EA];

	MAPMOVEDIRECTION mapMoveDirection;
	//맵이미지
	image* dungeon1Imager;
	//픽셀충돌용 맵
	image* dungeon1PixelImager;
	//안개
	image* dungeon1FogImager;	
	//안개 알파
	image* dungeon1FogAlphaImager;
	//케릭터 범위 렉트
	vector <tagRangeRc> rangeRc;
	//마우스 이미지
	image* mouseOver;

	float dungeon1MoveX;
	float dungeon1MoveY;

	int playerInitIdX, playerInitIdY;

	int CenterX;
	int CenterY;

	bool left;
	bool leftTop;
	bool top;
	bool rightTop;
	bool right;
	bool rightBottom;
	bool bottom;
	bool leftBottom;

	//플레이어가 공격할때 모션
	float AttackToMonster;
	bool isAttackToMonster;


	//플레이어 이동
	float move;
	
	float tempY;
	float tempX;

	float shaekCamX;
	float shaekCamY;
	int shakeCamTime;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	

	//픽셀충돌체크
	bool CanMoveMap(MAPMOVEDIRECTION _direct);

	//캐릭터 이동방향
	void moveToLeft();				//왼쪽 이동
	void moveToLeftTop();			//왼쪽위 이동
	void moveToTop();				//위 이동
	void moveToRightTop();			//오른쪽위 이동
	void moveToRight();				//오른쪽 이동
	void moveToRightBottom();		//오른쪽 아래 이동
	void moveToBottom();			//아래이동
	void moveToLeftBottom();		//왼쪽아래 이동


	//안개 충돌
	void rangeRcCheck();

	dungeonSecen() {}
	~dungeonSecen() {}
};

