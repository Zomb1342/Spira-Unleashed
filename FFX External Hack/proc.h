#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#pragma once

struct ProcInfo
{
public:
	HANDLE pHandle = NULL;
	uintptr_t modBaseAddr = 0;

	ProcInfo()
	{
		getProcId();
		if (procId == NULL)
		{
			std::cout << "Error getting process ID, make sure the process is running and try again..." << std::endl;
			return;
		}

		getBaseAddr();
		if (modBaseAddr == NULL)
		{
			std::cout << "Error getting module base address, make sure the process is running and try again..." << std::endl;
			return;
		}

		openProc();
		if (procId == NULL)
		{
			std::cout << "Error getting process HANDLE, make sure the process is running and try again..." << std::endl;
			return;
		}

	}

private:
	const wchar_t* procName = L"FFX.exe";
	const wchar_t* modName = L"FFX.exe";

	DWORD procId = NULL;
	HANDLE tempHandle = NULL;


private:

	void getProcId()
	{
		tempHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);																							// Get Proc ID by enumerating through all processes

		if (tempHandle != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 procEntry;
			procEntry.dwSize = sizeof(procEntry);

			if (Process32First(tempHandle, &procEntry))
			{
				do
				{
					if (!_wcsicmp(procEntry.szExeFile, procName))
					{
						procId = procEntry.th32ProcessID;
						break;
					}
				} while (Process32Next(tempHandle, &procEntry));
			}
			CloseHandle(tempHandle);
		}
	};

	void  getBaseAddr()
	{
		tempHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);																		// Use ProcID to get Module Base Addr by enumerating through all processes/modules of the process we obtained the procID for
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);


		if (Module32First(tempHandle, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(tempHandle, &modEntry));
		}

		CloseHandle(tempHandle);
	};

	void openProc()
	{
		pHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);																									// get target processes handle
	}

};
