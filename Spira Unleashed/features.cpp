#include "mem.h"
#include "features.h"
#include <conio.h>

void runEnabledFeatures(HANDLE hProcess, uintptr_t moduleBase, std::map<std::string, Feature>& featureMap)
{

	Character tidus(TIDUS, hProcess, moduleBase);
	Character yuna(YUNA, hProcess, moduleBase);
	Character auron(AURON, hProcess, moduleBase);
	Character kimahri(KIMAHRI, hProcess, moduleBase);
	Character wakka(WAKKA, hProcess, moduleBase);
	Character lulu(LULU, hProcess, moduleBase);
	Character rikku(RIKKU, hProcess, moduleBase);

	Inventory inventory(hProcess, moduleBase);



	bool gilFlag = false;
	bool maxItemFlag = false;
	bool itemFlag = false;
	bool godmodeFlag = false;

	while (true)
	{
		if (isPausePressed())																
		{
			return;
		}


		// global features

		if (isFeatureEnabled("GODMODE", featureMap) && isFeatureEnabled("1HITKO", featureMap))
		{
			// EXTERNAL HOOK!!! 
			if (!godmodeFlag)
			{
				LPVOID newMemAddr = VirtualAllocEx(hProcess, NULL, 1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);		// allocate new memory inside FFX.exe
				

				uintptr_t codeSection = moduleBase + 0x1000;																	// beginning of the ffx.exe.text portion of the process
				uintptr_t ogAddr = codeSection + 0x38D3A9;																		// add the base address of ffx.exe.text to the offset to the memory location to replace with a jmp instruction to initiate our hook

				JmpInstruction jmpNewMem = mem::prepAddrForJmp(ogAddr, (uintptr_t)newMemAddr);									// adds a jmp instruction, converts a memory address to little endian, and to BYTE* style so we can patch it to memory
				mem::PatchEx((BYTE*)ogAddr, jmpNewMem.jmpBytes, jmpNewMem.size, hProcess);										// patches the first jmp that creates our hook to memory replacing the memory at 'ogAddr' with a jump to 'newMemAddr'

				uintptr_t* pMemLoc = (uintptr_t*)&newMemAddr;																	// create a pointer to hold the current location in memory to calculate relative jumps beginning with 'newMemAddr'

				BYTE cmpEntId[8] = "\x83\xBE\xE0\x06\x00\x00\x00";																// create a BYTE array to hold the bytes for the comparision of entities ID's
				mem::PatchEx((BYTE*)*pMemLoc, cmpEntId, (sizeof(cmpEntId)-1), hProcess);										// patch memory of the beginning of our allocated memory
				
				*pMemLoc = *pMemLoc + (sizeof(cmpEntId)-1);																		// update ptr to memory, subtract 1 from size of array because we want to ignore the null-terminator

				JmpInstruction je = mem::prepAddrForJne((uintptr_t)*pMemLoc, ogAddr + 6);										// same as the above line of code except for a je assembly instruction
				mem::PatchEx((BYTE*)*pMemLoc, je.jmpBytes, je.size, hProcess);
				
				*pMemLoc = *pMemLoc + je.size;																					// update ptr to current memory address

				BYTE killEnt[12] = "\xBF\x00\x00\x00\x00\x89\xBE\xD0\x05\x00\x00";												// kills entitity by replacing their health with 0
				mem::PatchEx((BYTE*)*pMemLoc, killEnt, (sizeof(killEnt)-1), hProcess);											// patches the bytes to kill entitiy
				
				*pMemLoc = *pMemLoc + (sizeof(killEnt)-1);

				JmpInstruction jmpOgMem = mem::prepAddrForJmp(((uintptr_t)*pMemLoc), (ogAddr + 6));							
				mem::PatchEx((BYTE*)*pMemLoc, jmpOgMem.jmpBytes, jmpOgMem.size, hProcess);


				delete[] jmpOgMem.jmpBytes;
				delete[] je.jmpBytes;
				delete[] jmpNewMem.jmpBytes;

				godmodeFlag = true;
			}
		}
		else
			if (isFeatureEnabled("GODMODE", featureMap))
			{
				// compare ID value, nop health decrement if its the player
			}
			else
				if (isFeatureEnabled("1HITKO", featureMap))
				{
					// compare ID value, put 0 into entities health if it is a enemy
				}


		if (isFeatureEnabled("INFINITEGIL", featureMap) || (isFeatureEnabled("INFINITEGIL", featureMap) && isFeatureEnabled("MAXGIL", featureMap)))							// calls maxGil continuously as long as enabled features are running
		{
			// writes the value to memory using WPM in a function inside an object used to represent our inventory
			inventory.maxGil();
		}
		else
			// max gil using direct byte manipulation using PatchEx Function from GuidedHacking
			if (isFeatureEnabled("MAXGIL", featureMap))																													
			{
				if (!gilFlag)
				{
					BYTE* dstAddr = (BYTE*)(moduleBase + 0xD307D8);
					BYTE srcData[] = { "\xFF\xC9\x9A\x3B\x00\x00\x00\x00\x00" };
					unsigned int patchSize = sizeof(srcData);

					mem::PatchEx(dstAddr, srcData, patchSize, hProcess);

					gilFlag = true;
				}
			}

		if (isFeatureEnabled("INFINITEITEMS", featureMap) || (isFeatureEnabled("INFINITEITEMS", featureMap) && isFeatureEnabled("MAXITEMS", featureMap)))						// if INFINITEITEMS or INFINITEITEMS and MAXITEMS are enabled continuously fill Item Inventory to the max
		{
			inventory.maxItems();
		}
		else
			if (isFeatureEnabled("MAXITEMS", featureMap))																		// if only MAXITEMS are enabled fill item inventory to the max one time.
			{
				if (maxItemFlag = false)
				{
					inventory.maxItems();
					maxItemFlag = true;
				};
			}

		if (isFeatureEnabled("ALLITEMS", featureMap))
		{
			if (itemFlag = false)
			{
				inventory.allItems();
				itemFlag = true;
			}
		}


		// character specific features 

		// Tidus

		if (isFeatureEnabled("TIDUS_TEMPMAXSTATS", featureMap))
		{
			tidus.tempMaxStats();
		}

		if (isFeatureEnabled("TIDUS_MAXSTATS", featureMap))
		{
			tidus.maxStats();
		}

		if (isFeatureEnabled("TIDUS_INFINITEHP", featureMap))
		{
			tidus.infiniteHp();
		}

		if (isFeatureEnabled("TIDUS_INFINITEMP", featureMap))
		{
			tidus.infiniteMp();
		}

		if (isFeatureEnabled("TIDUS_INFINITEOVERDRIVE", featureMap))
		{
			tidus.infiniteOverdrive();
		}

		// Yuna

		if (isFeatureEnabled("YUNA_TEMPMAXSTATS", featureMap))
		{
			yuna.tempMaxStats();
		}

		if (isFeatureEnabled("YUNA_MAXSTATS", featureMap))
		{
			yuna.maxStats();
		}

		if (isFeatureEnabled("YUNA_INFINITEHP", featureMap))
		{
			yuna.infiniteHp();
		}

		if (isFeatureEnabled("YUNA_INFINITEMP", featureMap))
		{
			yuna.infiniteMp();
		}

		if (isFeatureEnabled("YUNA_INFINITEOVERDRIVE", featureMap))
		{
			yuna.infiniteOverdrive();
		}

		// Auron

		if (isFeatureEnabled("AURON_TEMPMAXSTATS", featureMap))
		{
			auron.tempMaxStats();
		}

		if (isFeatureEnabled("AURON_MAXSTATS", featureMap))
		{
			auron.maxStats();
		}

		if (isFeatureEnabled("AURON_INFINITEHP", featureMap))
		{
			auron.infiniteHp();
		}

		if (isFeatureEnabled("AURON_INFINITEMP", featureMap))
		{
			auron.infiniteMp();
		}

		if (isFeatureEnabled("AURON_INFINITEOVERDRIVE", featureMap))
		{
			auron.infiniteOverdrive();
		}

		// Kimahri

		if (isFeatureEnabled("KIMAHRI_TEMPMAXSTATS", featureMap))
		{
			kimahri.tempMaxStats();
		}

		if (isFeatureEnabled("KIMAHRI_MAXSTATS", featureMap))
		{
			kimahri.maxStats();
		}

		if (isFeatureEnabled("KIMAHRI_INFINITEHP", featureMap))
		{
			kimahri.infiniteHp();
		}

		if (isFeatureEnabled("KIMAHRI_INFINITEMP", featureMap))
		{
			kimahri.infiniteMp();
		}

		if (isFeatureEnabled("KIMAHRI_INFINITEOVERDRIVE", featureMap))
		{
			kimahri.infiniteOverdrive();
		}

		// Wakka

		if (isFeatureEnabled("WAKKA_TEMPMAXSTATS", featureMap))
		{
			wakka.tempMaxStats();
		}

		if (isFeatureEnabled("WAKKA_MAXSTATS", featureMap))
		{
			wakka.maxStats();
		}

		if (isFeatureEnabled("WAKKA_INFINITEHP", featureMap))
		{
			wakka.infiniteHp();
		}

		if (isFeatureEnabled("WAKKA_INFINITEMP", featureMap))
		{
			wakka.infiniteMp();
		}

		if (isFeatureEnabled("WAKKA_INFINITEOVERDRIVE", featureMap))
		{
			wakka.infiniteOverdrive();
		}

		// Lulu

		if (isFeatureEnabled("LULU_TEMPMAXSTATS", featureMap))
		{
			lulu.tempMaxStats();
		}

		if (isFeatureEnabled("LULU_MAXSTATS", featureMap))
		{
			lulu.maxStats();
		}

		if (isFeatureEnabled("LULU_INFINITEHP", featureMap))
		{
			lulu.infiniteHp();
		}

		if (isFeatureEnabled("LULU_INFINITEMP", featureMap))
		{
			lulu.infiniteMp();
		}

		if (isFeatureEnabled("LULU_INFINITEOVERDRIVE", featureMap))
		{
			lulu.infiniteOverdrive();
		}

		// Rikku

		if (isFeatureEnabled("RIKKU_TEMPMAXSTATS", featureMap))
		{
			rikku.tempMaxStats();
		}

		if (isFeatureEnabled("RIKKU_MAXSTATS", featureMap))
		{
			rikku.maxStats();
		}

		if (isFeatureEnabled("RIKKU_INFINITEHP", featureMap))
		{
			rikku.infiniteHp();
		}

		if (isFeatureEnabled("RIKKU_INFINITEMP", featureMap))
		{
			rikku.infiniteMp();
		}

		if (isFeatureEnabled("RIKKU_INFINITEOVERDRIVE", featureMap))
		{
			rikku.infiniteOverdrive();
		}

	}


	// blitzball specific features
}


