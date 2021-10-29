#ifndef GAME_ENEMYINFO_H
#define GAME_ENEMYINFO_H

#include "types.h"

namespace Game {

// Epoch's Structs
// size 0x34, alignment 0x1
struct EnemyInfo {
	char* name;
	char ID;
	char parentID;
	char members;
	short flags;
	char* model_name;
	char* anim_name;
	char* animmgr_name;
	char* texture_name;
	char* param_name;
	char* collision_name;
	char* stone_name;
	int childID;
	int childNum;
	char bitter_drops;
};

typedef enum EEnemyTypeID {
	Armor          = 15,
	Baby           = 31,
	BigFoot        = 69,
	BigTreasure    = 73,
	BlackMan       = 99,
	BlackPom       = 6,
	BlueChappy     = 42,
	BlueKochappy   = 44,
	BluePom        = 3,
	Bomb           = 36,
	BombOtakara    = 93,
	BombSarai      = 58,
	Catfish        = 26,
	Chappy         = 2,
	Chiyogami      = 89,
	Clover         = 47,
	DaiodoGreen    = 86,
	DaiodoRed      = 85,
	Damagumo       = 56,
	DangoMushi     = 94,
	Demon          = 32,
	Egg            = 37,
	ElecBug        = 28,
	ElecHiba       = 22,
	ElecOtakara    = 62,
	Fart           = 11,
	FireChappy     = 33,
	FireOtakara    = 59,
	Fkabuto        = 96,
	FminiHoudai    = 97,
	Frog           = 17,
	Fuefuki        = 41,
	GasHiba        = 21,
	GasOtakara     = 61,
	Hana           = 84,
	Hanachirashi   = 55,
	Hiba           = 20,
	HikariKinoko   = 48,
	Houdai         = 66,
	Imomushi       = 65,
	Jigumo         = 63,
	Kabuto         = 75,
	KareOoinu_l    = 92,
	KareOoinu_s    = 91,
	KingChappy     = 53,
	Kochappy       = 1,
	Kogane         = 9,
	KumaChappy     = 35,
	KumaKochappy   = 76,
	Kurage         = 57,
	LeafChappy     = 67,
	Magaret        = 87,
	Mar            = 29,
	MaroFrog       = 18,
	MiniHoudai     = 78,
	Miulin         = 54,
	INVALID        = 39,
	INVALID2       = 64,
	Nekojarashi    = 88,
	OniKurage      = 72,
	OoPanModoki    = 40,
	Ooinu_l        = 50,
	Ooinu_s        = 49,
	PanHouse       = 83,
	PanModoki      = 38,
	Pelplant       = 0,
	Pom            = 82,
	Queen          = 30,
	Qurione        = 16,
	RandPom        = 8,
	RedPom         = 4,
	Rkabuto        = 95,
	Rock           = 19,
	Sarai          = 23,
	ShijimiChou    = 77,
	SnakeCrow      = 34,
	SnakeWhole     = 70,
	Sokkuri        = 79,
	Stone          = 74,
	Tadpole        = 27,
	TamagoMushi    = 68,
	Tank           = 24,
	Tanpopo        = 46,
	Tobi           = 14,
	Tukushi        = 80,
	Tyre           = 98,
	UjiA           = 12,
	UjiB           = 13,
	UmiMushi       = 71,
	UmiMushiBase   = 100,
	UmiMushiBlind  = 101,
	Wakame_l       = 52,
	Wakame_s       = 51,
	Watage         = 81,
	WaterOtakara   = 60,
	Wealthy        = 10,
	WhitePom       = 7,
	Wtank          = 25,
	YellowChappy   = 43,
	YellowKochappy = 45,
	YellowPom      = 5,
	Zenmai         = 90
} EEnemyTypeID;

// clang-format off
	struct EnemyInfo gEnemyInfo[100] = {
		//  name                   ID	pID		members	flags	model			anim			animgr			texture		param		collision		stone			childID chNum	droptype
			{"Pelplant",           0,	-1,		1,		0x0007,	"Pelplant",		"Pelplant",		"Pelplant",		"Pelplant", "Pelplant", "Pelplant",		"Pelplant",		-1,		0,		4},
			{"Kochappy",           1,	-1,		1,		0x0117,	"",				"",				"",				"",         "",         "",				"",				-1,		0,		1},
			{"BlueKochappy",       44,	-1,		1,		0x0117,	"Kochappy",		"Kochappy",		"Kochappy",		"",         "",         "Kochappy",		"Kochappy",		-1,		0,		1},
			{"YellowKochappy",     45,	-1,		1,		0x0117,	"Kochappy",		"Kochappy",		"Kochappy",		"",         "",         "Kochappy",		"Kochappy",		-1,		0,		1},
			{"KumaKochappy",       76,	-1,		1,		0x0117,	"",				"Kochappy",		"Kochappy",		"",         "",         "Kochappy",		"",				-1,		0,		1},
			{"Chappy",             2,	-1,		1,		0x0097,	"",				"",				"",				"",         "",         "",				"",				-1,		0,		2},
			{"BlueChappy",         42,	-1,		1,		0x0097,	"Chappy",		"Chappy",		"Chappy",		"",         "",         "Chappy",		"Chappy",		-1,		0,		2},
			{"YellowChappy",       43,	-1,		1,		0x0097,	"Chappy",		"Chappy",		"Chappy",		"",         "",         "Chappy",		"Chappy",		-1,		0,		2},
			{"Pom",                82,	-1,		1,		0x0001,	"Pom",			"Pom",			"Pom",			"Pom",      "Pom",      "Pom",			"Pom",			-1,		0,		4},
			{"BluePom",            3,	82,		1,		0x0006,	"Pom",			"Pom",			"Pom",			"Pom",      "Pom",      "Pom",			"Pom",			-1,		0,		4},
			{"RedPom",             4,	82,		1,		0x0006,	"Pom",			"Pom",			"Pom",			"Pom",      "Pom",      "Pom",			"Pom",			-1,		0,		4},
			{"YellowPom",          5,	82,		1,		0x0006,	"Pom",			"Pom",			"Pom",			"Pom",      "Pom",		"Pom",			"Pom",			-1,		0,		4},
			{"BlackPom",           6,	82,		1,		0x0006,	"Pom",			"Pom",			"Pom",			"Pom",      "Pom",		"Pom",			"Pom",			-1,		0,		4},
			{"WhitePom",           7,	82,		1,		0x0006,	"Pom",			"Pom",			"Pom",			"Pom",      "Pom",		"Pom",			"Pom",			-1,		0,		4},
			{"RandPom",            8,	82,		1,		0x0006,	"Pom",			"Pom",			"Pom",			"Pom",      "Pom",		"Pom",			"Pom",			-1,		0,		4},
			{"Kogane",             9,	-1,		1,		0x0007,	"",				"",				"",				"",         "",			"",				"",				-1,		0,		4},
			{"Wealthy",            10,	-1,		1,		0x0007,	"Kogane",		"Kogane",		"Kogane",		"",         "",			"Kogane",		"Kogane",		-1,		0,		4},
			{"Fart",               11,	-1,		1,		0x0007,	"Kogane",		"Kogane",		"Kogane",		"",         "",			"Kogane",		"Kogane",		-1,		0,		4},
			{"Frog",               17,	-1,		1,		0x0097,	"",				"",				"",				"",         "",			"",				"",				-1,		0,		2},
			{"MaroFrog",           18,	-1,		1,		0x0097,	"",				"",				"",				"",         "",			"",				"",				-1,		0,		2},
			{"UjiA",               12,	-1,		1,		0x0007,	"",				"",				"",				"",         "",			"",				"",				-1,		0,		0},
			{"UjiB",               13,	-1,		1,		0x0117,	"",				"UjiA",			"",				"",         "",			"",				"",				-1,		0,		0},
			{"Armor",              15,	-1,		1,		0x0097,	"",				"",				"",				"",         "",			"",				"",				-1,		0,		2},
			{"Tobi",               14,	-1,		1,		0x0117,	"",				"",				"",				"",         "",			"",				"",				-1,		0,		0},
			{"Imomushi",           65,	-1,		1,		0x0007,	"",				"",				"",				"",         "",			"",				"",				-1,		0,		0},
			{"Qurione",            16,	-1,		1,		0x0007,	"",				"",				"",				"",         "",			"",				"",				25,		1,		4},
			{"Rock",			   19,	-1,		1,		0x0207,	"",				"",				"",				"",         "",			"",				"",				-1,		0,		4},
			{"Stone",			   74,	13,		1,		0x0206,	"Rock",			"Rock",			"Rock",			"Rock",		"Rock",		"Rock",			"Rock",			-1,		0,		4},
			{"Kabuto",			   75,	-1,		1,		0x0097,	"",				"",				"",				"",			"",			"",				"",				74,		5,		1},
			{"RKabuto",			   95,	-1,		1,		0x0097,	"Kabuto",		"Kabuto",		"Kabuto",		"",			"",			"Kabuto",		"Kabuto",		74,		5,		1},
			{"FKabuto",			   96,	-1,		1,		0x0097,	"Kabuto",		"Kabuto",		"Kabuto",		"",			"",			"Kabuto",		"Kabuto",		74,		5,		1},
			{"Hiba",			   20,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"GasHiba",			   21,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"ElecHiba",		   22,	-1,		2,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Sarai",			   23,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"Demon",			   32,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"BombSarai",		   58,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				36,		2,		2},
			{"Tank",			   24,	-1,		1,		0x0097,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"Wtank",			   25,	-1,		1,		0x0097,	"Tank",			"Tank",			"Tank",			"",			"",			"Tank",			"Tank",			-1,		0,		2},
			{"Catfish",			   26,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		1},
			{"Tadpole",			   27,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		0},
			{"ElecBug",			   28,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		1},
			{"Mar",				   29,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"Hanachirashi",	   55,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"Kurage",			   57,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		1},
			{"OniKurage",		   72,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"Queen",			   30,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				31,		50,		7},
			{"Baby",			   31,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		0},
			{"FireChappy",		   33,	-1,		1,		0x0097,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"Hana",			   84,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"KumaChappy",		   35,	-1,		1,		0x0097,	"",				"Chappy",		"",				"",			"",			"",				"",				-1,		0,		2},
			{"LeafChappy",		   67,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"SnakeCrow",		   34,	-1,		1,		0x0037,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		7},
			{"SnakeWhole",		   70,	-1,		1,		0x0037,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		7},
			{"Bomb",			   36,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Egg",				   37,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				68,		10,		4},
			{"PanModoki",		   38,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				83,		1,		4},
			{"OoPanModoki",		   40,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				83,		1,		4},
			{"PanHouse",		   83,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Fuefuki",			   41,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"Tanpopo",			   46,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				77,		5,		4},
			{"Watage",			   81,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Clover",			   47,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"HikariKinoko",	   48,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Ooinu_s",			   49,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"KareOoinu_s",		   91,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Ooinu_l",			   50,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				77,		5,		4},
			{"KareOoinu_l",		   92,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Wakame_s",		   51,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Wakame_l",		   52,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Tukushi",			   80,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"DaiodoRed",		   85,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"DaiodoGreen",		   86,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Magaret",			   87,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				77,		5,		4},
			{"Nekojarashi",		   88,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Chiyogami",		   89,	-1,		1,		0x0207,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"Zenmai",			   90,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"KingChappy",		   53,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		7},
			{"Miulin",			   54,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		2},
			{"Damagumo",		   56,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		7},
			{"BigFoot",			   69,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				68,		30,		7},
			{"Houdai",			   66,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		7},
			{"FireOtakara",		   59,	-1,		1,		0x0007,	"",				"",				"Otakara",		"",			"",			"Otakara",		"Otakara",		-1,		0,		1},
			{"WaterOtakara",	   60,	-1,		1,		0x0007,	"FireOtakara",	"FireOtakara",	"Otakara",		"",			"",			"Otakara",		"Otakara",		-1,		0,		1},
			{"GasOtakara",		   61,	-1,		1,		0x0007,	"FireOtakara",	"FireOtakara",	"Otakara",		"",			"",			"Otakara",		"Otakara",		-1,		0,		1},
			{"ElecOtakara",		   62,	-1,		1,		0x0007,	"FireOtakara",	"FireOtakara",	"Otakara",		"",			"",			"Otakara",		"Otakara",		-1,		0,		1},
			{"Jigumo",			   63,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				83,		1,		2},
			{"TamagoMushi",		   68,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		0},
			{"UmiMushiBase",	   100,	-1,		1,		0x0001,	"UmiMushi",		"UmiMushi",		"UmiMushi",		"UmiMushi",	"UmiMushi",	"UmiMushi",		"UmiMushi",		-1,		0,		7},
			{"UmiMushi",		   71,	100,	1,		0x0006,	"UmiMushi",		"UmiMushi",		"UmiMushi",		"UmiMushi",	"UmiMushi",	"UmiMushi",		"UmiMushi",		-1,		0,		7},
			{"UmiMushiBlind",	   101,	100,	1,		0x0006,	"UmiMushi",		"UmiMushi",		"UmiMushi",		"UmiMushi",	"UmiMushi",	"UmiMushi",		"UmiMushi",		-1,		0,		2},
			{"BigTreasure",		   73,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		8},
			{"ShijimiChou",		   77,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"MiniHoudai",		   78,	-1,		1,		0x0097,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		1},
			{"FminiHoudai",		   97,	-1,		1,		0x0097,	"MiniHoudai",	"MiniHoudai",	"MiniHoudai",	"",			"",			"MiniHoudai",	"MiniHoudai",	-1,		0,		1},
			{"Sokkuri",			   79,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		0},
			{"BombOtakara",		   93,	-1,		1,		0x0007,	"FireOtakara",	"FireOtakara",	"Otakara",		"",			"",			"Otakara",		"Otakara",		36,		1,		1},
			{"BlackMan",		   99,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				98,		1,		7},
			{"Tyre",			   98,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		4},
			{"DangoMushi",		   94,	-1,		1,		0x0007,	"",				"",				"",				"",			"",			"",				"",				-1,		0,		7},
	};
// clang-format on

extern int gEnemyInfoNum = sizeof gEnemyInfo / sizeof gEnemyInfo[0];

namespace EnemyInfoFunc {
	EnemyInfo* getEnemyInfo(int, int);
	char* getEnemyName(int, int);
	char* getEnemyResName(int, int);
	char getEnemyMember(int, int);
	int getEnemyID(char*, int);

} // namespace EnemyInfoFunc
} // namespace Game
#endif
