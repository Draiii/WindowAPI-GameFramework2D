#include "stdafx.h"
#include "dungeonSecen.h"
#include "myPlayer.h"
#include "monster_1.h"
#include "myAstar.h"

HRESULT dungeonSecen::init()
{
	//�ɸ��� ����
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

	//Ÿ��
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
	//���콺 �̹���
	mouseOver = IMAGEMANAGER->addFrameImage("mouseOver", "image/mouse/crosshair.bmp", 108, 54, 2, 1, true, RGB(255, 0, 255));
	mouseOver->setFrameX(0);


	//���� �ʱ�ȭ
	//��
	dungeon1MoveX = -1092;
	dungeon1MoveY = -1300;
	mapMoveDirection = HOLD;

	//dungeon1Imager = IMAGEMANAGER->addImage("stage1", "image/map/dungeon_1.bmp", 3000, 2576);
	//��
	dungeon1Imager = IMAGEMANAGER->addImage("stage1", "image/map/dungeon_1_1.bmp", dungeon1MoveX, dungeon1MoveY, 3016, 2600);
	//�ȼ�	
	//dungeon1PixelImager = IMAGEMANAGER->addImage("stagePixel1", "image/map/dungeon_1_1_pixel.bmp", 3016, 2600);
	dungeon1PixelImager = IMAGEMANAGER->addImage("stagePixel1", "image/map/dungeon_1_1_pixel.bmp", dungeon1MoveX, dungeon1MoveY, 3016, 2600);
	//�Ȱ�
	dungeon1FogImager = IMAGEMANAGER->addImage("fog", "image/map/dungeon_1_1_fog.bmp", dungeon1MoveX + (-TILE_WIDTH * 7), dungeon1MoveY, 3848, 2600, true, RGB(255, 0, 255));
	//�Ȱ� ����
	dungeon1FogAlphaImager = IMAGEMANAGER->addImage("fogAlpha", "image/map/dungeon_1_1_fog.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	float tempY = 0;
	float tempX = 0;
	//ī�޶� ����ŷ
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
	//���� ��ġ üũ�ϴ� ��
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






	//----------------------// �� + ī�޶� ���� ���� //----------------------//
	dungeon1MoveX;
	dungeon1MoveY;
	//----------------------// �� + ī�޶� ���� ���� //----------------------//

	

	//----------------------// ��� //----------------------//
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//���ο� ���� ��Ʈ��ġ ����
			//myAstarCss->getNode(x, y);
		 myAstarCss->setNode(x, y, dungeon1MoveX, dungeon1MoveY);
		}
	}
	myAstarCss->update();

	
	
	//A-star �����ϱ�
	//���콺 �̵�
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
		//����, ���� ��尡 �̹� ���õǾ��ִٸ� �׳� ������
		//if (startNode && endNode) return; //���� ������ ������Ʈ ����

		for (int y = 0; y < NODE_MAX_Y; y++)
		{
			for (int x = 0; x < NODE_MAX_X; x++)
			{
				//��Ʈ �浹ó��
				if (PtInRect(&myAstarCss->getNode(x,y)->rc, _ptMouse))
				{						
					//ȭ�� ���� Ÿ�ϸ� üũ�Ѵ�
					if (x > playerInitIdX - 14 && x < playerInitIdX + 13)
					{
						if (y > playerInitIdY - 7 && y < playerInitIdY + 7)
						{
							//���� Ÿ���� ���̶�� ��Ƽ��
							if (myAstarCss->getNode(x, y)->node_State == NODE_WALL) continue;
							//����Ÿ���� �̵��� �� �ִ� Ÿ���̸� ��ã�⸦ �����Ѵ�
							myAstarCss->pathFinding();
						}
					}
				}
			}
		}
	}

	
	//----------------------// ��� //----------------------//
	//���� �浹ó��
	for (int i = 0; i < myMonsterCss->getZombieMob().size(); i++)
	{
		//����
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[3], &myMonsterCss->getZombieMob(), i))
		{
			left = true;
		}
		//���� ��
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[0], &myMonsterCss->getZombieMob(), i))
		{
			leftTop = true;
		}
		//��
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[1], &myMonsterCss->getZombieMob(), i))
		{
			top = true;
		}
		//��������
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[2], &myMonsterCss->getZombieMob(), i))
		{
			rightTop = true;
		}
		//������
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[5], &myMonsterCss->getZombieMob(), i))
		{
			right = true;
		}
		//������ �Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[8], &myMonsterCss->getZombieMob(), i))
		{
			rightBottom = true;
		}
		//�Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[7], &myMonsterCss->getZombieMob(), i))
		{
			bottom = true;
		}
		//���� �Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[6], &myMonsterCss->getZombieMob(), i))
		{
			leftBottom = true;
		}
	}
	//���� �浹ó��
	for (int i = 0; i < myMonsterCss->getVampMob().size(); i++)
	{
		//����
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[3], &myMonsterCss->getVampMob(), i))
		{
			left = true;
		}
		//���� ��
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[0], &myMonsterCss->getVampMob(), i))
		{
			leftTop = true;
		}
		//��
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[1], &myMonsterCss->getVampMob(), i))
		{
			top = true;
		}
		//��������
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[2], &myMonsterCss->getVampMob(), i))
		{
			rightTop = true;
		}
		//������
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[5], &myMonsterCss->getVampMob(), i))
		{
			right = true;
		}
		//������ �Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[8], &myMonsterCss->getVampMob(), i))
		{
			rightBottom = true;
		}
		//�Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[7], &myMonsterCss->getVampMob(), i))
		{
			bottom = true;
		}
		//���� �Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[6], &myMonsterCss->getVampMob(), i))
		{
			leftBottom = true;
		}
	}

	//����_2 �浹ó��
	for (int i = 0; i < myMonsterCss->getVamp_2Mob().size(); i++)
	{
		//����
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[3], &myMonsterCss->getVamp_2Mob(), i))
		{
			left = true;
		}
		//���� ��
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[0], &myMonsterCss->getVamp_2Mob(), i))
		{
			leftTop = true;
		}
		//��
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[1], &myMonsterCss->getVamp_2Mob(), i))
		{
			top = true;
		}
		//��������
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[2], &myMonsterCss->getVamp_2Mob(), i))
		{
			rightTop = true;
		}
		//������
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[5], &myMonsterCss->getVamp_2Mob(), i))
		{
			right = true;
		}
		//������ �Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[9], &myMonsterCss->getVamp_2Mob(), i))
		{
			rightBottom = true;
		}
		//�Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[8], &myMonsterCss->getVamp_2Mob(), i))
		{
			bottom = true;
		}
		//���� �Ʒ�
		if (myMonsterCss->attackMonster(myPlayerCss->getMyPlayer().attackRc[6], &myMonsterCss->getVamp_2Mob(), i))
		{
			leftBottom = true;
		}
	}

	//�÷��̾ ���� ����
	
	//Ű �����̱�
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

	
	//ĳ���� Ÿ�� �����̴� �Լ���
	//tile = 52 size / 

	if (this->CanMoveMap(mapMoveDirection))
	{
		//�̵�
		if (mapMoveDirection == MOVE_LEFT)
		{
			move += MOVE_SPEED;
			dungeon1MoveX += MOVE_SPEED;
			//�̵� �Ϸ� Ȧ��
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
			//�̵� �Ϸ� Ȧ��
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
			//�̵� �Ϸ� Ȧ��
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
			//�̵� �Ϸ� Ȧ��
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
			//�̵� �Ϸ� Ȧ��
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
			//�̵� �Ϸ� Ȧ��
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
			//�̵� �Ϸ� Ȧ��
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
			//�̵� �Ϸ� Ȧ��
			if (move >= TILE_WIDTH)
			{
				left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
				move = 0;
				myAstarCss->setPlayerIdx(-1, 1);
				mapMoveDirection = HOLD;
			}
		}

		//����
		else if (mapMoveDirection == ATTACK_LEFT)
		{			
			//�÷��̾� �����Ҷ� ���� �̹��� ��ġ�� �����Ѵ� ( ĳ���� ���� )
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
			//�÷��̾� �����Ҷ� ���� �̹��� ��ġ�� �����Ѵ� ( ĳ���� ���� )
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
			//�÷��̾� �����Ҷ� ���� �̹��� ��ġ�� �����Ѵ� ( ĳ���� ���� )
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
			//�÷��̾� �����Ҷ� ���� �̹��� ��ġ�� �����Ѵ� ( ĳ���� ���� )
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
			//�÷��̾� �����Ҷ� ���� �̹��� ��ġ�� �����Ѵ� ( ĳ���� ���� )
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
			//�÷��̾� �����Ҷ� ���� �̹��� ��ġ�� �����Ѵ� ( ĳ���� ���� )
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
			//�÷��̾� �����Ҷ� ���� �̹��� ��ġ�� �����Ѵ� ( ĳ���� ���� )
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
			//�÷��̾� �����Ҷ� ���� �̹��� ��ġ�� �����Ѵ� ( ĳ���� ���� )
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
	//��
	//dungeon1Imager->render(getMemDC(), -1092, -1276);
	//�� 1_1
	dungeon1Imager->render(getMemDC(), dungeon1MoveX, dungeon1MoveY);
	if (KEYMANAGER->isToggleKey('M'))
	{
		//�� 1_1  �ȼ��浹 �� 
		dungeon1PixelImager->render(getMemDC(), dungeon1MoveX, dungeon1MoveY);
	}
	if (KEYMANAGER->isToggleKey('N'))
	{
		for (int i = 0; i < 5; i++)
		{
			//������ ��Ʈ
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
	// ---------------------------------------------------- // ���� ����// ---------------------------------------------------- //
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

	// ---------------------------------------------------- // �� ����// ---------------------------------------------------- //
	
	//myMonsterCss->zombieMonRender(&myMonsterCss->getZombieMob()[1], dungeon1MoveX, dungeon1MoveY);
	//1. ��������
	//������ų ��Ʈ�� ���� (ȭ�� ũ�⿵��)
	RECT tempRc = RectMake(dungeon1MoveX, dungeon1MoveY, 3016, 2600);
	//�Ȱ� ���� ����
	dungeon1FogAlphaImager->alphaRender(getMemDC(), 200);
	//�Ȱ� ����
	dungeon1FogImager->render(getMemDC(), dungeon1MoveX, dungeon1MoveY);
	//����
	//dungeon1FogImager->loopRender(getMemDC(), &tempRc, loofX, loofY);

		// ---------------------------------------------------- // ���콺 ���� ���� // ---------------------------------------------------- //
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//��Ʈ �浹ó��
			if (PtInRect(&myAstarCss->getNode(x, y)->rc, _ptMouse))
			{
				//ȭ�� ���� Ÿ�ϸ� üũ�Ѵ�

				if (myAstarCss->getNode(x, y)->node_State == NODE_WALL) mouseOver->setFrameX(1);
				else if (myAstarCss->getNode(x, y)->node_State == NODE_START) mouseOver->setFrameX(1);
				else mouseOver->setFrameX(0);
				mouseOver->frameRender(getMemDC(), myAstarCss->getNode(x, y)->rc.left - 2, myAstarCss->getNode(x, y)->rc.top - 2);
			}
		}
	}

	// ---------------------------------------------------- // �÷��̾� ����// ---------------------------------------------------- //

	//�÷��̾� ����  (�ɸ���)
	//Rectangle(getMemDC(), myPlayerCss->getMyPlayer().rc);
	//myPlayerCss->playerImageRender(myPlayerCss->getMyPlayer().rc);
	
	//�÷��̾�� �������� �ҷ��´� (�ɸ�/����â ���)
	myPlayerCss->playerImageRender(myPlayerCss->getMyPlayer());
	//���� ��� ��ġ ����
	for (int i = 0; i < 9; i++)
	{
		myPlayerCss->playerAttackImg(i);
	}



	 

	// ---------------------------------------------------- // ������Ʈ�� ����// ---------------------------------------------------- //

	



	if (KEYMANAGER->isToggleKey('M'))
	{
		//Ÿ�� �׸���
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
	
	//�ɸ��� ���� ��Ʈ �� �Ȱ� �浹 �Լ�
	this->rangeRcCheck();

	//�׽�Ʈ �κ�
	//------------------------------------------------------------------------------------------//


	if (left)
	{
		TextOut(getMemDC(), 560, 270, "���ʿ� ���Ͱ� �ֽ��ϴ�.", strlen("���ʿ� ���Ͱ� �ֽ��ϴ�"));
	}
	if (right)
	{
		TextOut(getMemDC(), 560, 270, "�����ʿ� ���Ͱ� �ֽ��ϴ�", strlen("�����ʿ� ���Ͱ� �ֽ��ϴ�"));
	}	
	if (top)
	{
		TextOut(getMemDC(), 560, 270, "���� ���Ͱ� �ֽ��ϴ�", strlen("���� ���Ͱ� �ֽ��ϴ�"));
	}
	if (bottom)
	{
		TextOut(getMemDC(), 560, 270, "�Ʒ��� ���Ͱ� �ֽ��ϴ�", strlen("�Ʒ��� ���Ͱ� �ֽ��ϴ�"));
	}

	int centerX = PLAYER_INIT_X + (TILE_WIDTH / 2) - dungeon1MoveX;
	int centerY = PLAYER_INIT_Y + (TILE_HEIGHT / 2) - dungeon1MoveY;
	COLORREF color = GetPixel(dungeon1PixelImager->getMemDC(), centerX, centerY + TILE_HEIGHT);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);





	//�׽�Ʈ
	char str[256];
	sprintf(str, "���� : %d,%d,%d ���� : %f", r,g,b, move);
	TextOut(getMemDC(), 20, 50, str, strlen(str));
	//char str2[256];
	//sprintf(str2, "statNode->Rc.left:%d", myAstarCss->getMyStartNode()->rc.left);
	//TextOut(getMemDC(), 20, 70, str2, strlen(str2));
	//char str3[256];
	//sprintf(str3, "statNode->Rc.top:%d", myAstarCss->getMyStartNode()->rc.top);
	//TextOut(getMemDC(), 20, 90, str3, strlen(str3));
	//------------------------------------------------------------------------------------------//
}


//�ȼ��浹üũ
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
			// �浹�ϸ� Ȧ���ϰ� �޽�
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
		// �浹�ϸ� Ȧ���ϰ� �޽�
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
		// �浹�ϸ� Ȧ���ϰ� �޽�
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
		// �浹�ϸ� Ȧ���ϰ� �޽�
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
		// �浹�ϸ� Ȧ���ϰ� �޽�
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
		// �浹�ϸ� Ȧ���ϰ� �޽�
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
		// �浹�ϸ� Ȧ���ϰ� �޽�
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
		// �浹�ϸ� Ȧ���ϰ� �޽�
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
//���� �̵�
void dungeonSecen::moveToLeft()
{
	//���� �浹 ��������
	if (!left)
	{	
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_LEFT;

		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
		//dungeon1MoveX += TILE_WIDTH;

	}
	else
	{	//ĳ���� ����
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		//�������� ����
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_LEFT;
	}
}
//������ �̵�
void dungeonSecen::moveToLeftTop()
{
	//���� �浹 ��������
	if (!leftTop)
	{		
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_LEFT_TOP;

		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
		//dungeon1MoveX += TILE_WIDTH;

	}
	else
	{	//ĳ���� ����
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		//�������� ����
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_LEFT_TOP;
	}
}
//�� �̵�
void dungeonSecen::moveToTop()
{
	//���� �浹 ��������
	if (!top)
	{		
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_TOP;
		//dungeon1MoveY += TILE_HEIGHT;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
	}
	else
	{
		//�������� ����
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_TOP;
	}
}
//�������� �̵�
void dungeonSecen::moveToRightTop()
{
	//���� �浹 ��������
	if (!rightTop)
	{
		//���� �浹 ��������
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_RIGHT_TOP;
		//dungeon1MoveX -= TILE_WIDTH;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;

	}
	else
	{
		//ĳ���� ����
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		//�������� ����
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_RIGHT_TOP;
	}
}
//������ �̵�
void dungeonSecen::moveToRight()
{
	//���� �浹 ��������
	if (!right)
	{
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_RIGHT;
		//dungeon1MoveX -= TILE_WIDTH;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;

	}
	else
	{
		//ĳ���� ����
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		//�������� ����
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_RIGHT;
	}
}
//������ �Ʒ� �̵�
void dungeonSecen::moveToRightBottom()
{
	//���� �浹 ��������
	if (!rightBottom)
	{
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		if (mapMoveDirection == HOLD) mapMoveDirection = MOVE_RIGHT_BOTTOM;
		//dungeon1MoveX -= TILE_WIDTH;
		left = leftTop = top = rightTop = right = rightBottom = bottom = leftBottom = false;
	}
	else
	{
		//ĳ���� ����
		myPlayerCss->setPlayerDirection(PLAYER_RIGTH);
		//�������� ����
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_RIGHT_BOTTOM;
	}
}
//�Ʒ��̵�
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
		//�������� ����
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_BOTTOM;
	}
}
//���ʾƷ� �̵�
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
	{	//ĳ���� ����
		myPlayerCss->setPlayerDirection(PLAYER_LEFT);
		//�������� ����
		isAttackToMonster = true;
		if (mapMoveDirection == HOLD) mapMoveDirection = ATTACK_LEFT_BOTTOM;
	}
}

//�浹üũ �Լ� ������
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
//�Ȱ� �浹
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
		//�� �����
		FillRect(dungeon1FogImager->getMemDC(), &eraseRc, brush);
		//�� ���� �����
		FillRect(dungeon1FogAlphaImager->getMemDC(), &rangeRc[i].rc, brush);
		//������ ��Ʈ
		//FrameRect(getMemDC(), rangeRc[i].rc, RGB(255,255,0));
		DeleteObject(brush);
	}
}

