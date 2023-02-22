#pragma once


//캐릭터 메인 주능력치 정보
struct tagMainStatus
{
	int lv;
	int strength;
	int agillity;
	int perception;
	int tellect;
	int willpower;		
	int abilityPoint;
	int skillPoint;
};

//컴뱃 인포 정보
struct tagCombatStatus
{
	int maxHp;	
	int currentHp;
	int hpRegen;
	int damage;
	int defence;
	int rangeDamage;
	int weaponDamage;
	int criticalDamage;
	int criticalChance;
	int accuracy;
	int evasionChance;	
};

//마법 정보
struct tagMagicStatus
{
	int MaxMp;
	int currentMp;
	int magicDamage;
	int magicDefence;
	int magicEvasionChance;
};

//저항 정보
struct tagResStatus
{
	int hunger;
	int thirst;
	int poison;
	int elemental;
	int bleeding;
};