bool isPausePressed()
{
	if (_kbhit())
	{
		char key = _getch();
		if (key == 'p' || key == 'P')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}


bool isFeatureEnabled(std::string_view featureName, std::map<std::string, Feature>& featureMap)
{
	auto it = featureMap.find(std::string(featureName));
	if (it != featureMap.end())
	{
		return it->second.isEnabled;
	}
	else
	{
		return false;
	}
}

void fillEquipment(HANDLE hProc, uintptr_t moduleBase, uint8_t choice)
{
	uintptr_t equipmentSlot = moduleBase + 0xD30F2C;	// offset to the first slot in equipment inventory
	uint8_t equipmentId = 0;							// variable to hold the value representing the ID of each weapon or armor	

	// constant values to hold the attributes we want to give each weapon
	const uint8_t tidusWeaponIcon = 0;
	const uint8_t tidusArmorIcon = 1;
	const uint8_t yunaWeaponIcon = 2;
	const uint8_t yunaArmorIcon = 3;
	const uint8_t auronWeaponIcon = 4;
	const uint8_t auronArmorIcon = 5;
	const uint8_t kimahriWeaponIcon = 6;
	const uint8_t kimahriArmorIcon = 7;
	const uint8_t wakkaWeaponIcon = 8;
	const uint8_t wakkaArmorIcon = 9;
	const uint8_t luluWeaponIcon = 10;
	const uint8_t luluArmorIcon = 11;
	const uint8_t rikkuWeaponIcon = 12;
	const uint8_t rikkuArmorIcon = 13;
	const uint8_t equipmentSlotIncr = 0x16;
	const uint8_t unequipped = 255;
	const uint8_t maxAbilitySlots = 4;
	const uint8_t slotActivator = 0;
	const uint8_t characterModel = 64;
	const uint8_t tidusWeaponModelId[67] = { 7, 1, 2, 5, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 3, 3, 3, 4, 6, 5, 4, 6, 6, 6, 6, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 2, 2, 5, 4, 4, 4, 4, 4, 4, 4, 4, 2, 5, 1, 5, 1, 2, 2, 2, 6, 3, 2, 3, 3, 3, 2, 3, 2, 3, 2 };


	switch (choice)
	{

	case 0:

		// writes every single one of tidus's swords to inventory
		for (uint8_t c = 0; c < 67; c++)
		{
			WriteProcessMemory(hProc, (BYTE*)equipmentSlot, &equipmentId, sizeof(equipmentId), 0);										// writes the weapon ID to the equipment slot starting at the 1st slot.
			++equipmentId;																			// increment equipmentId by 1 to change the weapon we are adding each loop

			WriteProcessMemory(hProc, (BYTE*)equipmentSlot + 0x3, &slotActivator, sizeof(slotActivator), 0);								// activates the slot so that if the slot does not exist in inventory yet it opens it

			WriteProcessMemory(hProc, (BYTE*)equipmentSlot + 0x5, &tidusWeaponIcon, sizeof(tidusWeaponIcon), 0);								// change the weapons icon to tidus's weapon

			WriteProcessMemory(hProc, (BYTE*)equipmentSlot + 0xB, &maxAbilitySlots, sizeof(maxAbilitySlots), 0);								// create 4 open ability slots in each weapon

			WriteProcessMemory(hProc, (BYTE*)equipmentSlot + 0xC, &tidusWeaponModelId[c], sizeof(tidusWeaponModelId[c]), 0);						// writes to each weapon its correct model Id for the weapon

			WriteProcessMemory(hProc, (BYTE*)equipmentSlot + 0xD, &characterModel, sizeof(characterModel), 0);								// model ID glitches if we do not 0 this byte of memory out (The above address at equipmentSlot + 0xC will correspond to character models 
			// so you would swing around characters as swords if we do not 0 out the memory at equipmentSlot + 0xD.

			WriteProcessMemory(hProc, (BYTE*)equipmentSlot + 0x6, &unequipped, sizeof(unequipped), 0);									// this makes sure all the created weapons will be unequipped, the model glitch above can accure without this code as well
			// I think because characters have tidus's weapons equipped as their weapon/armor but not compeletely sure.

			equipmentSlot = equipmentSlot + equipmentSlotIncr;														// increments equipmentSlot by 16 in hex (22 in decimal) and passes the value back into equipmentSlot to find the next slot in inventory
		}
		break;

	default:
		break;
	}

	return;

}

