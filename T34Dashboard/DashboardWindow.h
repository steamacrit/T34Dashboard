#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Dashboard.h"

#include "Events/Event.h"

using EventCallbackFn = std::function<void(Event&)>;

class DashboardWindow
{
public:
    DashboardWindow(bool windowed = false);
    ~DashboardWindow();

    void Initialize(bool windowed);
    
    inline int GetWidth() { return m_data.width; }
    inline int GetHeight() { return m_data.height; }
    inline GLFWwindow * GetGLFWWindow() { return m_window; }

    int Run();

    // Window attributes
    inline void SetEventCallback(const EventCallbackFn & callback) { m_data.event_callback = callback; }

private:
    GLFWwindow * m_window;

    struct WindowData
    {
        std::string title;
        unsigned int width, height;

        EventCallbackFn event_callback;
    };

    WindowData m_data;

    std::unique_ptr<Dashboard> m_dashboard;
};

