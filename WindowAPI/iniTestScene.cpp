#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init()
{
	return S_OK;
}

void iniTestScene::release()
{
}

void iniTestScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//섹션, 키, 밸류
		//[플밍15기]
		//선재=50
		//종택=100
		//...

		INIDATA->addData("플밍15기", "선재", "50.5");
		INIDATA->addData("플밍15기", "종택", "100");
		INIDATA->addData("플밍15기", "수현", "8");

		//파일 이름으로 세이브
		INIDATA->saveINI("플밍플밍");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		int num = INIDATA->loadDataInteger("플밍플밍", "플밍15기", "선재");
		cout << num << endl;
	}
}

void iniTestScene::render()
{
}
