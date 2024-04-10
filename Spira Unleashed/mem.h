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

	JmpInstruction prepAddrForJmp(uintptr_t address, uintptr_t jmpTarget, int32_t bytesFromAddr = 5);

	JmpInstruction prepAddrForJe(uintptr_t address, uintptr_t jmpTarget, int32_t bytesFromAddr = 6);
	
}