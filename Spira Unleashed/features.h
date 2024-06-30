#include <Windows.h>
#include <map>
#include <string>
#include <string_view>
#include <iostream>
#include <iomanip>
#include "Offsets.h"
#pragma once

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


// feature related function declarations


void runEnabledFeatures(HANDLE hProcess, uintptr_t moduleBase, std::map<std::string, Feature>& features);


bool isFeatureEnabled(std::string_view featureName, std::map<std::string, Feature>& featureMap);


bool isPausePressed();


void fillEquipment(HANDLE hProc, uintptr_t moduleBase, uint8_t choice);