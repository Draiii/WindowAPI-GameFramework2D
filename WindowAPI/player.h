#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"	//체력바 클래스를 사용하기 위해

//적매니져와 상호 참조하기 위해 클래스 전방선언
class enemyManager;

class player : public gameNode
{
private:
	image* _rocket;		//로켓(플레이어) 이미지
	//RECT _rcPlayer;
	missile* _missile;	//미사일 클래스
	bomb* _bomb;		//폭탄 클래스

	enemyManager* _em;	//동적할당 절대 안된다!!!
	//메인게임에서 생성한 em과 여기서 동적할당해버린 em은
	//전혀 다른 메모리 주소라거 서로 참조를 할 수없다

	progressBar* _hpBar;		//체력바
	float _maxHp, _currentHp;	//최대체력, 현재체력

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//충돌함수
	void collision();

	//체력바 피통깍기
	void hitDamage(float damage);

	//미사일 크래스 가져오기
	missile* getMissile() { return _missile; }

	//폭탄 클래스 가져오기
	bomb* getBomb() { return _bomb; }

	//폭탄 삭제
	void removeBomb(int index);

	//플레이어 이미지 가져오기
	image* getPlayerImg() { return _rocket; }

	//상호참조시 적매니져 포인터를 넘길 셋터함수
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

