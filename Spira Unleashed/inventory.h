#include "proc.h"

#pragma once


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