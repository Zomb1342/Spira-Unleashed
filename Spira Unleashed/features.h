#include <Windows.h>
#include <map>
#include <string>
#include <string_view>
#include <iostream>
#include <iomanip>
#pragma once

// feature related enums/data

enum CharacterNames
{
	TIDUS = 0, YUNA, AURON, KIMAHRI, WAKKA, LULU, RIKKU
};

// feature related classes / structs

struct Feature
{

public:

	std::string featureName;
	bool isEnabled = false;
};

struct Weapons
{
	uint8_t idNumber = 0;
	uint8_t abilitySlots = 0;
	uint8_t weaponIcon = 0;
	uint8_t weaponModel = 0;
	uint8_t weaponAbilities[4] = { 0, 0, 0 ,0 };
	bool useCharModel = false;
};

struct Armors
{
	uint8_t idNumber = 0;
	uint8_t abilitySlots = 0;
	uint8_t armorIcon = 0;
	uint8_t armorModel = 0;
	uint8_t armorAbilities[4] = { 0, 0, 0 ,0 };
	bool useCharModel = false;
};

class Character
{

public:
	// public variables/data

	Character(CharacterNames name, HANDLE procHandle, uintptr_t modBase)
	{
		processHandle = procHandle;
		moduleBase = modBase;
		battleBasePtr = modBase + 0xD334CC;

		switch (name)
		{
		case TIDUS:																	
		{

			hpOffset = 0xD32078;
			mpOffset = 0xD3207C;
			hpCapOffset = 0xD32080;
			mpCapOffset = 0xD32084;
			sLvOffset = 0xD32097;
			strengthOffset = 0xD32068;
			defenseOffset = 0xD32069;
			magicOffset = 0xD3206A;
			magicDefenseOffset = 0xD3206B;
			agilityOffset = 0xD3206C;
			luckOffset = 0xD3206D;
			EvasionOffset = 0xD3206E;
			accuracyOffset = 0xD3206F;
			tempStrengthOffset = 0xD3208B;
			tempDefenseOffset = 0xD3208C;
			tempMagicOffset = 0xD3208D;
			tempMagicDefenseOffset = 0xD3208E;
			tempAgilityOffset = 0xD3208F;
			tempLuckOffset = 0xD32090;
			tempEvasionOffset = 0xD32091;
			tempAccuracyOffset = 0xD32092;
			overdriveModeOffset = 0xD32094;
			overdriveCapOffset = 0xD32096;
			overdriveMeterOffset = 0xD32095;
			battleHpOffset = 0x5D0;
			battleMpOffset = 0x5D4;
			battleHpCapOffset = 0x594;
			battleMpCapOffset = 0x0;
			battleOverdriveOffset = 0x5BC;

			break;
		}

		case YUNA:																	
		{

			hpOffset = 0xD3210C;
			mpOffset = 0xD32110;
			hpCapOffset = 0xD32114;
			mpCapOffset = 0xD32118;
			sLvOffset = 0xD3212B;
			strengthOffset = 0xD320FC;
			defenseOffset = 0xD320FD;
			magicOffset = 0xD320FE;
			magicDefenseOffset = 0xD320FF;
			agilityOffset = 0xD32100;
			luckOffset = 0xD32101;
			EvasionOffset = 0xD32102;
			accuracyOffset = 0xD32103;
			tempStrengthOffset = 0xD3211F;
			tempDefenseOffset = 0xD32120;
			tempMagicOffset = 0xD32121;
			tempMagicDefenseOffset = 0xD32122;
			tempAgilityOffset = 0xD32123;
			tempLuckOffset = 0xD32124;
			tempEvasionOffset = 0xD32125;
			tempAccuracyOffset = 0xD32126;
			overdriveModeOffset = 0xD32128;
			overdriveCapOffset = 0xD32129;
			overdriveMeterOffset = 0xD3212A;
			battleHpOffset = 0x1560;
			battleMpOffset = 0x1564;
			battleHpCapOffset = 0x0;
			battleMpCapOffset = 0x0;
			battleOverdriveOffset = 0x154C;

			break;
		}

		case AURON:																	
		{

			hpOffset = 0xD321A0;
			mpOffset = 0xD321A4;
			hpCapOffset = 0xD321A8;
			mpCapOffset = 0xD321AC;
			sLvOffset = 0xD321BF;
			strengthOffset = 0xD32190;
			defenseOffset = 0xD32191;
			magicOffset = 0xD32192;
			magicDefenseOffset = 0xD32193;
			agilityOffset = 0xD32194;
			luckOffset = 0xD32195;
			EvasionOffset = 0xD32196;
			accuracyOffset = 0xD32197;
			tempStrengthOffset = 0xD321B3;
			tempDefenseOffset = 0xD321B4;
			tempMagicOffset = 0xD321B5;
			tempMagicDefenseOffset = 0xD321B6;
			tempAgilityOffset = 0xD321B7;
			tempLuckOffset = 0xD321B8;
			tempEvasionOffset = 0xD321B9;
			tempAccuracyOffset = 0xD321BA;
			overdriveModeOffset = 0xD321BC;
			overdriveCapOffset = 0xD321BD;
			overdriveMeterOffset = 0xD321BE;
			battleHpOffset = 0x24F0;
			battleMpOffset = 0x24F4;
			battleHpCapOffset = 0x0;
			battleMpCapOffset = 0x0;
			battleOverdriveOffset = 0x24DC;

			break;
		}

		case KIMAHRI:																
		{

			hpOffset = 0xD32234;
			mpOffset = 0xD32238;
			hpCapOffset = 0xD3223C;
			mpCapOffset = 0xD32240;
			sLvOffset = 0xD32253;
			strengthOffset = 0xD32224;
			defenseOffset = 0xD32225;
			magicOffset = 0xD32226;
			magicDefenseOffset = 0xD32227;
			agilityOffset = 0xD32228;
			luckOffset = 0xD32229;
			EvasionOffset = 0xD3222A;
			accuracyOffset = 0xD3222B;
			tempStrengthOffset = 0xD32247;
			tempDefenseOffset = 0xD32248;
			tempMagicOffset = 0xD32249;
			tempMagicDefenseOffset = 0xD3224A;
			tempAgilityOffset = 0xD3224B;
			tempLuckOffset = 0xD3224C;
			tempEvasionOffset = 0xD3224D;
			tempAccuracyOffset = 0xD3224E;
			overdriveModeOffset = 0xD32250;
			overdriveCapOffset = 0xD32252;
			overdriveMeterOffset = 0xD32251;
			battleHpOffset = 0x3480;
			battleMpOffset = 0x3484;
			battleHpCapOffset = 0x0;
			battleMpCapOffset = 0x0;
			battleOverdriveOffset = 0x346C;

			break;
		}

		case WAKKA:																	
		{
			hpOffset = 0xD322C8;
			mpOffset = 0xD322CC;
			hpCapOffset = 0xD322D0;
			mpCapOffset = 0xD322D4;
			sLvOffset = 0xD322E7;
			strengthOffset = 0xD322B8;
			defenseOffset = 0xD322B9;
			magicOffset = 0xD322BA;
			magicDefenseOffset = 0xD322BB;
			agilityOffset = 0xD322BC;
			luckOffset = 0xD322BD;
			EvasionOffset = 0xD322BE;
			accuracyOffset = 0xD322BF;
			tempStrengthOffset = 0xD322DB;
			tempDefenseOffset = 0xD322DC;
			tempMagicOffset = 0xD322DD;
			tempMagicDefenseOffset = 0xD322DE;
			tempAgilityOffset = 0xD322DF;
			tempLuckOffset = 0xD322E0;
			tempEvasionOffset = 0xD322E1;
			tempAccuracyOffset = 0xD322E2;
			overdriveModeOffset = 0xD322E4;
			overdriveCapOffset = 0xD322E6;
			overdriveMeterOffset = 0xD322E5;
			battleHpOffset = 0x4410;
			battleMpOffset = 0x4414;
			battleHpCapOffset = 0x0;
			battleMpCapOffset = 0x0;
			battleOverdriveOffset = 0x43FC;

			break;
		}

		case LULU:																	
		{
			hpOffset = 0xD3235C;
			mpOffset = 0xD32360;
			hpCapOffset = 0xD32364;
			mpCapOffset = 0xD32368;
			sLvOffset = 0xD3237B;
			strengthOffset = 0xD3234C;
			defenseOffset = 0xD3234D;
			magicOffset = 0xD3234E;
			magicDefenseOffset = 0xD3234F;
			agilityOffset = 0xD32350;
			luckOffset = 0xD32351;
			EvasionOffset = 0xD32352;
			accuracyOffset = 0xD32353;
			tempStrengthOffset = 0xD3236F;
			tempDefenseOffset = 0xD32370;
			tempMagicOffset = 0xD32371;
			tempMagicDefenseOffset = 0xD32372;
			tempAgilityOffset = 0xD32373;
			tempLuckOffset = 0xD32374;
			tempEvasionOffset = 0xD32375;
			tempAccuracyOffset = 0xD32376;
			overdriveModeOffset = 0xD32378;
			overdriveCapOffset = 0xD3237A;
			overdriveMeterOffset = 0xD32379;
			battleHpOffset = 0x53A0;
			battleMpOffset = 0x53A4;
			battleHpCapOffset = 0x0;
			battleMpCapOffset = 0x0;
			battleOverdriveOffset = 0x538C;

			break;
		}

		case RIKKU:																	
		{
			hpOffset = 0xD323F0;
			mpOffset = 0xD323F4;
			hpCapOffset = 0xD323F8;
			mpCapOffset = 0xD323FC;
			sLvOffset = 0xD3240F;
			strengthOffset = 0xD323E0;
			defenseOffset = 0xD323E1;
			magicOffset = 0xD323E2;
			magicDefenseOffset = 0xD323E3;
			agilityOffset = 0xD323E4;
			luckOffset = 0xD323E5;
			EvasionOffset = 0xD323E6;
			accuracyOffset = 0xD323E7;
			tempStrengthOffset = 0xD32403;
			tempDefenseOffset = 0xD32404;
			tempMagicOffset = 0xD32405;
			tempMagicDefenseOffset = 0xD32406;
			tempAgilityOffset = 0xD32407;
			tempLuckOffset = 0xD32408;
			tempEvasionOffset = 0xD32409;
			tempAccuracyOffset = 0xD3240A;
			overdriveModeOffset = 0xD3240C;
			overdriveCapOffset = 0xD3240E;
			overdriveMeterOffset = 0xD3240D;
			battleHpOffset = 0x6330;
			battleMpOffset = 0x6334;
			battleHpCapOffset = 0x0;
			battleMpCapOffset = 0x0;
			battleOverdriveOffset = 0x631C;

			break;
		}

		default:
			break;
		}
	}

private:
	// private variables/data

