#include <Windows.h>
#include "imports.h"

namespace IAT
{
	namespace Kernel32
	{
		VOID(WINAPI* GetSystemTime)(LPSYSTEMTIME lpSystemTime);
	}
}