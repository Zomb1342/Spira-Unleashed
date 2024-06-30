#include "features.h"
#include <iostream>
#include "proc.h"
#include "consolemenu.h"
#include <sstream>
#include <memory>
#include "inventory.h"
#pragma once



int main()
{

	std::string command;																																							// create a string named 'command' that will take input recieved and parse it in order to continue functionality based off of input recieved by the user
	
	// example of using a smart pointer to create an object
	std::unique_ptr<Menu> menu;																																									// create a menu object

		while (procInfo.pHandle != NULL)
		{	
			menu->mainMenu();																																						// run the 'updateMenu()' function within the menu object which displays the feature menu to the console screen
	
			std::getline(std::cin, command);																																		// gets user input

			std::istringstream iss(command);																																		// parses user input to enable or disable features, run enabled features, or quit the program->
			std::string action, featureName;
			iss >> action >> featureName;

			if (action == "enable")																																					// toggles the bool variable of a feature to Enabled
			{
				auto it = menu->globalFeatures.find(featureName);
				if (it != menu->globalFeatures.end())
				{
					it->second.isEnabled = true;
					std::cout << "Enabled feature: " << featureName << std::endl;
				}
				else
				{
					std::cout << "Feature not found: " << featureName << std::endl;
				}
			}
			else if (action == "disable")																																			// toggles the bool variable of a feature to Disabled
			{
				auto it = menu->globalFeatures.find(featureName);
				if (it != menu->globalFeatures.end())
				{
					it->second.isEnabled = false;
					std::cout << "Disabled feature: " << featureName << std::endl;
				}
				else
				{
					std::cout << "Feature not found: " << featureName << std::endl;
				}
			}
			else if (action == "run")																																				// calls a function to run all enabled features
			{
				std::cout << "Features will begin running. Press 'p' to pause the features in order to be able to enable or disable features again->" << std::endl;
				runEnabledFeatures(procInfo.pHandle, procInfo.modBaseAddr, menu->globalFeatures);
			}
			else if (action == "quit")																																				// quit/exits the program
			{
				break;
			}
			else
			{
				std::cout << "Invalid command. Please enter 'enable <feature>', 'disable <feature>', 'run', or 'quit'." << std::endl;
			}
		}

	return 0;

}