	uintptr_t 
		battleBasePtr = 0;

	HANDLE 
		processHandle = 0;

	uintptr_t 
		moduleBase = 0;

	uintptr_t
		hpOffset = 0, mpOffset = 0, hpCapOffset = 0, mpCapOffset = 0, sLvOffset = 0, strengthOffset = 0, defenseOffset = 0, magicOffset = 0, magicDefenseOffset = 0, agilityOffset = 0,
		luckOffset = 0, EvasionOffset = 0, accuracyOffset = 0, tempStrengthOffset = 0, tempDefenseOffset = 0, tempMagicOffset = 0, tempMagicDefenseOffset = 0, tempAgilityOffset = 0,
		tempLuckOffset = 0, tempEvasionOffset = 0, tempAccuracyOffset = 0, overdriveModeOffset = 0, overdriveCapOffset = 0, overdriveMeterOffset = 0, battleHpOffset = 0, battleMpOffset = 0,
		battleHpCapOffset = 0, battleMpCapOffset = 0, battleOverdriveOffset = 0;

public:
	// public functions

	void infiniteHp()
	{
		bool hasHpChanged = TRUE;
		if (isInBattle())
		{
			uintptr_t hpAddr = readBattleOffset(battleHpOffset);																															// resolves hp pointer chain using a function that reads and returns the pointer (only 1 offset from the pointer)
			const uint32_t maxValue = 99999;
			uint32_t ogValue = 0;
			ReadProcessMemory(processHandle, (BYTE*)hpAddr, &ogValue, sizeof(ogValue), nullptr);
			((ogValue < maxValue) ? (WriteProcessMemory(processHandle, (BYTE*)hpAddr, &maxValue, sizeof(maxValue), nullptr)) : ogValue);
		}
	};

