// T34Dashboard.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <Windows.h>
#include <conio.h>
#include "LimitInstance.h"
#include "Dashboard.h"
#include "DashboardWindow.h"

using namespace T34DB;


int main()
{
#ifdef NDEBUG
    FreeConsole();
#endif

    LimitInstance ThereCanBeOnlyOne;

    Log::Init();
    std::shared_ptr<DashboardWindow> win = DashboardWindow::GetInstance();
    win->Create();
    return win->Run();
}

