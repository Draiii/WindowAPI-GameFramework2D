#include "stdafx.h"
#include "dungeonSecen.h"
#include "myPlayer.h"
#include "monster_1.h"
#include "myAstar.h"

HRESULT dungeonSecen::init()
{
	//케릭터 범위
	for (int i = 0; i < 5; i++)
	{
		int width;
		int height;
		rangeRc.push_back({});


		switch (i)
		{
		case 0:
		{
			width = TILE_WIDTH * 3;
			height = TILE_WIDTH * 11;
			break;
		}
		case 1:
		{
			width = TILE_WIDTH * 5;
			height = TILE_WIDTH * 9;
			break;
		}
		case 2:
		{
			width = TILE_WIDTH * 7;
			height = TILE_WIDTH * 7;
			break;
		}
		case 3:
		{
			width = TILE_WIDTH * 9;
			height = TILE_WIDTH * 5;
			break;
		}
		case 4:
		{
			width = TILE_WIDTH * 11;
			height = TILE_WIDTH * 3;
			break;
		}
		default:
			break;
		}

		rangeRc[i].x = (TILE_WIDTH * 12) - (i * TILE_WIDTH);
		rangeRc[i].y = TILE_HEIGHT + (i * TILE_HEIGHT);
		rangeRc[i].rc = RectMake(rangeRc[i].x, rangeRc[i].y, width, height);
	}

	//타일
	for (int y = 0; y < TILE_Y_EA; y++)
	{
		for (int x = 0; x < TILE_X_EA; x++)
		{
			char str[50];
			sprintf(str, "%d", (y + TILE_X_EA * x));
			mainTile[y][x].Img = IMAGEMANAGER->addImage(str, "image/map/fogtile_1.bmp", TILE_WIDTH, TILE_HEIGHT);
			mainTile[y][x].x = x * TILE_WIDTH;
			mainTile[y][x].y = y * TILE_HEIGHT;
			mainTile[y][x].rc = RectMake(mainTile[y][x].x, mainTile[y][x].y, TILE_WIDTH, TILE_HEIGHT);
		}
	}
	//마우스 이미지
	mouseOver = IMAGEMANAGER->addFrameImage("mouseOver", "image/mouse/crosshair.bmp", 108, 54, 2, 1, true, RGB(255, 0, 255));
	mouseOver->setFrameX(0);


	//포그 초기화
	//맵
	dungeon1MoveX = -1092;
	dungeon1MoveY = -1300;
	mapMoveDirection = HOLD;

	//dungeon1Imager = IMAGEMANAGER->addImage("stage1", "image/map/dungeon_1.bmp", 3000, 2576);
	//맵
	dungeon1Imager = IMAGEMANAGER->addImage("stage1", "image/map/dungeon_1_1.bmp", dungeon1MoveX, dungeon1MoveY, 3016, 2600);
	//픽셀	
	//dungeon1PixelImager = IMAGEMANAGER->addImage("stagePixel1", "image/map/dungeon_1_1_pixel.bmp", 3016, 2600);
	dungeon1PixelImager = IMAGEMANAGER->addImage("stagePixel1", "image/map/dungeon_1_1_pixel.bmp", dungeon1MoveX, dungeon1MoveY, 3016, 2600);
	//안개
	dungeon1FogImager = IMAGEMANAGER->addImage("fog", "image/map/dungeon_1_1_fog.bmp", dungeon1MoveX + (-TILE_WIDTH * 7), dungeon1MoveY, 3848, 2600, true, RGB(255, 0, 255));
	//안개 알파
	dungeon1FogAlphaImager = IMAGEMANAGER->addImage("fogAlpha", "image/map/dungeon_1_1_fog.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	float tempY = 0;
	float tempX = 0;
	//카메라 쉐이킹
	shakeCamTime = GetTickCount();
	shaekCamX = 0;
	shaekCamY = 0;
	//dungeon1Imager->setX(-1092);
	//dungeon1Imager->setY(-1300);
	myPlayerCss = new myPlayer;
	myPlayerCss->init();
	myMonsterCss = new monster_1;
	myMonsterCss->init();
	playerInitIdX = 34;
	playerInitIdY = 31;
	myAstarCss = new myAstar;
	myAstarCss->init(playerInitIdX, playerInitIdY);
	myAstarCss->update();
	//몬스터 위치 체크하는 거
	left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
	left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
	AttackToMonster = 0;
	isAttackToMonster = false;
	move = 0;
	return S_OK;
}

void dungeonSecen::release()
{
	SAFE_DELETE(myPlayerCss);
	SAFE_DELETE(myMonsterCss);
	SAFE_DELETE(myAstarCss);
}

void dungeonSecen::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->loadScene("intro");
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->loadScene("dungeon");
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) SCENEMANAGER->loadScene("myAstar");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1)) this->moveToLeftBottom();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2)) this->moveToBottom();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3)) this->moveToRightBottom();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4)) this->moveToLeft();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6)) this->moveToRight();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7)) this->moveToLeftTop();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8)) this->moveToTop();
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9)) this->moveToRightTop();






	//----------------------// 맵 + 카메라 통합 변수 //----------------------//
	dungeon1MoveX;
	dungeon1MoveY;
	//----------------------// 맵 + 카메라 통합 변수 //----------------------//

	

	//----------------------// 노드 //----------------------//
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//새로운 노드와 렉트위치 설정
			//myAstarCss->getNode(x, y);
		 myAstarCss->setNode(x, y, dungeon1MoveX, dungeon1MoveY);
		}
	}
	myAstarCss->update();

	
	
	//A-star 적용하기
	//마우스 이동
	if (myAstarCss->getMoveStart())
	{
		if (myAstarCss->getMyStartNode()->rc.left < myPlayerCss->getMyPlayer().rc.left && myAstarCss->getMyStartNode()->rc.top < myPlayerCss->getMyPlayer().rc.top) this->moveToLeftTop();
		else if (myAstarCss->getMyStartNode()->rc.left < myPlayerCss->getMyPlayer().rc.left && myAstarCss->getMyStartNode()->rc.top > myPlayerCss->getMyPlayer().rc.top) this->moveToLeftBottom();
		else if (myAstarCss->getMyStartNode()->rc.left > myPlayerCss->getMyPlayer().rc.left && myAstarCss->getMyStartNode()->rc.top > myPlayerCss->getMyPlayer().rc.top) this->moveToRightBottom();
		else if (myAstarCss->getMyStartNode()->rc.left > myPlayerCss->getMyPlayer().rc.left && myAstarCss->getMyStartNode()->rc.top < myPlayerCss->getMyPlayer().rc.top) this->moveToRightTop();

		else if (myAstarCss->getMyStartNode()->rc.left < myPlayerCss->getMyPlayer().rc.left) this->moveToLeft();
		else if (myAstarCss->getMyStartNode()->rc.left > myPlayerCss->getMyPlayer().rc.left) this->moveToRight();
		else if (myAstarCss->getMyStartNode()->rc.top < myPlayerCss->getMyPlayer().rc.top) this->moveToTop();
		else if (myAstarCss->getMyStartNode()->rc.top > myPlayerCss->getMyPlayer().rc.top) this->moveToBottom();
	}

	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//시작, 종료 노드가 이미 세팅되어있다면 그냥 나가자
		//if (startNode && endNode) return; //리턴 만나면 업데이트 나감

		for (int y = 0; y < NODE_MAX_Y; y++)
		{
			for (int x = 0; x < NODE_MAX_X; x++)
			{
				//렉트 충돌처리
				if (PtInRect(&myAstarCss->getNode(x,y)->rc, _ptMouse))
				{						
					//화면 내의 타일만 체크한다
					if (x > playerInitIdX - 14 && x < playerInitIdX + 13)
					{
						if (y > playerInitIdY - 7 && y < playerInitIdY + 7)
						{
							//선택 타일이 벽이라면 컨티뉴
							if (myAstarCss->getNode(x, y)->node_State == NODE_WALL) continue;
							//선택타일이 이동할 수 있는 타일이면 길찾기를 실행한다
							myAstarCss->pathFinding();
						}
					}
				}
			}
		}
	}

	
	//----------------------// 노드 //----------------------//
	//좀비 충돌처리
	for (int i = 0; i < myMonsterCss->getZombieMob().size(); i++)
	{
		//왼쪽
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[3], &myMonsterCss->getZombieMob(), i))
		{
			left = true;
		}
		//왼쪽 위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[0], &myMonsterCss->getZombieMob(), i))
		{
			leftTop = true;
		}
		//위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[1], &myMonsterCss->getZombieMob(), i))
		{
			top = true;
		}
		//오른쪽위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[2], &myMonsterCss->getZombieMob(), i))
		{
			rightTop = true;
		}
		//오른쪽
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[5], &myMonsterCss->getZombieMob(), i))
		{
			right = true;
		}
		//오른쪽 아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[8], &myMonsterCss->getZombieMob(), i))
		{
			rightBottom = true;
		}
		//아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[7], &myMonsterCss->getZombieMob(), i))
		{
			bottom = true;
		}
		//왼쪽 아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[6], &myMonsterCss->getZombieMob(), i))
		{
			leftBottom = true;
		}
	}
	//뱀프 충돌처리
	for (int i = 0; i < myMonsterCss->getVampMob().size(); i++)
	{
		//왼쪽
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[3], &myMonsterCss->getVampMob(), i))
		{
			left = true;
		}
		//왼쪽 위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[0], &myMonsterCss->getVampMob(), i))
		{
			leftTop = true;
		}
		//위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[1], &myMonsterCss->getVampMob(), i))
		{
			top = true;
		}
		//오른쪽위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[2], &myMonsterCss->getVampMob(), i))
		{
			rightTop = true;
		}
		//오른쪽
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[5], &myMonsterCss->getVampMob(), i))
		{
			right = true;
		}
		//오른쪽 아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[8], &myMonsterCss->getVampMob(), i))
		{
			rightBottom = true;
		}
		//아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[7], &myMonsterCss->getVampMob(), i))
		{
			bottom = true;
		}
		//왼쪽 아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[6], &myMonsterCss->getVampMob(), i))
		{
			leftBottom = true;
		}
	}

	//뱀프_2 충돌처리
	for (int i = 0; i < myMonsterCss->getVamp_2Mob().size(); i++)
	{
		//왼쪽
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[3], &myMonsterCss->getVamp_2Mob(), i))
		{
			left = true;
		}
		//왼쪽 위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[0], &myMonsterCss->getVamp_2Mob(), i))
		{
			leftTop = true;
		}
		//위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[1], &myMonsterCss->getVamp_2Mob(), i))
		{
			top = true;
		}
		//오른쪽위
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[2], &myMonsterCss->getVamp_2Mob(), i))
		{
			rightTop = true;
		}
		//오른쪽
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[5], &myMonsterCss->getVamp_2Mob(), i))
		{
			right = true;
		}
		//오른쪽 아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[9], &myMonsterCss->getVamp_2Mob(), i))
		{
			rightBottom = true;
		}
		//아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[8], &myMonsterCss->getVamp_2Mob(), i))
		{
			bottom = true;
		}
		//왼쪽 아래
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[6], &myMonsterCss->getVamp_2Mob(), i))
		{
			leftBottom = true;
		}
	}

	//플레이어가 몬스터 공격
	
	//키 움직이기
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		this->moveToLeft();		
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		this->moveToTop();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		this->moveToRight();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		this->moveToBottom();

	}

	
	//캐릭터 타일 움직이는 함수임
	//tile = 52 size / 

	if (this->CanMoveMap(mapMoveDirection))
	{
		//이동
		if (mapMoveDirection == MOVE_LEFT)
		{
			move += MOVE_SPEED;
			dungeon1MoveX += MOVE_SPEED;
			//이동 완료 홀드
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(-1, 0);
				mapMoveDirection = HOLD;
			}
		}

		else if (mapMoveDirection == MOVE_LEFT_TOP)
		{
			move += MOVE_SPEED;
			dungeon1MoveX += MOVE_SPEED;
			dungeon1MoveY += MOVE_SPEED;
			//이동 완료 홀드
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(-1, -1);
				mapMoveDirection = HOLD;
			}
		}
		

		else if (mapMoveDirection == MOVE_TOP)
		{
			move += MOVE_SPEED;
			dungeon1MoveY += MOVE_SPEED;
			//이동 완료 홀드
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(0, -1);
				mapMoveDirection = HOLD;
			}
		}

		else if (mapMoveDirection == MOVE_RIGHT_TOP)
		{
			move += MOVE_SPEED;
			dungeon1MoveX -= MOVE_SPEED;
			dungeon1MoveY += MOVE_SPEED;
			//이동 완료 홀드
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(1, -1);
				mapMoveDirection = HOLD;
			}
		}

		else if (mapMoveDirection == MOVE_RIGHT)
		{
			move += MOVE_SPEED;
			dungeon1MoveX -= MOVE_SPEED;
			//이동 완료 홀드
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(1, 0);
				mapMoveDirection = HOLD;
			}
		}


		else if (mapMoveDirection == MOVE_RIGHT_BOTTOM)
		{
			move += MOVE_SPEED;
			dungeon1MoveX -= MOVE_SPEED;
			dungeon1MoveY -= MOVE_SPEED;
			//이동 완료 홀드
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(1, 1);
				mapMoveDirection = HOLD;
			}
		}

		else if (mapMoveDirection == MOVE_BOTTOM)
		{
			move += MOVE_SPEED;
			dungeon1MoveY -= MOVE_SPEED;
			//이동 완료 홀드
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(0, 1);
				mapMoveDirection = HOLD;
			}
		}

		else if (mapMoveDirection == MOVE_LEFT_BOTTOM)
		{
			move += MOVE_SPEED;
			dungeon1MoveX += MOVE_SPEED;
			dungeon1MoveY -= MOVE_SPEED;
			//이동 완료 홀드
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(-1, 1);
				mapMoveDirection = HOLD;
			}
		}

		//공격
		else if (mapMoveDirection == ATTACK_LEFT)
		{			
			//플레이어 공격할때 공격 이미지 위치를 지정한다 ( 캐릭터 범위 )
			myPlayerCss->setIsPlayerAttack(3);
			if (isAttackToMonster)
			{
				AttackToMonster += ATTACK_SPEED;
				dungeon1MoveX += ATTACK_SPEED;
			}		
			if (AttackToMonster >= ATTACK_SPEED * 2)
			{
				isAttackToMonster = false;
			}
				
			if (!isAttackToMonster)
			{
				AttackToMonster -= ATTACK_SPEED / 4;
				dungeon1MoveX -= ATTACK_SPEED / 4;
				if (AttackToMonster <= 0)
				{
					AttackToMonster = 0;
					mapMoveDirection = HOLD;
					left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				}
			}
		}		

		else if (mapMoveDirection == ATTACK_LEFT_TOP)
		{
			//플레이어 공격할때 공격 이미지 위치를 지정한다 ( 캐릭터 범위 )
			myPlayerCss->setIsPlayerAttack(0);
			if (isAttackToMonster)
			{
				AttackToMonster += ATTACK_SPEED;
				dungeon1MoveX += ATTACK_SPEED;
				dungeon1MoveY += ATTACK_SPEED;
			}
			if (AttackToMonster >= ATTACK_SPEED * 2)
			{
				isAttackToMonster = false;
			}

			if (!isAttackToMonster)
			{
				AttackToMonster -= ATTACK_SPEED / 4;
				dungeon1MoveX -= ATTACK_SPEED / 4;
				dungeon1MoveY -= ATTACK_SPEED / 4;
				if (AttackToMonster <= 0)
				{
					AttackToMonster = 0;
					mapMoveDirection = HOLD;
					left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				}
			}
		}

		else if (mapMoveDirection == ATTACK_TOP)
		{
			//플레이어 공격할때 공격 이미지 위치를 지정한다 ( 캐릭터 범위 )
			myPlayerCss->setIsPlayerAttack(1);
			if (isAttackToMonster)
			{
				AttackToMonster += ATTACK_SPEED;
				dungeon1MoveY += ATTACK_SPEED;
			}
			if (AttackToMonster >= ATTACK_SPEED * 2)
			{
				isAttackToMonster = false;
			}

			if (!isAttackToMonster)
			{
				AttackToMonster -= ATTACK_SPEED / 4;
				dungeon1MoveY -= ATTACK_SPEED / 4;
				if (AttackToMonster <= 0)
				{
					AttackToMonster = 0;
					mapMoveDirection = HOLD;
					left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				}
			}
		}

		else if (mapMoveDirection == ATTACK_RIGHT_TOP)
		{
			//플레이어 공격할때 공격 이미지 위치를 지정한다 ( 캐릭터 범위 )
			myPlayerCss->setIsPlayerAttack(2);
			if (isAttackToMonster)
			{
				AttackToMonster += ATTACK_SPEED;
				dungeon1MoveX -= ATTACK_SPEED;
				dungeon1MoveY += ATTACK_SPEED;
			}
			if (AttackToMonster >= ATTACK_SPEED * 2)
			{
				isAttackToMonster = false;
			}

			if (!isAttackToMonster)
			{
				AttackToMonster -= ATTACK_SPEED / 4;
				dungeon1MoveX += ATTACK_SPEED / 4;
				dungeon1MoveY -= ATTACK_SPEED / 4;
				if (AttackToMonster <= 0)
				{
					AttackToMonster = 0;
					mapMoveDirection = HOLD;
					left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				}
			}
			}

		else if (mapMoveDirection == ATTACK_RIGHT)
		{
			//플레이어 공격할때 공격 이미지 위치를 지정한다 ( 캐릭터 범위 )
			myPlayerCss->setIsPlayerAttack(5);
			if (isAttackToMonster)
			{
				AttackToMonster += ATTACK_SPEED;
				dungeon1MoveX -= ATTACK_SPEED;
			}

			if (AttackToMonster >= ATTACK_SPEED * 2)
			{
				isAttackToMonster = false;
			}

			if (!isAttackToMonster)
			{
				AttackToMonster -= ATTACK_SPEED / 4;
				dungeon1MoveX += ATTACK_SPEED / 4;
				if (AttackToMonster <= 0)
				{
					AttackToMonster = 0;
					mapMoveDirection = HOLD;
					left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				}
			}
		}

		else if (mapMoveDirection == ATTACK_RIGHT_BOTTOM)
		{
			//플레이어 공격할때 공격 이미지 위치를 지정한다 ( 캐릭터 범위 )
			myPlayerCss->setIsPlayerAttack(8);
			if (isAttackToMonster)
			{
				AttackToMonster += ATTACK_SPEED;
				dungeon1MoveX -= ATTACK_SPEED;
				dungeon1MoveY -= ATTACK_SPEED;
			}
			if (AttackToMonster >= ATTACK_SPEED * 2)
			{
				isAttackToMonster = false;
			}

			if (!isAttackToMonster)
			{
				AttackToMonster -= ATTACK_SPEED / 4;
				dungeon1MoveX += ATTACK_SPEED / 4;
				dungeon1MoveY += ATTACK_SPEED / 4;
				if (AttackToMonster <= 0)
				{
					AttackToMonster = 0;
					mapMoveDirection = HOLD;
					left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				}
			}
		}

		else if (mapMoveDirection == ATTACK_BOTTOM)
		{
			//플레이어 공격할때 공격 이미지 위치를 지정한다 ( 캐릭터 범위 )
			myPlayerCss->setIsPlayerAttack(7);
			if (isAttackToMonster)
			{
				AttackToMonster += ATTACK_SPEED;
				dungeon1MoveY -= ATTACK_SPEED;
			}

			if (AttackToMonster >= ATTACK_SPEED * 2)
			{
				isAttackToMonster = false;
			}

			if (!isAttackToMonster)
			{
				AttackToMonster -= ATTACK_SPEED / 4;
				dungeon1MoveY += ATTACK_SPEED / 4;
				if (AttackToMonster <= 0)
				{
					AttackToMonster = 0;
					mapMoveDirection = HOLD;
					left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				}
			}			
		}

		else if (mapMoveDirection == ATTACK_LEFT_BOTTOM)
		{
			//플레이어 공격할때 공격 이미지 위치를 지정한다 ( 캐릭터 범위 )
			myPlayerCss->setIsPlayerAttack(6);
			if (isAttackToMonster)
			{
				AttackToMonster += ATTACK_SPEED;
				dungeon1MoveX += ATTACK_SPEED;
				dungeon1MoveY -= ATTACK_SPEED;
			}

			if (AttackToMonster >= ATTACK_SPEED * 2)
			{
				isAttackToMonster = false;
			}

			if (!isAttackToMonster)
			{
				AttackToMonster -= ATTACK_SPEED / 4;
				dungeon1MoveX -= ATTACK_SPEED / 4;
				dungeon1MoveY += ATTACK_SPEED / 4;
				if (AttackToMonster <= 0)
				{
					AttackToMonster = 0;
					mapMoveDirection = HOLD;
					left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				}
			}
		}
	}


	
	myPlayerCss->update();

}

