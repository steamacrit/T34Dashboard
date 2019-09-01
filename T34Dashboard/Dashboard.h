#pragma once

class Event;
class WindowWidget;
struct GLFWwindow;

class Dashboard
{
public:
    Dashboard(bool windowed = false);
    ~Dashboard();
    
    void Render();

private:


    std::unique_ptr<WindowWidget> m_base_window;

private:
    void Initialize(bool windowed = true);

    void OnEvent(Event & event);
};

