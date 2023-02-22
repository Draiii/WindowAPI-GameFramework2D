#include "stdafx.h"
#include "isometricTest.h"

HRESULT isometricTest::init()
{
	//타일 구조체 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tile[i][j].x = STARTX + (j * (TILESIZEX_HALF)) - (i * (TILESIZEX_HALF));
			_tile[i][j].y = STARTY + (j * (TILESIZEY_HALF)) + (i * (TILESIZEY_HALF));
			_tile[i][j].rc = RectMakeCenter(_tile[i][j].x, _tile[i][j].y, TILESIZEX, TILESIZEY);
		}
	}

	//인덱스 초기화
	_index = { 0, 0 };

	return S_OK;
}

void isometricTest::release()
{
}

void isometricTest::update()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//렉트들과 마우스좌표가 충돌했는지?
			if (PtInRect(&_tile[i][j].rc, _ptMouse))
			{

				if (_ptMouse.y > _tile[i][j].y) //3, 4분면
				{
					if (_ptMouse.x > _tile[i][j].x) //4분면
					{
						if ((_ptMouse.x) <= _tile[i][j].x + TILESIZEX_HALF + _tile[i][j].y - (_ptMouse.y - _tile[i][j].y))
						{
							_index.x = j;
							_index.y = i;
						}
					}
					else//3분면
					{
						if (_ptMouse.x >= (_tile[i][j].x - TILESIZEX_HALF) + ((_ptMouse.y - _tile[i][j].y) * 2))
						{
							_index.x = j;
							_index.y = i;
						}
					}
				}
				else//1, 2분면
				{
					if (_ptMouse.x > _tile[i][j].x) //1분면
					{

					}
					else //2분면
					{

					}

				}


			}
		}
	}

}

void isometricTest::render()
{
	char str[128];

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//디버깅용 렉트 보여주기
			if (KEYMANAGER->isToggleKey(VK_F1))
			{
				Rectangle(getMemDC(), _tile[i][j].rc);
				//FrameRect(getMemDC(), _tile[i][j].rc, RGB(255, 0, 0));
			}

			//마름모 선 그리기
			MoveToEx(getMemDC(), _tile[i][j].x - (TILESIZEX / 2), _tile[i][j].y, NULL);
			LineTo(getMemDC(), _tile[i][j].x, _tile[i][j].y - (TILESIZEY / 2));
			LineTo(getMemDC(), _tile[i][j].x + (TILESIZEX / 2), _tile[i][j].y);
			LineTo(getMemDC(), _tile[i][j].x , _tile[i][j].y + (TILESIZEY / 2));
			LineTo(getMemDC(), _tile[i][j].x - (TILESIZEX / 2), _tile[i][j].y);

			//타일안에 인덱스 표시
			sprintf(str, "[%d, %d]", j, i);
			TextOut(getMemDC(), _tile[i][j].x, _tile[i][j].y - 15, str, strlen(str));

		}
	}

	sprintf(str, "현재인덱스 : [%d, %d]", _index.x, _index.y);
	TextOut(getMemDC(), STARTX + 200, STARTY - 50, str, strlen(str));

}
