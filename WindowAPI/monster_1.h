#pragma once
#include "gameNode.h"


#define MONSTER_IMAGE_HEIGHT 74
#define ZOMBIE_EA 5
#define VAMP_EA 3

//클래스 전방선언 / 상호참조
//던전씬
class dungeonSecen;

enum STATE
{
	
};

enum WAVINGH
{
	LEFT, RIGHT
}; 
struct tagMonster
{

	image* img;
	RECT rc;
	WAVINGH wavingH;
	float x, y;
	float moveX, moveY;
	bool isMeeting;
};

class myPlayer;

class monster_1 :	public gameNode
{
private:
	myPlayer* myPlayerCss_Mon;

	//좜비 몬스터
	vector <tagMonster> vZombieMonster;
	//뱀프 몬스터
	vector <tagMonster> vVampMonster;
	//뱀프 칼 몬승터
	vector <tagMonster> vVamp_2Monster;

public:

	
	HRESULT init();
	void release();
	void update();
	void render();
	
	
	//겟터
	vector <tagMonster> getZombieMob() { return vZombieMonster; }
	//좀비 렌더
	void zombieMonRender(int _index, float _moveX, float _moveY);
	

	//겟터
	vector <tagMonster> getVampMob() { return vVampMonster; }
	//뱀프 렌더
	void vampMonRender(int _index, float _moveX, float _moveY);
	

	//겟터
	vector <tagMonster> getVamp_2Mob() { return vVamp_2Monster; }
	//뱀프 렌더
	void vamp_2MonRender(int _index, float _moveX, float _moveY);

	//캐릭터의 공격과 몬스터 피격처리 함수
	bool attackMonster(RECT _rc, vector <tagMonster>* _monster, int _index);

	monster_1() {}
	~monster_1() {}
};

