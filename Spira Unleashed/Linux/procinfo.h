#ifndef PROCINFO_H
#define PROCINFO_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>

struct ProcInfo
{
public:
    ProcInfo();

    pid_t getProcessHandle() const;
    uintptr_t getModuleBaseAddress() const;

private:
    void getProcId();
    void getBaseAddr();
    void openProc();

    const char* procName = "FFX";
    const char* modName = "FFX";

    pid_t procId = -1;
    pid_t pHandle = -1;
    uintptr_t modBaseAddr = 0;
};

#endif // PROCINFO_H