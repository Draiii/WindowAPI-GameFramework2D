#include "stdafx.h"
#include "optionUI.h"
#include "introSecen.h"



HRESULT optionUI::init()
{
	//�ɼ� Ű�� �Լ���
	isOption = false;

	optionFrameImage = IMAGEMANAGER->addImage("optionFrame", "image/option/option_frame.bmp", OPTION_FRAME_WIDTH, OPTION_FRAME_HEIGHT);
	//�����ӹ� x , y ����
	optionFrameImage->setX((WINSIZEX - OPTION_FRAME_WIDTH) / 2);
	optionFrameImage->setY((WINSIZEY - OPTION_FRAME_HEIGHT) / 2);
	// X ��ư
	optionExitImage = IMAGEMANAGER->addImage("optionExit", "image/option_button/exit_button.bmp", 40, 40);
	optionExitOverImage = IMAGEMANAGER->addImage("optionExitOver", "image/option_button/exit_button_over.bmp", 40, 40);
	optionExitRc = RectMake(1143, 37, 40, 40);
	//���� ��ư
	videoRc = RectMake(optionFrameImage->getX() + 64, optionFrameImage->getY() + 158, LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	videoButtonImage = IMAGEMANAGER->addImage("videoButton", "image/option_button/video_button.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	videoButtonOverImage = IMAGEMANAGER->addImage("videoButtonOver", "image/option_button/video_button_over.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	//�����ư
	soundRc = RectMake(optionFrameImage->getX() + 64, optionFrameImage->getY() + 158 + LEFT_RC_HEIGHT + 4, LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	soundButtonImage = IMAGEMANAGER->addImage("soundButton", "image/option_button/sound_button.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	soundButtonOverImage = IMAGEMANAGER->addImage("souondButtonOver", "image/option_button/sound_button_over.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	//��Ʈ�� ��ư
	controlsRc = RectMake(optionFrameImage->getX() + 64, optionFrameImage->getY() + 158 + (LEFT_RC_HEIGHT * 2) + 8, LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	controlsButtonImage = IMAGEMANAGER->addImage("controlsButton", "image/option_button/controls_button.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	controlsButtonOverImage = IMAGEMANAGER->addImage("controlsButtonOver", "image/option_button/controls_button_over.bmp", LEFT_RC_WIDTH, LEFT_RC_HEIGHT);
	//ĵ�� ��ư
	cancelRc = RectMake(optionFrameImage->getX() + 176, optionFrameImage->getY() + 586, BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	cancelButtonImage = IMAGEMANAGER->addImage("cancelButton", "image/option_button/cancel_button.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	cancelButtonOverImage = IMAGEMANAGER->addImage("cancelButtonOVer", "image/option_button/cancel_button_over.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	//����Ʈ ��ư
	defaultRc = RectMake(optionFrameImage->getX() + 176+ BOTTOM_RC_WIDTH + 4, optionFrameImage->getY() + 586, BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	defaultButtonImage = IMAGEMANAGER->addImage("defaultButton", "image/option_button/default_button.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	defaultButtonOverImage = IMAGEMANAGER->addImage("defaultButtonOVer", "image/option_button/default_button_over.bmp", BOTTOM_RC_WIDTH, BOTTOM_RC_HEIGHT);
	//���� ��ư
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
		//�ɼ������� ����
		optionFrameImage->render(getMemDC(), (WINSIZEX - OPTION_FRAME_WIDTH) / 2, (WINSIZEY - OPTION_FRAME_HEIGHT) / 2);

		//��ư ��Ʈ
		//Rectangle(getMemDC(), videoRc);
		//Rectangle(getMemDC(), soundRc);
		//Rectangle(getMemDC(), controlsRc);
		//Rectangle(getMemDC(), cancelRc);
		//Rectangle(getMemDC(), defaultRc);
		//Rectangle(getMemDC(), applyRc);
		//Rectangle(getMemDC(), optionExitRc);

		//X ��ư
		this->buttonImagerRender(optionExitRc, optionExitImage, optionExitOverImage);
		//���� ��ư
		this->buttonImagerRender(videoRc, videoButtonImage, videoButtonOverImage);
		//���� ��ư
		this->buttonImagerRender(soundRc, soundButtonImage, soundButtonOverImage);
		//��Ʈ�� ��ư
		this->buttonImagerRender(controlsRc, controlsButtonImage, controlsButtonOverImage);
		//ĵ�� ��ư
		this->buttonImagerRender(cancelRc, cancelButtonImage, cancelButtonOverImage);
		//����Ʈ ��ư
		this->buttonImagerRender(defaultRc, defaultButtonImage, defaultButtonOverImage);
		//���� ��ư
		this->buttonImagerRender(applyRc, applyButtonImage, applyButtonOverImage);		
	}
}
//��ư �浹 ó�� �Լ�
void optionUI::buttonImagerRender(RECT _rc, image * _buttonImage, image * _buttonOverImage)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		_buttonOverImage->render(getMemDC(), _rc.left, _rc.top);
	}
	else _buttonImage->render(getMemDC(), _rc.left, _rc.top);
}


