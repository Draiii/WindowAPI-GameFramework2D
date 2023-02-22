#pragma once
#include "gameNode.h"
#include "dungeonSecen.h"

#define NODE_MAX_X 58
#define NODE_MAX_Y 50

enum NODE_STATE
{
	NODE_START,
	NODE_END,
	NODE_MONSTER,
	NODE_WALL,
	NODE_EMPTY
};

//��� Ŭ����
class MyNode
{
private:

	//���� GETTER, SETTER ���� ���� �ؾ������� �������� �ۺ��� ������
	//���̽�Ÿ���� �⿪�ؾ� �� 2����
	//1. ���(F, G, H)
	//2. �θ��� ������(��������� ������)

public:


	RECT rc;				//��Ʈ
	float x, y;
	int idx, idy;			//�ε��� x, y
	int F, G, H;			//F = G + H //G = ���� to ���� // H = ���� to ����
	MyNode* parentNode;		//�θ� ����ų ��� (�������)
	NODE_STATE node_State;	//����� ����(����, ����, ��, ����)


	//��� ������
	MyNode() {}
	//������ �����ε��� ���� �ʱ�ȭ
	MyNode(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		node_State = NODE_EMPTY;
		parentNode = NULL;
	}

	//��� �Ҹ���
	~MyNode() {}
};

class dungeonSecen;

class myAstar :	public gameNode
{
private:

	dungeonSecen* dungeonSecenNode;

	MyNode* totalNode[NODE_MAX_X][NODE_MAX_Y];
	MyNode* startNode;				//���۳��	
	MyNode* endNode;					//������
	MyNode* curNode;					//������ - ��ó���� ���۳�� = ������

	vector <MyNode*> vOpenList;		//���¸���Ʈ (Ž���� ��带 ��Ƶ� ����)
	vector <MyNode*> vCloseList;		//Ŭ�����Ʈ (���¸���Ʈ�� �ִܰŸ�(�̹�Ž���Ϸ���) ��带 ������ Ŭ�����Ʈ ���Ϳ� ��´�)
	vector <MyNode*> vFinalList;		//���̳θ���Ʈ (��ã�� �� Ŭ�����Ʈ�� ����ִ� ������ ������ ��ų �뵵)

	int count;						//����, ���� ����ѹ����� �����ϱ� ���� ����
	bool isFind;					//�� ã�ҳ�?


	bool isMoveStart;
	int MoveStartCount;
	bool isMoveCount;
	int moveCount;
	bool isLastMove;
	int lastMoveCount;




	int playerIdX;
	int playerIdY;


public:
	   	 
	HRESULT init(int _x, int _y);
	HRESULT init();
	void release();
	void update();
	void render();
	
	//����� �˻�
	void CheckIsWall();

	//��� ��ä��� (���������� ��ĥ��)
	void setNodeColor(MyNode* node, COLORREF color);

	MyNode* getNode(int _x, int _y) { return totalNode[_x][_y]; }

	void setNode(int XX, int YY, float _x, float _y)
	{ 
		totalNode[XX][YY]->x = _x;
		totalNode[XX][YY]->y = _y;
		totalNode[XX][YY]->rc = RectMake(totalNode[XX][YY]->x + (XX * TILE_WIDTH), totalNode[XX][YY]->y + (YY * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT);
	}
	//��ŸƮ��� �޾ƿ���
	MyNode* getMyStartNode() { return startNode; }
	//���� ��ŸƮ �޾ƿ���
	bool getMoveStart() { return isMoveStart; }
	//�÷��̾� �ε���
	int getPlayeridX() { return playerIdX; }
	int getPlayeridY() { return playerIdY; }
	void setPlayerIdx(int _x, int _y) { playerIdX += _x; playerIdY += _y; }

	//*�߿�*//
	//��ã�� �Լ�
	void pathFinding();
	//���¸���Ʈ�� �߰� �Լ�
	void addOpenList(int idx, int idy);
	//���¸���Ʈ ����
	void delOpenList(int index);


	myAstar() : startNode(NULL), endNode(NULL) {}
	~myAstar() {}


};

