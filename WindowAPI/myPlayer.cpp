#include "stdafx.h"
#include "myPlayer.h"
#include "dungeonSecen.h"



HRESULT myPlayer::init()
{
	
	//�÷��̾� �ʱ�ȭ

	player.direction = PLAYER_RIGTH;
	statusFrameIsOn = false;
	invenFrameIsOn = false;
	skillFrameIsOn = false;
	player.timer = GetTickCount64();
	//player.x = TILE_WIDTH * 10 / 2;
	//player.y = TILE_HEIGHT * 10 / 2;
	player.x = PLAYER_INIT_X;
	player.y = PLAYER_INIT_Y;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			player.attackRc[i * 3 + j] = RectMake((player.x - TILE_WIDTH) + j * TILE_WIDTH, (player.y - TILE_HEIGHT) + i * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
			player.attackDirection[i * 3 + j] = false;
		}		
	}
	player.rc = RectMake(player.x, player.y, TILE_WIDTH, TILE_HEIGHT);
	player.img = IMAGEMANAGER->addFrameImage("playerIdle", "image/player/player.bmp", 104, PLAYER_IMAGE_HEIGHT, 2, 1, true, RGB(255, 0, 255));
	player.shadowImg = IMAGEMANAGER->addFrameImage("playerShadowIdle", "image/player/player_shadow.bmp", 104, PLAYER_IMAGE_HEIGHT, 2, 1, true, RGB(255, 0, 255));
	player.attackImg = IMAGEMANAGER->addFrameImage("attack", "image/player/attack.bmp", 208, 104, 4, 2, true, RGB(255, 0, 255));
	player.attackCount = player.attackIndex = 0;
	playerStatusFrameBackImage = IMAGEMANAGER->addImage("playerStatusFrameBack", "image/player/player_status_back.bmp", PLAYER_INVEN_WIDTH, PLAYER_INVEN_HEIGHT);
	//����â
	playerStatusFrameImage = IMAGEMANAGER->addImage("playerStatusFrame", "image/player/player_status_1.bmp", PLAYER_INVEN_WIDTH, PLAYER_INVEN_HEIGHT, true, RGB(255, 0, 255));
	playerStatusFrameImage->setX(2);
	playerStatusFrameImage->setY(2);
	//����â ���� ��ư RC//�̹���
	playerStatusFrameExitRc = RectMake(playerStatusFrameImage->getX() + 638, playerStatusFrameImage->getY() + 2, 40, 40);
	playerStatusFrameExitOverImage = IMAGEMANAGER->addImage("playerStatusFrameExitOver", "image/option_button/exit_button_over.bmp", 40, 40);

	//�Ĺ� ���� ���� ��Ʈ
	combatStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338, 30, 30);
	combatStatus.selectImage = IMAGEMANAGER->addImage("selectCombat", "image/player/player_status_combat_bar.bmp", 532, 42);
	combatStatus.infoImage = IMAGEMANAGER->addImage("infoCombat", "image/player/combat_info.bmp", 540, 284);
	combatStatus.isClick = false;
	combatStatus.scroll = 0;

	//���� ���� ���� ��Ʈ
	magicStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338 + 42 + 4, 30, 30);
	magicStatus.selectImage = IMAGEMANAGER->addImage("selectMagic", "image/player/player_status_magic_bar.bmp", 532, 42);
	magicStatus.infoImage = IMAGEMANAGER->addImage("infoMagic", "image/player/magic_info.bmp", 540, 140);
	magicStatus.isClick = false;
	magicStatus.scroll = 0;
	//���� ���� ���� ��Ʈ
	resStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338 + 84 + 8, 30, 30);
	resStatus.selectImage = IMAGEMANAGER->addImage("selectRes", "image/player/player_status_res_bar.bmp", 532, 42);
	resStatus.infoImage = IMAGEMANAGER->addImage("infoRes", "image/player/res_info.bmp", 540, 140);
	resStatus.isClick = false;
	resStatus.scroll = 0;
	//����â ��ũ��


	//��ųâ 
	playerSkillWindowImage = IMAGEMANAGER->addImage("playerSkillFrame", "image/player/player_skill_frame.bmp", PLAYER_INVEN_WIDTH, PLAYER_INVEN_HEIGHT);
	playerSkillWindowImage->setX(WINSIZEX - PLAYER_INVEN_WIDTH - 2);
	playerSkillWindowImage->setY(2);

	//��ųâ//�κ�â ���� ��ư RC//�̹���
	playerSkillWindowExitRc = RectMake(playerSkillWindowImage->getX() + 638, playerSkillWindowImage->getY() + 2, 40, 40);
	playerSkillWindowExitOverImage = IMAGEMANAGER->addImage("playerSkillWindowExitOver", "image/option_button/exit_button_over.bmp", 40, 40);

	//��ųâ Ÿ��
	playerSkillTypeFrameImage = IMAGEMANAGER->addImage("playerSkillTypeFrame", "image/player/skills/player_skill_type_frame.bmp", PLAYER_SKILL_TYPE_WIDTH, PLAYER_SKILL_TYPE_HEIGHT);

	//��ų ��Ʈ ���콺 ����
	skillsRectOverImage = IMAGEMANAGER->addImage("skillOver", "image/player/skills/rectover.bmp", SKILL_FRAME_WIDTH, SKILL_FRAME_HEIGHT, true, RGB(255, 0, 255));


	//��ųâ Ÿ�� ��Ʈ
	playerSkillTypeImage[0] = IMAGEMANAGER->addFrameImage("�ҵ�Ÿ��", "image/player/skills/swords.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//�ҵ�
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[0].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("�ҵ��Ƽ��", "image/player/skills/swords/swords_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[0].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("�ҵ��нú�", "image/player/skills/swords/swords_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[0].SkillActiveExImage = IMAGEMANAGER->addImage("�ҵ��Ƽ�꼳��", "image/player/skills/swords/skills_explain_swords_active.bmp", 444, 326);
	playerSkills[0].SkillPassiveExImage = IMAGEMANAGER->addImage("�ҵ��нú꼳��", "image/player/skills/swords/skills_explain_swords_passive.bmp", 444, 222);

	playerSkillTypeImage[1] = IMAGEMANAGER->addFrameImage("����Ÿ��", "image/player/skills/axes.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//����
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[1].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("������Ƽ��", "image/player/skills/axes/axes_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[1].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("�����нú�", "image/player/skills/axes/axes_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[1].SkillActiveExImage = IMAGEMANAGER->addImage("������Ƽ�꼳��", "image/player/skills/axes/skills_explain_axes_active.bmp", 444, 326);
	playerSkills[1].SkillPassiveExImage = IMAGEMANAGER->addImage("�����нú꼳��", "image/player/skills/axes/skills_explain_axes_passive.bmp", 444, 222);

	playerSkillTypeImage[2] = IMAGEMANAGER->addFrameImage("���̽�Ÿ��", "image/player/skills/maces.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//���̽�
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[2].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("���̽���Ƽ��", "image/player/skills/maces/maces_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[2].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("���̽��нú�", "image/player/skills/maces/maces_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[2].SkillActiveExImage = IMAGEMANAGER->addImage("���̽���Ƽ�꼳��", "image/player/skills/maces/skills_explain_maces_active.bmp", 444, 326);
	playerSkills[2].SkillPassiveExImage = IMAGEMANAGER->addImage("���̽��нú꼳��", "image/player/skills/maces/skills_explain_maces_passive.bmp", 444, 222);

	playerSkillTypeImage[3] = IMAGEMANAGER->addFrameImage("���Ÿ��", "image/player/skills/daggers.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//���
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[3].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("��ž�Ƽ��", "image/player/skills/daggers/daggers_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[3].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("����нú�", "image/player/skills/daggers/daggers_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[3].SkillActiveExImage = IMAGEMANAGER->addImage("��ž�Ƽ�꼳��", "image/player/skills/daggers/skills_explain_daggers_active.bmp", 444, 326);
	playerSkills[3].SkillPassiveExImage = IMAGEMANAGER->addImage("����нú꼳��", "image/player/skills/daggers/skills_explain_daggers_passive.bmp", 444, 222);

	playerSkillTypeImage[4] = IMAGEMANAGER->addFrameImage("�׷���Ʈ�ҵ�Ÿ��", "image/player/skills/greatswords.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//�׷���Ʈ�ҵ�
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[4].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("�׷���Ʈ�ҵ��Ƽ��", "image/player/skills/greatswords/greatswords_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[4].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("�׷���Ʈ�ҵ��нú�", "image/player/skills/greatswords/greatswords_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[4].SkillActiveExImage = IMAGEMANAGER->addImage("�׷���Ʈ�ҵ��Ƽ�꼳��", "image/player/skills/greatswords/skills_explain_greatswords_active.bmp", 444, 326);
	playerSkills[4].SkillPassiveExImage = IMAGEMANAGER->addImage("�׷���Ʈ�ҵ��нú꼳��", "image/player/skills/greatswords/skills_explain_greatswords_passive.bmp", 444, 222);

	playerSkillTypeImage[5] = IMAGEMANAGER->addFrameImage("����Ÿ��", "image/player/skills/bows.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//����
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[5].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("�����Ƽ��", "image/player/skills/bows/bows_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[5].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("�����нú�", "image/player/skills/bows/bows_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[5].SkillActiveExImage = IMAGEMANAGER->addImage("�����Ƽ�꼳��", "image/player/skills/bows/skills_explain_bows_active.bmp", 444, 326);
	playerSkills[5].SkillPassiveExImage = IMAGEMANAGER->addImage("�����нú꼳��", "image/player/skills/bows/skills_explain_bows_passive.bmp", 444, 222)
		;
	playerSkillTypeImage[6] = IMAGEMANAGER->addFrameImage("����Ÿ��", "image/player/skills/shields.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//����
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[6].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("�����Ƽ��", "image/player/skills/shields/shields_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[6].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("�����нú�", "image/player/skills/shields/shields_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[6].SkillActiveExImage = IMAGEMANAGER->addImage("�����Ƽ�꼳��", "image/player/skills/shields/skills_explain_shields_active.bmp", 444, 326);
	playerSkills[6].SkillPassiveExImage = IMAGEMANAGER->addImage("�����нú꼳��", "image/player/skills/shields/skills_explain_shields_passive.bmp", 444, 222);

	playerSkillTypeImage[7] = IMAGEMANAGER->addFrameImage("Ŭ������ƿ", "image/player/skills/classskills.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//Ŭ������ų
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[7].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("Ŭ������ƿ��Ƽ��", "image/player/skills/classskills/classskills_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[7].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("Ŭ������ƿ�нú�", "image/player/skills/classskills/classskills_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[7].SkillActiveExImage = IMAGEMANAGER->addImage("Ŭ������ƿ��Ƽ�꼳��", "image/player/skills/classskills/skills_explain_classskills_active.bmp", 444, 326);
	playerSkills[7].SkillPassiveExImage = IMAGEMANAGER->addImage("Ŭ������ƿ�нú꼳��", "image/player/skills/classskills/skills_explain_classskills_passive.bmp", 444, 222);

	playerSkillTypeImage[8] = IMAGEMANAGER->addFrameImage("��������ƿ", "image/player/skills/basicskills.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//��������ų
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[8].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("��������ƿ��Ƽ��", "image/player/skills/basicskills/basicskills_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[8].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("��������ƿ�нú�", "image/player/skills/basicskills/basicskills_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[8].SkillActiveExImage = IMAGEMANAGER->addImage("��������ƿ��Ƽ�꼳��", "image/player/skills/basicskills/skills_explain_basicskills_active.bmp", 444, 326);
	playerSkills[8].SkillPassiveExImage = IMAGEMANAGER->addImage("��������ƿ�нú꼳��", "image/player/skills/basicskills/skills_explain_basicskills_passive.bmp", 444, 222);

	playerSkillTypeImage[9] = IMAGEMANAGER->addFrameImage("�Ƹ���ƿ", "image/player/skills/armor.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//�Ƹ�
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[9].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("�Ƹ���ƿ��Ƽ��", "image/player/skills/armor/armor_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[9].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("�Ƹ���ƿ�нú�", "image/player/skills/armor/armor_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[9].SkillActiveExImage = IMAGEMANAGER->addImage("�Ƹ���ƿ��Ƽ�꼳��", "image/player/skills/armor/skills_explain_armor_active.bmp", 444, 326);
	playerSkills[9].SkillPassiveExImage = IMAGEMANAGER->addImage("�Ƹ���ƿ�нú꼳��", "image/player/skills/armor/skills_explain_armor_passive.bmp", 444, 222);

	playerSkillTypeImage[10] = IMAGEMANAGER->addFrameImage("�����ƿ", "image/player/skills/dualwielding.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//���
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[10].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("�����ƿ��Ƽ��", "image/player/skills/dualwielding/dualwielding_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[10].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("�����ƿ�нú�", "image/player/skills/dualwielding/dualwielding_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[10].SkillActiveExImage = IMAGEMANAGER->addImage("�����ƿ��Ƽ�꼳��", "image/player/skills/dualwielding/skills_explain_dualwielding_active.bmp", 444, 326);
	playerSkills[10].SkillPassiveExImage = IMAGEMANAGER->addImage("�����ƿ�нú꼳��", "image/player/skills/dualwielding/skills_explain_dualwielding_passive.bmp", 444, 222);

	playerSkillTypeImage[11] = IMAGEMANAGER->addFrameImage("ġ����ƿ", "image/player/skills/medicine.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//ġ��
	//��Ƽ��/�нú� ��ų �̹���
	playerSkills[11].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("ġ����ƿ��Ƽ��", "image/player/skills/medicine/medicine_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[11].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("ġ����ƿ�нú�", "image/player/skills/medicine/medicine_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[11].SkillActiveExImage = IMAGEMANAGER->addImage("ġ����ƿ��Ƽ�꼳��", "image/player/skills/medicine/skills_explain_medicine_active.bmp", 444, 326);
	playerSkills[11].SkillPassiveExImage = IMAGEMANAGER->addImage("ġ����ƿ�нú꼳��", "image/player/skills/medicine/skills_explain_medicine_passive.bmp", 444, 222);
	//��ų Ÿ�� ��Ʈ
	for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
	{	
		//��ųŸ�� �� ��
		playerSkillTypeIstouch[i] = false;
		playerSkills[i].learnActive = NONE_ACTIVE;
		playerSkills[i].learnPassive = NONE_PASSIVE;
		int num = 48;
		if (i > 6) playerSkillTypeSelectRc[i] = RectMake(playerSkillWindowImage->getX() + 62, playerSkillWindowImage->getY() + 157 + num + (i * 25) + (i * 3), PLAYER_SKILL_TYPE_SELECT_WIDTH, PLAYER_SKILL_TYPE_SELECT_HEIGHT);
		else playerSkillTypeSelectRc[i] = RectMake(playerSkillWindowImage->getX() + 62, playerSkillWindowImage->getY() + 157 + (i * 25) + (i * 3), PLAYER_SKILL_TYPE_SELECT_WIDTH, PLAYER_SKILL_TYPE_SELECT_HEIGHT);
	}
	//��Ƽ��/�нú� ��ų ��Ʈ
	activeSkillRc = RectMake(playerSkillWindowImage->getX() + 408, playerSkillWindowImage->getY() + 194, SKILL_FRAME_WIDTH, SKILL_FRAME_HEIGHT);
	passiveSkillRc = RectMake(playerSkillWindowImage->getX() + 514, playerSkillWindowImage->getY() + 194, SKILL_FRAME_WIDTH, SKILL_FRAME_HEIGHT);



	
	
	//�κ�
	playerInvenFrameImage = IMAGEMANAGER->addImage("playerInvenFrame", "image/player/player_inven.bmp", PLAYER_INVEN_WIDTH, PLAYER_INVEN_HEIGHT);
	playerInvenFrameImage->setX(WINSIZEX - PLAYER_INVEN_WIDTH - 2);
	playerInvenFrameImage->setY(2);
	
	//�κ��丮 ��Ʈ �ʱ�ȭ
	for (int i = 0; i < INVEN_RECT_Y; i++)
	{
		for (int j = 0; j < INVEN_RECT_X; j++)
		{
			invenRc[i][j].width = invenRc[i][j].height = TILE_WIDTH;
			invenRc[i][j].IdY = i;
			invenRc[i][j].idX = j;
			invenRc[i][j].x = playerInvenFrameImage->getX() + 72 + (j * TILE_WIDTH) + (j * 2);
			invenRc[i][j].y = playerInvenFrameImage->getY() + 336 + (i * TILE_HEIGHT) + (i * 2);
			invenRc[i][j].rc = RectMake(invenRc[i][j].x, invenRc[i][j].y, TILE_WIDTH, TILE_HEIGHT);
		}
	}
	//����EQUIP_RECT
	weaponEquipRc = RectMake(playerInvenFrameImage->getX() + 74, playerInvenFrameImage->getY() + 112, ALL_EQUIP_WIDTH, WEAPON_EQUIP_HEIGHT);
	//����EQUIP_RECT
	shieldEquipRc = RectMake(playerInvenFrameImage->getX() + 504, playerInvenFrameImage->getY() + 112, ALL_EQUIP_WIDTH, SHIELD_EQUIP_HEIGHT);
	//�Ƹ�EQUIP_RECT
	armorEquipRc = RectMake(playerInvenFrameImage->getX() + 194, playerInvenFrameImage->getY() + 164, ALL_EQUIP_WIDTH, ARMOR_EQUIP_HEIGHT);
	//����EQUIP_RECT
	helmetEquipRc = RectMake(playerInvenFrameImage->getX() + 194, playerInvenFrameImage->getY() + 56, ALL_EQUIP_WIDTH, HELMET_EQUIP_HEIGHT);
	//�尩EQUIP_RECT
	gloveEquipRc = RectMake(playerInvenFrameImage->getX() + 384, playerInvenFrameImage->getY() + 56, ALL_EQUIP_WIDTH, GLOVE_EQUIP_HEIGHT);
	//����EQUIP_RECT
	bootEquipRc = RectMake(playerInvenFrameImage->getX() + 384, playerInvenFrameImage->getY() + 218, ALL_EQUIP_WIDTH, BOOT_EQUIP_HEIGHT);
	//��ƮEQUIP_RECT
	beltEquipRc = RectMake(playerInvenFrameImage->getX() + 384, playerInvenFrameImage->getY() + 164, ALL_EQUIP_WIDTH, BELT_EQUIP_HEIGHT);

	//�����EQUIP_RECT
	necklaceEquipRc = RectMake(playerInvenFrameImage->getX() + 316, playerInvenFrameImage->getY() + 102, ACC_EQUIP_WIDTH, ACC_EQUIP_HEIGHT);
	//����(��)EQUIP_RECT
	leftRingEquipRc = RectMake(playerInvenFrameImage->getX() + 316, playerInvenFrameImage->getY() + 166, ACC_EQUIP_WIDTH, ACC_EQUIP_HEIGHT);
	//����(����)EQUIP_RECT
	rightRingEquipRc = RectMake(playerInvenFrameImage->getX() + 316, playerInvenFrameImage->getY() + 230, ACC_EQUIP_WIDTH, ACC_EQUIP_HEIGHT);

	//�ϴܹ�
	playerUIImage = IMAGEMANAGER->addImage("playerUI", "image/player/player_UI.bmp", PLAYER_UI_IMAGE_WIDTH, PLAYER_UI_IMAGE_HEIGTH, true, RGB(255, 0, 255));

	
	return S_OK;
}

void myPlayer::release()
{
}

void myPlayer::update()
{
	//�÷��̾� ��Ʈ ������Ʈ
	player.rc = RectMake(player.x, player.y, TILE_WIDTH, TILE_HEIGHT);
	//�÷��̾� ���� ������Ʈ
	if (player.direction == PLAYER_RIGTH)
	{
		player.img->setFrameX(PLAYER_RIGTH);
		player.shadowImg->setFrameX(PLAYER_RIGTH);
	}
	if (player.direction == PLAYER_LEFT)
	{
		player.img->setFrameX(PLAYER_LEFT);
		player.shadowImg->setFrameX(PLAYER_LEFT);
	}

	//�Ĺ� ���� ���� ��Ʈ
	combatStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338, 30, 30);
	//���� ���� ���� ��Ʈ
	magicStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338 + 42 + 4 + combatStatus.scroll, 30, 30);
	//���� ���� ���� ��Ʈ
	resStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338 + 84 + 8 + combatStatus.scroll + magicStatus.scroll, 30, 30);

	if (combatStatus.isClick) combatStatus.scroll = 284;
	else  combatStatus.scroll = 0;
	if (magicStatus.isClick) magicStatus.scroll = 140;
	else  magicStatus.scroll = 0;

	//�÷��̾� �̹����� ���Ÿ�������Ʈ
	//�̳ѹ����� ����Ʈ ����Ʈ ž ���� ����




		

	


	//ĳ���� ����â ����
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (!statusFrameIsOn) statusFrameIsOn = true;		
		else statusFrameIsOn = false;
	}
	//ĳ���� �κ��丮 ����
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (!invenFrameIsOn) invenFrameIsOn = true;
		else invenFrameIsOn = false;
	}
	//ĳ���� ��ųâ ����
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!skillFrameIsOn) skillFrameIsOn = true;
		else skillFrameIsOn = false;
	}
	






	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//��â�� ���� ��ư
		if (PtInRect(&playerStatusFrameExitRc, _ptMouse) && statusFrameIsOn) statusFrameIsOn = false;
		if (PtInRect(&playerSkillWindowExitRc, _ptMouse) && invenFrameIsOn) invenFrameIsOn = false;
		if (PtInRect(&playerSkillWindowExitRc, _ptMouse) && skillFrameIsOn) skillFrameIsOn = false;

		//����â���� �Ĺ� ���� ����
		if (PtInRect(&combatStatus.rc, _ptMouse))
		{
			if (combatStatus.isClick) combatStatus.isClick = false;
			else combatStatus.isClick = true;

		
		}
		//����â���� ���� ���� ����
		if (PtInRect(&magicStatus.rc, _ptMouse))
		{
			if (magicStatus.isClick) magicStatus.isClick = false;
			else magicStatus.isClick = true;
		}
		//����â���� ���� ���� ����
		if (PtInRect(&resStatus.rc, _ptMouse))
		{
			if (resStatus.isClick) resStatus.isClick = false;
			else resStatus.isClick = true;
		}
		
		//��ų Ÿ�� Ŭ���� Ʈ��� ����
		for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
		{
			if (PtInRect(&playerSkillTypeSelectRc[i], _ptMouse))
			{
				for (int j = 0; j < PLAYER_SKILL_TYPE_MAX; j++)
				{
					//��ų Ÿ�� �� �޽��϶�	
					//���� ���� Ȯ���ϰ� �ؽ�Ʈ �� �ٲٱ�
					playerSkillTypeIstouch[j] = false;
					playerSkillTypeImage[j]->setFrameY(0);
				}
				//��ų Ÿ�� �� Ʈ���϶�	
				//���� ���� Ȯ���ϰ� �ؽ�Ʈ �� �ٲٱ�
				playerSkillTypeIstouch[i] = true;
							
			}

			//�׽�Ʈ�� ��ų ����
			if (PtInRect(&activeSkillRc, _ptMouse))
			{
				if (playerSkillTypeIstouch[i])
				{
					playerSkills[i].learnActive = GET_ACTIVE;						
				}
			}
			if (PtInRect(&passiveSkillRc, _ptMouse))
			{
				if (playerSkillTypeIstouch[i])
				{
					playerSkills[i].learnPassive = GET_PASSIVE;
				}
			}
		}
	}
	//��ų Ÿ�� �� Ʈ���϶�	
    //���� ���� Ȯ���ϰ� �ؽ�Ʈ �� �ٲٱ�
	for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
	{
		if (playerSkillTypeIstouch[i]) playerSkillTypeImage[i]->setFrameY(2);				
	}	
	
}

void myPlayer::render()
{	

}

//���â ��Ʈ ��ĥ�ϱ�
void myPlayer::ptInGreenRect(RECT _rc)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(20, 160, 20));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		Rectangle(getMemDC(), _rc);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myBrush);
	}
}

//��ų Ÿ�� ���콺 ����
void myPlayer::selectSkillTypeMover(int _i)
{
	if (PtInRect(&playerSkillTypeSelectRc[_i], _ptMouse))
	{		
		playerSkillTypeImage[_i]->setFrameY(1);
	}
	else if (playerSkillTypeImage[_i]->getFrameY() < 2 )
	{
		playerSkillTypeImage[_i]->setFrameY(0);
	}	
}
//��ųŸ�Կ� �°� ��Ƽ��/�нú�/���� �����ϱ�
void myPlayer::skillsWindow(int _i)
{
	for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
	{
		//��ųŸ�Կ� �°� ��Ƽ��/�нú�/���� �����ϱ�
		if (playerSkillTypeIstouch[_i])
		{
			if (playerSkills[_i].learnActive == NONE_ACTIVE) playerSkills[_i].WindowFrameActiveImage->setFrameY(NONE_ACTIVE);			
			if (playerSkills[_i].learnActive == GET_ACTIVE) playerSkills[_i].WindowFrameActiveImage->setFrameY(GET_ACTIVE);
			if (playerSkills[_i].learnPassive == NONE_PASSIVE) playerSkills[_i].WindowFramePassiveImage->setFrameY(NONE_PASSIVE);
			if (playerSkills[_i].learnPassive == GET_PASSIVE) playerSkills[_i].WindowFramePassiveImage->setFrameY(GET_PASSIVE);		
			playerSkills[_i].WindowFrameActiveImage->frameRender(getMemDC(), activeSkillRc.left, activeSkillRc.top);
			playerSkills[_i].WindowFramePassiveImage->frameRender(getMemDC(), passiveSkillRc.left, passiveSkillRc.top);
		}
	}
}


//�÷��̾� �̹��� ���� �Լ�
void myPlayer::playerImageRender(tagPlayer _player)
{
#define WAVE_SPEED 0.1f
#define WAVE_AREA 2.0f
	//���̺� �¿�
	enum wavingH
	{
		LEFT, RIGHT
	};
	_player.shadowImg->setX(_player.rc.left);
	_player.shadowImg->setY(_player.rc.top);

	_player.img->setX(_player.rc.left);
	_player.img->setY(_player.rc.top);

	static float wavingH = RIGHT;

	static float moveX = 0;
	static float moveY = 0;
	
	if (wavingH == RIGHT)
	{
		if (moveX <= 0)
			moveY -= WAVE_SPEED * 2;
		else
			moveY += WAVE_SPEED * 2;
		
		moveX += WAVE_SPEED;
		if (moveX > WAVE_AREA)
		{
			//moveY = 0;
			//moveX = 0.0f;
			wavingH = LEFT;
		}
	}
	if (wavingH == LEFT)
	{
		if (moveX >= 0)
			moveY -= WAVE_SPEED * 2;
		else
			moveY += WAVE_SPEED * 2;

		moveX -= WAVE_SPEED;
		if (moveX < -WAVE_AREA)
		{
			//moveY = 0;
			//moveX = 0.0f;
			wavingH = RIGHT;
		}
	}

	//�׸���
	_player.shadowImg->setX(_player.img->getX() + moveX);
	_player.shadowImg->setY(_player.img->getY() + moveY);
	//�÷��̾�
	_player.img->setX(_player.img->getX() + moveX);
	_player.img->setY(_player.img->getY() + moveY);
	//��Ʈ
	//Rectangle(getMemDC(), _player.rc);
	//for (int i = 0; i < 9; i++)
	//{
	//	//���� ��Ʈ
	//	Rectangle(getMemDC(), player.attackRc[i]);
	//}
	//�׸���
	_player.shadowImg->alphaFrameRender(getMemDC(), _player.img->getX(), _player.img->getY() + (TILE_HEIGHT - PLAYER_IMAGE_HEIGHT), SHADOW_ALPHA);
	//������
	_player.img->frameRender(getMemDC(), _player.img->getX(), _player.img->getY() + (TILE_HEIGHT - PLAYER_IMAGE_HEIGHT));
	//������Ʈ ������
	//_player.img->rotateFrameRender(getMemDC(), _player.img->getX(), _player.img->getY() + (TILE_HEIGHT - PLAYER_IMAGE_HEIGHT), _player.img->getFrameX(), _player.img->getFrameY(), PI/16);

	char stst[255];
	sprintf(stst, "moveX=%f, moveY=%f", moveX, moveY);
	TextOut(getMemDC(), 30, 30, stst, strlen(stst));

	//����â
	if (statusFrameIsOn)
	{
		//����â �޹��
		playerStatusFrameBackImage->render(getMemDC(), 2, 2);
		//�Ĺ� ����		
		combatStatus.selectImage->render(getMemDC(), combatStatus.rc.left - 6, combatStatus.rc.top - 6);
		Rectangle(getMemDC(), combatStatus.rc);
		if (combatStatus.isClick) combatStatus.infoImage->render(getMemDC(), combatStatus.rc.left - 12, combatStatus.rc.top - 6 + 42 + 4);
		//���� ����
		magicStatus.selectImage->render(getMemDC(), magicStatus.rc.left - 6, magicStatus.rc.top - 6);
		Rectangle(getMemDC(), magicStatus.rc);
		if (magicStatus.isClick) magicStatus.infoImage->render(getMemDC(), magicStatus.rc.left - 12, magicStatus.rc.top - 6 + 42 + 4);
		//���� ����
		resStatus.selectImage->render(getMemDC(), resStatus.rc.left - 6, resStatus.rc.top - 6);
		if (resStatus.isClick) resStatus.infoImage->render(getMemDC(), resStatus.rc.left - 12, resStatus.rc.top - 6 + 42 + 4);
		Rectangle(getMemDC(), resStatus.rc);

		//����â �̹���
		//âƲ������ �Ǿ������� �������� ����
		playerStatusFrameImage->render(getMemDC(), 2, 2);
		//�����ư ����
		if (PtInRect(&playerStatusFrameExitRc, _ptMouse)) playerStatusFrameExitOverImage->render(getMemDC(), playerStatusFrameExitRc.left, playerStatusFrameExitRc.top);
		//Rectangle(getMemDC(), playerStatusFrameExitRc);	
	}

	//��ųâ 
	if (skillFrameIsOn)
	{
		//��ųâ
		playerSkillWindowImage->render(getMemDC(), WINSIZEX - PLAYER_INVEN_WIDTH - 2, 2);
		playerSkillTypeFrameImage->render(getMemDC(), playerSkillWindowImage->getX() + 58, playerSkillWindowImage->getY() + 100);
		//�����ưRC
		for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
		{
			Rectangle(getMemDC(), playerSkillTypeSelectRc[i]);
			//��ųŸ�� ����
			playerSkillTypeImage[i]->frameRender(getMemDC(), playerSkillTypeSelectRc[i].left, playerSkillTypeSelectRc[i].top);
			//��ųŸ�Կ� ���콺 ���� ������
			this->selectSkillTypeMover(i);
			//��Ƽ��/�нú� ��ų ��Ʈ
			this->skillsWindow(i);
		}

		//��ų ���� ������ ����� ����
		if (PtInRect(&activeSkillRc, _ptMouse))
		{
			skillsRectOverImage->alphaRender(getMemDC(), activeSkillRc.left, activeSkillRc.top, 100);
			//��Ƽ�� ��ų ����			
			for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
			{
				if (playerSkillTypeIstouch[i])
				{
					playerSkills[i].SkillActiveExImage->render(getMemDC(), activeSkillRc.left - 200, activeSkillRc.bottom + 4);
				}
			}
		}

		if (PtInRect(&passiveSkillRc, _ptMouse))
		{
			skillsRectOverImage->alphaRender(getMemDC(), passiveSkillRc.left, passiveSkillRc.top, 100);
			//�нú� ��ų ����
			for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
			{
				if (playerSkillTypeIstouch[i])
				{
					playerSkills[i].SkillPassiveExImage->render(getMemDC(), activeSkillRc.left - 200, activeSkillRc.bottom + 4);
				}
			}
		}
		// ��Ƽ�� �нú� ��Ʈ
		//Rectangle(getMemDC(), activeSkillRc);
		//Rectangle(getMemDC(), passiveSkillRc);	

		//�����ư ����
		if (PtInRect(&playerSkillWindowExitRc, _ptMouse)) playerSkillWindowExitOverImage->render(getMemDC(), playerSkillWindowExitRc.left, playerSkillWindowExitRc.top);
	}

	//�κ��丮
	if (invenFrameIsOn)
	{
		//�κ��丮 �̹���
		playerInvenFrameImage->render(getMemDC(), WINSIZEX - PLAYER_INVEN_WIDTH - 2, 2);

		//�κ��丮 ��Ʈ 
		for (int i = 0; i < INVEN_RECT_Y; i++)
		{
			for (int j = 0; j < INVEN_RECT_X; j++)
			{
				Rectangle(getMemDC(), invenRc[i][j].rc);
				this->ptInGreenRect(invenRc[i][j].rc);		//���콺 ���� �ʷϻ�ĥ
			}
		}

		//���â ��Ʈ
		Rectangle(getMemDC(), weaponEquipRc);	//����
		this->ptInGreenRect(weaponEquipRc);		//���콺 ���� �ʷϻ�ĥ
		Rectangle(getMemDC(), shieldEquipRc);	//����
		this->ptInGreenRect(shieldEquipRc);		//���콺 ���� �ʷϻ�ĥ
		Rectangle(getMemDC(), armorEquipRc);	//�Ƹ�
		this->ptInGreenRect(armorEquipRc);		//���콺 ���� �ʷϻ�ĥ
		Rectangle(getMemDC(), helmetEquipRc);	//���
		this->ptInGreenRect(helmetEquipRc);		//���콺 ���� �ʷϻ�ĥ
		Rectangle(getMemDC(), gloveEquipRc);	//�尩
		this->ptInGreenRect(gloveEquipRc);		//���콺 ���� �ʷϻ�ĥ
		Rectangle(getMemDC(), beltEquipRc);		//��Ʈ
		this->ptInGreenRect(beltEquipRc);		//���콺 ���� �ʷϻ�ĥ
		Rectangle(getMemDC(), bootEquipRc);		//����
		this->ptInGreenRect(bootEquipRc);		//���콺 ���� �ʷϻ�ĥ

		Rectangle(getMemDC(), necklaceEquipRc);	//�����
		this->ptInGreenRect(necklaceEquipRc);		//���콺 ���� �ʷϻ�ĥ
		Rectangle(getMemDC(), leftRingEquipRc);	//���� ����
		this->ptInGreenRect(leftRingEquipRc);		//���콺 ���� �ʷϻ�ĥ
		Rectangle(getMemDC(), rightRingEquipRc);//�����ʹ���
		this->ptInGreenRect(rightRingEquipRc);		//���콺 ���� �ʷϻ�ĥ

		//�����ư ����
		if (PtInRect(&playerSkillWindowExitRc, _ptMouse)) playerSkillWindowExitOverImage->render(getMemDC(), playerSkillWindowExitRc.left, playerSkillWindowExitRc.top);
	}

	//�ϴܹ�
	playerUIImage->render(getMemDC(), 0, 0 + (WINSIZEY - PLAYER_UI_IMAGE_HEIGTH));
}

//���� ��� ��ġ ����
void myPlayer::playerAttackImg(int _i)
{
	if (player.direction == PLAYER_RIGTH) player.attackImg->setFrameY(0);
	else  player.attackImg->setFrameY(1);

	if (player.attackDirection[_i])
	{
		player.attackCount++;
		if (player.attackCount % 6 == 0)
		{
			player.attackIndex++;
		}
		player.attackImg->setFrameX(player.attackIndex);
		player.attackImg->frameRender(getMemDC(), player.attackRc[_i].left, player.attackRc[_i].top);
	}
	if (player.attackIndex >= player.attackImg->getMaxFrameX())
	{
		player.attackCount = 0;
		player.attackIndex = 0;
		player.attackDirection[_i] = false;
	}
	//if (_attack == ATTACK_LEFT_TOP)
	//{
	//	player.attackCount++;
	//	if (player.attackCount % 6 == 0)
	//	{
	//		player.attackIndex++;
	//	}
	//	player.attackImg->setFrameX(player.attackIndex);
	//	player.attackImg->frameRender(getMemDC(), player.attackRc[0].left, player.attackRc[0].top);
	//}

	//else if (_attack == ATTACK_TOP)
	//{
	//	player.attackCount++;
	//	if (player.attackCount % 6 == 0)
	//	{
	//		player.attackIndex++;
	//	}
	//	player.attackImg->setFrameX(player.attackIndex);
	//	player.attackImg->frameRender(getMemDC(), player.attackRc[1].left, player.attackRc[1].top);
	//}


	//else if (_attack == ATTACK_RIGHT_TOP)
	//{
	//	player.attackCount++;
	//	if (player.attackCount % 6 == 0)
	//	{
	//		player.attackIndex++;
	//	}
	//	player.attackImg->setFrameX(player.attackIndex);
	//	player.attackImg->frameRender(getMemDC(), player.attackRc[2].left, player.attackRc[2].top);
	//}


	//else if (_attack == ATTACK_LEFT)
	//{
	//	player.attackCount++;
	//	if (player.attackCount % 6 == 0)
	//	{
	//		player.attackIndex++;
	//	}
	//	player.attackImg->setFrameX(player.attackIndex);
	//	player.attackImg->frameRender(getMemDC(), player.attackRc[3].left, player.attackRc[3].top);
	//}


	//else if (_attack == ATTACK_RIGHT)
	//{
	//	player.attackCount++;
	//	if (player.attackCount % 6 == 0)
	//	{
	//		player.attackIndex++;
	//	}
	//	player.attackImg->setFrameX(player.attackIndex);
	//	player.attackImg->frameRender(getMemDC(), player.attackRc[5].left, player.attackRc[5].top);
	//}


	//else if (_attack == ATTACK_LEFT_BOTTOM)
	//{
	//	player.attackCount++;
	//	if (player.attackCount % 6 == 0)
	//	{
	//		player.attackIndex++;
	//	}
	//	player.attackImg->setFrameX(player.attackIndex);
	//	player.attackImg->frameRender(getMemDC(), player.attackRc[6].left, player.attackRc[6].top);
	//}


	//else if (_attack == ATTACK_BOTTOM)
	//{
	//	player.attackCount++;
	//	if (player.attackCount % 6 == 0)
	//	{
	//		player.attackIndex++;
	//	}
	//	player.attackImg->setFrameX(player.attackIndex);
	//	player.attackImg->frameRender(getMemDC(), player.attackRc[7].left, player.attackRc[7].top);
	//}


	//else if (_attack == ATTACK_RIGHT_BOTTOM)
	//{
	//	player.attackCount++;
	//	if (player.attackCount % 6 == 0)
	//	{
	//		player.attackIndex++;
	//	}
	//	player.attackImg->setFrameX(player.attackIndex);
	//	player.attackImg->frameRender(getMemDC(), player.attackRc[8].left, player.attackRc[8].top);
	//}

	//if (player.attackIndex > player.attackImg->getFrameX())
	//{
	//	player.attackCount = 0;
	//	player.attackIndex = 0;
	//}
}

//������Ʈ�� ���̺� �ϱ�
void myPlayer::wavingObject(RECT _rc, image* _img)
{
	_img->setX(_rc.left);
	_img->setY(_rc.top);


	//���̺� �¿�
	enum wavingH
	{
		LEFT, RIGHT
	};

	//���̺� ����
	enum wavingV
	{
		TOP, BOTTOM
	};
	static int wavingH = 3;
	static int wavingV = BOTTOM;
	static int moveX = 0;
	static int moveY = 0;
	moveX++;
	if (wavingH == LEFT)
	{
		moveX -= 0.005f;
		if (moveX < -0.2f)
		{
			moveX = 0.0f;
			wavingH = RIGHT;
		}
	}
	if (wavingH == RIGHT)
	{
		moveX += 0.005f;
		if (moveX > 0.2f)
		{
			moveX = 0.0f;
			wavingH = LEFT;
		}
	}
	if (wavingV == TOP)
	{
		moveY -= 0.01f;
		if (moveY < -0.2f)
		{
			moveY = 0.0f;
			wavingV = BOTTOM;
		}
	}
	if (wavingV == BOTTOM)
	{
		moveY += 0.01f;
		if (moveY > 0.2f)
		{
			moveY = 0.0f;
			wavingV = TOP;
		}
	}
	_img->setX(_img->getX() + moveX);
	_img->setY(_img->getY() + moveY);

	_img->frameRender(getMemDC(), _rc.left, _rc.top + (TILE_HEIGHT - PLAYER_IMAGE_HEIGHT));

	char stst[255];
	sprintf(stst, "waveH=%d, waveV=%d, moveX=%d, moveY=%d", wavingH, wavingV, moveX, moveY);
	TextOut(getMemDC(), 30,30, stst, strlen(stst));	
}
