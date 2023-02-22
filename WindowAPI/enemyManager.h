#pragma once
#include "gameNode.h"
#include "minion.h"		//미니언 클래스를 사용하기 위해
#include "bullet.h"		//공용총알 클래스를 사용하기 위해

//플레이어와 상호참조하기 위해 클래스 전방선언
class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;
	
	bullet* _bullet;	//공용총알 클래스
	int _count;

	player* _player;	//동적할당 하면 안된다!!
	//메인게임에서 생성한 플레이어와 여기서 생성한 플레이어는
	//전혀 다른 메모리에 생성되어서 서로 참조가 불가능

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//충돌함수
	void collision();

	//미니언 세팅 => 초기화 넣기
	void setMinion();
	//미니언 총알발사
	void minionBulletFire();
	//미니언 삭제
	void removeMinion(int index);
	//미니언 벡터 가져오기
	vector<enemy*> getVMinion() { return _vMinion; }

	//상호참조시 플레이어 포인터를 넘길 셋터함수
	void setPlayerLink(player* player) { _player = player; }

	enemyManager() {}
	~enemyManager() {}
};

