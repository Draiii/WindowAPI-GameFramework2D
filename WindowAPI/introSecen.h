#pragma once
#include "gameNode.h"


#define INTRO_IMAGE_MAX 71
#define BACK_IMAGE_WIDTH 1366
#define BACK_IMAGE_HEIGHT 768
#define INTRO_BUTTON_IMAGE_MAX 3
#define BUTTON_WIDTH 255
#define BUTTON_HEIGHT 52
//Ŭ���� ���漱�� / ��ȣ����
class optionUI;


class introSecen :	public gameNode
{
private:
	//Ŭ���� ���漱�� / ��ȣ����
	optionUI* optionCss;

	int nextImageCount;
	int nextImageIndex;
	RECT buttonRc[3];

	//�÷��̹�ư
	image* playButtonImage;
	image* playButtonOverImage;
	//���ù�ư
	image* settingButtonImage;
	image* settingButtonOverImage;
	//�����ư
	image* exitButtonImage;
	image* exitButtonOverImage;
	//�÷��̹�ư ��������
	bool isPlay;


	//��Ƽ�� ��ư
	image* continueButtonImage;
	image* continueButtonOverImage;
	//������ ��ư
	image* newGameButtonImage;
	image* newGameButtonOverImage;
	//�� ��ư
	image* backButtonImage;
	image* backButtonOverImage;

	//���ӹ�
	image* nameBarImage;

public:

	HRESULT init();
	void release();
	void update();
	void render();


	

	introSecen() {}
	~introSecen() {}
};

