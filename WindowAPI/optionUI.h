#pragma once
#include "gameNode.h"

#define OPTION_FRAME_WIDTH 1008
#define OPTION_FRAME_HEIGHT 702

#define LEFT_RC_WIDTH 209
#define LEFT_RC_HEIGHT 48


#define BOTTOM_RC_WIDTH 216
#define BOTTOM_RC_HEIGHT 52
//클래스 전방선언 / 상호참조
class introSecen;

class optionUI :	public gameNode
{
private:
	//클래스 전방선언 / 상호참조
	introSecen* intro;

	bool isOption;

	//옵션창 메인프레임
	image* optionFrameImage;
	//X 버튼
	image* optionExitImage;
	image* optionExitOverImage;
	RECT optionExitRc;	
	//비디오 버튼
	image* videoButtonImage;
	image* videoButtonOverImage;
	RECT videoRc;
	//사운드 버튼
	image* soundButtonImage;
	image* soundButtonOverImage;
	RECT soundRc;
	// 콘트롤 버튼
	image* controlsButtonImage;
	image* controlsButtonOverImage;
	RECT controlsRc;
	//캔슬 버튼
	image* cancelButtonImage;
	image* cancelButtonOverImage;
	RECT cancelRc;
	//디폴트 버튼
	image* defaultButtonImage;
	image* defaultButtonOverImage;
	RECT defaultRc;
	//적용버튼
	image* applyButtonImage;
	image* applyButtonOverImage;
	RECT applyRc;

public:


	HRESULT init();
	void release();
	void update();
	void render();
	
	//버튼 충돌 처리 함수
	void buttonImagerRender(RECT _rc, image* _buttonImage, image* _buttonOverImage);
	// 옵션 창 on//off
	bool getIsOption() { return isOption; }
	// 옵션 창 키는거 불러오는 함수
	void setIsOptionOn() { isOption = true; }
	void setIsOptiOff() { isOption = false; }
	image* getOptionFrameImage() { return optionFrameImage; }
	RECT getOptionExitRc() { return optionExitRc; }
	optionUI() {}
	~optionUI() {}
};

