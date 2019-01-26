#pragma once

#include "Events/Event.h"
#include "Editor.h"

class DashboardWindow;
class WindowWidget;


class Dashboard
{
public:
    Dashboard(DashboardWindow * window);
    ~Dashboard();

    void Render();
    

    void OnEvent(Event & event);
//    inline static void SetActiveWidget(Renderable * widget) { m_active_widget = widget; }

private:
    DashboardWindow * m_window;
    Editor m_editor;
    bool m_edit_mode;
    float m_Time = 0.0f;

    bool mouse_dragging{ false };

    std::unordered_map<WID, WindowWidget *> m_windows;

    
};

