#include "stdafx.h"
#include "myAstar.h"
#include "dungeonSecen.h"

HRESULT myAstar::init(int _x, int _y)
{
	//��ü��� �ʱ�ȭ
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//���ο� ���� ��Ʈ��ġ ����
			totalNode[x][y] = new MyNode(x, y); //�ε���
			totalNode[x][y]->x = -1092;
			totalNode[x][y]->y = -1300 ;
			totalNode[x][y]->rc = RectMake(totalNode[x][y]->x + (x * TILE_WIDTH), totalNode[x][y]->y + (y * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT);
		}
	}
	//34, 31
	playerIdX = _x;
	playerIdY = _y;
	IMAGEMANAGER->addImage("stagePixel1", "image/map/dungeon_1_1_pixel.bmp", 3016, 2600);


	//�� ��� �˻�
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("stagePixel1")->getMemDC(), x * TILE_WIDTH + (TILE_WIDTH / 2), y * TILE_HEIGHT + (TILE_HEIGHT / 2));
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			bool checkPixelWall = (r == 255 && g == 0 && b == 255);
			// �浹�ϸ� Ȧ���ϰ� �޽�
			if (checkPixelWall)
			{
				totalNode[x][y]->node_State = NODE_WALL;
			}
		}
	}
	//�ʱ�ȭ
	startNode = {};
	endNode = {};
	curNode = {};

	//ùŬ���� ¦���� �ǰ� �ϱ����� -1�� �ʱ�ȭ
	//�������� ¦���� �ǰ� �ϱ�����
	//��ã�����϶� 0
	count = -1;
	
	isFind = false;

	isMoveStart = false;
	MoveStartCount = 0;
	isMoveCount = false;
	moveCount = 0;
	isLastMove = false;
	lastMoveCount = 0;
	

	
	return S_OK;
}

HRESULT myAstar::init()
{
	//��ü��� �ʱ�ȭ
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//���ο� ���� ��Ʈ��ġ ����
			totalNode[x][y] = new MyNode(x, y); //�ε���
			totalNode[x][y]->x = -1092;
			totalNode[x][y]->y = -1300;
			totalNode[x][y]->rc = RectMake(totalNode[x][y]->x + (x * TILE_WIDTH), totalNode[x][y]->y + (y * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT);
		}
	}
	//34, 31
	playerIdX = 34;
	playerIdY = 31;
	IMAGEMANAGER->addImage("stagePixel1", "image/map/dungeon_1_1_pixel.bmp", 3016, 2600);


	//�� ��� �˻�
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("stagePixel1")->getMemDC(), x * TILE_WIDTH + (TILE_WIDTH / 2), y * TILE_HEIGHT + (TILE_HEIGHT / 2));
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			bool checkPixelWall = (r == 255 && g == 0 && b == 255);
			// �浹�ϸ� Ȧ���ϰ� �޽�
			if (checkPixelWall)
			{
				totalNode[x][y]->node_State = NODE_WALL;
			}
		}
	}
	//�ʱ�ȭ
	startNode = {};
	endNode = {};
	curNode = {};

	//ùŬ���� ¦���� �ǰ� �ϱ����� -1�� �ʱ�ȭ
	//�������� ¦���� �ǰ� �ϱ�����
	//��ã�����϶� 0
	count = -1;

	isFind = false;

	isMoveStart = false;
	MoveStartCount = 0;
	isMoveCount = false;
	moveCount = 0;
	isLastMove = false;
	lastMoveCount = 0;
	return S_OK;
}

void myAstar::release()
{
	//for (int y = 0; y < NODE_MAX_Y; y++)
	//{
	//	for (int x = 0; x < NODE_MAX_X; x++)
	//	{
	//		SAFE_DELETE(totalNode[x][y]);
	//	}
	//}
	vOpenList.clear();		//Ŭ����
	vCloseList.clear();		//Ŭ����
	vFinalList.clear();		//Ŭ����
	
}

