#pragma once
#include <Windows.h>

namespace IAT
{
	namespace Kernel32
	{
		extern VOID(WINAPI* GetSystemTime)(LPSYSTEMTIME lpSystemTime);
	}
}