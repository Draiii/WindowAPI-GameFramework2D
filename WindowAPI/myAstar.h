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

//노드 클래스
class MyNode
{
private:

	//원래 GETTER, SETTER 만들어서 접근 해야하지만 귀찮귀찮 퍼블릭에 때려박
	//에이스타에서 기역해야 할 2가지
	//1. 비용(F, G, H)
	//2. 부모노드 포인터(이전노드의 포인터)

public:


	RECT rc;				//렉트
	float x, y;
	int idx, idy;			//인덱스 x, y
	int F, G, H;			//F = G + H //G = 시작 to 현재 // H = 현재 to 종료
	MyNode* parentNode;		//부모를 가리킬 노드 (이전노드)
	NODE_STATE node_State;	//노드의 상태(시작, 종료, 벽, 빈노드)


	//노드 생성자
	MyNode() {}
	//생성자 오버로딩을 통한 초기화
	MyNode(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		node_State = NODE_EMPTY;
		parentNode = NULL;
	}

	//노드 소멸자
	~MyNode() {}
};

class dungeonSecen;

class myAstar :	public gameNode
{
private:

	dungeonSecen* dungeonSecenNode;

	MyNode* totalNode[NODE_MAX_X][NODE_MAX_Y];
	MyNode* startNode;				//시작노드	
	MyNode* endNode;					//종료노드
	MyNode* curNode;					//현재노드 - 맨처음엔 시작노드 = 현재노드

	vector <MyNode*> vOpenList;		//오픈리스트 (탐색한 노드를 담아둘 벡터)
	vector <MyNode*> vCloseList;		//클로즈리스트 (오픈리스트의 최단거리(이미탐색완료한) 노드를 삭제후 클로즈리스트 벡터에 담는다)
	vector <MyNode*> vFinalList;		//파이널리스트 (길찾은 후 클로즈리스트에 담겨있는 노드들을 리버스 시킬 용도)

	int count;						//시작, 종료 노드한번씩만 선택하기 위한 변수
	bool isFind;					//길 찾았냐?


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
	
	//벽노드 검사
	void CheckIsWall();

	//노드 색채우기 (편리성때문에 색칠함)
	void setNodeColor(MyNode* node, COLORREF color);

	MyNode* getNode(int _x, int _y) { return totalNode[_x][_y]; }

	void setNode(int XX, int YY, float _x, float _y)
	{ 
		totalNode[XX][YY]->x = _x;
		totalNode[XX][YY]->y = _y;
		totalNode[XX][YY]->rc = RectMake(totalNode[XX][YY]->x + (XX * TILE_WIDTH), totalNode[XX][YY]->y + (YY * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT);
	}
	//스타트노드 받아오기
	MyNode* getMyStartNode() { return startNode; }
	//무브 스타트 받아오기
	bool getMoveStart() { return isMoveStart; }
	//플레이어 인덱스
	int getPlayeridX() { return playerIdX; }
	int getPlayeridY() { return playerIdY; }
	void setPlayerIdx(int _x, int _y) { playerIdX += _x; playerIdY += _y; }

	//*중요*//
	//길찾기 함수
	void pathFinding();
	//오픈리스트에 추가 함수
	void addOpenList(int idx, int idy);
	//오픈리스트 삭제
	void delOpenList(int index);


	myAstar() : startNode(NULL), endNode(NULL) {}
	~myAstar() {}


};

