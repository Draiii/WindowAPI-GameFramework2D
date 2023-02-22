#include "stdafx.h"
#include "Astar.h"

HRESULT Astar::init()
{
	//전체노드 초기화
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			//새로운 노드와 렉트위치 설정
			totalNode[x][y] = new node(x, y); //인덱스
			totalNode[x][y]->rc = RectMake(5 + x * 20, 5 + y * 20, 20, 20);
		}
	}
	
	//첫클릭이 짝수가 되게 하기위해 -1로 초기화
	//나눈값이 짝수가 되게 하기위해
	count = -1;
	//길 찾았냐?
	isFind = false;


	

	return S_OK;
}

void Astar::release()
{

}

void Astar::update()
{
	//시작, 종료 세팅
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//시작, 종료 노드가 이미 세팅되어있다면 그냥 나가자
		if (startNode && endNode) return; //리턴 만나면 업데이트 나감

		for (int y = 0; y < MAX_Y; y++)
		{
			for (int x = 0; x < MAX_X; x++)
			{
				//렉트 충돌처리
				if (PtInRect(&totalNode[x][y]->rc, _ptMouse))
				{
					count++;
					if (count % 2 == 0) //카운트가 -1에서 0이 되기때문에 처음 클릭은 0 그래서 시작지점
					{
						totalNode[x][y]->nodeState = NODE_START;
						startNode = totalNode[x][y];
					}
					else
					{
						totalNode[x][y]->nodeState = NODE_END;
						endNode = totalNode[x][y];
					}

				}
			}
		}
	}

	//벽 세팅 ( 시작 종료 노드 설정전에 벽세우지 못하게 막기 ) 
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) && startNode && endNode)
	{

		for (int y = 0; y < MAX_Y; y++)
		{
			for (int x = 0; x < MAX_X; x++)
			{
				//렉트 충돌처리
				if (PtInRect(&totalNode[x][y]->rc, _ptMouse))
				{
					//시작노드, 종료노드는 선택하지 못하게 막기
					if (totalNode[x][y]->nodeState == NODE_START) continue;
					if (totalNode[x][y]->nodeState == NODE_END) continue;					
					totalNode[x][y]->nodeState = NODE_WALL;
				}
			}
		}
	}


	//길찾기 시작
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		this->pathFinding();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		//count = -1;
		this->init();
	}

}

void Astar::render()
{
	//전체노드 렌더
	char str[128];
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			//새로운 노드와 렉트위치 설정
			Rectangle(getMemDC(), totalNode[x][y]->rc );

			//시작노드 보여주기
			if (totalNode[x][y]->nodeState == NODE_START)
			{
				this->setNodeColor(startNode, RGB(255, 0, 0));
				TextOut(getMemDC(), startNode->rc.left + 100, startNode->rc.top + 10, "START", strlen("START"));					
			}
			//종료노드 보여주기
			if (totalNode[x][y]->nodeState == NODE_END)
			{
				this->setNodeColor(endNode, RGB(0, 0, 255));
				TextOut(getMemDC(), endNode->rc.left + 100, endNode->rc.top + 10, "END", strlen("END"));
			}
			//벽노드 보여주기
			if (totalNode[x][y]->nodeState == NODE_WALL)
			{
				this->setNodeColor(totalNode[x][y], RGB(0, 0, 0));
				TextOut(getMemDC(), totalNode[x][y]->rc.left + 100, totalNode[x][y]->rc.top + 10, "WALL", strlen("WALL"));
			}

			//전체 노드의 인덱스 보여주기
			sprintf(str, "%d, %d", totalNode[x][y]->idx, totalNode[x][y]->idy);
			TextOut(getMemDC(), totalNode[x][y]->rc.left + 10, totalNode[x][y]->rc.top + 10, str, strlen(str));
		}
	}

	if (isFind)
	{
		for (int i = 0; i < vFinalList.size(); i++)
		{
			setNodeColor(vFinalList[i], RGB(200, 200, 0));
			sprintf(str, "[%d, %d]      %d번째 노드", vFinalList[i]->idx, vFinalList[i]->idy, i+1);
			TextOut(getMemDC(), vFinalList[i]->rc.left + 10, vFinalList[i]->rc.top + 30, str, strlen(str));
			sprintf(str, "F:%d, G:%d, H:%d", vFinalList[i]->F, vFinalList[i]->G, vFinalList[i]->H);
			TextOut(getMemDC(), vFinalList[i]->rc.left + 10, vFinalList[i]->rc.top + 50, str, strlen(str));
		}
	}
}

