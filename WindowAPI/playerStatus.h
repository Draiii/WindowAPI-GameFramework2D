#pragma once


//ĳ���� ���� �ִɷ�ġ ����
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

//�Ĺ� ���� ����
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

//���� ����
struct tagMagicStatus
{
	int MaxMp;
	int currentMp;
	int magicDamage;
	int magicDefence;
	int magicEvasionChance;
};

//���� ����
struct tagResStatus
{
	int hunger;
	int thirst;
	int poison;
	int elemental;
	int bleeding;
};