#include "stdafx.h"
#include "monster_1.h"
#include "dungeonSecen.h"


HRESULT monster_1::init()
{

	//좀비ㅑ 초기화
	for (int i = 0; i < ZOMBIE_EA; i++)
	{
		tagMonster zombie;
		zombie.wavingH = LEFT;
		zombie.moveX = zombie.moveY = 0;
		zombie.x = NULL;
		zombie.y = NULL;
		zombie.rc = RectMake(zombie.x, zombie.y, TILE_WIDTH, TILE_HEIGHT);
		zombie.isMeeting = false;
		char str[128];
		sprintf(str, "zombie_%d", i);
		zombie.img = IMAGEMANAGER->addFrameImage(str, "image/monster/zombie_1.bmp", 104, 74, 2, 1, true, RGB(255, 0, 255));

		vZombieMonster.push_back(zombie);
	}

	// 좀비 좌표 값
	vZombieMonster[0].x = 936;
	vZombieMonster[0].y = 2132;
	vZombieMonster[1].x = 2080;
	vZombieMonster[1].y = 2184;
	vZombieMonster[2].x = 1664;
	vZombieMonster[2].y = 1144;
	vZombieMonster[3].x = 1508;
	vZombieMonster[3].y = 416;
	vZombieMonster[4].x = 416;
	vZombieMonster[4].y = 718;


	//뱀프 초기화
	for (int i = 0; i < VAMP_EA; i++)
	{
		tagMonster vamp;
		vamp.wavingH = LEFT;
		vamp.moveX = vamp.moveY = 0;
		vamp.x = NULL;
		vamp.y = NULL;
		vamp.rc = RectMake(vamp.x, vamp.y, TILE_WIDTH, TILE_HEIGHT);
		vamp.isMeeting = false;
		char str[128];
		sprintf(str, "vamp_%d", i);
		vamp.img = IMAGEMANAGER->addFrameImage(str, "image/monster/vamp_1.bmp", 104, 74, 2, 1, true, RGB(255, 0, 255));

		vVampMonster.push_back(vamp);
	}

	//뱀프 좌표 값
	vVampMonster[0].x = 676;
	vVampMonster[0].y = 1872;
	vVampMonster[1].x = 1716;
	vVampMonster[1].y = 676;
	vVampMonster[2].x = 1092;
	vVampMonster[2].y = 728;


	//뱀프2 초기화
	for (int i = 0; i < VAMP_EA; i++)
	{
		tagMonster vamp_2;
		vamp_2.wavingH = LEFT;
		vamp_2.moveX = vamp_2.moveY = 0;
		vamp_2.x = NULL;
		vamp_2.y = NULL;
		vamp_2.rc = RectMake(vamp_2.x, vamp_2.y, TILE_WIDTH, TILE_HEIGHT);
		vamp_2.isMeeting = false;
		char str[128];
		sprintf(str, "vamp_2_%d", i);
		vamp_2.img = IMAGEMANAGER->addFrameImage(str, "image/monster/vamp_2.bmp", 104, 74, 2, 1, true, RGB(255, 0, 255));

		vVamp_2Monster.push_back(vamp_2);
	}

	//뱀프 좌표 값
	vVamp_2Monster[0].x = 2444 - 52;
	vVamp_2Monster[0].y = 1300;
	vVamp_2Monster[1].x = 676;
	vVamp_2Monster[1].y = 416;
	vVamp_2Monster[2].x = 572;
	vVamp_2Monster[2].y = 832;


	return S_OK;
}

void monster_1::release()
{
}

void monster_1::update()
{
	if (KEYMANAGER->isOnceKeyDown('F1')) SCENEMANAGER->loadScene("intro");
	if (KEYMANAGER->isOnceKeyDown('F2')) SCENEMANAGER->loadScene("dungeonSecen");
	if (KEYMANAGER->isOnceKeyDown('F3')) SCENEMANAGER->loadScene("myAstar");
}

