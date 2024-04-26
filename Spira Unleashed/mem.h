#include <Windows.h>
#include <cstdint>
#pragma once

struct JmpInstruction
{
	BYTE* jmpBytes;
	size_t size;
};

namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);

	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);

	JmpInstruction prepAddrForJmp(uintptr_t currentAddress, uintptr_t destinationAddress);

	JmpInstruction prepAddrForJe(uintptr_t currentAddress, uintptr_t destinationAddress);

	JmpInstruction prepAddrForJne(uintptr_t currAddr, uintptr_t dstAddr);
	
}