	void infiniteMp()
	{
		if (isInBattle())
		{
			uintptr_t mpAddr = readBattleOffset(battleMpOffset);
			const uint32_t maxValue = 9999;
			uint32_t ogValue = 0;

				ReadProcessMemory(processHandle, (BYTE*)mpAddr, &ogValue, sizeof(ogValue), nullptr);

				if (ogValue < maxValue)
				{
					(WriteProcessMemory(processHandle, (LPVOID)mpAddr, &maxValue, sizeof(maxValue), nullptr));
				}
		}
	};

	void infiniteOverdrive()
	{
		if (isInBattle())
		{
			const uint8_t maxValue = 100;
			uint8_t ogValue = 0;
			ReadProcessMemory(processHandle, (LPVOID)readBattleOffset(battleOverdriveOffset), &ogValue, sizeof(ogValue), nullptr);
			if (ogValue < maxValue)
			{
				(WriteProcessMemory(processHandle, (LPVOID)readBattleOffset(battleOverdriveOffset), &maxValue, sizeof(maxValue), nullptr));
			}
		}
	};

	void tempMaxStats()
	{
		if (!isInBattle())																																										// checks battle state, only changes stats if outside of battle.
		{
			uintptr_t startAddr = moduleBase + tempStrengthOffset;																																	// static address no need to resolve a pointer
			uintptr_t endAddr = moduleBase + tempAccuracyOffset;
			uint8_t currentValue = 0;

			for (startAddr; startAddr < (endAddr + 1); startAddr++)
			{
				ReadProcessMemory(processHandle, (BYTE*)startAddr, &currentValue, sizeof(currentValue), nullptr);

				uint8_t maxValue = 255;
				if (currentValue < maxValue)

				{
					(WriteProcessMemory(processHandle, (BYTE*)startAddr, &maxValue, sizeof(maxValue), nullptr));
				}
			};
		}
	};

