#include <iostream>
#include <iomanip>
#include <map>
#include "features.h"
#pragma once


class Menu
{
private:


public:
	std::map<std::string, Feature> globalFeatures;
	std::map<std::string, Feature> charFeatures;
	std::map<std::string, Feature> blitzFeatures;
	std::map<std::string, Weapons> allWeapons;
	std::map<std::string, Armors> allArmors;

	Menu()
	{
		globalFeatures["GODMODE"] = { "GODMODE", false };															// create features inside of the unordered_map 'featureMap'
		globalFeatures["1HITKO"] = { "1HITKO", false };
		globalFeatures["INFINITEGIL"] = { "INFINITEGIL", false };
		globalFeatures["MAXGIL"] = { "MAXGIL", false };
		globalFeatures["ALLITEMS"] = { "ALLITEMS" , false };
		globalFeatures["MAXITEMS"] = { "MAXITEMS", false };
		globalFeatures["INFINITEITEMS"] = { "INFINITEITEMS", false };
		globalFeatures["CUSTOMWEAPONS"] = { "CUSTOMWEAPONS", false };
		globalFeatures["CUSTOMARMOR"] = { "CUSTOMARMOR", false };
		globalFeatures["CELESTIALWEAPONS"] = { "CELESTIALWEAPONS", false };
		globalFeatures["ALLAEONS"] = { "ALLAEONS", false };
		globalFeatures["ALLOVERDRIVES"] = { "ALLOVERDRIVES", false };
		globalFeatures["EASYTHUNDERDODGE"] = { "EASYTHUNDERDODGE", false };
		globalFeatures["EASYCHOCOBORACE"] = { "EASYCHOCOBORACE", false };
		globalFeatures["CHARACTERWEAPONS"] = { "CHARACTERWEAPONS", false };
		globalFeatures["NORANDOMENCOUNTERS"] = { "NORANDOMENCOUNTERS", false };
		globalFeatures["ALLMAXSTATS"] = { "ALLMAXSTATS", false };
		globalFeatures["ALLKEYITEMS"] = { "ALLKEYITEMS", false };
		// Tidus
		charFeatures["TIDUS_INFINITEHP"] = { "TIDUS_INFINITEHP", false };
		charFeatures["TIDUS_INFINITEMP"] = { "TIDUS_INFINITEMP", false };
		charFeatures["TIDUS_INFINITEOVERDRIVE"] = { "TIDUS_INFINITEOVERDRIVE", false };
		charFeatures["TIDUS_TEMPMAXSTATS"] = { "TIDUS_TEMPMAXSTATS", false };
		charFeatures["TIDUS_ALLOVERDRIVEMODES"] = { "TIDUS_ALLOVERDRIVEMODES", false };
		charFeatures["TIDUS_MAXHP"] = { "TIDUS_MAXHP", false };
		charFeatures["TIDUS_MAXMP"] = { "TIDUS_MAXMP", false };
		charFeatures["TIDUS_MAXSTATS"] = { "TIDUS_MAXSTATS", false };
		// Yuna
		charFeatures["YUNA_INFINITEHP"] = { "YUNA_INFINITEHP", false };
		charFeatures["YUNA_INFINITEMP"] = { "YUNA_INFINITEMP", false };
		charFeatures["YUNA_INFINITEOVERDRIVE"] = { "YUNA_INFINITEOVERDRIVE", false };
		charFeatures["YUNA_TEMPMAXSTATS"] = { "YUNA_TEMPMAXSTATS", false };
		charFeatures["YUNA_ALLOVERDRIVEMODES"] = { "YUNA_ALLOVERDRIVEMODES", false };
		charFeatures["YUNA_MAXHP"] = { "YUNA_MAXHP", false };
		charFeatures["YUNA_MAXMP"] = { "YUNA_MAXMP", false };
		charFeatures["YUNA_MAXSTATS"] = { "YUNA_MAXSTATS", false };
		// Auron
		charFeatures["AURON_INFINITEHP"] = { "AURON_INFINITEHP", false };
		charFeatures["AURON_INFINITEMP"] = { "AURON_INFINITEMP", false };
		charFeatures["AURON_INFINITEOVERDRIVE"] = { "AURON_INFINITEOVERDRIVE", false };
		charFeatures["AURON_TEMPMAXSTATS"] = { "AURON_TEMPMAXSTATS", false };
		charFeatures["AURON_ALLOVERDRIVEMODES"] = { "AURON_ALLOVERDRIVEMODES", false };
		charFeatures["AURON_MAXHP"] = { "AURON_INFINITEMP", false };
		charFeatures["AURON_MAXMP"] = { "AURON_INFINITEMP", false };
		charFeatures["AURON_MAXSTATS"] = { "AURON_INFINITEMP", false };
		// Kimahri
		charFeatures["KIMAHRI_INFINITEHP"] = { "KIMAHRI_INFINITEHP", false };
		charFeatures["KIMAHRI_INFINITEMP"] = { "KIMAHRI_INFINITEMP", false };
		charFeatures["KIMAHRI_INFINITEOVERDRIVE"] = { "KIMAHRI_INFINITEOVERDRIVE", false };
		charFeatures["KIMAHRI_TEMPMAXSTATS"] = { "KIMAHRI_TEMPMAXSTATS", false };
		charFeatures["KIMAHRI_ALLOVERDRIVEMODES"] = { "KIMAHRI_ALLOVERDRIVEMODES", false };
		charFeatures["KIMAHRI_MAXHP"] = { "KIMAHRI_INFINITEMP", false };
		charFeatures["KIMAHRI_MAXMP"] = { "KIMAHRI_INFINITEMP", false };
		charFeatures["KIMAHRI_MAXSTATS"] = { "KIMAHRI_INFINITEMP", false };
		// Wakka
		charFeatures["WAKKA_INFINITEHP"] = { "WAKKA_INFINITEHP", false };
		charFeatures["WAKKA_INFINITEMP"] = { "WAKKA_INFINITEMP", false };
		charFeatures["WAKKA_INFINITEOVERDRIVE"] = { "WAKKA_INFINITEOVERDRIVE", false };
		charFeatures["WAKKA_TEMPMAXSTATS"] = { "WAKKA_TEMPMAXSTATS", false };
		charFeatures["WAKKA_ALLOVERDRIVEMODES"] = { "WAKKA_ALLOVERDRIVEMODES", false };
		charFeatures["WAKKA_MAXHP"] = { "WAKKA_INFINITEMP", false };
		charFeatures["WAKKA_MAXMP"] = { "WAKKA_INFINITEMP", false };
		charFeatures["WAKKA_MAXSTATS"] = { "WAKKA_INFINITEMP", false };
		// Lulu
		charFeatures["LULU_INFINITEHP"] = { "LULU_INFINITEHP", false };
		charFeatures["LULU_INFINITEMP"] = { "LULU_INFINITEMP", false };
		charFeatures["LULU_INFINITEOVERDRIVE"] = { "LULU_INFINITEOVERDRIVE", false };
		charFeatures["LULU_TEMPMAXSTATS"] = { "LULU_TEMPMAXSTATS", false };
		charFeatures["LULU_ALLOVERDRIVEMODES"] = { "LULU_ALLOVERDRIVEMODES", false };
		charFeatures["LULU_MAXHP"] = { "LULU_INFINITEMP", false };
		charFeatures["LULU_MAXMP"] = { "LULU_INFINITEMP", false };
		charFeatures["LULU_MAXSTATS"] = { "LULU_INFINITEMP", false };
		// Rikku
		charFeatures["RIKKU_INFINITEHP"] = { "RIKKU_INFINITEHP", false };
		charFeatures["RIKKU_INFINITEMP"] = { "RIKKU_INFINITEMP", false };
		charFeatures["RIKKU_INFINITEOVERDRIVE"] = { "RIKKU_INFINITEOVERDRIVE", false };
		charFeatures["RIKKU_TEMPMAXSTATS"] = { "RIKKU_TEMPMAXSTATS", false };
		charFeatures["RIKKU_ALLOVERDRIVEMODES"] = { "RIKKU_ALLOVERDRIVEMODES", false };
		charFeatures["RIKKU_MAXHP"] = { "RIKKU_INFINITEMP", false };
		charFeatures["RIKKU_MAXMP"] = { "RIKKU_INFINITEMP", false };
		charFeatures["RIKKU_MAXSTATS"] = { "RIKKU_INFINITEMP", false };


	}

private:

