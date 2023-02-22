#pragma once
#include "gameNode.h"


#define INTRO_IMAGE_MAX 71
#define BACK_IMAGE_WIDTH 1366
#define BACK_IMAGE_HEIGHT 768
#define INTRO_BUTTON_IMAGE_MAX 3
#define BUTTON_WIDTH 255
#define BUTTON_HEIGHT 52
//클래스 전방선언 / 상호참조
class optionUI;


class introSecen :	public gameNode
{
private:
	//클래스 전방선언 / 상호참조
	optionUI* optionCss;

	int nextImageCount;
	int nextImageIndex;
	RECT buttonRc[3];

	//플레이버튼
	image* playButtonImage;
	image* playButtonOverImage;
	//세팅버튼
	image* settingButtonImage;
	image* settingButtonOverImage;
	//종료버튼
	image* exitButtonImage;
	image* exitButtonOverImage;
	//플레이버튼 눌렀을시
	bool isPlay;


	//콘티뉴 버튼
	image* continueButtonImage;
	image* continueButtonOverImage;
	//뉴게임 버튼
	image* newGameButtonImage;
	image* newGameButtonOverImage;
	//백 버튼
	image* backButtonImage;
	image* backButtonOverImage;

	//네임바
	image* nameBarImage;

public:

	HRESULT init();
	void release();
	void update();
	void render();


	

	introSecen() {}
	~introSecen() {}
};