void dungeonSecen::render()
{
	//맵
	//dungeon1Imager->render(getMemDC(), -1092, -1276);
	//맵 1_1
	dungeon1Imager->render(getMemDC(), dungeon1MoveX, dungeon1MoveY);
	if (KEYMANAGER->isToggleKey('M'))
	{
		//맵 1_1  픽셀충돌 맵 
		dungeon1PixelImager->render(getMemDC(), dungeon1MoveX, dungeon1MoveY);
	}
	if (KEYMANAGER->isToggleKey('N'))
	{
		for (int i = 0; i < 5; i++)
		{
			//프레임 렉트
			FrameRect(getMemDC(), rangeRc[i].rc, RGB(255,255,0));
		}
		for (int i = 0; i < 9; i++)
		{
			FrameRect(getMemDC(), myPlayerCss->getMyPlayer().attackRc[i], RGB(255, 0, 0));
		}
	}

	if (KEYMANAGER->isToggleKey('B'))
	{
		myAstarCss->render();
	}
	// ---------------------------------------------------- // 몬스터 렌더// ---------------------------------------------------- //
	for (int i = 0; i < ZOMBIE_EA; i++)
	{
		myMonsterCss->zombieMonRender(i, dungeon1MoveX, dungeon1MoveY);
	}

	for (int i = 0; i < VAMP_EA; i++)
	{
		myMonsterCss->vampMonRender(i, dungeon1MoveX, dungeon1MoveY);
		myMonsterCss->vamp_2MonRender(i, dungeon1MoveX, dungeon1MoveY);
	}
	//myMonsterCss->zombieMonRender(myMonsterCss->getZombieMob()[0], dungeon1MoveX, dungeon1MoveY);

	// ---------------------------------------------------- // 맵 랜더// ---------------------------------------------------- //
	
	//myMonsterCss->zombieMonRender(&myMonsterCss->getZombieMob()[1], dungeon1MoveX, dungeon1MoveY);
	//1. 루프렌더
	//루프시킬 렉트의 영역 (화면 크기영역)
	RECT tempRc = RectMake(dungeon1MoveX, dungeon1MoveY, 3016, 2600);
	//안개 알파 렌더
	dungeon1FogAlphaImager->alphaRender(getMemDC(), 200);
	//안개 렌더
	dungeon1FogImager->render(getMemDC(), dungeon1MoveX, dungeon1MoveY);
	//루프
	//dungeon1FogImager->loopRender(getMemDC(), &tempRc, loofX, loofY);

		// ---------------------------------------------------- // 마우스 오버 렌더 // ---------------------------------------------------- //
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//렉트 충돌처리
			if (PtInRect(&myAstarCss->getNode(x, y)->rc, _ptMouse))
			{
				//화면 내의 타일만 체크한다

				if (myAstarCss->getNode(x, y)->node_State == NODE_WALL) mouseOver->setFrameX(1);
				else if (myAstarCss->getNode(x, y)->node_State == NODE_START) mouseOver->setFrameX(1);
				else mouseOver->setFrameX(0);
				mouseOver->frameRender(getMemDC(), myAstarCss->getNode(x, y)->rc.left - 2, myAstarCss->getNode(x, y)->rc.top - 2);
			}
		}
	}

	// ---------------------------------------------------- // 플레이어 렌더// ---------------------------------------------------- //

	//플레이어 렌더  (케릭터)
	//Rectangle(getMemDC(), myPlayerCss->getMyPlayer().rc);
	//myPlayerCss->playerImageRender(myPlayerCss->getMyPlayer().rc);
	
	//플레이어는 통합으러 불러온다 (케릭/스탯창 등등)
	myPlayerCss->playerImageRender(myPlayerCss->getMyPlayer());
	//공격 모션 위치 설정
	for (int i = 0; i < 9; i++)
	{
		myPlayerCss->playerAttackImg(i);
	}



	 

	// ---------------------------------------------------- // 오브젝트들 렌더// ---------------------------------------------------- //

	



	if (KEYMANAGER->isToggleKey('M'))
	{
		//타일 그리드
		HPEN nPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		HPEN oPen = (HPEN)SelectObject(getMemDC(), nPen);
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 27; x++)
			{
				LineMake(getMemDC(), x * TILE_WIDTH, 0, x * TILE_WIDTH, WINSIZEY);
				LineMake(getMemDC(), 0, y * TILE_HEIGHT, WINSIZEX, y * TILE_HEIGHT);
			}
		}
		SelectObject(getMemDC(), oPen);
		DeleteObject(nPen);
	}
	
	//케릭터 범위 렉트 및 안개 충돌 함수
	this->rangeRcCheck();

	//테스트 부분
	//------------------------------------------------------------------------------------------//


	if (left)
	{
		TextOut(getMemDC(), 560, 270, "왼쪽에 몬스터가 있습니다.", strlen("왼쪽에 몬스터가 있습니다"));
	}
	if (right)
	{
		TextOut(getMemDC(), 560, 270, "오른쪽에 몬스터가 있습니다", strlen("오른쪽에 몬스터가 있습니다"));
	}	
	if (top)
	{
		TextOut(getMemDC(), 560, 270, "위에 몬스터가 있습니다", strlen("위에 몬스터가 있습니다"));
	}
	if (bottom)
	{
		TextOut(getMemDC(), 560, 270, "아래에 몬스터가 있습니다", strlen("아래에 몬스터가 있습니다"));
	}

	int centerX = PLAYER_INIT_X + (TILE_WIDTH / 2) - dungeon1MoveX;
	int centerY = PLAYER_INIT_Y + (TILE_HEIGHT / 2) - dungeon1MoveY;
	COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX, centerY + TILE_HEIGHT);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);





	//테스트
	char str[256];
	sprintf(str, "바텀 : %d,%d,%d 무브 : %f", r,g,b, move);
	TextOut(getMemDC(), 20, 50, str, strlen(str));
	//char str2[256];
	//sprintf(str2, "statNode->Rc.left:%d", myAstarCss->getMyStartNode()->rc.left);
	//TextOut(getMemDC(), 20, 70, str2, strlen(str2));
	//char str3[256];
	//sprintf(str3, "statNode->Rc.top:%d", myAstarCss->getMyStartNode()->rc.top);
	//TextOut(getMemDC(), 20, 90, str3, strlen(str3));
	//------------------------------------------------------------------------------------------//
}


