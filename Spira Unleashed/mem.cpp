#include "proc.h"
#include "mem.h"

template void mem::PatchEx<7>(BYTE* dst, std::array<std::byte, 7> src, HANDLE hProcess);
template void mem::PatchEx<9>(BYTE* dst, std::array<std::byte, 9> src, HANDLE hProcess);
template void mem::PatchEx<11>(BYTE* dst, std::array<std::byte, 11> src, HANDLE hProcess);

void mem::PatchEx(BYTE* dst, std::vector<std::byte> src, HANDLE hProcess)
{
	DWORD oldProtect;
	VirtualProtectEx(hProcess, dst, src.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hProcess, dst, src.data(), src.size(), nullptr);
	VirtualProtectEx(hProcess, dst, src.size(), oldProtect, &oldProtect);
}

template <std::size_t x>
void mem::PatchEx(BYTE* dst, std::array<std::byte, x> src, HANDLE hProcess)
{
    DWORD oldProtect;
    VirtualProtectEx(hProcess, dst, src.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
    WriteProcessMemory(hProcess, dst, src.data(), src.size(), nullptr);
    VirtualProtectEx(hProcess, dst, src.size(), oldProtect, &oldProtect);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProcess)
{
    std::vector<std::byte> nopArray;
	memset(nopArray.data(), 0x90, size);
  
	PatchEx(dst, nopArray, hProcess);
}

std::vector<std::byte> prepJmp(int32_t currAddr, int32_t destinationAddr, JmpType jmpType, int32_t padding)
{
    switch (jmpType)
    {
    case 0:                                                                                                                  // initial jmp from origin code to allocated code
    {
        int jmpSize = (5 + padding);

        int32_t relativeOffset = destinationAddr - (currAddr + jmpSize);                                                     // calculates the distance from our current address to our destination address

        std::vector<std::byte> result =                                                                                      // writes the jmp instructions into a vector of bytes
        {
            std::byte{0xE9},                                                                                                               // OpCode for 'jmp'
            static_cast<std::byte>((relativeOffset & 0xFF)),                                                                               // converts the offset to our destination to little endian
            static_cast<std::byte>((relativeOffset >> 8) & 0xFF),                                                                         // to be used in the jmp instructions
            static_cast<std::byte>((relativeOffset >> 16) & 0xFF),                                                                        // we will patch into memory
            static_cast<std::byte>((relativeOffset >> 24) & 0xFF)
        };

        for (int i = 5; i < (jmpSize); i++)                                                                                  // writes NOP codes into the vector of bytes until the vector of bytes = the size of the jmp instructions we are to write into memory
        {
            result.push_back(std::byte{ 0x90 });
        }

        return result;                                                                                                       // returns the result
    }
    case 1:                                                                                                                  // JE
    {
        int jmpSize =  (6 + padding);

        intptr_t relativeOffset = destinationAddr - (currAddr + jmpSize);                                                                 // calculates the distance from our current address to our destination address

        std::vector<std::byte> result =                                                                                      // writes the jmp instructions into a vector of bytes
        {
            std::byte{0x0F},                                                                                                 // OpCode for 'JE'
            std::byte{0x84},                                                                                // converts the offset to our destination to little endian

            static_cast<std::byte>((relativeOffset >> 8) & 0xFF),                                                                         // to be used in the jmp instructions
            static_cast<std::byte>((relativeOffset >> 16) & 0xFF),                                                                        // we will patch into memory
            static_cast<std::byte>((relativeOffset >> 24) & 0xFF)
        };

        return result;                                                                                                       // returns the result
    }

    case 2:                                                                                                                  // JNE
    {
        int32_t relativeOffset = destinationAddr - (currAddr + (padding + 6));                                                      // calculates the distance from our current address to our destination address
        
        std::vector<std::byte> result =                                                                                                 // writes the jmp instructions into a vector of bytes
        {
            std::byte{0x0F},                                                                                                              // OpCode for 'JNE'
            std::byte{0x85},                                                                                                                 // converts the offset to our destination to little endian

            static_cast<std::byte>((relativeOffset >> 8) & 0xFF),                                                                         // to be used in the jmp instructions
            static_cast<std::byte>((relativeOffset >> 16) & 0xFF),                                                                        // we will patch into memory
            static_cast<std::byte>((relativeOffset >> 24) & 0xFF)
        };

        return result;                                                                                                       // returns the result
    }
    default:
    {
      std::vector<std::byte> result = { std::byte{ 0x00 } };
      return result;
    }
    }
}