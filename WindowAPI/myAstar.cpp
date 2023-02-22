#include "stdafx.h"
#include "myAstar.h"
#include "dungeonSecen.h"

HRESULT myAstar::init(int _x, int _y)
{
	//전체노드 초기화
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//새로운 노드와 렉트위치 설정
			totalNode[x][y] = new MyNode(x, y); //인덱스
			totalNode[x][y]->x = -1092;
			totalNode[x][y]->y = -1300 ;
			totalNode[x][y]->rc = RectMake(totalNode[x][y]->x + (x * TILE_WIDTH), totalNode[x][y]->y + (y * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT);
		}
	}
	//34, 31
	playerIdX = _x;
	playerIdY = _y;
	IMAGEMANAGER->addImage("stagePixel1", "image/map/dungeon_1_1_pixel.bmp", 3016, 2600);


	//벽 노드 검사
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("stagePixel1")->getMemDC(), x * TILE_WIDTH + (TILE_WIDTH / 2), y * TILE_HEIGHT + (TILE_HEIGHT / 2));
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			bool checkPixelWall = (r == 255 && g == 0 && b == 255);
			// 충돌하면 홀드하고 펄스
			if (checkPixelWall)
			{
				totalNode[x][y]->node_State = NODE_WALL;
			}
		}
	}
	//초기화
	startNode = {};
	endNode = {};
	curNode = {};

	//첫클릭이 짝수가 되게 하기위해 -1로 초기화
	//나눈값이 짝수가 되게 하기위해
	//길찾기중일땐 0
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
	//전체노드 초기화
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			//새로운 노드와 렉트위치 설정
			totalNode[x][y] = new MyNode(x, y); //인덱스
			totalNode[x][y]->x = -1092;
			totalNode[x][y]->y = -1300;
			totalNode[x][y]->rc = RectMake(totalNode[x][y]->x + (x * TILE_WIDTH), totalNode[x][y]->y + (y * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT);
		}
	}
	//34, 31
	playerIdX = 34;
	playerIdY = 31;
	IMAGEMANAGER->addImage("stagePixel1", "image/map/dungeon_1_1_pixel.bmp", 3016, 2600);


	//벽 노드 검사
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("stagePixel1")->getMemDC(), x * TILE_WIDTH + (TILE_WIDTH / 2), y * TILE_HEIGHT + (TILE_HEIGHT / 2));
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			bool checkPixelWall = (r == 255 && g == 0 && b == 255);
			// 충돌하면 홀드하고 펄스
			if (checkPixelWall)
			{
				totalNode[x][y]->node_State = NODE_WALL;
			}
		}
	}
	//초기화
	startNode = {};
	endNode = {};
	curNode = {};

	//첫클릭이 짝수가 되게 하기위해 -1로 초기화
	//나눈값이 짝수가 되게 하기위해
	//길찾기중일땐 0
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
	vOpenList.clear();		//클리어
	vCloseList.clear();		//클리어
	vFinalList.clear();		//클리어
	
}

