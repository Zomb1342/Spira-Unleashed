#include <Windows.h>
#include <cstdint>
#include <memory>
#pragma once

struct JmpInstruction
{
	std::unique_ptr<BYTE[]> jmpBytes = NULL;
	size_t size = 0;
};

namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);

	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);

	JmpInstruction prepAddrForJmp(uintptr_t currentAddress, uintptr_t destinationAddress, int padding = 0);

	JmpInstruction prepAddrForJe(uintptr_t currentAddress, uintptr_t destinationAddress);

	JmpInstruction prepAddrForJne(uintptr_t currAddr, uintptr_t dstAddr);
	
}