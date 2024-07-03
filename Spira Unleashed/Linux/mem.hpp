#pragma once
#include <filesystem>
#include <sys/uio.h>
#include <math.h>
#include "Config.hpp"
#include "Features.hpp"

class Cum {
private:
	// private member variable delcarations
    pid_t m_id;
    
    
    
    // private function declarations
    bool Read(int dickSize, long address, void* pBuff, size_t size);

    bool Write(long address, void* pBuff, size_t size);

public:
    Cum();

    pid_t GetM_ID();

    bool IsValidPointer(long pointer);

    template <class T>
    T Read(long Address);

    template <class T>
    void Write(long Address, T Value);

    std::string ReadString(long address);

    std::string ReadStringSize(long address, int size);

    std::string ConvertPointerToHexString(long pointer);

    void WriteAttack();
};

#include "Memory.tpp" // Include template definitions

#endif // MEMORY_H

