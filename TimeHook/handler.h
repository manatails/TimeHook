#pragma once
#include <Windows.h>

extern SYSTEMTIME SavedTime;

namespace Handler
{
	BOOL Init();
	VOID Start();
}