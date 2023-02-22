#include "stdafx.h"
#include "introSecen.h"
#include "optionUI.h"

HRESULT introSecen::init()
{
	//배경 이미지 돌릴거 초기화한다
	for (int i = 1; i < INTRO_IMAGE_MAX; i++)
	{
		char str[128];
		sprintf(str, "%02d", i);
		char file[128];		
		sprintf(file, "image/intro/%02d.bmp", i);
		IMAGEMANAGER->addImage(str, file, BACK_IMAGE_WIDTH, BACK_IMAGE_HEIGHT);
	}


	//배경이미지를 프레임 렌더처럼 돌리기위한 변수
	nextImageCount = 1;
	nextImageIndex = 1;
	
	//배경 이미지 위에 버튼
	for (int i = 0; i < INTRO_BUTTON_IMAGE_MAX; i++)
	{
		buttonRc[i] = RectMake(1016, 450 + (i * 55), BUTTON_WIDTH, BUTTON_HEIGHT);
	}
	//플레이 버튼 on/off 
	isPlay = false;

	//플레이버튼
	playButtonImage = IMAGEMANAGER->addImage("playerButton", "image/intro_button/play_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	playButtonOverImage = IMAGEMANAGER->addImage("playerButtonOver", "image/intro_button/play_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//세팅버튼
	settingButtonImage = IMAGEMANAGER->addImage("settingButton", "image/intro_button/setting_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	settingButtonOverImage = IMAGEMANAGER->addImage("settingButtonOver", "image/intro_button/setting_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//종료버튼
	exitButtonImage = IMAGEMANAGER->addImage("exitButton", "image/intro_button/exit_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	exitButtonOverImage = IMAGEMANAGER->addImage("exitButtonOver", "image/intro_button/exit_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//콘티뉴 버튼
	continueButtonImage = IMAGEMANAGER->addImage("continueButton", "image/intro_button/continue_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	continueButtonOverImage = IMAGEMANAGER->addImage("continueButtonOver", "image/intro_button/continue_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//뉴게임 버튼
	newGameButtonImage = IMAGEMANAGER->addImage("newGameButton", "image/intro_button/newgame_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	newGameButtonOverImage = IMAGEMANAGER->addImage("newGameButtonOver", "image/intro_button/newgame_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//백 버튼
	backButtonImage = IMAGEMANAGER->addImage("backButton", "image/intro_button/back_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	backButtonOverImage = IMAGEMANAGER->addImage("backButtonOver", "image/intro_button/back_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//네임바
	nameBarImage = IMAGEMANAGER->addImage("namebar", "image/intro_button/namebar.bmp", 256, 61);


	//옵션 클래스 메모리 할당
	optionCss = new optionUI;
	optionCss->init();


	return S_OK;
}

void introSecen::release()
{
	SAFE_DELETE(optionCss);
}

void introSecen::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->loadScene("intro");
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->loadScene("dungeon");
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) SCENEMANAGER->loadScene("myAstar");
	//옵션클래스 업데이트
	optionCss->update();

	//배경이미지를 프레인 렌더처럼 돌릴 업데이트
	nextImageCount++;
	if (nextImageCount % 3 == 0)		
	{
		nextImageIndex++;
		if (nextImageIndex > INTRO_IMAGE_MAX - 1)
		{
			nextImageIndex = 1;
		}		
	}

	//마우스 클릭
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (!isPlay)
		{
			//플레이 클릭시
			if (PtInRect(&buttonRc[0], _ptMouse))
			{
				isPlay = true;
			}
		}
		if (isPlay)
		{
			//뉴게임 시작시 
			if (PtInRect(&buttonRc[1], _ptMouse))
			{
				SCENEMANAGER->loadScene("dungeon");

				return;
			}
			//BACK 클릭시
			if (PtInRect(&buttonRc[2], _ptMouse))
			{
				isPlay = false;
			}

		}

		//옵션창 열기
		if (!optionCss->getIsOption() && !isPlay)
		{
			if (PtInRect(&buttonRc[1], _ptMouse))
			{
				optionCss->setIsOptionOn();
			}
		}
		//옵션창 닫기
		if (optionCss->getIsOption())
		{
			if (PtInRect(&optionCss->getOptionExitRc(), _ptMouse))
			{
				optionCss->setIsOptiOff();
			}
		}
	}
}

void introSecen::render()
{	
	//배경이미지를 계속 렌더한다
	for (int i = 1; i < INTRO_IMAGE_MAX; i++)
	{
		if (nextImageIndex == i)
		{
			char str[10];
			sprintf(str, "%02d", i);
			IMAGEMANAGER->render(str, getMemDC(), 0, 0);
		}
	}

	//버튼 RC
	for (int i = 0; i < INTRO_BUTTON_IMAGE_MAX; i++)
	{
		Rectangle(getMemDC(), buttonRc[i]);
		//플레이버튼 안눌렀을때
		if (!isPlay)
		{
			//마우스 버튼 충돌
			if (PtInRect(&buttonRc[0], _ptMouse))
			{
				//플레이
				playButtonOverImage->render(getMemDC(), buttonRc[0].left, buttonRc[0].top);
			}
			else if (!PtInRect(&buttonRc[0], _ptMouse))
			{
				//플레이
				playButtonImage->render(getMemDC(), buttonRc[0].left, buttonRc[0].top);
			}
			if (PtInRect(&buttonRc[1], _ptMouse))
			{
				//세팅
				settingButtonOverImage->render(getMemDC(), buttonRc[1].left, buttonRc[1].top);
			}
			else if (!PtInRect(&buttonRc[1], _ptMouse))
			{
				//세팅
				settingButtonImage->render(getMemDC(), buttonRc[1].left, buttonRc[1].top);
			}
			if (PtInRect(&buttonRc[2], _ptMouse))
			{
				//종료
				exitButtonOverImage->render(getMemDC(), buttonRc[2].left, buttonRc[2].top);
			}
			else if (!PtInRect(&buttonRc[2], _ptMouse))
			{
				//종료
				exitButtonImage->render(getMemDC(), buttonRc[2].left, buttonRc[2].top);
			}

		}
		//플레이버튼 눌렀을때
		else
		{
			//마우스 버튼 충돌
			if (PtInRect(&buttonRc[0], _ptMouse))
			{
				//컨티뉴
				continueButtonOverImage->render(getMemDC(), buttonRc[0].left, buttonRc[0].top);
			}
			else if (!PtInRect(&buttonRc[0], _ptMouse))
			{
				//컨티뉴
				continueButtonImage->render(getMemDC(), buttonRc[0].left, buttonRc[0].top);
			}
			if (PtInRect(&buttonRc[1], _ptMouse))
			{
				//뉴게임
				newGameButtonOverImage->render(getMemDC(), buttonRc[1].left, buttonRc[1].top);
			}
			else if (!PtInRect(&buttonRc[1], _ptMouse))
			{
				//뉴게임
				newGameButtonImage->render(getMemDC(), buttonRc[1].left, buttonRc[1].top);
			}
			if (PtInRect(&buttonRc[2], _ptMouse))
			{
				//백
				backButtonOverImage->render(getMemDC(), buttonRc[2].left, buttonRc[2].top);
			}
			else if (!PtInRect(&buttonRc[2], _ptMouse))
			{
				//백
				backButtonImage->render(getMemDC(), buttonRc[2].left, buttonRc[2].top);
			}
		}
	}
	//네임바 렌더
	nameBarImage->render(getMemDC(), 1014, 639);

	//옵션창 렌더
	if (optionCss->getIsOption())
	{
		optionCss->render();
	}

	TextOut(getMemDC(), 50, 50, "아아아아", strlen("아아아아"));

	//TextOut(getMemDC(), WINSIZEX / 2 - 300, 230, "나 송태운 코딩안해서 잡혀옴", strlen("나 송태운 코딩안해서 잡혀옴"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 330, 250, "이게 나야! 이게... 나라고...! This~ Is~ Me...", strlen("이게 나야! 이게... 나라고...! This~ Is~ Me..."));
	//TextOut(getMemDC(), WINSIZEX / 2 - 230, 290, "우웩", strlen("우웩"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 250, 310, "에욱", strlen("에욱"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 280, 320, "우웩", strlen("우웩"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 300, 330, "에욱", strlen("에욱"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 200, 290, "에욱", strlen("에욱"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 180, 310, "우웩", strlen("우웩"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 160, 320, "에욱", strlen("에욱"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 140, 330, "우웩", strlen("우웩"));

}