 #pragma once
/*
Este header, ira compartilhar as structs entre servidor e client a medida que o mesmo for sendo atualizado
outros headers também poder´ser criado como de constantes por exemplo.
*/

#ifndef _SHAREDSTRUCTS_ // Last updated 27/01/2013

#define _SHAREDSTRUCTS_

#define _MSG      	short		  Size;			\
					char		  KeyWord;		\
					char		  CheckSum;		\
					short		  Type;			\
					short		  ID;			\
					unsigned int  ClientTick;

struct MSG_HSTANDARD
{
	short Size;
	char KeyWord;
	char CheckSum;
	short Type;
	short ID;
	int Tick;
};

#define _PCKHEADER MSG_HSTANDARD Header

#ifdef _WYDCLIENT
struct		 MSG_STANDARD
{
	short Size;
	char KeyWord;
	char CheckSum;
	short Type;
	short ID;
	int Tick;
};
#endif // _WYDCLIENT

#pragma pack(push, 1)
union STRUCT_BONUSEFFECT
{
	struct
	{
		unsigned char cEffect;
		unsigned char cValue;
	};
	short sValue;
};
struct STRUCT_ITEM
{
	short sIndex;
	STRUCT_BONUSEFFECT stEffect[3];


	bool EquipCostume()
	{
		//Trajes communs
		if (this->sIndex >= 4150 && this->sIndex <= 4189)
			return true;

		//Trajes novos
		if (this->sIndex >= 4300 && this->sIndex < 4899)
			return true;

		return false;
	}
	int GetTimePet(int DefaultValue = 30)
	{
		//3 Dias
		if (this->sIndex >= 3980 && this->sIndex <= 3982)
			return 3;
		//15 Dias
		else if (this->sIndex >= 3983 && this->sIndex <= 3985)
			return 15;
		//30 Dias
		else if (this->sIndex >= 3986 && this->sIndex <= 3989)
			return 30;

		//Other
		return DefaultValue;
	}
	bool EsferaPet()
	{
		//Esferas communs
		if (this->sIndex >= 3980 && this->sIndex <= 3994)
			return true;

		//Esferas novos
		if (this->sIndex >= 3995 && this->sIndex < 3999)
			return true;

		return false;
	}
	unsigned char getSancValue()
	{
		if (this->sIndex >= 2360 && this->sIndex <= 2389)
			return this->stEffect[2].cValue;

		if (this->stEffect[0].cEffect == 43)
			return this->stEffect[0].cValue;
		else if (this->stEffect[1].cEffect == 43)
			return this->stEffect[1].cValue;
		else if (this->stEffect[2].cEffect == 43)
			return this->stEffect[2].cValue;

		else if (this->stEffect[0].cEffect >= 116 && this->stEffect[0].cEffect <= 125)
			return this->stEffect[0].cValue;

		else if (this->stEffect[1].cEffect >= 116 && this->stEffect[1].cEffect <= 125)
			return this->stEffect[1].cValue;

		else if (this->stEffect[2].cEffect >= 116 && this->stEffect[2].cEffect <= 125)
			return this->stEffect[2].cValue;

		else
			return 0;
	}
};

struct		  MSG_AccountLogin
{
	_PCKHEADER;

	char AccountPassword[16];
	char AccountName[12];
	char Zero[52];
	int  ClientVersion;
	int  DBNeedSave;
	int AdapterName[4];
};

struct STRUCT_SCORE
{
	short Level;
	int Ac;
	int Damage;
	char Reserved;
	char AttackRun;
	int MaxHp;
	int MaxMp;
	int Hp;
	int Mp;
	short Str;
	short Int;
	short Dex;
	short Con;
	unsigned short Special[4];
};


struct STRUCT_MOBNPC
{
	char MobName[16];
	char Clan;
	char Merchant;
	unsigned short Guild;
	char Class;
	char Rsv;
	unsigned short Quest;
	int Coin;
	long long Exp;
	unsigned short HomeTownX;
	unsigned short HomeTownY;
	STRUCT_SCORE BaseScore;
	STRUCT_SCORE CurrentScore;
	STRUCT_ITEM Equip[16];
	STRUCT_ITEM Carry[64];
	unsigned int LearnedSkill;
	short ScoreBonus;
	short SpecialBonus;
	short SkillBonus;
	char Critical;
	char SaveMana;
	char ShortSkill[4];
	char GuildLevel;
	char Magic;
	char RegenHP;
	char RegenMP;
	union
	{
		char  Resist[4];	 // The mob's resistencies, to fire / ice / thunder / magic
		struct
		{
			char   Fogo;
			char   Gelo;
			char   Sagrado;
			char   Trovao;
		} Resistencia;//[4]
	};
	unsigned short CurrentKill;
	unsigned short TotalKill;
	char UNS[244];
};

struct STRUCT_MOB
{
	char MobName[16];
	char Clan;
	char Merchant;
	unsigned short Guild;
	char Class;
	char Rsv;
	unsigned short Quest;
	int Coin;
	long long Exp;
	unsigned short HomeTownX;
	unsigned short HomeTownY;
	STRUCT_SCORE BaseScore;
	STRUCT_SCORE CurrentScore;
	STRUCT_ITEM Equip[18];
	STRUCT_ITEM Carry[64];
	unsigned int LearnedSkill[2];
	short ScoreBonus;
	short SpecialBonus;
	short SkillBonus;
	char Critical;
	char SaveMana;
	char ShortSkill[4];
	char GuildLevel;
	char Magic;
	char RegenHP;
	char RegenMP;
	union
	{
		char  Resist[4];	 // The mob's resistencies, to fire / ice / thunder / magic
		struct
		{
			char   Fogo;
			char   Gelo;
			char   Sagrado;
			char   Trovao;
		} Resistencia;//[4]
	};
	unsigned short CurrentKill;
	unsigned short TotalKill;

	bool HasSoulSkill() const
	{
		return this->LearnedSkill[0] & 0x40000000;
	}
};


struct MSG_UpdateEtc
{
	_PCKHEADER;
	int FakeExp;
	long long Exp;
	unsigned int LearnedSkill[2];
	short ScoreBonus;
	short SpecialBonus;
	short SkillBonus;
	int Coin;
};


struct MSG_UpdateScore
{
	_PCKHEADER;
	STRUCT_SCORE Score;
	char Critical;
	char SaveMana;
	unsigned short Affect[32];
	unsigned short Guild;
	unsigned short GuildLevel;
	union
	{
		char  Resist[4];	 // The mob's resistencies, to fire / ice / thunder / magic
		struct
		{
			char   Fogo;
			char   Gelo;
			char   Sagrado;
			char   Trovao;
		} Resistencia;//[4]
	};
	int ReqHp;
	int ReqMp;
	unsigned short Magic;
	unsigned short Rsv;
	char LearnedSkill;
};
#pragma pack(pop)

#endif