void myAstar::update()
{
	
	///////////////////////////////////////////////////////////////
		//ĳ���� ��ġ
		startNode = totalNode[playerIdX][playerIdY];
		totalNode[playerIdX][playerIdY]->node_State = NODE_START;

	//////////////////////////////////////////////////////////////

	//����, ���� ����
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//����, ���� ��尡 �̹� ���õǾ��ִٸ� �׳� ������
		//if (startNode && endNode) return; //���� ������ ������Ʈ ����

		//��ã�� ���϶� ���� Ŭ���ϸ� ������ ��Ų��
		if (count == 0)
		{
			this->release();
			this->init(playerIdX, playerIdY);
		}

		else
		{
			for (int y = 0; y < NODE_MAX_Y; y++)
			{
				for (int x = 0; x < NODE_MAX_X; x++)
				{
					//��Ʈ �浹ó��
					if (PtInRect(&totalNode[x][y]->rc, _ptMouse))
					{
						if (totalNode[x][y]->node_State == NODE_WALL) continue;
						isMoveStart = true;
						totalNode[x][y]->node_State = NODE_END;
						endNode = totalNode[x][y];
						count += 1;
						this->pathFinding();
					}
				}
			}
		}
	}

	//------------------------------------------------// ĳ���� �̵� �Լ� //------------------------------------------------//

	if (isMoveStart)
	{
		//ĳ���� ���� 1ĭ�� ���̳� ����Ʈ�� ���⶧���� �ٷ� ������� �����ϰ�
		//ĳ���͸� �̵���Ų��
		if (vFinalList.size() == 0) isLastMove = true;

		//�׿ܿ��� ���̳γ�尡 �����ǰ� ��������� ���̳� ��带 ���� ĳ���͸� �̵�
		else
		{
			MoveStartCount++;
			for (int i = 0; i < vFinalList.size(); i++)
			{
				if (MoveStartCount > i * 15 && MoveStartCount < (i + 1) * 15)
				{
					startNode->rc = vFinalList[i]->rc;

					if (startNode->rc.left == vFinalList[vFinalList.size() - 1]->rc.left && startNode->rc.top == vFinalList[vFinalList.size() - 1]->rc.top)
					{
						isMoveCount = true;
					}
				}
			}
		}
	}
	if (isMoveCount) moveCount++;

	if (moveCount >= 15)
	{
		isLastMove = true;
	}

	if (isLastMove)
	{
		lastMoveCount++;
		startNode->rc = endNode->rc;
	}

	if (lastMoveCount > 20)
	{
		this->release();
		this->init(playerIdX, playerIdY);
	}

	//------------------------------------------------// ĳ���� �̵� �Լ� //------------------------------------------------//
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
			this->release();
		this->init(playerIdX, playerIdY);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->loadScene("intro");
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->loadScene("dungeon");
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) SCENEMANAGER->loadScene("myAstar");

	//�� ���� ( ���� ���� ��� �������� �������� ���ϰ� ���� ) 
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) && startNode && endNode)
	{

		for (int y = 0; y < NODE_MAX_Y; y++)
		{
			for (int x = 0; x < NODE_MAX_X; x++)
			{
				//��Ʈ �浹ó��
				if (PtInRect(&totalNode[x][y]->rc, _ptMouse))
				{
					//���۳��, ������� �������� ���ϰ� ����
					if (totalNode[x][y]->node_State == NODE_START) continue;
					if (totalNode[x][y]->node_State == NODE_END) continue;
					//totalNode[x][y]->node_State = NODE_WALL;
				}
			}
		}
	}
}


void myAstar::render()
{
	//��ü��� ����
	char str[128];
	char str2[128];


	if (isFind)
	{
		//moveTime = GetTickCount64();
		for (int i = 0; i < vFinalList.size(); i++)
		{			

			setNodeColor(vFinalList[i], RGB(200, 200, 0));
			sprintf(str, "[%d, %d]      %d��° ���", vFinalList[i]->idx, vFinalList[i]->idy, i + 1);
			TextOut(getMemDC(), vFinalList[i]->rc.left + 10, vFinalList[i]->rc.top + 30, str, strlen(str));
			sprintf(str, "F:%d, G:%d, H:%d", vFinalList[i]->F, vFinalList[i]->G, vFinalList[i]->H);
			TextOut(getMemDC(), vFinalList[i]->rc.left + 10, vFinalList[i]->rc.top + 50, str, strlen(str));

			


			//if (GetTickCount64() - moveTime >= 500)
			//{
			//	startNode->rc = vFinalList[i]->rc;
			//	if (i == vFinalList.size() - 1)
			//	{
			//		startNode->rc = endNode->rc;
			//		turn = 0;
			//		moveTime = GetTickCount64();
			//		isFind = false;
			//		break;
			//	}
			//}
		}
	}

	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			if (PtInRect(&totalNode[y][x]->rc, _ptMouse))
			{

			}
		}
	}
	

	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//���ο� ���� ��Ʈ��ġ ���� && �÷��̾� ����
			if (x > playerIdX - 14 && x < playerIdX + 13)
			{
				if (y > playerIdY - 7 && y < playerIdY + 7)
				{
					FrameRect(getMemDC(), totalNode[x][y]->rc, RGB(0, 0, 200));

					//������ �����ֱ�
					if (totalNode[x][y]->node_State == NODE_END)
					{						
						this->setNodeColor(endNode, RGB(0, 0, 255));
						TextOut(getMemDC(), endNode->rc.left + 10, endNode->rc.top + 20, "END", strlen("END"));
					}
					//���۳�� �����ֱ�
					if (totalNode[x][y]->node_State == NODE_START)
					{
						this->setNodeColor(startNode, RGB(255, 0, 0));
						TextOut(getMemDC(), startNode->rc.left + 10, startNode->rc.top + 20, "START", strlen("START"));
					}
					//����� �����ֱ�
					//if (totalNode[x][y]->node_State == NODE_WALL)
					//{
					//	this->setNodeColor(totalNode[x][y], RGB(100, 100, 0));
					//	TextOut(getMemDC(), totalNode[x][y]->rc.left + 100, totalNode[x][y]->rc.top + 10, "WALL", strlen("WALL"));
					//}
					if (totalNode[x][y]->node_State == NODE_WALL)
					{
						this->setNodeColor(totalNode[x][y], RGB(100, 100, 0));
						TextOut(getMemDC(), totalNode[x][y]->rc.left + 10, totalNode[x][y]->rc.top + 23, "��", strlen("��"));
					}
					//��ü ����� �ε��� �����ֱ�
					sprintf(str, "%d, %d", totalNode[x][y]->idx, totalNode[x][y]->idy);
					TextOut(getMemDC(), totalNode[x][y]->rc.left + 5, totalNode[x][y]->rc.top + 5, str, strlen(str));

				}
			}
		}
	}
	char stt[128];	
	sprintf(stt, "moveCount:%d", count);
	TextOut(getMemDC(), 20, 30, stt, strlen(stt));


}
//����� �˻�
void myAstar::CheckIsWall()
{
	//�� ��� �˻�
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("stagePixel1")->getMemDC(), x + (TILE_WIDTH / 2), y + (TILE_HEIGHT / 2));
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			bool checkPixelWall = (r == 255 && g == 0, b == 255);
			//�ȼ��浹�ϴ°��� ��
			if (checkPixelWall)
			{
				totalNode[x][y]->node_State = NODE_WALL;			
			}
		}
	}
}

