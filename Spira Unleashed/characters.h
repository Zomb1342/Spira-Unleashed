#include <Windows.h>
#include <map>
#include <string>
#include <string_view>
#include <iostream>
#include <iomanip>
#include "offsets.h"
#pragma once

enum CharacterNames
{
	TIDUS = 0, YUNA, AURON, KIMAHRI, WAKKA, LULU, RIKKU
};

class Character
{

public:
	// public variables/data

	// example of how to use a pointer to a struct inside of a class as a member variable
	// initialized here and declared with private member variables
	Character(CharacterNames name, HANDLE procHandle, uintptr_t modBase)
		: processHandle(procHandle), moduleBase(modBase), charOff(new CharacterOffsets())
	{

		battleBasePtr = modBase + 0xD334CC;

		switch (name)
		{
		case TIDUS:
		{
			setTidusOffsets();
			break;
		}

		case YUNA:
		{
			setYunaOffsets();
			break;
		}

		case AURON:
		{
			setAuronOffsets();
			break;
		}

		case KIMAHRI:
		{
			setKimahriOffsets();
			break;
		}

		case WAKKA:
		{
			setWakkaOffsets();
			break;
		}

		case LULU:
		{
			setLuluOffsets();
			break;
		}

		case RIKKU:
		{
			setRikkuOffsets();
			break;
		}

		default:
			break;
		}
	}

	~Character()
	{
		// cleanup pointer
		delete charOff;
		charOff = nullptr;
	}

private:
	// private variables/data

	// pointer to struct 'CharacterOffsets' declared here
	CharacterOffsets* charOff;

	uintptr_t
		battleBasePtr = 0;

	HANDLE
		processHandle = 0;

	uintptr_t
		moduleBase = 0;


public:
	// public functions

	void infiniteHp()
	{
		bool hasHpChanged = TRUE;
		if (isInBattle())
		{
			uintptr_t hpAddr = readBattleOffset(charOff->battleHpOffset);																															// resolves hp pointer chain using a function that reads and returns the pointer (only 1 offset from the pointer)
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
			uintptr_t mpAddr = readBattleOffset(charOff->battleMpOffset);
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
			ReadProcessMemory(processHandle, (LPVOID)readBattleOffset(charOff->battleOverdriveOffset), &ogValue, sizeof(ogValue), nullptr);
			if (ogValue < maxValue)
			{
				(WriteProcessMemory(processHandle, (LPVOID)readBattleOffset(charOff->battleOverdriveOffset), &maxValue, sizeof(maxValue), nullptr));
			}
		}
	};

