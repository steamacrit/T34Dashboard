#pragma once

#include <windows.h> 
#include <iostream>

class LimitInstance
{
protected:
    HANDLE m_Mutex;

public:
    LimitInstance(const char * mutex_name = "Global\\{67A628BD-7BF2-4588-AEE3-A5849C995AAE}")
    {
        m_Mutex = CreateMutex(NULL, FALSE, mutex_name);

        if (ERROR_ALREADY_EXISTS == GetLastError())
        {
            std::cout << "T34Dashboard is already running...\n";
            exit(1);
        }
    }

    ~LimitInstance()
    {
        if (m_Mutex)  
        {
            CloseHandle(m_Mutex); 
            m_Mutex = nullptr; 
        }
    }
};
