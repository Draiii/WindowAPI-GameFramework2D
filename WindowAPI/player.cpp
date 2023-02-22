#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init()
{
	//플레이어 이미지 초기화
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));
	//_rcPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 52, 64);
	
	//미사일 클래스 초기화
	_missile = new missile;
	_missile->init(10, 400);

	//폭탄 클래스 초기화
	_bomb = new bomb;
	_bomb->init(5, 600);

	//체력바 클래스 생성후 초기화
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack", _rocket->getX(), _rocket->getY() - 20, 50, 10);
	//피통 초기화
	_maxHp = _currentHp = 100;
	_hpBar->setGauge(_currentHp, _maxHp);

	return S_OK;
}

void player::release()
{
	//미사일 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);

	//폭탄 클래스 해제
	_bomb->release();
	SAFE_DELETE(_bomb);

	//체력바 클래스 해제
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void player::update()
{
	//이미지 바운딩박스로 충돌처리
	//RECT rc;
	//if(IntersectRect(&rc, &_rocket->boudingBox(), ))
	
	//플레이어 움직이기 & 화면밖으로 벗어나지 못하게
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		_rocket->setX(_rocket->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() < WINSIZEX)
	{
		_rocket->setX(_rocket->getX() + 5.0f);
	}
	//총알발사
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//총알클래스야 니꺼 발사시켜라~
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//폭탄발사
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		//폭탄클래스야 니꺼 발사시켜라~
		_bomb->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//미사일 클래스 업데이트
	_missile->update();

	//폭탄 클래스 업데이트
	_bomb->update();

	//충돌함수
	this->collision();

	//체력바 클래스 업데이트
	_hpBar->update();
	//체력바가 플레이어 머리위에 따라다니게 만들기
	_hpBar->setX(_rocket->getX());
	_hpBar->setY(_rocket->getY() - 20);
	_hpBar->setGauge(_currentHp, _maxHp);

	//세이브
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//PLAYERDATA->setHp(_currentHp);
		//POINT pos;
		//pos.x = _rocket->getX();
		//pos.y = _rocket->getY();
		//PLAYERDATA->setPos(pos);

		//itoa =>정수를 문자로
		char temp[128];
		vector<string> vStr;
		vStr.push_back(itoa(_currentHp, temp, 10));
		vStr.push_back(itoa(_rocket->getX(), temp, 10));
		vStr.push_back(itoa(_rocket->getY(), temp, 10));

		TXTDATA->txtSave("save.txt", vStr);
	}
	//로드
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//_currentHp = PLAYERDATA->getHp();
		//_rocket->setX(PLAYERDATA->getPos().x);
		//_rocket->setY(PLAYERDATA->getPos().y);
	
		vector<string> vStr;
		vStr = TXTDATA->txtLoad("save.txt");
		//atoi => 문자를 정수로
		_currentHp = atoi(vStr[0].c_str());
		_rocket->setX(atoi(vStr[1].c_str()));
		_rocket->setY(atoi(vStr[2].c_str()));

	}

}

void player::render()
{
	//플레이어 렌더
	_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	//_rocket->render(getMemDC(), _rcPlayer.left, _rcPlayer.top);

	//미사일 클래스 렌더
	_missile->render();

	//폭탄 클래스 렌더
	_bomb->render();

	//체력바 클래스 렌더
	_hpBar->render();
}

//충돌함수 (플레이어 총알들과 적매니져의 미니언)
void player::collision()
{
	for (int i = 0; i < _bomb->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_bomb->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_bomb->removeBomb(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}

void player::removeBomb(int index)
{
	//폭탄클래스야 니가 총알 삭제해~ 내가 인덱스만 넘겨줄께
	_bomb->removeBomb(index);
}