	void setConsoleWindowSize(int width, int height)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SMALL_RECT rect = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
		SetConsoleWindowInfo(console, TRUE, &rect);
	}

	void menuFeatures()
	{
		const int maxLength = 30;
		bool endLine = false;
		const std::string globalTitle = " Global Features ";
		const std::string characterTitle = "Character Features";
		const std::string blitzTitle = "Blitzball Features";
		std::cout << std::boolalpha;																																													// sets the boolalpha flag for boolean value ouput to be represented as true/false

		// Global Feature Title
		std::cout << std::setw(globalTitle.length() + 10) << globalTitle << std::endl;

		for (auto it = globalFeatures.begin(); it != globalFeatures.end(); ++it)
		{															
			int strLengthDiff = maxLength - (int)it->second.featureName.length();

			std::cout << std::setw((int)it->second.featureName.length()) << it->second.featureName << std::setw(strLengthDiff) << it->second.isEnabled;

			if (endLine)
			{
				std::cout << std::endl;
				endLine = false;
			}
			else
				if (!endLine)																																															// ensures we end the line after the second feature is added
				{
					std::cout << std::setw(2) << " | " << std::setw(3);
					endLine = true;
				}
			
		}

		// Character Feature Title

		std::cout << std::setw(globalTitle.length() + 10) << characterTitle << std::endl;
		std::cout << std::setw(120) << std::setfill('-') << " " << std::endl;
		std::cout << std::setfill(' ');

		for (auto it = charFeatures.begin(); it != charFeatures.end(); ++it)
		{
			int strLengthDiff = maxLength - (int)it->second.featureName.length();

			std::cout << std::setw((int)it->second.featureName.length()) << it->second.featureName << std::setw(strLengthDiff) << it->second.isEnabled;

			if (endLine)
			{
				std::cout << std::endl;
				endLine = false;
			}
			else
				if (!endLine)																																															// ensures we end the line after the second feature is added
				{
					std::cout << std::setw(2) << " | " << std::setw(3);
					endLine = true;
				}

		}


		// Blitz Feature Title

		std::cout << std::setw(globalTitle.length() + 10) << blitzTitle << std::endl;

		for (auto it = blitzFeatures.begin(); it != blitzFeatures.end(); ++it)
		{
			int strLengthDiff = maxLength - (int)it->second.featureName.length();

			std::cout << std::setw((int)it->second.featureName.length()) << it->second.featureName << std::setw(strLengthDiff) << it->second.isEnabled;

			if (endLine)
			{
				std::cout << std::endl;
				endLine = false;
			}
			else
				if (!endLine)																																															// ensures we end the line after the second feature is added
				{
					std::cout << std::setw(2) << " | " << std::setw(3);
					endLine = true;
				}

		}


	}

	
public:

	void mainMenu()
	{
		system("cls");																																																															// Clears the console screen
		setConsoleWindowSize(120, 40);																																																											// Sets console windows size
		menuFeatures();
		std::cout << "Please enter a command ( 'enable FEATURE', 'disable FEATURE', 'run', or 'quit'): ";
	}

	void createWeaponMenu()
	{
		system("cls");
		setConsoleWindowSize(120, 40);
		// WeaponFeatures();
	}

	void createArmorMenu()
	{
		system("cls");
		setConsoleWindowSize(120, 40);
		// ArmorFeatures();
	}

};