//��� ��ä��� (���������� ��ĥ��)
void myAstar::setNodeColor(MyNode * node, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(getMemDC(), &node->rc, brush);
	DeleteObject(brush);
	FrameRect(getMemDC(), node->rc, RGB(0, 0, 0));
}


//*�߿�*//
//��ã�� �Լ�
void myAstar::pathFinding()
{
	//���۳�� �� ���� ��尡 �ִ� ��쿡�� ��ã��
	if (!startNode || !endNode) return;	//����������

	//��ã�� ����
	//�˻��� �Ϸ��� ������ ���¸���Ʈ�� ��Ƶΰ� F�� H �� �������� ���� ã�Ƽ� �׳��� ������� �����ϰ� ���¸���Ʈ���� ������� �����ϰ� ������� Ŭ�����Ʈ�� ��Ƶд�

	//1. ���۳�尡 �־�� ����� �����ϴ� ���۳�带 ���¸���Ʈ�� ����ش�
	vOpenList.push_back(startNode);

	//2. ���¸���Ʈ�� ��� �ִ� ���͸� �˻��ؼ� �����忡 �����ҋ����� ���ѷ���
	while (vOpenList.size() > 0) //��ŸƮ�븣�� ������ �̰��� ����
	{
		curNode = vOpenList[0];

		//���¸���Ʈ �� ���� F�� �۰ų� F�� ���ٸ�  H�� ���� �� ����븣�� �ϰ� �����带 ���¸���Ʈ���� Ŭ���� ����Ʈ�� �ű��
		//�񱳸� �Ϸ��� �ϸ� �ּ� ���۳�忡�� �ֺ��� Ž���� ���� ��ã�Ⱑ ���۵Ǵ� 1���� ��������
		for (int i = 1; i < vOpenList.size(); i++)
		{
			if (vOpenList[i]->F <= curNode->F && vOpenList[i]->H < curNode->H)
			{
				curNode = vOpenList[i];
			}
		}

		//Ŭ�����Ʈ�� �־��ش�
		for (int i = 0; i < vOpenList.size(); i++)
		{
			if (curNode == vOpenList[i])
			{
				this->delOpenList(i);
				vCloseList.push_back(curNode);
			}
		}

		//������� ������ ���� ���� == �� ã�ҳ�?
		if (curNode == endNode)
		{
			MyNode* _endNode = endNode;
			vector <MyNode*> tempNode;
			while (_endNode != startNode)
			{
				tempNode.push_back(_endNode);
				_endNode = _endNode->parentNode;
			}

			//STL����Ʈ�� �̿��ϸ� reverse() ����ϰų�, push_front()�� ���
			//�츰 ���͸� �̿��ϴ� �Ųٷ� Ǫ�ù� ���ش�
			for (int i = tempNode.size() - 1; i > 0; i--)
			{
				vFinalList.push_back(tempNode[i]);
			}
			isFind = true;
			//�����ϰ� ����������
			return;
		}

		// �����¿� ( ������ ��� x) �ֺ� Ÿ�� ��� ���¸���Ʈ�� �־ �˻� �� ����
		this->addOpenList(curNode->idx, curNode->idy - 1); //��
		this->addOpenList(curNode->idx, curNode->idy + 1); //��
		this->addOpenList(curNode->idx - 1, curNode->idy); //��
		this->addOpenList(curNode->idx + 1, curNode->idy); //��

		// �밢���� �˻� ����
		
		if (totalNode[curNode->idx][curNode->idy - 1]->node_State == NODE_WALL) this->addOpenList(curNode->idx - 1, curNode->idy); //�� �� - �·��̵�
		else if (totalNode[curNode->idx - 1][curNode->idy]->node_State == NODE_WALL) this->addOpenList(curNode->idx, curNode->idy - 1); //�� �� - ������ ����
		else this->addOpenList(curNode->idx - 1, curNode->idy - 1); //�»�

		if (totalNode[curNode->idx - 1][curNode->idy]->node_State == NODE_WALL) this->addOpenList(curNode->idx, curNode->idy + 1); // �� �� - �Ϸ� �̵�
		else if (totalNode[curNode->idx][curNode->idy + 1]->node_State == NODE_WALL) this->addOpenList(curNode->idx - 1, curNode->idy); // �� �� - �·� �̵�
		else this->addOpenList(curNode->idx - 1, curNode->idy + 1); //����

		if (totalNode[curNode->idx + 1][curNode->idy]->node_State == NODE_WALL) this->addOpenList(curNode->idx, curNode->idy - 1); // �� �� - �����η� �̵�
		else if (totalNode[curNode->idx][curNode->idy - 1]->node_State == NODE_WALL) this->addOpenList(curNode->idx + 1, curNode->idy); // �� �� - ��� �̵�
		else this->addOpenList(curNode->idx + 1, curNode->idy - 1); //���

		if (totalNode[curNode->idx + 1][curNode->idy]->node_State == NODE_WALL) this->addOpenList(curNode->idx, curNode->idy - 1); // �� �� - �Ϸ� �̵�
		else if (totalNode[curNode->idx][curNode->idy + 1]->node_State == NODE_WALL) this->addOpenList(curNode->idx - 1, curNode->idy); // �� �� - ��� �̵�
		else this->addOpenList(curNode->idx + 1, curNode->idy + 1); //����
	}
}
//���¸���Ʈ�� �߰� �Լ�
void myAstar::addOpenList(int idx, int idy)
{
	//����ó��
	//���¸���Ʈ�� ���� ��尡 ��ü��� �ε��� ������ ������ �߰����� ���ϰ� ó���Ѵ�(�ε��� ������ 0~ 4)
	if (idx < 0 || idx >NODE_MAX_X || idy < 0 || idy > NODE_MAX_Y) return;
	//��ֹ��� ���¸���Ʈ�� ���� �� ����
	if (totalNode[idx][idy]->node_State == NODE_WALL) return;
	//Ŭ�����Ʈ�� �ִٸ� �̹� ������ ���̴� ������ �ȵȴ�
	for (int i = 0; i < vCloseList.size(); i++)
	{
		if (totalNode[idx][idy] == vCloseList[i]) return;
	}

	//������� �͝��� ������ ������ ���� ���¸���Ʈ�� �߰��ϱ�
	//���� ��� 4���� ��带 �̿������ �ϰ� ���� = 10, �밢�� 14���
	MyNode* neightNode = totalNode[idx][idy];
	int moveCost = curNode->G + (curNode->idx - idx == 0 || curNode->idy - idy == 0) ? 10 : 14;  //�ε������� �ε��� ������ 0 �̸� �������� �̵��� �� + 10 // �ƴϸ� �밢�̵��̴� +14
	//���¸���Ʈ�ȿ� �̿���尡 ������ �ȵȴ�
	for (int i = 0; i < vOpenList.size(); i++)
	{
		if (vOpenList[i] == neightNode) return;
	}

	//�����¤����� ��������Ʈ���� ���� ��� G, H, ParentNode ������ ���¸���Ʈ�� �߰�
	neightNode->G = moveCost;
	neightNode->H = (abs(neightNode->idx - endNode->idx) + abs(neightNode->idy - endNode->idy) * 10); // adb�� ���밪 ���
	neightNode->F = neightNode->G + neightNode->H;
	neightNode->parentNode = curNode;
	vOpenList.push_back(neightNode);


}
//���¸���Ʈ ����
void myAstar::delOpenList(int index)
{
	vOpenList.erase(vOpenList.begin() + index);
}
