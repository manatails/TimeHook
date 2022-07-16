#include <stdio.h>
#include <windows.h>
#include <detours.h>
#include "imports.h"
#include "handler.h"

namespace Hook
{
	namespace Kernel32
	{
		VOID WINAPI GetSystemTime(LPSYSTEMTIME lpSystemTime)
		{
			SYSTEMTIME tmSystemTemp;
			IAT::Kernel32::GetSystemTime(&tmSystemTemp);

			printf("Hooking GetSystemTime: (%04i-%02i-%02i %02i:%02i:%02i) -> (%04i-%02i-%02i %02i:%02i:%02i)\n", tmSystemTemp.wYear, tmSystemTemp.wMonth, tmSystemTemp.wDay, tmSystemTemp.wHour, tmSystemTemp.wMinute, tmSystemTemp.wSecond,
																 SavedTime.wYear, SavedTime.wMonth, SavedTime.wDay, SavedTime.wHour, SavedTime.wMinute, SavedTime.wSecond);

			tmSystemTemp.wYear = SavedTime.wYear;
			tmSystemTemp.wMonth = SavedTime.wMonth;
			tmSystemTemp.wDay = SavedTime.wDay;
			tmSystemTemp.wHour = SavedTime.wHour;
			tmSystemTemp.wMinute = SavedTime.wMinute;
			tmSystemTemp.wSecond = SavedTime.wSecond;

			*lpSystemTime = tmSystemTemp;


			return;
		}
	}
}

namespace Handler
{
	BOOL Init()
	{
		HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
		if (hKernel32 != NULL)
		{
			IAT::Kernel32::GetSystemTime = { reinterpret_cast<decltype(IAT::Kernel32::GetSystemTime)>(GetProcAddress(hKernel32, "GetSystemTime")) };
		}

		return hKernel32 != NULL;
	}

	VOID Start()
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		if (IAT::Kernel32::GetSystemTime != NULL)
		{
			DetourAttach(&(LPVOID&)IAT::Kernel32::GetSystemTime, Hook::Kernel32::GetSystemTime);
		}

		DetourTransactionCommit();
	}
}