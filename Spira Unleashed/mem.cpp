#include "proc.h"
#include "mem.h"

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess)
{
	DWORD oldProtect;
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hProcess, dst, src, size, nullptr);
	VirtualProtectEx(hProcess, dst, size, oldProtect, &oldProtect);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProcess)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);

	PatchEx(dst, nopArray, size, hProcess);
	delete[] nopArray;
}


JmpInstruction mem::prepAddrForJmp(uintptr_t currAddr, uintptr_t dstAddr)
{
    int32_t relativeOffset = (int32_t)(dstAddr - (currAddr + 5));                       // Add 5 to current address to account for the size of the jmp instruction.


    BYTE* jmpInstruction = new BYTE[6]; 
    jmpInstruction[0] = 0xE9;                                                            // JMP opcode
    jmpInstruction[1] = (relativeOffset & 0xFF);
    jmpInstruction[2] = ((relativeOffset >> 8) & 0xFF);
    jmpInstruction[3] = ((relativeOffset >> 16) & 0xFF);
    jmpInstruction[4] = ((relativeOffset >> 24) & 0xFF);
    jmpInstruction[5] = 0x90;                                                             // NOP opcode for padding
    JmpInstruction result{};
    result.jmpBytes = jmpInstruction;
    result.size = 6;

    return result;
}

JmpInstruction mem::prepAddrForJe(uintptr_t currAddr, uintptr_t dstAddr)
{
    int32_t offset = (int32_t)(dstAddr - (currAddr + 6));                                 // add 6 to current address to account for size of the JE instruction

    BYTE* jneInstruction = new BYTE[6]; 
    jneInstruction[0] = 0x0F;       // JE opcode
    jneInstruction[1] = 0x84;       // JE opcode
   
    jneInstruction[2] = (offset & 0xFF);
    jneInstruction[3] = ((offset >> 8) & 0xFF);
    jneInstruction[4] = ((offset >> 16) & 0xFF);
    jneInstruction[5] = ((offset >> 24) & 0xFF);

    JmpInstruction result;
    result.jmpBytes = jneInstruction;
    result.size = 6; 

    return result;
}

JmpInstruction mem::prepAddrForJne(uintptr_t currAddr, uintptr_t dstAddr)
{
    int32_t offset = (int32_t)(dstAddr - (currAddr + 6));                                    // calculate relative offset from the address we are jumping from

    BYTE* jneInstruction = new BYTE[6];
    jneInstruction[0] = 0x0F;       // JNE opcode
    jneInstruction[1] = 0x85;       // JNE opcode

    jneInstruction[2] = (offset & 0xFF);
    jneInstruction[3] = ((offset >> 8) & 0xFF);
    jneInstruction[4] = ((offset >> 16) & 0xFF);
    jneInstruction[5] = ((offset >> 24) & 0xFF);

    JmpInstruction result;
    result.jmpBytes = jneInstruction;
    result.size = 6;

    return result;
}