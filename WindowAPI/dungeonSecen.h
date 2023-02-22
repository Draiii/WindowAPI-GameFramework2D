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
//ĳ�� ���� ��Ʈ
struct tagRangeRc
{
	RECT rc;
	float x, y;
};

//Ÿ��
struct tagMainTile
{
	image* Img;
	RECT rc;
	float x, y;	
};

//Ŭ���� ���漱�� / ��ȣ����
//�÷��̾�
class myPlayer;
//���� 
class monster_1;
//astar
class myAstar;

class dungeonSecen :	public gameNode
{
private:
	//Ŭ���� ���漱�� / ��ȣ����
	myPlayer* myPlayerCss;
	monster_1* myMonsterCss;
	myAstar* myAstarCss;

	tagMainTile mainTile[TILE_Y_EA][TILE_X_EA];

	MAPMOVEDIRECTION mapMoveDirection;
	//���̹���
	image* dungeon1Imager;
	//�ȼ��浹�� ��
	image* dungeon1PixelImager;
	//�Ȱ�
	image* dungeon1FogImager;	
	//�Ȱ� ����
	image* dungeon1FogAlphaImager;
	//�ɸ��� ���� ��Ʈ
	vector <tagRangeRc> rangeRc;
	//���콺 �̹���
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

	//�÷��̾ �����Ҷ� ���
	float AttackToMonster;
	bool isAttackToMonster;


	//�÷��̾� �̵�
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

	

	//�ȼ��浹üũ
	bool CanMoveMap(MAPMOVEDIRECTION _direct);

	//ĳ���� �̵�����
	void moveToLeft();				//���� �̵�
	void moveToLeftTop();			//������ �̵�
	void moveToTop();				//�� �̵�
	void moveToRightTop();			//�������� �̵�
	void moveToRight();				//������ �̵�
	void moveToRightBottom();		//������ �Ʒ� �̵�
	void moveToBottom();			//�Ʒ��̵�
	void moveToLeftBottom();		//���ʾƷ� �̵�


	//�Ȱ� �浹
	void rangeRcCheck();

	dungeonSecen() {}
	~dungeonSecen() {}
};

