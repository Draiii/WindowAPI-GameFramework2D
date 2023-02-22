#pragma once
#include "gameNode.h"

#define MAX_X 40
#define MAX_Y 40


//타일값
enum NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_WALL,
	NODE_EMPTY
};

//노드 클래스
class node 
{
private:
	//원래 GETTER, SETTER 만들어서 접근 해야하지만 귀찮귀찮 퍼블릭에 때려박
	//에이스타에서 기역해야 할 2가지
	//1. 비용(F, G, H)
	//2. 부모노드 포인터(이전노드의 포인터)
public:
	RECT rc;				//렉트
	int idx, idy;			//인덱스 x, y
	int F, G, H;			//F = G + H //G = 시작 to 현재 // H = 현재 to 종료
	node* parentNode;		//부모를 가리킬 노드 (이전노드)
	NODESTATE nodeState;	//노드의 상태(시작, 종료, 벽, 빈노드)

	 
	//노드 생성자
	node() {}
	//생성자 오버로딩을 통한 초기화
	node(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		nodeState = NODE_EMPTY;
		parentNode = NULL;
	}

	//노드 소멸자
	~node() {}
};




class Astar :	public gameNode
{
private:

	node* totalNode[MAX_X][MAX_Y];	//전체 노드 25개
	node* startNode;				//시작노드	
	node* endNode;					//종료노드
	node* curNode;					//현재노드  - 맨처음엔 시작노드 = 현재노드
	
	vector <node*> vOpenList;		//오픈리스트 (탐색한 노드를 담아둘 벡터)
	vector <node*> vCloseList;		//클로즈리스트 (오픈리스트의 최단거리(이미탐색완료한) 노드를 삭제후 클로즈리스트 벡터에 담는다)
	vector <node*> vFinalList;		//파이널리스트 (길찾은 후 클로즈리스트에 담겨있는 노드들을 리버스 시킬 용도)

	int count;						//시작, 종료 노드한번씩만 선택하기 위한 변수
	bool isFind;					//길 찾았냐?

	

public:

	HRESULT init();
	void release();
	void update();
	void render();


	//노드 색채우기 (편리성때문에 색칠함)
	void setNodeColor(node* node, COLORREF color);

	//*중요*//
	//길찾기 함수
	void pathFinding();
	//오픈리스트에 추가 함수
	void addOpenList(int idx, int idy);
	//오픈리스트 삭제
	void delOpenList(int index);

	Astar() : startNode(NULL), endNode(NULL) {}
	~Astar() {}
};

