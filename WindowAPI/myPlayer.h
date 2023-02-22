#pragma once
#include "gameNode.h"
#include "playerStatus.h"



#define PLAYER_IMAGE_WIDTH 52
#define PLAYER_IMAGE_HEIGHT 74

#define PLAYER_INIT_X (TILE_WIDTH * 13)
#define PLAYER_INIT_Y (TILE_HEIGHT * 6)

#define PLAYER_UI_IMAGE_WIDTH 1366
#define PLAYER_UI_IMAGE_HEIGTH 117
#define PLAYER_INVEN_WIDTH 680
#define PLAYER_INVEN_HEIGHT 686

#define PLAYER_SKILL_TYPE_WIDTH 194
#define PLAYER_SKILL_TYPE_HEIGHT 488
#define PLAYER_SKILL_TYPE_MAX 12
#define PLAYER_SKILL_TYPE_SELECT_WIDTH 186
#define PLAYER_SKILL_TYPE_SELECT_HEIGHT 25
#define SKILL_FRAME_WIDTH 50
#define SKILL_FRAME_HEIGHT 48

//인벤토리 렉트 사이즈
#define INVEN_RECT_Y 5
#define INVEN_RECT_X 10

//장비착용 렉트 사이즈
#define ALL_EQUIP_WIDTH 106
#define WEAPON_EQUIP_HEIGHT 160
#define SHIELD_EQUIP_HEIGHT 160
#define ARMOR_EQUIP_HEIGHT 160
#define HELMET_EQUIP_HEIGHT 106
#define GLOVE_EQUIP_HEIGHT 106
#define BOOT_EQUIP_HEIGHT 106
#define BELT_EQUIP_HEIGHT 52

//악세착용 렉트 사이즈
#define ACC_EQUIP_WIDTH 52
#define ACC_EQUIP_HEIGHT 52

//# 그림자 알파값

#define SHADOW_ALPHA 100
//클래스 전방선언 / 상호참조
//던전씬
class dungeonSecen;



enum PLAYERDIRECTION
{
	PLAYER_RIGTH, PLAYER_LEFT
};

//플레이어
struct tagPlayer
{
	image* img;
	image* shadowImg;
	image* attackImg;
	int attackCount;
	int attackIndex;
	PLAYERDIRECTION direction;
	RECT rc;
	RECT attackRc[9];
	bool attackDirection[9];
	float x, y;

	int width, height;
	float timer;
};

//스탯 정보
struct tagStatusiInfo
{
	image* selectImage;
	image* infoImage;
	RECT rc;
	bool isClick;
	int scroll;
};
//인벤 렉트
struct tagInvenRc
{
	RECT rc;
	int idX, IdY;
	int width, height;
	float x, y;
};

//장비 타입
enum EQUIPTYPE
{
	WEAPOM, SHIELD, ARMOR, 
	HELMET, GLOVE, BOOT, 
	LEFT_RING, RIGHT_RING, NECKLACE
};

//장비템
struct tagGear
{
	EQUIPTYPE equipType;
	float value;
	bool isEquip;
};

//스킬 배움 안배움
enum learnActiveSkills
{
	NONE_ACTIVE, GET_ACTIVE
};
enum learnPassiveSkills
{
	NONE1, NONE2, NONE_PASSIVE, GET_PASSIVE
};
//스킬
struct tagSkills
{
	image* WindowFrameActiveImage;
	image* WindowFramePassiveImage;

	image* SkillActiveExImage;
	image* SkillPassiveExImage;

	learnActiveSkills learnActive;
	learnPassiveSkills learnPassive;	
};
class myPlayer :	public gameNode
{
private:

	//클래스 전방선언 / 상호참조
	dungeonSecen* dungeonSecen;
	//플레이어 구조
	tagPlayer player;
	
	//각 창들 키는 값
	bool statusFrameIsOn;		//스탯
	bool invenFrameIsOn;	//인벤
	bool skillFrameIsOn;	//스킬