//픽셀충돌체크
bool dungeonSecen::CanMoveMap(MAPMOVEDIRECTION _direct)
{
	int centerX = PLAYER_INIT_X + (TILE_WIDTH / 2) - dungeon1MoveX;
	int centerY = PLAYER_INIT_Y + (TILE_HEIGHT / 2) - dungeon1MoveY;
	switch (_direct)
	{		
		
	case MOVE_LEFT :
		{
			COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX - TILE_WIDTH + 25, centerY);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			bool checkPixel = (r == 255 && g == 0, b == 255);
			// 충돌하면 홀드하고 펄스
			if (checkPixel)
			{
				mapMoveDirection = HOLD;
				return false;
			}			
			break;
		}

	case MOVE_LEFT_TOP:
	{
		COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX - TILE_WIDTH + 25, centerY - TILE_HEIGHT + 25);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		bool checkPixel = (r == 255 && g == 0, b == 255);
		// 충돌하면 홀드하고 펄스
		if (checkPixel)
		{
			mapMoveDirection = HOLD;
			return false;
		}
		break;
	}

	case MOVE_TOP:
	{
		COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX , centerY - TILE_HEIGHT + 25);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		bool checkPixel = (r == 255 && g == 0, b == 255);
		// 충돌하면 홀드하고 펄스
		if (checkPixel)
		{
			mapMoveDirection = HOLD;
			return false;
		}
		break;
	}

	case MOVE_RIGHT_TOP:
	{
		COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX + TILE_WIDTH - 25, centerY - TILE_HEIGHT + 25);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		bool checkPixel = (r == 255 && g == 0, b == 255);
		// 충돌하면 홀드하고 펄스
		if (checkPixel)
		{
			mapMoveDirection = HOLD;
			return false;
		}
		break;
	}

	case MOVE_RIGHT:
	{
		COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX + TILE_WIDTH - 25, centerY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		bool checkPixel = (r == 255 && g == 0, b == 255);
		// 충돌하면 홀드하고 펄스
		if (checkPixel)
		{
			mapMoveDirection = HOLD;
			return false;
		}
		break;
	}

	case MOVE_RIGHT_BOTTOM:
	{
		COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX + TILE_WIDTH - 25, centerY + TILE_HEIGHT - 25);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		bool checkPixel = (r == 255 && g == 0, b == 255);
		// 충돌하면 홀드하고 펄스
		if (checkPixel)
		{
			mapMoveDirection = HOLD;
			return false;
		}
		break;
	}
	case MOVE_BOTTOM:
	{
		COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX , centerY + TILE_HEIGHT - 25);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		bool checkPixel = (r == 255 && g == 0, b == 255);
		// 충돌하면 홀드하고 펄스
		if (checkPixel)
		{
			mapMoveDirection = HOLD;
			return false;
		}
		break;
	}
	case MOVE_LEFT_BOTTOM:
	{
		COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX - TILE_WIDTH + 25, centerY + TILE_HEIGHT - 25);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		bool checkPixel = (r == 255 && g == 0, b == 255);
		// 충돌하면 홀드하고 펄스
		if (checkPixel)
		{
			mapMoveDirection = HOLD;
			return false;
		}
		break;
	}
	}
	return true;	
}
//왼쪽 이동
void dungeonSecen::moveToLeft()
{
	//몬스터 충돌 안했을때
	if (!left)
	{	
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_LEFT;

		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
		//dungeon1MoveX += TILE_WIDTH;

	}
	else
	{	//캐릭터 방향
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		//공격으로 설정
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_LEFT;
	}
}
//왼쪽위 이동
void dungeonSecen::moveToLeftTop()
{
	//몬스터 충돌 안했을때
	if (!leftTop)
	{		
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_LEFT_TOP;

		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
		//dungeon1MoveX += TILE_WIDTH;

	}
	else
	{	//캐릭터 방향
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		//공격으로 설정
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_LEFT_TOP;
	}
}
//위 이동
void dungeonSecen::moveToTop()
{
	//몬스터 충돌 안했을때
	if (!top)
	{		
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_TOP;
		//dungeon1MoveY += TILE_HEIGHT;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
	}
	else
	{
		//공격으로 설정
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_TOP;
	}
}
//오른쪽위 이동
void dungeonSecen::moveToRightTop()
{
	//몬스터 충돌 안했을때
	if (!rightTop)
	{
		//몬스터 충돌 안했을때
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_RIGHT_TOP;
		//dungeon1MoveX -= TILE_WIDTH;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;

	}
	else
	{
		//캐릭터 방향
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		//공격으로 설정
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_RIGHT_TOP;
	}
}
//오른쪽 이동
void dungeonSecen::moveToRight()
{
	//몬스터 충돌 안했을때
	if (!right)
	{
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_RIGHT;
		//dungeon1MoveX -= TILE_WIDTH;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;

	}
	else
	{
		//캐릭터 방향
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		//공격으로 설정
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_RIGHT;
	}
}
//오른쪽 아래 이동
void dungeonSecen::moveToRightBottom()
{
	//몬스터 충돌 안했을때
	if (!rightBottom)
	{
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_RIGHT_BOTTOM;
		//dungeon1MoveX -= TILE_WIDTH;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
	}
	else
	{
		//캐릭터 방향
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		//공격으로 설정
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_RIGHT_BOTTOM;
	}
}
//아래이동
void dungeonSecen::moveToBottom()
{
	if (!bottom)
	{
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_BOTTOM;
		//dungeon1MoveY -= TILE_HEIGHT;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;

	}
	else
	{
		//공격으로 설정
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_BOTTOM;
	}
}
//왼쪽아래 이동
void dungeonSecen::moveToLeftBottom()
{
	if (!leftBottom)
	{
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_LEFT_BOTTOM;

		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
		//dungeon1MoveX += TILE_WIDTH;

	}
	else
	{	//캐릭터 방향
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		//공격으로 설정
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_LEFT_BOTTOM;
	}
}

//충돌체크 함수 만들자
//bool dungeonSecen::attackMonster(RECT _rc, vector<tagMonster>* _monster, int _index)
//{
//	RECT temp;
//
//	if (IntersectRect(&temp, &_rc, &_monster->at(_index).rc))
//	{
//		return true;
//	}
//	else return false;	
//}
//안개 충돌
void dungeonSecen::rangeRcCheck()
{
	for (int i = 0; i < 5; i++)
	{	
		RECT eraseRc = rangeRc[i].rc;
		eraseRc.left -= dungeon1MoveX;
		eraseRc.right -= dungeon1MoveX;
		eraseRc.top -= dungeon1MoveY;
		eraseRc.bottom -= dungeon1MoveY;
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oBrush;		
		SelectObject(dungeon1FogImager->getMemDC(), brush);
		//맵 지우기
		FillRect(dungeon1FogImager->getMemDC(), &eraseRc, brush);
		//맵 알파 지우기
		FillRect(dungeon1FogAlphaImager->getMemDC(), &rangeRc[i].rc, brush);
		//프레임 렉트
		//FrameRect(getMemDC(), rangeRc[i].rc, RGB(255,255,0));
		DeleteObject(brush);
	}
}

