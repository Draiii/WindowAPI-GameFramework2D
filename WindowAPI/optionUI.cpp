#include "stdafx.h"
#include "optionUI.h"
#include "introSecen.h"



HRESULT optionUI::init()
{
	//옵션 키는 함수임
	isOption = false;

	optionFrameImage = IMAGEMANAGER->addImage("optionFrame", "image/option/option_frame.bmp", OPTION_FRAME_WIDTH, OPTION_FRAME_HEIGHT);
	//프레임바 x , y 설정
	optionFrameImage->setX((WINSIZEX - OPTION_FRAME_WIDTH) / 2);
	optionFrameImage->setY((WINSIZEY - OPTION_FRAME_HEIGHT) / 2);
	// X 버튼
	optionExitImage = IMAGEMANAGER->addImage("optionExit", "image/option_button/exit_button.bmp", 40, 40);
	optionExitOverImage = IMAGEMANAGER->addImage("optionExitOver", "image/option_button/exit_button_over.bmp", 40, 40);
	optionExitRc = RectMake(1143, 37, 40, 40);
	//비디오 버튼
	videoRc = RectMake(optionFrameImage->getX() + 64, optionFrameImage->getY() + 158, LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	videoButtonImage = IMAGEMANAGER->addImage("videoButton", "image/option_button/video_button.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	videoButtonOverImage = IMAGEMANAGER->addImage("videoButtonOver", "image/option_button/video_button_over.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	//사운드버튼
	soundRc = RectMake(optionFrameImage->getX() + 64, optionFrameImage->getY() + 158 + LEFT_RC_HEIGHT + 4, LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	soundButtonImage = IMAGEMANAGER->addImage("soundButton", "image/option_button/sound_button.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	soundButtonOverImage = IMAGEMANAGER->addImage("souondButtonOver", "image/option_button/sound_button_over.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	//콘트롤 버튼
	controlsRc = RectMake(optionFrameImage->getX() + 64, optionFrameImage->getY() + 158 + (LEFT_RC_HEIGHT * 2) + 8, LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	controlsButtonImage = IMAGEMANAGER->addImage("controlsButton", "image/option_button/controls_button.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	controlsButtonOverImage = IMAGEMANAGER->addImage("controlsButtonOver", "image/option_button/controls_button_over.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	//캔슬 버튼
	cancelRc = RectMake(optionFrameImage->getX() + 176, optionFrameImage->getY() + 586, BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	cancelButtonImage = IMAGEMANAGER->addImage("cancelButton", "image/option_button/cancel_button.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	cancelButtonOverImage = IMAGEMANAGER->addImage("cancelButtonOVer", "image/option_button/cancel_button_over.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	//디폴트 버튼
	defaultRc = RectMake(optionFrameImage->getX() + 176+ BOTTOM_RC_WIDTH + 4, optionFrameImage->getY() + 586, BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	defaultButtonImage = IMAGEMANAGER->addImage("defaultButton", "image/option_button/default_button.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	defaultButtonOverImage = IMAGEMANAGER->addImage("defaultButtonOVer", "image/option_button/default_button_over.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	//적용 버튼
	applyRc = RectMake(optionFrameImage->getX() + 176 + (BOTTOM_RC_WIDTH * 2) + 8, optionFrameImage->getY() + 586, BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	applyButtonImage = IMAGEMANAGER->addImage("applyButton", "image/option_button/apply_button.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	applyButtonOverImage = IMAGEMANAGER->addImage("applyButtonOVer", "image/option_button/apply_button_over.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);

	return S_OK;
}

void optionUI::release()
{	
}

void optionUI::update()
{

}

void optionUI::render()
{
	if (isOption)
	{
		//옵션프레임 렌더
		optionFrameImage->render(getMemDC(), (WINSIZEX - OPTION_FRAME_WIDTH) / 2, (WINSIZEY - OPTION_FRAME_HEIGHT) / 2);

		//버튼 렉트
		//Rectangle(getMemDC(), videoRc);
		//Rectangle(getMemDC(), soundRc);
		//Rectangle(getMemDC(), controlsRc);
		//Rectangle(getMemDC(), cancelRc);
		//Rectangle(getMemDC(), defaultRc);
		//Rectangle(getMemDC(), applyRc);
		//Rectangle(getMemDC(), optionExitRc);

		//X 버튼
		this->buttonImagerRender(optionExitRc, optionExitImage, optionExitOverImage);
		//비디오 버튼
		this->buttonImagerRender(videoRc, videoButtonImage, videoButtonOverImage);
		//사운드 버튼
		this->buttonImagerRender(soundRc, soundButtonImage, soundButtonOverImage);
		//콘트롤 버튼
		this->buttonImagerRender(controlsRc, controlsButtonImage, controlsButtonOverImage);
		//캔슬 버튼
		this->buttonImagerRender(cancelRc, cancelButtonImage, cancelButtonOverImage);
		//디폴트 버튼
		this->buttonImagerRender(defaultRc, defaultButtonImage, defaultButtonOverImage);
		//적용 버튼
		this->buttonImagerRender(applyRc, applyButtonImage, applyButtonOverImage);		
	}
}
//버튼 충돌 처리 함수
void optionUI::buttonImagerRender(RECT _rc, image * _buttonImage, image * _buttonOverImage)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		_buttonOverImage->render(getMemDC(), _rc.left, _rc.top);
	}
	else _buttonImage->render(getMemDC(), _rc.left, _rc.top);
}


