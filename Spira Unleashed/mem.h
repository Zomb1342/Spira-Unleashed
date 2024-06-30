#include <Windows.h>
#include <cstdint>
#include <memory>
#include <vector>
#include <array>

#pragma once

enum JmpType
{
	JMP,
	JE,
	JNE,
};

std::vector<std::byte> prepJmp(int32_t currAddr, int32_t destinationAddr, JmpType jmpType, int32_t padding = 0);

namespace mem
{

	void PatchEx(BYTE* dst, std::vector<std::byte> src, HANDLE hProcess);

	template<size_t x>
	void PatchEx(BYTE* dst, std::array<std::byte, x> src, HANDLE hProcess);

	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
	
}