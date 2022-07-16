// dllmain.cpp : Defines the entry point for the DLL application.
#include <stdio.h>
#include <windows.h>
#include <thread>
#include "handler.h"

SYSTEMTIME SavedTime;
LPCWSTR iniPath = L"C:\\timehook.ini";

VOID WINAPI DllThread()
{
    //open debug console
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    
    //MessageBox(NULL, L"Injection complete", L"DLL", MB_OK);

    if (Handler::Init())
    {
        Handler::Start();
    }

    while (1)
    {
        printf("Refreshing settings...\n");

        wchar_t wYear[16];
        GetPrivateProfileString(L"Time", L"year", 0, wYear, 16, iniPath);
        SavedTime.wYear = _wtoi(wYear);

        wchar_t wMonth[16];
        GetPrivateProfileString(L"Time", L"month", 0, wMonth, 16, iniPath);
        SavedTime.wMonth = _wtoi(wMonth);

        wchar_t wDay[16];
        GetPrivateProfileString(L"Time", L"day", 0, wDay, 16, iniPath);
        SavedTime.wDay = _wtoi(wDay);

        wchar_t wHour[16];
        GetPrivateProfileString(L"Time", L"hour", 0, wHour, 16, iniPath);
        SavedTime.wHour = _wtoi(wHour);

        wchar_t wMinute[16];
        GetPrivateProfileString(L"Time", L"minute", 0, wMinute, 16, iniPath);
        SavedTime.wMinute = _wtoi(wMinute);

        wchar_t wSecond[16];
        GetPrivateProfileString(L"Time", L"second", 0, wSecond, 16, iniPath);
        SavedTime.wSecond = _wtoi(wSecond);

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DllThread, NULL, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