	//스탯창 이미지
	image* playerStatusFrameImage;
	image* playerStatusFrameBackImage;
	//스탯창 종료 버튼 RC//이미지
	RECT playerStatusFrameExitRc;
	image* playerStatusFrameExitOverImage;
	//컴뱃 스탯 선택 렉트
	tagStatusiInfo combatStatus;	
	//마법 스탯 선택 렉트
	tagStatusiInfo magicStatus;
	//레지 스탯 선택 렉트
	tagStatusiInfo resStatus;


	//스킬창 이미지
	image* playerSkillWindowImage;
	//스킬창/인벤창 종료 버튼 RC//이미지
	RECT  playerSkillWindowExitRc;
	image*  playerSkillWindowExitOverImage;
	//스킬창 타입 이미지 
	image* playerSkillTypeFrameImage;
	//스킬창 타입 렉트
	RECT playerSkillTypeSelectRc[PLAYER_SKILL_TYPE_MAX];
	//스킬타입 마우스 오버
	image* playerSkillTypeImage[PLAYER_SKILL_TYPE_MAX];
	//스킬타입 불
	bool playerSkillTypeIstouch[PLAYER_SKILL_TYPE_MAX];
	//스킬 렉트 마우스 오버
	image* skillsRectOverImage;
	//액티브/패시브 스킬 렉트	
	RECT activeSkillRc;
	RECT passiveSkillRc;
	//스킬
	tagSkills playerSkills[PLAYER_SKILL_TYPE_MAX];
	

	//인벤토리 창 이미지
	image* playerInvenFrameImage;

	//무기EQUIP_RECT
	RECT weaponEquipRc;
	//방패EQUIP_RECT
	RECT shieldEquipRc;
	//아머EQUIP_RECT
	RECT armorEquipRc;
	//투구EQUIP_RECT
	RECT helmetEquipRc;
	//장갑EQUIP_RECT
	RECT gloveEquipRc;
	//부츠EQUIP_RECT
	RECT bootEquipRc;
	//벨트EQUIP_RECT
	RECT beltEquipRc;	
	//목걸이EQUIP_RECT
	RECT necklaceEquipRc;
	//반지(왼)EQUIP_RECT
	RECT leftRingEquipRc;
	//반지(오른)EQUIP_RECT
	RECT rightRingEquipRc;
	//인벤토리 렉트
	tagInvenRc invenRc[INVEN_RECT_Y][INVEN_RECT_X];
	//하단 UI
	image* playerUIImage;

	

public:
	

	HRESULT init();
	void release();
	void update();
	void render();
	//스탯창에서 정보 보기



	
	//장비창 렉트 색칠하기
	void ptInGreenRect(RECT _rc);
	//스킬 타입 마우스 오버
	void selectSkillTypeMover(int _i);
	//스킬 액티브/패시브
	void skillsWindow(int _i);
	//플레이어 겟
	tagPlayer getMyPlayer() { return player; }
	//플레이어 렉트 겟
	RECT getMyplayerRect() { return player.rc; }
	//플레이어 방향 설정
	void setPlayerDirection(PLAYERDIRECTION _d) { player.direction = _d; }
	//플레이어 좌우 공격 이미지 셋
	void setXPlayerAtackToMonster(float _motion) { player.img->setX(player.img->getX() + _motion); }
	//인벤토리 이미지
	image* getInven() { return playerInvenFrameImage; }
	tagInvenRc getInvenRect(int _x, int _y) { return  invenRc[_x][_y]; }
	//플레이어 이미지 렌더 함수
	void playerImageRender(tagPlayer _player);
	//공격 모션 위치 설정
	bool setIsPlayerAttack(int _i) { return player.attackDirection[_i] = true; }
	void playerAttackImg(int _i);

	//오브젝트들 웨이빙 하기
	void wavingObject(RECT _rc, image* _img);
	myPlayer() {}
	~myPlayer() {}
};

