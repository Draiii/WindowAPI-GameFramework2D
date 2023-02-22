#pragma once
#include "gameNode.h"


#define MONSTER_IMAGE_HEIGHT 74
#define ZOMBIE_EA 5
#define VAMP_EA 3

//Ŭ���� ���漱�� / ��ȣ����
//������
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

	//���� ����
	vector <tagMonster> vZombieMonster;
	//���� ����
	vector <tagMonster> vVampMonster;
	//���� Į �����
	vector <tagMonster> vVamp_2Monster;

public:

	
	HRESULT init();
	void release();
	void update();
	void render();
	
	
	//����
	vector <tagMonster> getZombieMob() { return vZombieMonster; }
	//���� ����
	void zombieMonRender(int _index, float _moveX, float _moveY);
	

	//����
	vector <tagMonster> getVampMob() { return vVampMonster; }
	//���� ����
	void vampMonRender(int _index, float _moveX, float _moveY);
	

	//����
	vector <tagMonster> getVamp_2Mob() { return vVamp_2Monster; }
	//���� ����
	void vamp_2MonRender(int _index, float _moveX, float _moveY);

	//ĳ������ ���ݰ� ���� �ǰ�ó�� �Լ�
	bool attackMonster(RECT _rc, vector <tagMonster>* _monster, int _index);

	monster_1() {}
	~monster_1() {}
};

