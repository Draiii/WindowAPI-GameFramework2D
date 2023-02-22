#include "stdafx.h"
#include "sceneTest1.h"


HRESULT sceneTest1::init()
{
	return S_OK;
}

void sceneTest1::release()
{
}

void sceneTest1::update()
{
	//씬변경
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//씬변경전에 반드시 데이터는 저장해두기

		//저장후에 씬변경하기
		SCENEMANAGER->loadScene("테스트씬");
	}
}

void sceneTest1::render()
{
	TextOut(getMemDC(), 100, 100, "테스트1씬임", strlen("테스트1씬임"));
}
