#pragma once
#include "gameNode.h"

#define OPTION_FRAME_WIDTH 1008
#define OPTION_FRAME_HEIGHT 702

#define LEFT_RC_WIDTH 209
#define LEFT_RC_HEIGHT 48


#define BOTTOM_RC_WIDTH 216
#define BOTTOM_RC_HEIGHT 52
//Ŭ���� ���漱�� / ��ȣ����
class introSecen;

class optionUI :	public gameNode
{
private:
	//Ŭ���� ���漱�� / ��ȣ����
	introSecen* intro;

	bool isOption;

	//�ɼ�â ����������
	image* optionFrameImage;
	//X ��ư
	image* optionExitImage;
	image* optionExitOverImage;
	RECT optionExitRc;	
	//���� ��ư
	image* videoButtonImage;
	image* videoButtonOverImage;
	RECT videoRc;
	//���� ��ư
	image* soundButtonImage;
	image* soundButtonOverImage;
	RECT soundRc;
	// ��Ʈ�� ��ư
	image* controlsButtonImage;
	image* controlsButtonOverImage;
	RECT controlsRc;
	//ĵ�� ��ư
	image* cancelButtonImage;
	image* cancelButtonOverImage;
	RECT cancelRc;
	//����Ʈ ��ư
	image* defaultButtonImage;
	image* defaultButtonOverImage;
	RECT defaultRc;
	//�����ư
	image* applyButtonImage;
	image* applyButtonOverImage;
	RECT applyRc;

public:


	HRESULT init();
	void release();
	void update();
	void render();
	
	//��ư �浹 ó�� �Լ�
	void buttonImagerRender(RECT _rc, image* _buttonImage, image* _buttonOverImage);
	// �ɼ� â on//off
	bool getIsOption() { return isOption; }
	// �ɼ� â Ű�°� �ҷ����� �Լ�
	void setIsOptionOn() { isOption = true; }
	void setIsOptiOff() { isOption = false; }
	image* getOptionFrameImage() { return optionFrameImage; }
	RECT getOptionExitRc() { return optionExitRc; }
	optionUI() {}
	~optionUI() {}
};

