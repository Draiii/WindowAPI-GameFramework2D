#include "stdafx.h"
#include "introSecen.h"
#include "optionUI.h"

HRESULT introSecen::init()
{
	//��� �̹��� ������ �ʱ�ȭ�Ѵ�
	for (int i = 1; i < INTRO_IMAGE_MAX; i++)
	{
		char str[128];
		sprintf(str, "%02d", i);
		char file[128];		
		sprintf(file, "image/intro/%02d.bmp", i);
		IMAGEMANAGER->addImage(str, file, BACK_IMAGE_WIDTH, BACK_IMAGE_HEIGHT);
	}


	//����̹����� ������ ����ó�� ���������� ����
	nextImageCount = 1;
	nextImageIndex = 1;
	
	//��� �̹��� ���� ��ư
	for (int i = 0; i < INTRO_BUTTON_IMAGE_MAX; i++)
	{
		buttonRc[i] = RectMake(1016, 450 + (i * 55), BUTTON_WIDTH, BUTTON_HEIGHT);
	}
	//�÷��� ��ư on/off 
	isPlay = false;

	//�÷��̹�ư
	playButtonImage = IMAGEMANAGER->addImage("playerButton", "image/intro_button/play_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	playButtonOverImage = IMAGEMANAGER->addImage("playerButtonOver", "image/intro_button/play_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//���ù�ư
	settingButtonImage = IMAGEMANAGER->addImage("settingButton", "image/intro_button/setting_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	settingButtonOverImage = IMAGEMANAGER->addImage("settingButtonOver", "image/intro_button/setting_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//�����ư
	exitButtonImage = IMAGEMANAGER->addImage("exitButton", "image/intro_button/exit_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	exitButtonOverImage = IMAGEMANAGER->addImage("exitButtonOver", "image/intro_button/exit_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//��Ƽ�� ��ư
	continueButtonImage = IMAGEMANAGER->addImage("continueButton", "image/intro_button/continue_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	continueButtonOverImage = IMAGEMANAGER->addImage("continueButtonOver", "image/intro_button/continue_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//������ ��ư
	newGameButtonImage = IMAGEMANAGER->addImage("newGameButton", "image/intro_button/newgame_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	newGameButtonOverImage = IMAGEMANAGER->addImage("newGameButtonOver", "image/intro_button/newgame_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//�� ��ư
	backButtonImage = IMAGEMANAGER->addImage("backButton", "image/intro_button/back_button.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	backButtonOverImage = IMAGEMANAGER->addImage("backButtonOver", "image/intro_button/back_button_over.bmp", BUTTON_WIDTH, BUTTON_HEIGHT);
	//���ӹ�
	nameBarImage = IMAGEMANAGER->addImage("namebar", "image/intro_button/namebar.bmp", 256, 61);


	//�ɼ� Ŭ���� �޸� �Ҵ�
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
	//�ɼ�Ŭ���� ������Ʈ
	optionCss->update();

	//����̹����� ������ ����ó�� ���� ������Ʈ
	nextImageCount++;
	if (nextImageCount % 3 == 0)		
	{
		nextImageIndex++;
		if (nextImageIndex > INTRO_IMAGE_MAX - 1)
		{
			nextImageIndex = 1;
		}		
	}

	//���콺 Ŭ��
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (!isPlay)
		{
			//�÷��� Ŭ����
			if (PtInRect(&buttonRc[0], _ptMouse))
			{
				isPlay = true;
			}
		}
		if (isPlay)
		{
			//������ ���۽� 
			if (PtInRect(&buttonRc[1], _ptMouse))
			{
				SCENEMANAGER->loadScene("dungeon");

				return;
			}
			//BACK Ŭ����
			if (PtInRect(&buttonRc[2], _ptMouse))
			{
				isPlay = false;
			}

		}

		//�ɼ�â ����
		if (!optionCss->getIsOption() && !isPlay)
		{
			if (PtInRect(&buttonRc[1], _ptMouse))
			{
				optionCss->setIsOptionOn();
			}
		}
		//�ɼ�â �ݱ�
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
	//����̹����� ��� �����Ѵ�
	for (int i = 1; i < INTRO_IMAGE_MAX; i++)
	{
		if (nextImageIndex == i)
		{
			char str[10];
			sprintf(str, "%02d", i);
			IMAGEMANAGER->render(str, getMemDC(), 0, 0);
		}
	}

	//��ư RC
	for (int i = 0; i < INTRO_BUTTON_IMAGE_MAX; i++)
	{
		Rectangle(getMemDC(), buttonRc[i]);
		//�÷��̹�ư �ȴ�������
		if (!isPlay)
		{
			//���콺 ��ư �浹
			if (PtInRect(&buttonRc[0], _ptMouse))
			{
				//�÷���
				playButtonOverImage->render(getMemDC(), buttonRc[0].left, buttonRc[0].top);
			}
			else if (!PtInRect(&buttonRc[0], _ptMouse))
			{
				//�÷���
				playButtonImage->render(getMemDC(), buttonRc[0].left, buttonRc[0].top);
			}
			if (PtInRect(&buttonRc[1], _ptMouse))
			{
				//����
				settingButtonOverImage->render(getMemDC(), buttonRc[1].left, buttonRc[1].top);
			}
			else if (!PtInRect(&buttonRc[1], _ptMouse))
			{
				//����
				settingButtonImage->render(getMemDC(), buttonRc[1].left, buttonRc[1].top);
			}
			if (PtInRect(&buttonRc[2], _ptMouse))
			{
				//����
				exitButtonOverImage->render(getMemDC(), buttonRc[2].left, buttonRc[2].top);
			}
			else if (!PtInRect(&buttonRc[2], _ptMouse))
			{
				//����
				exitButtonImage->render(getMemDC(), buttonRc[2].left, buttonRc[2].top);
			}

		}
		//�÷��̹�ư ��������
		else
		{
			//���콺 ��ư �浹
			if (PtInRect(&buttonRc[0], _ptMouse))
			{
				//��Ƽ��
				continueButtonOverImage->render(getMemDC(), buttonRc[0].left, buttonRc[0].top);
			}
			else if (!PtInRect(&buttonRc[0], _ptMouse))
			{
				//��Ƽ��
				continueButtonImage->render(getMemDC(), buttonRc[0].left, buttonRc[0].top);
			}
			if (PtInRect(&buttonRc[1], _ptMouse))
			{
				//������
				newGameButtonOverImage->render(getMemDC(), buttonRc[1].left, buttonRc[1].top);
			}
			else if (!PtInRect(&buttonRc[1], _ptMouse))
			{
				//������
				newGameButtonImage->render(getMemDC(), buttonRc[1].left, buttonRc[1].top);
			}
			if (PtInRect(&buttonRc[2], _ptMouse))
			{
				//��
				backButtonOverImage->render(getMemDC(), buttonRc[2].left, buttonRc[2].top);
			}
			else if (!PtInRect(&buttonRc[2], _ptMouse))
			{
				//��
				backButtonImage->render(getMemDC(), buttonRc[2].left, buttonRc[2].top);
			}
		}
	}
	//���ӹ� ����
	nameBarImage->render(getMemDC(), 1014, 639);

	//�ɼ�â ����
	if (optionCss->getIsOption())
	{
		optionCss->render();
	}

	TextOut(getMemDC(), 50, 50, "�ƾƾƾ�", strlen("�ƾƾƾ�"));

	//TextOut(getMemDC(), WINSIZEX / 2 - 300, 230, "�� ���¿� �ڵ����ؼ� ������", strlen("�� ���¿� �ڵ����ؼ� ������"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 330, 250, "�̰� ����! �̰�... �����...! This~ Is~ Me...", strlen("�̰� ����! �̰�... �����...! This~ Is~ Me..."));
	//TextOut(getMemDC(), WINSIZEX / 2 - 230, 290, "����", strlen("����"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 250, 310, "����", strlen("����"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 280, 320, "����", strlen("����"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 300, 330, "����", strlen("����"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 200, 290, "����", strlen("����"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 180, 310, "����", strlen("����"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 160, 320, "����", strlen("����"));
	//TextOut(getMemDC(), WINSIZEX / 2 - 140, 330, "����", strlen("����"));

}