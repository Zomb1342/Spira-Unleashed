#include "ProcInfo.h"

ProcInfo::ProcInfo()
{
    getProcId();
    if (procId == -1)
    {
        std::cout << "Error getting process ID, make sure the process is running and try again..." << std::endl;
        return;
    }

    getBaseAddr();
    if (modBaseAddr == 0)
    {
        std::cout << "Error getting module base address, make sure the process is running and try again..." << std::endl;
        return;
    }

    openProc();
    if (pHandle == -1)
    {
        std::cout << "Error getting process HANDLE, make sure the process is running and try again..." << std::endl;
        return;
    }
}

void ProcInfo::getProcId()
{
    DIR* dir = opendir("/proc");
    if (dir == nullptr)
    {
        std::cerr << "Could not open /proc directory" << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_DIR)
        {
            int id = atoi(entry->d_name);
            if (id > 0)
            {
                std::string cmd_path = std::string("/proc/") + entry->d_name + "/cmdline";
                std::ifstream cmd_file(cmd_path);
                std::string cmd_line;
                std::getline(cmd_file, cmd_line);
                if (cmd_line.find(procName) != std::string::npos)
                {
                    procId = id;
                    break;
                }
            }
        }
    }
    closedir(dir);
}

void ProcInfo::getBaseAddr()
{
    std::string maps_path = "/proc/" + std::to_string(procId) + "/maps";
    std::ifstream maps_file(maps_path);
    std::string line;
    while (std::getline(maps_file, line))
    {
        if (line.find(modName) != std::string::npos)
        {
            std::string addr = line.substr(0, line.find('-'));
            modBaseAddr = std::stoull(addr, nullptr, 16);
            break;
        }
    }
}

void ProcInfo::openProc()
{
    pHandle = procId;
}

pid_t ProcInfo::getProcessHandle() const
{
    return pHandle;
}

uintptr_t ProcInfo::getModuleBaseAddress() const
{
    return modBaseAddr;
}