	void maxStats()
	{
		if (!isInBattle())																																							// checks battle state, only changes stats if outside of battle.
		{
			uintptr_t startAddr = moduleBase + strengthOffset;
			uintptr_t endAddr = moduleBase + accuracyOffset;
			uint8_t currentValue = 0;

			for (startAddr; startAddr < (endAddr + 1); startAddr++)
			{
				ReadProcessMemory(processHandle, (BYTE*)startAddr, &currentValue, sizeof(currentValue), nullptr);

				uint8_t maxValue = 255;
				if (currentValue < maxValue)

				{
					(WriteProcessMemory(processHandle, (BYTE*)startAddr, &maxValue, sizeof(maxValue), nullptr));
				}
			};
		}
	};


private:

	uintptr_t readBattleOffset(uintptr_t offset)
	{
		uintptr_t battleBuffer = 0;
		ReadProcessMemory(processHandle, (BYTE*)battleBasePtr, &battleBuffer, sizeof(battleBuffer), 0);			    																// read battleBasePtr
		return battleBuffer + offset;
	};


	bool isInBattle()
	{
		uintptr_t battleBuffer = 0;
		ReadProcessMemory(processHandle, (BYTE*)battleBasePtr, &battleBuffer, sizeof(battleBuffer), 0);
		return battleBuffer != 0;																																					// compares battleBuffer to 0 and returns the result as a boolean value : returns true if the value isn't 0 : false if it is 0
	};
};


class Inventory
{
		// public variables
public:

	Inventory(HANDLE processHandle, uintptr_t modBase)
	{
		hProc = processHandle;
		moduleBase = modBase;
	}
		
public:
	
	void maxGil()
	{
		const int infiniteGil = 999999999;

		// write 999999 into the address that holds the value of Gil in game
		WriteProcessMemory(hProc, (BYTE*)(moduleBase + gilOffset), &infiniteGil, sizeof(infiniteGil), nullptr);
	}

