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

//�κ��丮 ��Ʈ ������
#define INVEN_RECT_Y 5
#define INVEN_RECT_X 10

//������� ��Ʈ ������
#define ALL_EQUIP_WIDTH 106
#define WEAPON_EQUIP_HEIGHT 160
#define SHIELD_EQUIP_HEIGHT 160
#define ARMOR_EQUIP_HEIGHT 160
#define HELMET_EQUIP_HEIGHT 106
#define GLOVE_EQUIP_HEIGHT 106
#define BOOT_EQUIP_HEIGHT 106
#define BELT_EQUIP_HEIGHT 52

//�Ǽ����� ��Ʈ ������
#define ACC_EQUIP_WIDTH 52
#define ACC_EQUIP_HEIGHT 52

//# �׸��� ���İ�

#define SHADOW_ALPHA 100
//Ŭ���� ���漱�� / ��ȣ����
//������
class dungeonSecen;



enum PLAYERDIRECTION
{
	PLAYER_RIGTH, PLAYER_LEFT
};

//�÷��̾�
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

//���� ����
struct tagStatusiInfo
{
	image* selectImage;
	image* infoImage;
	RECT rc;
	bool isClick;
	int scroll;
};
//�κ� ��Ʈ
struct tagInvenRc
{
	RECT rc;
	int idX, IdY;
	int width, height;
	float x, y;
};

//��� Ÿ��
enum EQUIPTYPE
{
	WEAPOM, SHIELD, ARMOR, 
	HELMET, GLOVE, BOOT, 
	LEFT_RING, RIGHT_RING, NECKLACE
};

//�����
struct tagGear
{
	EQUIPTYPE equipType;
	float value;
	bool isEquip;
};

//��ų ��� �ȹ��
enum learnActiveSkills
{
	NONE_ACTIVE, GET_ACTIVE
};
enum learnPassiveSkills
{
	NONE1, NONE2, NONE_PASSIVE, GET_PASSIVE
};
//��ų
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

	//Ŭ���� ���漱�� / ��ȣ����
	dungeonSecen* dungeonSecen;
	//�÷��̾� ����
	tagPlayer player;
	
	//�� â�� Ű�� ��
	bool statusFrameIsOn;		//����
	bool invenFrameIsOn;	//�κ�
	bool skillFrameIsOn;	//��ų

	//����â �̹���
	image* playerStatusFrameImage;
	image* playerStatusFrameBackImage;
	//����â ���� ��ư RC//�̹���
	RECT playerStatusFrameExitRc;
	image* playerStatusFrameExitOverImage;
	//�Ĺ� ���� ���� ��Ʈ
	tagStatusiInfo combatStatus;	
	//���� ���� ���� ��Ʈ
	tagStatusiInfo magicStatus;
	//���� ���� ���� ��Ʈ
	tagStatusiInfo resStatus;


	//��ųâ �̹���
	image* playerSkillWindowImage;
	//��ųâ/�κ�â ���� ��ư RC//�̹���
	RECT  playerSkillWindowExitRc;
	image*  playerSkillWindowExitOverImage;
	//��ųâ Ÿ�� �̹��� 
	image* playerSkillTypeFrameImage;
	//��ųâ Ÿ�� ��Ʈ
	RECT playerSkillTypeSelectRc[PLAYER_SKILL_TYPE_MAX];
	//��ųŸ�� ���콺 ����
	image* playerSkillTypeImage[PLAYER_SKILL_TYPE_MAX];
	//��ųŸ�� ��
	bool playerSkillTypeIstouch[PLAYER_SKILL_TYPE_MAX];
	//��ų ��Ʈ ���콺 ����
	image* skillsRectOverImage;
	//��Ƽ��/�нú� ��ų ��Ʈ	
	RECT activeSkillRc;
	RECT passiveSkillRc;
	//��ų
	tagSkills playerSkills[PLAYER_SKILL_TYPE_MAX];
	

	//�κ��丮 â �̹���
	image* playerInvenFrameImage;

	//����EQUIP_RECT
	RECT weaponEquipRc;
	//����EQUIP_RECT
	RECT shieldEquipRc;
	//�Ƹ�EQUIP_RECT
	RECT armorEquipRc;
	//����EQUIP_RECT
	RECT helmetEquipRc;
	//�尩EQUIP_RECT
	RECT gloveEquipRc;
	//����EQUIP_RECT
	RECT bootEquipRc;
	//��ƮEQUIP_RECT
	RECT beltEquipRc;	
	//�����EQUIP_RECT
	RECT necklaceEquipRc;
	//����(��)EQUIP_RECT
	RECT leftRingEquipRc;
	//����(����)EQUIP_RECT
	RECT rightRingEquipRc;
	//�κ��丮 ��Ʈ
	tagInvenRc invenRc[INVEN_RECT_Y][INVEN_RECT_X];
	//�ϴ� UI
	image* playerUIImage;

	

public:
	

	HRESULT init();
	void release();
	void update();
	void render();
	//����â���� ���� ����



	
	//���â ��Ʈ ��ĥ�ϱ�
	void ptInGreenRect(RECT _rc);
	//��ų Ÿ�� ���콺 ����
	void selectSkillTypeMover(int _i);
	//��ų ��Ƽ��/�нú�
	void skillsWindow(int _i);
	//�÷��̾� ��
	tagPlayer getMyPlayer() { return player; }
	//�÷��̾� ��Ʈ ��
	RECT getMyplayerRect() { return player.rc; }
	//�÷��̾� ���� ����
	void setPlayerDirection(PLAYERDIRECTION _d) { player.direction = _d; }
	//�÷��̾� �¿� ���� �̹��� ��
	void setXPlayerAtackToMonster(float _motion) { player.img->setX(player.img->getX() + _motion); }
	//�κ��丮 �̹���
	image* getInven() { return playerInvenFrameImage; }
	tagInvenRc getInvenRect(int _x, int _y) { return  invenRc[_x][_y]; }
	//�÷��̾� �̹��� ���� �Լ�
	void playerImageRender(tagPlayer _player);
	//���� ��� ��ġ ����
	bool setIsPlayerAttack(int _i) { return player.attackDirection[_i] = true; }
	void playerAttackImg(int _i);

	//������Ʈ�� ���̺� �ϱ�
	void wavingObject(RECT _rc, image* _img);
	myPlayer() {}
	~myPlayer() {}
};

