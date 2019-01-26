// T34Dashboard.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <Windows.h>
#include <conio.h>
#include "LimitInstance.h"
#include "DashboardWindow.h"

using namespace T34DB;


int main()
{
#ifdef NDEBUG
    FreeConsole();
#endif

    LimitInstance ThereCanBeOnlyOne;

    Log::Init();
    DashboardWindow win(true);
    return win.Run();
}