	// calling this function gives you 99 of each consumeable/useable item in the game. 
	void maxItems()
	{
		uint16_t itemId = 0x2000;																									// unitId is only 16 bits or 2 bytes in size because thats all is needed to write to the address
		const uint8_t  unitQuantity = 99;																							// unitQuantity is only 8 bits or 1 byte in size for the same reason, Quantity only goes from 0-99 so we don't need more than 1 byte.


		for (int i = 0; i < (sizeof(invIdOffsets) / sizeof(invIdOffsets[0])); i++)													// loops over all of the elements in the array variable 'invIdAddr' which has 112 elements, so it loops 112 times
		{
			WriteProcessMemory(hProc, (LPVOID)(moduleBase + invQtyOffsets[i]), &unitQuantity, sizeof(unitQuantity), 0);				// write the units/items quantity at the specific inventory slot
			WriteProcessMemory(hProc, (LPVOID)(moduleBase + invIdOffsets[i]), &itemId, sizeof(itemId), 0);							// write the units/items identification number at the specific inventory slot 
			itemId++;																												// increment itemIdStart by 1 at the end of every cycle of the loop essentially cycling through every item in the game,
																																	// by the end of the 'for' loop
		}

		return;
	}

	// calling this function gives you 1 of each item in the game you do not already own.
	void allItems()
	{
		uint16_t itemId = 0x2000;																									// unitId is only 16 bits or 2 bytes in size because thats all is needed to write to the address
		const uint8_t  unitQuantity = 1;																							// unitQuantity is only 8 bits or 1 byte in size for the same reason, Quantity only goes from 0-99 so we don't need more than 1 byte.


		for (int i = 0; i < (sizeof(invIdOffsets) / sizeof(invIdOffsets[0])); i++)													// loops over all of the elements in the array variable 'invIdAddr' which has 112 elements, so it loops 112 times
		{

			if (isQtyEmpty(invQtyOffsets, i))																						// We only write to the quantitiy of the item if the item did not exist in inventory to begin with.
			{
				WriteProcessMemory(hProc, (LPVOID)(moduleBase + invQtyOffsets[i]), &unitQuantity, sizeof(unitQuantity), 0);			// write the units/items quantity at the specific inventory slot
			}

			WriteProcessMemory(hProc, (LPVOID)(moduleBase + invIdOffsets[i]), &itemId, sizeof(itemId), 0);							// write the units/items identification number at the specific inventory slot 
			itemId++;																												// increment itemIdStart by 1 at the end of every cycle of the loop essentially cycling through every item in the game,
																																	// by the end of the 'for' loop
		}

		return;
	}
	
	void allKeyItems()
	{
		// creates all key items
	}

	void allAlbedBooks()
	{
		// creates albed books
	}

	void allCelestialWeapons()
	{
		// creates celestials weapons
	}

		// private variables
private:
	uintptr_t moduleBase = 0;
	HANDLE hProc = NULL;
	
	const uintptr_t gilOffset = 0xD307D8;

	const uintptr_t weaponAddrArray[178] = { 0 };
	const uintptr_t keyItemAddryArray[100] = { 0 };

	const uintptr_t invIdOffsets[112] =
	{ 
		0xD3095C, 0xD3095E, 0xD30960, 0xD30962, 0xD30964, 0xD30966, 0xD30968, 0xD3096A, 0xD3096C, 0xD3096E, 0xD30970, 0xD30972, 0xD30974, 0xD30976, 0xD30978, 0xD3097A, 0xD3097C, 0xD3097E,0xD30980, 0xD30982, 0xD30984,
		0xD30986, 0xD30988, 0xD3098A, 0xD3098C, 0xD3098E, 0xD30990, 0xD30992, 0xD30994, 0xD30996, 0xD30998, 0xD3099A, 0xD3099C, 0xD3099E, 0xD309A0, 0xD309A2, 0xD309A4, 0xD309A6, 0xD309A8,0xD309AA, 0xD309AC, 0xD309AE, 
		0xD309B0, 0xD309B2, 0xD309B4, 0xD309B6, 0xD309B8, 0xD309BA, 0xD309BC, 0xD309BE, 0xD309C0, 0xD309C2, 0xD309C4, 0xD309C6, 0xD309C8, 0xD309CA, 0xD309CC, 0xD309CE, 0xD309D0, 0xD309D2,0xD309D4, 0xD309D6, 0xD309D8, 
		0xD309DA, 0xD309DC, 0xD309DE, 0xD309E0, 0xD309E2, 0xD309E4, 0xD309E6, 0xD309E8, 0xD309EA, 0xD309EC, 0xD309EE, 0xD309F0, 0xD309F2, 0xD309F4, 0xD309F6, 0xD309F8, 0xD309FA, 0xD309FC,0xD309FE, 0xD30A00, 0xD30A02,
		0xD30A04, 0xD30A06, 0xD30A08, 0xD30A0A, 0xD30A0C, 0xD30A0E, 0xD30A10, 0xD30A12, 0xD30A14, 0xD30A16, 0xD30A18, 0xD30A1A, 0xD30A1C, 0xD30A1E, 0xD30A20, 0xD30A22, 0xD30A24, 0xD30A26,0xD30A28, 0xD30A2A, 0xD30A2C, 
		0xD30A2E, 0xD30A30, 0xD30A32, 0xD30A34, 0xD30A36, 0xD30A38 
	};