	void tempMaxStats()
	{
		if (!isInBattle())																																										// checks battle state, only changes stats if outside of battle.
		{
			uintptr_t startAddr = moduleBase + charOff->tempStrengthOffset;																																	// static address no need to resolve a pointer
			uintptr_t endAddr = moduleBase + charOff->tempAccuracyOffset;
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
			uintptr_t startAddr = moduleBase + charOff->strengthOffset;
			uintptr_t endAddr = moduleBase + charOff->accuracyOffset;
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

	void setTidusOffsets()
	{
		charOff->hpOffset = 0xD32078;
		charOff->mpOffset = 0xD3207C;
		charOff->hpCapOffset = 0xD32080;
		charOff->mpCapOffset = 0xD32084;
		charOff->sLvOffset = 0xD32097;
		charOff->strengthOffset = 0xD32068;
		charOff->defenseOffset = 0xD32069;
		charOff->magicOffset = 0xD3206A;
		charOff->magicDefenseOffset = 0xD3206B;
		charOff->agilityOffset = 0xD3206C;
		charOff->luckOffset = 0xD3206D;
		charOff->EvasionOffset = 0xD3206E;
		charOff->accuracyOffset = 0xD3206F;
		charOff->tempStrengthOffset = 0xD3208B;
		charOff->tempDefenseOffset = 0xD3208C;
		charOff->tempMagicOffset = 0xD3208D;
		charOff->tempMagicDefenseOffset = 0xD3208E;
		charOff->tempAgilityOffset = 0xD3208F;
		charOff->tempLuckOffset = 0xD32090;
		charOff->tempEvasionOffset = 0xD32091;
		charOff->tempAccuracyOffset = 0xD32092;
		charOff->overdriveModeOffset = 0xD32094;
		charOff->overdriveCapOffset = 0xD32096;
		charOff->overdriveMeterOffset = 0xD32095;
		charOff->battleHpOffset = 0x5D0;
		charOff->battleMpOffset = 0x5D4;
		charOff->battleHpCapOffset = 0x594;
		charOff->battleMpCapOffset = 0x0;
		charOff->battleOverdriveOffset = 0x5BC;
	}

	void setYunaOffsets()
	{
		charOff->hpOffset = 0xD3210C;
		charOff->mpOffset = 0xD32110;
		charOff->hpCapOffset = 0xD32114;
		charOff->mpCapOffset = 0xD32118;
		charOff->sLvOffset = 0xD3212B;
		charOff->strengthOffset = 0xD320FC;
		charOff->defenseOffset = 0xD320FD;
		charOff->magicOffset = 0xD320FE;
		charOff->magicDefenseOffset = 0xD320FF;
		charOff->agilityOffset = 0xD32100;
		charOff->luckOffset = 0xD32101;
		charOff->EvasionOffset = 0xD32102;
		charOff->accuracyOffset = 0xD32103;
		charOff->tempStrengthOffset = 0xD3211F;
		charOff->tempDefenseOffset = 0xD32120;
		charOff->tempMagicOffset = 0xD32121;
		charOff->tempMagicDefenseOffset = 0xD32122;
		charOff->tempAgilityOffset = 0xD32123;
		charOff->tempLuckOffset = 0xD32124;
		charOff->tempEvasionOffset = 0xD32125;
		charOff->tempAccuracyOffset = 0xD32126;
		charOff->overdriveModeOffset = 0xD32128;
		charOff->overdriveCapOffset = 0xD32129;
		charOff->overdriveMeterOffset = 0xD3212A;
		charOff->battleHpOffset = 0x1560;
		charOff->battleMpOffset = 0x1564;
		charOff->battleHpCapOffset = 0x0;
		charOff->battleMpCapOffset = 0x0;
		charOff->battleOverdriveOffset = 0x154C;
	}

	void setAuronOffsets()
	{
		charOff->hpOffset = 0xD321A0;
		charOff->mpOffset = 0xD321A4;
		charOff->hpCapOffset = 0xD321A8;
		charOff->mpCapOffset = 0xD321AC;
		charOff->sLvOffset = 0xD321BF;
		charOff->strengthOffset = 0xD32190;
		charOff->defenseOffset = 0xD32191;
		charOff->magicOffset = 0xD32192;
		charOff->magicDefenseOffset = 0xD32193;
		charOff->agilityOffset = 0xD32194;
		charOff->luckOffset = 0xD32195;
		charOff->EvasionOffset = 0xD32196;
		charOff->accuracyOffset = 0xD32197;
		charOff->tempStrengthOffset = 0xD321B3;
		charOff->tempDefenseOffset = 0xD321B4;
		charOff->tempMagicOffset = 0xD321B5;
		charOff->tempMagicDefenseOffset = 0xD321B6;
		charOff->tempAgilityOffset = 0xD321B7;
		charOff->tempLuckOffset = 0xD321B8;
		charOff->tempEvasionOffset = 0xD321B9;
		charOff->tempAccuracyOffset = 0xD321BA;
		charOff->overdriveModeOffset = 0xD321BC;
		charOff->overdriveCapOffset = 0xD321BD;
		charOff->overdriveMeterOffset = 0xD321BE;
		charOff->battleHpOffset = 0x24F0;
		charOff->battleMpOffset = 0x24F4;
		charOff->battleHpCapOffset = 0x0;
		charOff->battleMpCapOffset = 0x0;
		charOff->battleOverdriveOffset = 0x24DC;
	}

	void setKimahriOffsets()
	{
		charOff->hpOffset = 0xD32234;
		charOff->mpOffset = 0xD32238;
		charOff->hpCapOffset = 0xD3223C;
		charOff->mpCapOffset = 0xD32240;
		charOff->sLvOffset = 0xD32253;
		charOff->strengthOffset = 0xD32224;
		charOff->defenseOffset = 0xD32225;
		charOff->magicOffset = 0xD32226;
		charOff->magicDefenseOffset = 0xD32227;
		charOff->agilityOffset = 0xD32228;
		charOff->luckOffset = 0xD32229;
		charOff->EvasionOffset = 0xD3222A;
		charOff->accuracyOffset = 0xD3222B;
		charOff->tempStrengthOffset = 0xD32247;
		charOff->tempDefenseOffset = 0xD32248;
		charOff->tempMagicOffset = 0xD32249;
		charOff->tempMagicDefenseOffset = 0xD3224A;
		charOff->tempAgilityOffset = 0xD3224B;
		charOff->tempLuckOffset = 0xD3224C;
		charOff->tempEvasionOffset = 0xD3224D;
		charOff->tempAccuracyOffset = 0xD3224E;
		charOff->overdriveModeOffset = 0xD32250;
		charOff->overdriveCapOffset = 0xD32252;
		charOff->overdriveMeterOffset = 0xD32251;
		charOff->battleHpOffset = 0x3480;
		charOff->battleMpOffset = 0x3484;
		charOff->battleHpCapOffset = 0x0;
		charOff->battleMpCapOffset = 0x0;
		charOff->battleOverdriveOffset = 0x346C;
	}

	void setWakkaOffsets()
	{
		charOff->hpOffset = 0xD322C8;
		charOff->mpOffset = 0xD322CC;
		charOff->hpCapOffset = 0xD322D0;
		charOff->mpCapOffset = 0xD322D4;
		charOff->sLvOffset = 0xD322E7;
		charOff->strengthOffset = 0xD322B8;
		charOff->defenseOffset = 0xD322B9;
		charOff->magicOffset = 0xD322BA;
		charOff->magicDefenseOffset = 0xD322BB;
		charOff->agilityOffset = 0xD322BC;
		charOff->luckOffset = 0xD322BD;
		charOff->EvasionOffset = 0xD322BE;
		charOff->accuracyOffset = 0xD322BF;
		charOff->tempStrengthOffset = 0xD322DB;
		charOff->tempDefenseOffset = 0xD322DC;
		charOff->tempMagicOffset = 0xD322DD;
		charOff->tempMagicDefenseOffset = 0xD322DE;
		charOff->tempAgilityOffset = 0xD322DF;
		charOff->tempLuckOffset = 0xD322E0;
		charOff->tempEvasionOffset = 0xD322E1;
		charOff->tempAccuracyOffset = 0xD322E2;
		charOff->overdriveModeOffset = 0xD322E4;
		charOff->overdriveCapOffset = 0xD322E6;
		charOff->overdriveMeterOffset = 0xD322E5;
		charOff->battleHpOffset = 0x4410;
		charOff->battleMpOffset = 0x4414;
		charOff->battleHpCapOffset = 0x0;
		charOff->battleMpCapOffset = 0x0;
		charOff->battleOverdriveOffset = 0x43FC;
	}

	void setLuluOffsets()
	{
		charOff->hpOffset = 0xD3235C;
		charOff->mpOffset = 0xD32360;
		charOff->hpCapOffset = 0xD32364;
		charOff->mpCapOffset = 0xD32368;
		charOff->sLvOffset = 0xD3237B;
		charOff->strengthOffset = 0xD3234C;
		charOff->defenseOffset = 0xD3234D;
		charOff->magicOffset = 0xD3234E;
		charOff->magicDefenseOffset = 0xD3234F;
		charOff->agilityOffset = 0xD32350;
		charOff->luckOffset = 0xD32351;
		charOff->EvasionOffset = 0xD32352;
		charOff->accuracyOffset = 0xD32353;
		charOff->tempStrengthOffset = 0xD3236F;
		charOff->tempDefenseOffset = 0xD32370;
		charOff->tempMagicOffset = 0xD32371;
		charOff->tempMagicDefenseOffset = 0xD32372;
		charOff->tempAgilityOffset = 0xD32373;
		charOff->tempLuckOffset = 0xD32374;
		charOff->tempEvasionOffset = 0xD32375;
		charOff->tempAccuracyOffset = 0xD32376;
		charOff->overdriveModeOffset = 0xD32378;
		charOff->overdriveCapOffset = 0xD3237A;
		charOff->overdriveMeterOffset = 0xD32379;
		charOff->battleHpOffset = 0x53A0;
		charOff->battleMpOffset = 0x53A4;
		charOff->battleHpCapOffset = 0x0;
		charOff->battleMpCapOffset = 0x0;
		charOff->battleOverdriveOffset = 0x538C;
	}

	void setRikkuOffsets()
	{
		charOff->hpOffset = 0xD323F0;
		charOff->mpOffset = 0xD323F4;
		charOff->hpCapOffset = 0xD323F8;
		charOff->mpCapOffset = 0xD323FC;
		charOff->sLvOffset = 0xD3240F;
		charOff->strengthOffset = 0xD323E0;
		charOff->defenseOffset = 0xD323E1;
		charOff->magicOffset = 0xD323E2;
		charOff->magicDefenseOffset = 0xD323E3;
		charOff->agilityOffset = 0xD323E4;
		charOff->luckOffset = 0xD323E5;
		charOff->EvasionOffset = 0xD323E6;
		charOff->accuracyOffset = 0xD323E7;
		charOff->tempStrengthOffset = 0xD32403;
		charOff->tempDefenseOffset = 0xD32404;
		charOff->tempMagicOffset = 0xD32405;
		charOff->tempMagicDefenseOffset = 0xD32406;
		charOff->tempAgilityOffset = 0xD32407;
		charOff->tempLuckOffset = 0xD32408;
		charOff->tempEvasionOffset = 0xD32409;
		charOff->tempAccuracyOffset = 0xD3240A;
		charOff->overdriveModeOffset = 0xD3240C;
		charOff->overdriveCapOffset = 0xD3240E;
		charOff->overdriveMeterOffset = 0xD3240D;
		charOff->battleHpOffset = 0x6330;
		charOff->battleMpOffset = 0x6334;
		charOff->battleHpCapOffset = 0x0;
		charOff->battleMpCapOffset = 0x0;
		charOff->battleOverdriveOffset = 0x631C;
	}
};