//노드 색채우기 (편리성때문에 색칠함)
void Astar::setNodeColor(node * node, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(getMemDC(), &node->rc, brush);
	DeleteObject(brush);
	FrameRect(getMemDC(), node->rc, RGB(0, 0, 0));
}
//*중요*//
//길찾기 함수
void Astar::pathFinding()
{
	//시작노드 및 종료 노드가 있는 경우에만 길찾기
	if (!startNode || !endNode) return;	//빠져나오기

	//길찾기 ㄱㄱ
	//검색을 하려면 무조건 오픈리스트에 담아두고 F와 H 값 가장작은 놈을 찾아서 그놈을 현재노드로 변경하고 오픈리스트에서 현재노드는 삭제하고 현재노드는 클로즈리스트에 담아둔다

	//1. 시작노드가 있어야 출발이 가능하니 시작노드를 오픈리스트에 담아준다
	vOpenList.push_back(startNode);

	//2. 오픈리스트에 담겨 있는 벡터를 검사해서 종료노드에 도착할떄까지 무한루프
	while (vOpenList.size() > 0) //스타트노르르 넣으면 이곳에 들어옴
	{
		curNode = vOpenList[0];

		//오픈리스트 중 가장 F가 작거나 F가 같다면  H가 작은 걸 현재노르로 하고 현재노드를 오픈리스트에서 클로즈 리스트로 옮기기
		//비교를 하려고 하면 최소 시작노드에서 주변을 탐색한 이후 길찾기가 시작되니 1부터 시작하자
		for (int i = 1; i < vOpenList.size(); i++)
		{
			if (vOpenList[i]->F <= curNode->F && vOpenList[i]->H < curNode->H)
			{
				curNode = vOpenList[i];
			}
		}

		//클로즈리스트에 넣어준다
		for (int i = 0; i < vOpenList.size(); i++)
		{
			if (curNode == vOpenList[i])
			{
				this->delOpenList(i);
				vCloseList.push_back(curNode);
			}
		}

		//현재노드와 마지막 노드와 같냐 == 길 찾았냐?
		if (curNode == endNode)
		{
			node* _endNode = endNode;
			vector <node*> tempNode;
			while (_endNode != startNode)
			{
				tempNode.push_back(_endNode);
				_endNode = _endNode->parentNode;
			}

			//STL리스트를 이용하면 reverse() 사용하거나, push_front()를 사용
			//우린 벡터를 이용하니 거꾸로 푸시백 해준다
			for (int i = tempNode.size() - 1; i > 0; i--)
			{
				vFinalList.push_back(tempNode[i]);
			}
			isFind = true;
			//종료하고 빠져나오기
			return;
		}

		// 상하좌우 ( 순서는 상관 x) 주변 타일 모두 오픈리스트에 넣어서 검사 할 예정
		this->addOpenList(curNode->idx, curNode->idy - 1); //상
		this->addOpenList(curNode->idx, curNode->idy + 1); //하
		this->addOpenList(curNode->idx - 1, curNode->idy); //좌
		this->addOpenList(curNode->idx + 1, curNode->idy); //우
		
		//추후 대각선도 검사 가능
		this->addOpenList(curNode->idx- 1, curNode->idy - 1); //좌상
		this->addOpenList(curNode->idx- 1, curNode->idy + 1); //좌하
		this->addOpenList(curNode->idx + 1, curNode->idy - 1); //우상
		this->addOpenList(curNode->idx + 1, curNode->idy + 1); //우하
	}
}
//오픈리스트에 추가 함수
void Astar::addOpenList(int idx, int idy)
{
	//예외처리
	//오픈리스트에 담을 노드가 전체노드 인덱스 밖으로 나가면 추가하지 못하게 처리한다(인덱스 범위는 0~ 4)
	if (idx < 0 || idx >MAX_X || idy < 0 || idy > MAX_Y) return;
	//장애물은 오픈리스트에 담을 수 없다
	if (totalNode[idx][idy]->nodeState == NODE_WALL) return;
	//클로즈리스트에 있다면 이미 지나온 길이니 담으면 안된다
	for (int i = 0; i < vCloseList.size(); i++)
	{
		if (totalNode[idx][idy] == vCloseList[i]) return;
	}

	//여기까지 와씅면 문제가 없으며 이제 오픈리스트에 추가하기
	//현재 노드 4방향 노드를 이웃노드라고 하고 직선 = 10, 대각은 14비용
	node* neightNode = totalNode[idx][idy];
	int moveCost = curNode->G + (curNode->idx - idx == 0 || curNode->idy - idy == 0) ? 10 : 14;  //인덱스에서 인덱스 뺀값이 0 이면 직선으로 이동한 것 + 10 // 아니면 대각이동이니 +14
	//오픈리스트안에 이웃노드가 있으면 안된다
	for (int i = 0; i < vOpenList.size(); i++)
	{
		if (vOpenList[i] == neightNode) return;
	}

	//마지맞ㄱ으로 오른리스트에도 없는 경우 G, H, ParentNode 설정후 오픈리스트에 추가
	neightNode->G = moveCost;
	neightNode->H = (abs(neightNode->idx - endNode->idx) + abs(neightNode->idy - endNode->idy) * 10); // adb는 절대값 계싼
	neightNode->F = neightNode->G + neightNode->H;
	neightNode->parentNode = curNode;
	vOpenList.push_back(neightNode);


}
//오픈리스트 삭제
void Astar::delOpenList(int index)
{
	vOpenList.erase(vOpenList.begin() + index);
}