	const uintptr_t invQtyOffsets[112] =
	{
		0xD30B5C, 0xD30B5D, 0xD30B5E, 0xD30B5F, 0xD30B60, 0xD30B61, 0xD30B62, 0xD30B63, 0xD30B64, 0xD30B65, 0xD30B66, 0xD30B67, 0xD30B68, 0xD30B69, 0xD30B6A, 0xD30B6B, 0xD30B6C, 0xD30B6D, 0xD30B6E, 0xD30B6F, 0xD30B70,
		0xD30B71, 0xD30B72, 0xD30B73, 0xD30B74, 0xD30B75, 0xD30B76, 0xD30B77, 0xD30B78, 0xD30B79, 0xD30B7A, 0xD30B7B, 0xD30B7C, 0xD30B7D, 0xD30B7E, 0xD30B7F, 0xD30B80, 0xD30B81, 0xD30B82, 0xD30B83, 0xD30B84, 0xD30B85,
		0xD30B86, 0xD30B87, 0xD30B88, 0xD30B89, 0xD30B8A, 0xD30B8B, 0xD30B8C, 0xD30B8D, 0xD30B8E, 0xD30B8F, 0xD30B90, 0xD30B91, 0xD30B92, 0xD30B93, 0xD30B94, 0xD30B95, 0xD30B96, 0xD30B97, 0xD30B98, 0xD30B99, 0xD30B9A,
		0xD30B9B, 0xD30B9C, 0xD30B9D, 0xD30B9E, 0xD30B9F, 0xD30BA0, 0xD30BA1, 0xD30BA2, 0xD30BA3, 0xD30BA4, 0xD30BA5, 0xD30BA6, 0xD30BA7, 0xD30BA8, 0xD30BA9, 0xD30BAA, 0xD30BAB, 0xD30BAC, 0xD30BAD, 0xD30BAE, 0xD30BAF,
		0xD30BB0, 0xD30BB1, 0xD30BB2, 0xD30BB3, 0xD30BB4, 0xD30BB5, 0xD30BB6, 0xD30BB7, 0xD30BB8, 0xD30BB9, 0xD30BBA, 0xD30BBB, 0xD30BBC, 0xD30BBD, 0xD30BBE, 0xD30BBF, 0xD30BC0, 0xD30BC1, 0xD30BC2, 0xD30BC3, 0xD30BC4,
		0xD30BC5, 0xD30BC6, 0xD30BC7, 0xD30BC8, 0xD30BC9, 0xD30BCA, 0xD30BCB
	};


	
		// private functions
private:

	bool isQtyEmpty(const uintptr_t array[], const uint16_t& index)
	{
		uint16_t itemQty = 0x0;
		const uint16_t emptyQty = 0x0;


		ReadProcessMemory(hProc, (LPCVOID)(moduleBase + array[index]), &itemQty, sizeof(itemQty), 0);

		if (itemQty == emptyQty)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
};


// feature related function declarations


void runEnabledFeatures(HANDLE hProcess, uintptr_t moduleBase, std::map<std::string, Feature>& features);


bool isFeatureEnabled(std::string_view featureName, std::map<std::string, Feature>& featureMap);


bool isPausePressed();


void fillEquipment(HANDLE hProc, uintptr_t moduleBase, uint8_t choice);