#pragma once
#include "cum.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <array>
#include <cstdio>
#include <memory>


Cum::Cum() : PID(0) {}

	pid_t Cum::GetM_ID()
	{
		if (m_id > 0)
		{
			return m_id;
		}
		
		std::string cmd = "ls -l /proc/self/fd | grep /proc | awk '{print $11}'";
		std::array<char, 128> buffer;
		std::string result;
		std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
		
		if (!pipe)
		{ return 0; }
		
		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
		{ result += buffer.data(); }
		
		if (!result.empty()) 
		{
		    std::istringstream iss(result);
		    std::string proc_path;
		    
		    while (iss >> proc_path) 
		    {
		        if (proc_path.find("/proc") != std::string::npos) 
		        {
		            std::ifstream cmd_file(proc_path + "/cmdline");
		            std::string cmd_line;
		            std::getline(cmd_file, cmd_line);
		            
		            if (cmd_line.find("r5apex.exe") != std::string::npos) 
		            {
		                m_id = std::stoi(proc_path.substr(proc_path.find_last_of('/') + 1)); 
		                break;
		            }
		         }
		     }
     	}
     	return m_id;
     }

bool Cum::IsValidPointer(long pointer) 
{
    return pointer > 0x00010000 && pointer < 0x7FFFFFFEFFFF;
}

bool Cum::Read(long address, void* pBuff, size_t size) 
{
    if (size == 0)
        return false;
    void* pAddress = (void*)address;
    pid_t pid = GetPID();
    struct iovec iovLocalAddressSpace[1];
    struct iovec iovRemoteAddressSpace[1];
    iovLocalAddressSpace[0].iov_base = pBuff;
    iovLocalAddressSpace[0].iov_len = size;
    iovRemoteAddressSpace[0].iov_base = pAddress;
    iovRemoteAddressSpace[0].iov_len = size;
    ssize_t sSize = process_vm_readv(pid, iovLocalAddressSpace, 1, iovRemoteAddressSpace, 1, 0);
    if (sSize == (ssize_t)size)
        return true;
    else if (sSize == 0)
        return false;
    return false;
}

bool Cum::Write(long address, void* pBuff, size_t size) 
{
    if (size == 0)
        return false;
    void* pAddress = (void*)address;
    pid_t pid = GetPID();
    struct iovec iovLocalAddressSpace[1];
    struct iovec iovRemoteAddressSpace[1];
    iovLocalAddressSpace[0].iov_base = pBuff;
    iovLocalAddressSpace[0].iov_len = size;
    iovRemoteAddressSpace[0].iov_base = pAddress;
    iovRemoteAddressSpace[0].iov_len = size;
    ssize_t sSize = process_vm_writev(pid, iovLocalAddressSpace, 1, iovRemoteAddressSpace, 1, 0);
    if (sSize == (ssize_t)size)
        return true;
    else if (sSize == 0)
        return false;
    return false;
}

std::string Cum::ReadString(long address) 
{
    int size = sizeof(std::string);
    char buffer[size] = {0};
    bool success = Read(address, &buffer, size);
    return std::string(buffer);
}

std::string Cum::ReadStringSize(long address, int size) 
{
    char buffer[size] = {0};
    bool success = Read(address, &buffer, size);
    return std::string(buffer);
}

std::string Cum::ConvertPointerToHexString(long pointer) 
{
    std::stringstream stream;
    stream << "0x" << std::hex << pointer;
    std::string result(stream.str());
    return result;
}

void Cum::WriteAttack() 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(Features::Triggerbot::Delay));
    Write(OFF_REGION + OFF_INATTACK + 0x8, 4);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    Write(OFF_REGION + OFF_INATTACK + 0x8, 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    Write(OFF_REGION + OFF_INATTACK + 0x8, 4);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