void myAstar::update()
{
	
	///////////////////////////////////////////////////////////////
		//캐릭터 위치
		startNode = totalNode[playerIdX][playerIdY];
		totalNode[playerIdX][playerIdY]->node_State = NODE_START;

	//////////////////////////////////////////////////////////////

	//시작, 종료 세팅
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//시작, 종료 노드가 이미 세팅되어있다면 그냥 나가자
		//if (startNode && endNode) return; //리턴 만나면 업데이트 나감

		//길찾기 중일때 새로 클릭하면 릴리스 시킨다
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
					//렉트 충돌처리
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

	//------------------------------------------------// 캐릭터 이동 함수 //------------------------------------------------//

	if (isMoveStart)
	{
		//캐릭터 주위 1칸은 파이널 리스트가 없기때문에 바로 엔드노드로 설정하고
		//캐릭터를 이동시킨다
		if (vFinalList.size() == 0) isLastMove = true;

		//그외에는 파이널노드가 생성되고 엔드노드까지 파이널 노드를 따라서 캐릭터를 이동
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

	//------------------------------------------------// 캐릭터 이동 함수 //------------------------------------------------//
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
			this->release();
		this->init(playerIdX, playerIdY);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->loadScene("intro");
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->loadScene("dungeon");
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) SCENEMANAGER->loadScene("myAstar");

	//벽 세팅 ( 시작 종료 노드 설정전에 벽세우지 못하게 막기 ) 
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) && startNode && endNode)
	{

		for (int y = 0; y < NODE_MAX_Y; y++)
		{
			for (int x = 0; x < NODE_MAX_X; x++)
			{
				//렉트 충돌처리
				if (PtInRect(&totalNode[x][y]->rc, _ptMouse))
				{
					//시작노드, 종료노드는 선택하지 못하게 막기
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
	//전체노드 렌더
	char str[128];
	char str2[128];


	if (isFind)
	{
		//moveTime = GetTickCount64();
		for (int i = 0; i < vFinalList.size(); i++)
		{			

			setNodeColor(vFinalList[i], RGB(200, 200, 0));
			sprintf(str, "[%d, %d]      %d번째 노드", vFinalList[i]->idx, vFinalList[i]->idy, i + 1);
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
			//새로운 노드와 렉트위치 설정 && 플레이어 기준
			if (x > playerIdX - 14 && x < playerIdX + 13)
			{
				if (y > playerIdY - 7 && y < playerIdY + 7)
				{
					FrameRect(getMemDC(), totalNode[x][y]->rc, RGB(0, 0, 200));

					//종료노드 보여주기
					if (totalNode[x][y]->node_State == NODE_END)
					{						
						this->setNodeColor(endNode, RGB(0, 0, 255));
						TextOut(getMemDC(), endNode->rc.left + 10, endNode->rc.top + 20, "END", strlen("END"));
					}
					//시작노드 보여주기
					if (totalNode[x][y]->node_State == NODE_START)
					{
						this->setNodeColor(startNode, RGB(255, 0, 0));
						TextOut(getMemDC(), startNode->rc.left + 10, startNode->rc.top + 20, "START", strlen("START"));
					}
					//벽노드 보여주기
					//if (totalNode[x][y]->node_State == NODE_WALL)
					//{
					//	this->setNodeColor(totalNode[x][y], RGB(100, 100, 0));
					//	TextOut(getMemDC(), totalNode[x][y]->rc.left + 100, totalNode[x][y]->rc.top + 10, "WALL", strlen("WALL"));
					//}
					if (totalNode[x][y]->node_State == NODE_WALL)
					{
						this->setNodeColor(totalNode[x][y], RGB(100, 100, 0));
						TextOut(getMemDC(), totalNode[x][y]->rc.left + 10, totalNode[x][y]->rc.top + 23, "벽", strlen("벽"));
					}
					//전체 노드의 인덱스 보여주기
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
//벽노드 검사
void myAstar::CheckIsWall()
{
	//벽 노드 검사
	for (int y = 0; y < NODE_MAX_Y; y++)
	{
		for (int x = 0; x < NODE_MAX_X; x++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("stagePixel1")->getMemDC(), x + (TILE_WIDTH / 2), y + (TILE_HEIGHT / 2));
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			bool checkPixelWall = (r == 255 && g == 0, b == 255);
			//픽셀충돌하는곳은 벽
			if (checkPixelWall)
			{
				totalNode[x][y]->node_State = NODE_WALL;			
			}
		}
	}
}

//노드 색채우기 (편리성때문에 색칠함)
void myAstar::setNodeColor(MyNode * node, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(getMemDC(), &node->rc, brush);
	DeleteObject(brush);
	FrameRect(getMemDC(), node->rc, RGB(0, 0, 0));
}


//*중요*//
//길찾기 함수
void myAstar::pathFinding()
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
			MyNode* _endNode = endNode;
			vector <MyNode*> tempNode;
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

		// 대각선도 검사 가능
		
		if (totalNode[curNode->idx][curNode->idy - 1]->node_State == NODE_WALL) this->addOpenList(curNode->idx - 1, curNode->idy); //상 벽 - 좌로이동
		else if (totalNode[curNode->idx - 1][curNode->idy]->node_State == NODE_WALL) this->addOpenList(curNode->idx, curNode->idy - 1); //좌 벽 - 상으로 위동
		else this->addOpenList(curNode->idx - 1, curNode->idy - 1); //좌상

		if (totalNode[curNode->idx - 1][curNode->idy]->node_State == NODE_WALL) this->addOpenList(curNode->idx, curNode->idy + 1); // 좌 벽 - 하로 이동
		else if (totalNode[curNode->idx][curNode->idy + 1]->node_State == NODE_WALL) this->addOpenList(curNode->idx - 1, curNode->idy); // 하 벽 - 좌로 이동
		else this->addOpenList(curNode->idx - 1, curNode->idy + 1); //좌하

		if (totalNode[curNode->idx + 1][curNode->idy]->node_State == NODE_WALL) this->addOpenList(curNode->idx, curNode->idy - 1); // 우 벽 - 상으로로 이동
		else if (totalNode[curNode->idx][curNode->idy - 1]->node_State == NODE_WALL) this->addOpenList(curNode->idx + 1, curNode->idy); // 상 벽 - 우로 이동
		else this->addOpenList(curNode->idx + 1, curNode->idy - 1); //우상

		if (totalNode[curNode->idx + 1][curNode->idy]->node_State == NODE_WALL) this->addOpenList(curNode->idx, curNode->idy - 1); // 우 벽 - 하로 이동
		else if (totalNode[curNode->idx][curNode->idy + 1]->node_State == NODE_WALL) this->addOpenList(curNode->idx - 1, curNode->idy); // 하 벽 - 우로 이동
		else this->addOpenList(curNode->idx + 1, curNode->idy + 1); //우하
	}
}
//오픈리스트에 추가 함수
void myAstar::addOpenList(int idx, int idy)
{
	//예외처리
	//오픈리스트에 담을 노드가 전체노드 인덱스 밖으로 나가면 추가하지 못하게 처리한다(인덱스 범위는 0~ 4)
	if (idx < 0 || idx >NODE_MAX_X || idy < 0 || idy > NODE_MAX_Y) return;
	//장애물은 오픈리스트에 담을 수 없다
	if (totalNode[idx][idy]->node_State == NODE_WALL) return;
	//클로즈리스트에 있다면 이미 지나온 길이니 담으면 안된다
	for (int i = 0; i < vCloseList.size(); i++)
	{
		if (totalNode[idx][idy] == vCloseList[i]) return;
	}

	//여기까지 와씅면 문제가 없으며 이제 오픈리스트에 추가하기
	//현재 노드 4방향 노드를 이웃노드라고 하고 직선 = 10, 대각은 14비용
	MyNode* neightNode = totalNode[idx][idy];
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
void myAstar::delOpenList(int index)
{
	vOpenList.erase(vOpenList.begin() + index);
}