void monster_1::render()
{
}
//좀비 렌더
void monster_1::zombieMonRender(int _index, float _moveX, float _moveY)
{
#define SPEED 0.1f
#define AREA 2.0f

	vZombieMonster[_index].rc = RectMake(vZombieMonster[_index].x + _moveX, vZombieMonster[_index].y + _moveY, TILE_WIDTH, TILE_HEIGHT);
	vZombieMonster[_index].img->setX(vZombieMonster[_index].rc.left);
	vZombieMonster[_index].img->setY(vZombieMonster[_index].rc.top );




	if (vZombieMonster[_index].wavingH == RIGHT)
	{
		if (vZombieMonster[_index].moveX <= 0)
			vZombieMonster[_index].moveY -= SPEED * 2;
		else
			vZombieMonster[_index].moveY += SPEED * 2;

		vZombieMonster[_index].moveX += SPEED;

		if (vZombieMonster[_index].moveX > AREA)
		{
			//moveY = 0;
			//moveX = 0.0f;
			vZombieMonster[_index].wavingH = LEFT;
		}
	}
	if (vZombieMonster[_index].wavingH == LEFT)
	{
		if (vZombieMonster[_index].moveX >= 0)
			vZombieMonster[_index].moveY -= SPEED * 2;
		else
			vZombieMonster[_index].moveY += SPEED * 2;

		vZombieMonster[_index].moveX -= SPEED;

		if (vZombieMonster[_index].moveX < -AREA)
		{
			//moveY = 0;
			//moveX = 0.0f;
			vZombieMonster[_index].wavingH = RIGHT;
		}
	}

	vZombieMonster[_index].img->setX(vZombieMonster[_index].img->getX() + vZombieMonster[_index].moveX);
	vZombieMonster[_index].img->setY(vZombieMonster[_index].img->getY() + vZombieMonster[_index].moveY);
	//렉트
	//Rectangle(getMemDC(), vZombieMonster[_index].rc);
	vZombieMonster[_index].img->frameRender(getMemDC(), vZombieMonster[_index].img->getX(), vZombieMonster[_index].img->getY() + (TILE_HEIGHT - MONSTER_IMAGE_HEIGHT));
}
//뱀프 렌더
void monster_1::vampMonRender(int _index, float _moveX, float _moveY)
{
#define SPEED 0.1f
#define AREA 2.0f

	vVampMonster[_index].rc = RectMake(vVampMonster[_index].x + _moveX, vVampMonster[_index].y + _moveY, TILE_WIDTH, TILE_HEIGHT);
	vVampMonster[_index].img->setX(vVampMonster[_index].rc.left);
	vVampMonster[_index].img->setY(vVampMonster[_index].rc.top);



	if (vVampMonster[_index].wavingH == RIGHT)
	{
		if (vVampMonster[_index].moveX <= 0)
			vVampMonster[_index].moveY -= SPEED * 2;
		else
			vVampMonster[_index].moveY += SPEED * 2;

		vVampMonster[_index].moveX += SPEED;

		if (vVampMonster[_index].moveX > AREA)
		{
			vVampMonster[_index].wavingH = LEFT;
		}
	}
	if (vVampMonster[_index].wavingH == LEFT)
	{
		if (vVampMonster[_index].moveX >= 0)
			vVampMonster[_index].moveY -= SPEED * 2;
		else
			vVampMonster[_index].moveY += SPEED * 2;

		vVampMonster[_index].moveX -= SPEED;

		if (vVampMonster[_index].moveX < -AREA)
		{
			vVampMonster[_index].wavingH = RIGHT;
		}
	}

	vVampMonster[_index].img->setX(vVampMonster[_index].img->getX() + vVampMonster[_index].moveX);
	vVampMonster[_index].img->setY(vVampMonster[_index].img->getY() + vVampMonster[_index].moveY);

	//렉트
	//Rectangle(getMemDC(), vVampMonster[_index].rc);
	vVampMonster[_index].img->frameRender(getMemDC(), vVampMonster[_index].img->getX(), vVampMonster[_index].img->getY() + (TILE_HEIGHT - MONSTER_IMAGE_HEIGHT));
}
//뱀프2 렌더
void monster_1::vamp_2MonRender(int _index, float _moveX, float _moveY)
{
#define SPEED 0.1f
#define AREA 2.0f
	//웨이브 좌우

	vVamp_2Monster[_index].rc = RectMake(vVamp_2Monster[_index].x + _moveX, vVamp_2Monster[_index].y + _moveY, TILE_WIDTH, TILE_HEIGHT);
	vVamp_2Monster[_index].img->setX(vVamp_2Monster[_index].rc.left);
	vVamp_2Monster[_index].img->setY(vVamp_2Monster[_index].rc.top);

	

	if (vVamp_2Monster[_index].wavingH == RIGHT)
	{
		if (vVamp_2Monster[_index].moveX <= 0)
			vVamp_2Monster[_index].moveY -= SPEED * 2;
		else
			vVamp_2Monster[_index].moveY += SPEED * 2;

		vVamp_2Monster[_index].moveX += SPEED;

		if (vVamp_2Monster[_index].moveX > AREA)
		{
			//moveY = 0;
			//moveX = 0.0f;
			vVamp_2Monster[_index].wavingH = LEFT;
		}
	}
	if (vVamp_2Monster[_index].wavingH == LEFT)
	{
		if (vVamp_2Monster[_index].moveX >= 0)
			vVamp_2Monster[_index].moveY -= SPEED * 2;
		else
			vVamp_2Monster[_index].moveY += SPEED * 2;

		vVamp_2Monster[_index].moveX -= SPEED;

		if (vVamp_2Monster[_index].moveX < -AREA)
		{
			//moveY = 0;
			//moveX = 0.0f;
			vVamp_2Monster[_index].wavingH = RIGHT;
		}
	}

	vVamp_2Monster[_index].img->setX(vVamp_2Monster[_index].img->getX() + vVamp_2Monster[_index].moveX);
	vVamp_2Monster[_index].img->setY(vVamp_2Monster[_index].img->getY() + vVamp_2Monster[_index].moveY);

	//렉트
	//Rectangle(getMemDC(), vVamp_2Monster[_index].rc);
	vVamp_2Monster[_index].img->frameRender(getMemDC(), vVamp_2Monster[_index].img->getX(), vVamp_2Monster[_index].img->getY() + (TILE_HEIGHT - MONSTER_IMAGE_HEIGHT));
}

//캐릭터의 공격과 몬스터 피격처리 함수
bool monster_1::attackMonster(RECT _rc, vector<tagMonster>* _monster, int _index)
{
	RECT temp;
	//충돌하면 트루값 반환
	if (IntersectRect(&temp, &_rc, &_monster->at(_index).rc))
	{
		return true;
	}
	//충돌 안하면 펄스값 
	else return false;	
}
