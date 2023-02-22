#include "stdafx.h"
#include "myPlayer.h"
#include "dungeonSecen.h"



HRESULT myPlayer::init()
{
	
	//플레이어 초기화

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
	//스탯창
	playerStatusFrameImage = IMAGEMANAGER->addImage("playerStatusFrame", "image/player/player_status_1.bmp", PLAYER_INVEN_WIDTH, PLAYER_INVEN_HEIGHT, true, RGB(255, 0, 255));
	playerStatusFrameImage->setX(2);
	playerStatusFrameImage->setY(2);
	//스탯창 종료 버튼 RC//이미지
	playerStatusFrameExitRc = RectMake(playerStatusFrameImage->getX() + 638, playerStatusFrameImage->getY() + 2, 40, 40);
	playerStatusFrameExitOverImage = IMAGEMANAGER->addImage("playerStatusFrameExitOver", "image/option_button/exit_button_over.bmp", 40, 40);

	//컴뱃 스탯 선택 렉트
	combatStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338, 30, 30);
	combatStatus.selectImage = IMAGEMANAGER->addImage("selectCombat", "image/player/player_status_combat_bar.bmp", 532, 42);
	combatStatus.infoImage = IMAGEMANAGER->addImage("infoCombat", "image/player/combat_info.bmp", 540, 284);
	combatStatus.isClick = false;
	combatStatus.scroll = 0;

	//마법 스탯 선택 렉트
	magicStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338 + 42 + 4, 30, 30);
	magicStatus.selectImage = IMAGEMANAGER->addImage("selectMagic", "image/player/player_status_magic_bar.bmp", 532, 42);
	magicStatus.infoImage = IMAGEMANAGER->addImage("infoMagic", "image/player/magic_info.bmp", 540, 140);
	magicStatus.isClick = false;
	magicStatus.scroll = 0;
	//레지 스탯 선택 렉트
	resStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338 + 84 + 8, 30, 30);
	resStatus.selectImage = IMAGEMANAGER->addImage("selectRes", "image/player/player_status_res_bar.bmp", 532, 42);
	resStatus.infoImage = IMAGEMANAGER->addImage("infoRes", "image/player/res_info.bmp", 540, 140);
	resStatus.isClick = false;
	resStatus.scroll = 0;
	//정보창 스크롤


	//스킬창 
	playerSkillWindowImage = IMAGEMANAGER->addImage("playerSkillFrame", "image/player/player_skill_frame.bmp", PLAYER_INVEN_WIDTH, PLAYER_INVEN_HEIGHT);
	playerSkillWindowImage->setX(WINSIZEX - PLAYER_INVEN_WIDTH - 2);
	playerSkillWindowImage->setY(2);

	//스킬창//인벤창 종료 버튼 RC//이미지
	playerSkillWindowExitRc = RectMake(playerSkillWindowImage->getX() + 638, playerSkillWindowImage->getY() + 2, 40, 40);
	playerSkillWindowExitOverImage = IMAGEMANAGER->addImage("playerSkillWindowExitOver", "image/option_button/exit_button_over.bmp", 40, 40);

	//스킬창 타입
	playerSkillTypeFrameImage = IMAGEMANAGER->addImage("playerSkillTypeFrame", "image/player/skills/player_skill_type_frame.bmp", PLAYER_SKILL_TYPE_WIDTH, PLAYER_SKILL_TYPE_HEIGHT);

	//스킬 렉트 마우스 오버
	skillsRectOverImage = IMAGEMANAGER->addImage("skillOver", "image/player/skills/rectover.bmp", SKILL_FRAME_WIDTH, SKILL_FRAME_HEIGHT, true, RGB(255, 0, 255));


	//스킬창 타입 렉트
	playerSkillTypeImage[0] = IMAGEMANAGER->addFrameImage("소드타입", "image/player/skills/swords.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//소드
	//액티브/패시브 스킬 이미지
	playerSkills[0].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("소드액티브", "image/player/skills/swords/swords_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[0].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("소드패시브", "image/player/skills/swords/swords_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[0].SkillActiveExImage = IMAGEMANAGER->addImage("소드액티브설명", "image/player/skills/swords/skills_explain_swords_active.bmp", 444, 326);
	playerSkills[0].SkillPassiveExImage = IMAGEMANAGER->addImage("소드패시브설명", "image/player/skills/swords/skills_explain_swords_passive.bmp", 444, 222);

	playerSkillTypeImage[1] = IMAGEMANAGER->addFrameImage("엑스타입", "image/player/skills/axes.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//엑스
	//액티브/패시브 스킬 이미지
	playerSkills[1].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("엑스액티브", "image/player/skills/axes/axes_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[1].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("엑스패시브", "image/player/skills/axes/axes_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[1].SkillActiveExImage = IMAGEMANAGER->addImage("엑스액티브설명", "image/player/skills/axes/skills_explain_axes_active.bmp", 444, 326);
	playerSkills[1].SkillPassiveExImage = IMAGEMANAGER->addImage("엑스패시브설명", "image/player/skills/axes/skills_explain_axes_passive.bmp", 444, 222);

	playerSkillTypeImage[2] = IMAGEMANAGER->addFrameImage("메이스타입", "image/player/skills/maces.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//메이스
	//액티브/패시브 스킬 이미지
	playerSkills[2].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("메이스액티브", "image/player/skills/maces/maces_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[2].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("메이스패시브", "image/player/skills/maces/maces_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[2].SkillActiveExImage = IMAGEMANAGER->addImage("메이스액티브설명", "image/player/skills/maces/skills_explain_maces_active.bmp", 444, 326);
	playerSkills[2].SkillPassiveExImage = IMAGEMANAGER->addImage("메이스패시브설명", "image/player/skills/maces/skills_explain_maces_passive.bmp", 444, 222);

	playerSkillTypeImage[3] = IMAGEMANAGER->addFrameImage("대거타입", "image/player/skills/daggers.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//대거
	//액티브/패시브 스킬 이미지
	playerSkills[3].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("대거액티브", "image/player/skills/daggers/daggers_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[3].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("대거패시브", "image/player/skills/daggers/daggers_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[3].SkillActiveExImage = IMAGEMANAGER->addImage("대거액티브설명", "image/player/skills/daggers/skills_explain_daggers_active.bmp", 444, 326);
	playerSkills[3].SkillPassiveExImage = IMAGEMANAGER->addImage("대거패시브설명", "image/player/skills/daggers/skills_explain_daggers_passive.bmp", 444, 222);

	playerSkillTypeImage[4] = IMAGEMANAGER->addFrameImage("그레이트소드타입", "image/player/skills/greatswords.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//그레이트소드
	//액티브/패시브 스킬 이미지
	playerSkills[4].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("그레이트소드액티브", "image/player/skills/greatswords/greatswords_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[4].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("그레이트소드패시브", "image/player/skills/greatswords/greatswords_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[4].SkillActiveExImage = IMAGEMANAGER->addImage("그레이트소드액티브설명", "image/player/skills/greatswords/skills_explain_greatswords_active.bmp", 444, 326);
	playerSkills[4].SkillPassiveExImage = IMAGEMANAGER->addImage("그레이트소드패시브설명", "image/player/skills/greatswords/skills_explain_greatswords_passive.bmp", 444, 222);

	playerSkillTypeImage[5] = IMAGEMANAGER->addFrameImage("보우타입", "image/player/skills/bows.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//보우
	//액티브/패시브 스킬 이미지
	playerSkills[5].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("보우액티브", "image/player/skills/bows/bows_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[5].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("보우패시브", "image/player/skills/bows/bows_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[5].SkillActiveExImage = IMAGEMANAGER->addImage("보우액티브설명", "image/player/skills/bows/skills_explain_bows_active.bmp", 444, 326);
	playerSkills[5].SkillPassiveExImage = IMAGEMANAGER->addImage("보우패시브설명", "image/player/skills/bows/skills_explain_bows_passive.bmp", 444, 222)
		;
	playerSkillTypeImage[6] = IMAGEMANAGER->addFrameImage("쉴드타입", "image/player/skills/shields.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//쉴드
	//액티브/패시브 스킬 이미지
	playerSkills[6].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("쉴드액티브", "image/player/skills/shields/shields_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[6].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("쉴드패시브", "image/player/skills/shields/shields_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[6].SkillActiveExImage = IMAGEMANAGER->addImage("쉴드액티브설명", "image/player/skills/shields/skills_explain_shields_active.bmp", 444, 326);
	playerSkills[6].SkillPassiveExImage = IMAGEMANAGER->addImage("쉴드패시브설명", "image/player/skills/shields/skills_explain_shields_passive.bmp", 444, 222);

	playerSkillTypeImage[7] = IMAGEMANAGER->addFrameImage("클래스유틸", "image/player/skills/classskills.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//클래스스킬
	//액티브/패시브 스킬 이미지
	playerSkills[7].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("클래스유틸액티브", "image/player/skills/classskills/classskills_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[7].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("클래스유틸패시브", "image/player/skills/classskills/classskills_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[7].SkillActiveExImage = IMAGEMANAGER->addImage("클래스유틸액티브설명", "image/player/skills/classskills/skills_explain_classskills_active.bmp", 444, 326);
	playerSkills[7].SkillPassiveExImage = IMAGEMANAGER->addImage("클래스유틸패시브설명", "image/player/skills/classskills/skills_explain_classskills_passive.bmp", 444, 222);

	playerSkillTypeImage[8] = IMAGEMANAGER->addFrameImage("베이직유틸", "image/player/skills/basicskills.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//베이직스킬
	//액티브/패시브 스킬 이미지
	playerSkills[8].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("베이직유틸액티브", "image/player/skills/basicskills/basicskills_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[8].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("베이직유틸패시브", "image/player/skills/basicskills/basicskills_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[8].SkillActiveExImage = IMAGEMANAGER->addImage("베이직유틸액티브설명", "image/player/skills/basicskills/skills_explain_basicskills_active.bmp", 444, 326);
	playerSkills[8].SkillPassiveExImage = IMAGEMANAGER->addImage("베이직유틸패시브설명", "image/player/skills/basicskills/skills_explain_basicskills_passive.bmp", 444, 222);

	playerSkillTypeImage[9] = IMAGEMANAGER->addFrameImage("아머유틸", "image/player/skills/armor.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//아머
	//액티브/패시브 스킬 이미지
	playerSkills[9].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("아머유틸액티브", "image/player/skills/armor/armor_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[9].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("아머유틸패시브", "image/player/skills/armor/armor_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[9].SkillActiveExImage = IMAGEMANAGER->addImage("아머유틸액티브설명", "image/player/skills/armor/skills_explain_armor_active.bmp", 444, 326);
	playerSkills[9].SkillPassiveExImage = IMAGEMANAGER->addImage("아머유틸패시브설명", "image/player/skills/armor/skills_explain_armor_passive.bmp", 444, 222);

	playerSkillTypeImage[10] = IMAGEMANAGER->addFrameImage("듀얼유틸", "image/player/skills/dualwielding.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//듀얼
	//액티브/패시브 스킬 이미지
	playerSkills[10].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("듀얼유틸액티브", "image/player/skills/dualwielding/dualwielding_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[10].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("듀얼유틸패시브", "image/player/skills/dualwielding/dualwielding_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[10].SkillActiveExImage = IMAGEMANAGER->addImage("듀얼유틸액티브설명", "image/player/skills/dualwielding/skills_explain_dualwielding_active.bmp", 444, 326);
	playerSkills[10].SkillPassiveExImage = IMAGEMANAGER->addImage("듀얼유틸패시브설명", "image/player/skills/dualwielding/skills_explain_dualwielding_passive.bmp", 444, 222);

	playerSkillTypeImage[11] = IMAGEMANAGER->addFrameImage("치유유틸", "image/player/skills/medicine.bmp", PLAYER_SKILL_TYPE_SELECT_WIDTH, 75, 1, 3);	//치유
	//액티브/패시브 스킬 이미지
	playerSkills[11].WindowFrameActiveImage = IMAGEMANAGER->addFrameImage("치유유틸액티브", "image/player/skills/medicine/medicine_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[11].WindowFramePassiveImage = IMAGEMANAGER->addFrameImage("치유유틸패시브", "image/player/skills/medicine/medicine_50x192.bmp", SKILL_FRAME_WIDTH, 192, 1, 4, true, RGB(255, 0, 255));
	playerSkills[11].SkillActiveExImage = IMAGEMANAGER->addImage("치유유틸액티브설명", "image/player/skills/medicine/skills_explain_medicine_active.bmp", 444, 326);
	playerSkills[11].SkillPassiveExImage = IMAGEMANAGER->addImage("치유유틸패시브설명", "image/player/skills/medicine/skills_explain_medicine_passive.bmp", 444, 222);
	//스킬 타입 렉트
	for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
	{	
		//스킬타입 불 값
		playerSkillTypeIstouch[i] = false;
		playerSkills[i].learnActive = NONE_ACTIVE;
		playerSkills[i].learnPassive = NONE_PASSIVE;
		int num = 48;
		if (i > 6) playerSkillTypeSelectRc[i] = RectMake(playerSkillWindowImage->getX() + 62, playerSkillWindowImage->getY() + 157 + num + (i * 25) + (i * 3), PLAYER_SKILL_TYPE_SELECT_WIDTH, PLAYER_SKILL_TYPE_SELECT_HEIGHT);
		else playerSkillTypeSelectRc[i] = RectMake(playerSkillWindowImage->getX() + 62, playerSkillWindowImage->getY() + 157 + (i * 25) + (i * 3), PLAYER_SKILL_TYPE_SELECT_WIDTH, PLAYER_SKILL_TYPE_SELECT_HEIGHT);
	}
	//액티브/패시브 스킬 렉트
	activeSkillRc = RectMake(playerSkillWindowImage->getX() + 408, playerSkillWindowImage->getY() + 194, SKILL_FRAME_WIDTH, SKILL_FRAME_HEIGHT);
	passiveSkillRc = RectMake(playerSkillWindowImage->getX() + 514, playerSkillWindowImage->getY() + 194, SKILL_FRAME_WIDTH, SKILL_FRAME_HEIGHT);



	
	
	//인벤
	playerInvenFrameImage = IMAGEMANAGER->addImage("playerInvenFrame", "image/player/player_inven.bmp", PLAYER_INVEN_WIDTH, PLAYER_INVEN_HEIGHT);
	playerInvenFrameImage->setX(WINSIZEX - PLAYER_INVEN_WIDTH - 2);
	playerInvenFrameImage->setY(2);
	
	//인벤토리 렉트 초기화
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
	//무기EQUIP_RECT
	weaponEquipRc = RectMake(playerInvenFrameImage->getX() + 74, playerInvenFrameImage->getY() + 112, ALL_EQUIP_WIDTH, WEAPON_EQUIP_HEIGHT);
	//방패EQUIP_RECT
	shieldEquipRc = RectMake(playerInvenFrameImage->getX() + 504, playerInvenFrameImage->getY() + 112, ALL_EQUIP_WIDTH, SHIELD_EQUIP_HEIGHT);
	//아머EQUIP_RECT
	armorEquipRc = RectMake(playerInvenFrameImage->getX() + 194, playerInvenFrameImage->getY() + 164, ALL_EQUIP_WIDTH, ARMOR_EQUIP_HEIGHT);
	//투구EQUIP_RECT
	helmetEquipRc = RectMake(playerInvenFrameImage->getX() + 194, playerInvenFrameImage->getY() + 56, ALL_EQUIP_WIDTH, HELMET_EQUIP_HEIGHT);
	//장갑EQUIP_RECT
	gloveEquipRc = RectMake(playerInvenFrameImage->getX() + 384, playerInvenFrameImage->getY() + 56, ALL_EQUIP_WIDTH, GLOVE_EQUIP_HEIGHT);
	//부츠EQUIP_RECT
	bootEquipRc = RectMake(playerInvenFrameImage->getX() + 384, playerInvenFrameImage->getY() + 218, ALL_EQUIP_WIDTH, BOOT_EQUIP_HEIGHT);
	//벨트EQUIP_RECT
	beltEquipRc = RectMake(playerInvenFrameImage->getX() + 384, playerInvenFrameImage->getY() + 164, ALL_EQUIP_WIDTH, BELT_EQUIP_HEIGHT);

	//목걸이EQUIP_RECT
	necklaceEquipRc = RectMake(playerInvenFrameImage->getX() + 316, playerInvenFrameImage->getY() + 102, ACC_EQUIP_WIDTH, ACC_EQUIP_HEIGHT);
	//반지(왼)EQUIP_RECT
	leftRingEquipRc = RectMake(playerInvenFrameImage->getX() + 316, playerInvenFrameImage->getY() + 166, ACC_EQUIP_WIDTH, ACC_EQUIP_HEIGHT);
	//반지(오른)EQUIP_RECT
	rightRingEquipRc = RectMake(playerInvenFrameImage->getX() + 316, playerInvenFrameImage->getY() + 230, ACC_EQUIP_WIDTH, ACC_EQUIP_HEIGHT);

	//하단바
	playerUIImage = IMAGEMANAGER->addImage("playerUI", "image/player/player_UI.bmp", PLAYER_UI_IMAGE_WIDTH, PLAYER_UI_IMAGE_HEIGTH, true, RGB(255, 0, 255));

	
	return S_OK;
}

void myPlayer::release()
{
}

void myPlayer::update()
{
	//플레이어 렉트 업데이트
	player.rc = RectMake(player.x, player.y, TILE_WIDTH, TILE_HEIGHT);
	//플레이어 방향 업데이트
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

	//컴뱃 스탯 선택 렉트
	combatStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338, 30, 30);
	//마법 스탯 선택 렉트
	magicStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338 + 42 + 4 + combatStatus.scroll, 30, 30);
	//레지 스탯 선택 렉트
	resStatus.rc = RectMake(playerStatusFrameImage->getX() + 70, playerStatusFrameImage->getY() + 338 + 84 + 8 + combatStatus.scroll + magicStatus.scroll, 30, 30);

	if (combatStatus.isClick) combatStatus.scroll = 284;
	else  combatStatus.scroll = 0;
	if (magicStatus.isClick) magicStatus.scroll = 140;
	else  magicStatus.scroll = 0;

	//플레이어 이미지를 흔들거림업데이트
	//이넘문으로 레프트 라이트 탑 바텀 구분




		

	


	//캐릭터 스탯창 보기
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (!statusFrameIsOn) statusFrameIsOn = true;		
		else statusFrameIsOn = false;
	}
	//캐릭터 인벤토리 보기
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (!invenFrameIsOn) invenFrameIsOn = true;
		else invenFrameIsOn = false;
	}
	//캐릭터 스킬창 보기
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (!skillFrameIsOn) skillFrameIsOn = true;
		else skillFrameIsOn = false;
	}
	






	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//각창들 종료 버튼
		if (PtInRect(&playerStatusFrameExitRc, _ptMouse) && statusFrameIsOn) statusFrameIsOn = false;
		if (PtInRect(&playerSkillWindowExitRc, _ptMouse) && invenFrameIsOn) invenFrameIsOn = false;
		if (PtInRect(&playerSkillWindowExitRc, _ptMouse) && skillFrameIsOn) skillFrameIsOn = false;

		//스탯창에서 컴뱃 인포 보기
		if (PtInRect(&combatStatus.rc, _ptMouse))
		{
			if (combatStatus.isClick) combatStatus.isClick = false;
			else combatStatus.isClick = true;

		
		}
		//스탯창에서 매직 인포 보기
		if (PtInRect(&magicStatus.rc, _ptMouse))
		{
			if (magicStatus.isClick) magicStatus.isClick = false;
			else magicStatus.isClick = true;
		}
		//스탯창에서 레지 인포 보기
		if (PtInRect(&resStatus.rc, _ptMouse))
		{
			if (resStatus.isClick) resStatus.isClick = false;
			else resStatus.isClick = true;
		}
		
		//스킬 타입 클릭시 트루로 변경
		for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
		{
			if (PtInRect(&playerSkillTypeSelectRc[i], _ptMouse))
			{
				for (int j = 0; j < PLAYER_SKILL_TYPE_MAX; j++)
				{
					//스킬 타입 이 펄스일때	
					//선택 여부 확인하고 텍스트 색 바꾸기
					playerSkillTypeIstouch[j] = false;
					playerSkillTypeImage[j]->setFrameY(0);
				}
				//스킬 타입 이 트루일때	
				//선택 여부 확인하고 텍스트 색 바꾸기
				playerSkillTypeIstouch[i] = true;
							
			}

			//테스트로 스킬 배우기
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
	//스킬 타입 이 트루일때	
    //선택 여부 확인하고 텍스트 색 바꾸기
	for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
	{
		if (playerSkillTypeIstouch[i]) playerSkillTypeImage[i]->setFrameY(2);				
	}	
	
}

void myPlayer::render()
{	

}

//장비창 렉트 색칠하기
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

//스킬 타입 마우스 오버
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
//스킬타입에 맞게 액티브/패시브/설명 렌더하기
void myPlayer::skillsWindow(int _i)
{
	for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
	{
		//스킬타입에 맞게 액티브/패시브/설명 렌더하기
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


//플레이어 이미지 렌더 함수
void myPlayer::playerImageRender(tagPlayer _player)
{
#define WAVE_SPEED 0.1f
#define WAVE_AREA 2.0f
	//웨이브 좌우
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

	//그림자
	_player.shadowImg->setX(_player.img->getX() + moveX);
	_player.shadowImg->setY(_player.img->getY() + moveY);
	//플레이어
	_player.img->setX(_player.img->getX() + moveX);
	_player.img->setY(_player.img->getY() + moveY);
	//렉트
	//Rectangle(getMemDC(), _player.rc);
	//for (int i = 0; i < 9; i++)
	//{
	//	//어택 렉트
	//	Rectangle(getMemDC(), player.attackRc[i]);
	//}
	//그림자
	_player.shadowImg->alphaFrameRender(getMemDC(), _player.img->getX(), _player.img->getY() + (TILE_HEIGHT - PLAYER_IMAGE_HEIGHT), SHADOW_ALPHA);
	//프레임
	_player.img->frameRender(getMemDC(), _player.img->getX(), _player.img->getY() + (TILE_HEIGHT - PLAYER_IMAGE_HEIGHT));
	//로테이트 프레임
	//_player.img->rotateFrameRender(getMemDC(), _player.img->getX(), _player.img->getY() + (TILE_HEIGHT - PLAYER_IMAGE_HEIGHT), _player.img->getFrameX(), _player.img->getFrameY(), PI/16);

	char stst[255];
	sprintf(stst, "moveX=%f, moveY=%f", moveX, moveY);
	TextOut(getMemDC(), 30, 30, stst, strlen(stst));

	//스탯창
	if (statusFrameIsOn)
	{
		//스탯창 뒷배경
		playerStatusFrameBackImage->render(getMemDC(), 2, 2);
		//컴뱃 인포		
		combatStatus.selectImage->render(getMemDC(), combatStatus.rc.left - 6, combatStatus.rc.top - 6);
		Rectangle(getMemDC(), combatStatus.rc);
		if (combatStatus.isClick) combatStatus.infoImage->render(getMemDC(), combatStatus.rc.left - 12, combatStatus.rc.top - 6 + 42 + 4);
		//매직 인포
		magicStatus.selectImage->render(getMemDC(), magicStatus.rc.left - 6, magicStatus.rc.top - 6);
		Rectangle(getMemDC(), magicStatus.rc);
		if (magicStatus.isClick) magicStatus.infoImage->render(getMemDC(), magicStatus.rc.left - 12, magicStatus.rc.top - 6 + 42 + 4);
		//레지 인포
		resStatus.selectImage->render(getMemDC(), resStatus.rc.left - 6, resStatus.rc.top - 6);
		if (resStatus.isClick) resStatus.infoImage->render(getMemDC(), resStatus.rc.left - 12, resStatus.rc.top - 6 + 42 + 4);
		Rectangle(getMemDC(), resStatus.rc);

		//스탯창 이미지
		//창틀형으로 되어있으니 마지막에 렌더
		playerStatusFrameImage->render(getMemDC(), 2, 2);
		//종료버튼 오버
		if (PtInRect(&playerStatusFrameExitRc, _ptMouse)) playerStatusFrameExitOverImage->render(getMemDC(), playerStatusFrameExitRc.left, playerStatusFrameExitRc.top);
		//Rectangle(getMemDC(), playerStatusFrameExitRc);	
	}

	//스킬창 
	if (skillFrameIsOn)
	{
		//스킬창
		playerSkillWindowImage->render(getMemDC(), WINSIZEX - PLAYER_INVEN_WIDTH - 2, 2);
		playerSkillTypeFrameImage->render(getMemDC(), playerSkillWindowImage->getX() + 58, playerSkillWindowImage->getY() + 100);
		//종료버튼RC
		for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
		{
			Rectangle(getMemDC(), playerSkillTypeSelectRc[i]);
			//스킬타입 렌더
			playerSkillTypeImage[i]->frameRender(getMemDC(), playerSkillTypeSelectRc[i].left, playerSkillTypeSelectRc[i].top);
			//스킬타입에 마우스 오버 했을때
			this->selectSkillTypeMover(i);
			//액티브/패시브 스킬 렉트
			this->skillsWindow(i);
		}

		//스킬 오버 했을때 흰바탕 띄우기
		if (PtInRect(&activeSkillRc, _ptMouse))
		{
			skillsRectOverImage->alphaRender(getMemDC(), activeSkillRc.left, activeSkillRc.top, 100);
			//액티브 스킬 설명			
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
			//패시브 스킬 설명
			for (int i = 0; i < PLAYER_SKILL_TYPE_MAX; i++)
			{
				if (playerSkillTypeIstouch[i])
				{
					playerSkills[i].SkillPassiveExImage->render(getMemDC(), activeSkillRc.left - 200, activeSkillRc.bottom + 4);
				}
			}
		}
		// 액티브 패시브 렉트
		//Rectangle(getMemDC(), activeSkillRc);
		//Rectangle(getMemDC(), passiveSkillRc);	

		//종료버튼 오버
		if (PtInRect(&playerSkillWindowExitRc, _ptMouse)) playerSkillWindowExitOverImage->render(getMemDC(), playerSkillWindowExitRc.left, playerSkillWindowExitRc.top);
	}

	//인벤토리
	if (invenFrameIsOn)
	{
		//인벤토리 이미지
		playerInvenFrameImage->render(getMemDC(), WINSIZEX - PLAYER_INVEN_WIDTH - 2, 2);

		//인벤토리 렉트 
		for (int i = 0; i < INVEN_RECT_Y; i++)
		{
			for (int j = 0; j < INVEN_RECT_X; j++)
			{
				Rectangle(getMemDC(), invenRc[i][j].rc);
				this->ptInGreenRect(invenRc[i][j].rc);		//마우스 오버 초록색칠
			}
		}

		//장비창 렉트
		Rectangle(getMemDC(), weaponEquipRc);	//무기
		this->ptInGreenRect(weaponEquipRc);		//마우스 오버 초록색칠
		Rectangle(getMemDC(), shieldEquipRc);	//방패
		this->ptInGreenRect(shieldEquipRc);		//마우스 오버 초록색칠
		Rectangle(getMemDC(), armorEquipRc);	//아머
		this->ptInGreenRect(armorEquipRc);		//마우스 오버 초록색칠
		Rectangle(getMemDC(), helmetEquipRc);	//헬멧
		this->ptInGreenRect(helmetEquipRc);		//마우스 오버 초록색칠
		Rectangle(getMemDC(), gloveEquipRc);	//장갑
		this->ptInGreenRect(gloveEquipRc);		//마우스 오버 초록색칠
		Rectangle(getMemDC(), beltEquipRc);		//벨트
		this->ptInGreenRect(beltEquipRc);		//마우스 오버 초록색칠
		Rectangle(getMemDC(), bootEquipRc);		//부츠
		this->ptInGreenRect(bootEquipRc);		//마우스 오버 초록색칠

		Rectangle(getMemDC(), necklaceEquipRc);	//목걸이
		this->ptInGreenRect(necklaceEquipRc);		//마우스 오버 초록색칠
		Rectangle(getMemDC(), leftRingEquipRc);	//왼쪽 반지
		this->ptInGreenRect(leftRingEquipRc);		//마우스 오버 초록색칠
		Rectangle(getMemDC(), rightRingEquipRc);//오른쪽반지
		this->ptInGreenRect(rightRingEquipRc);		//마우스 오버 초록색칠

		//종료버튼 오버
		if (PtInRect(&playerSkillWindowExitRc, _ptMouse)) playerSkillWindowExitOverImage->render(getMemDC(), playerSkillWindowExitRc.left, playerSkillWindowExitRc.top);
	}

	//하단바
	playerUIImage->render(getMemDC(), 0, 0 + (WINSIZEY - PLAYER_UI_IMAGE_HEIGTH));
}

//공격 모션 위치 설정
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

//오브젝트들 웨이빙 하기
void myPlayer::wavingObject(RECT _rc, image* _img)
{
	_img->setX(_rc.left);
	_img->setY(_rc.top);


	//웨이브 좌우
	enum wavingH
	{
		LEFT, RIGHT
	};

	//웨이브 상하
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
