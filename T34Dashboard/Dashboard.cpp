#include "pch.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl.h>

#include "T34Dashboard.h"
#include "Dashboard.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

//#include <wpilib/ntcore_c.h>
//#include <wpilib/networktables/NetworkTableInstance.h>

#include "Widgets/WindowWidget.h"
#include "Widgets/TextWidget.h"

WID wnd_id;
WID text_id;
TextWidget tw;
//Editor editor;

//nt::NetworkTableInstance nt_inst;
//std::shared_ptr<nt::NetworkTable> nt_table;

#define BIND_EVENT_FN(x) std::bind(&Dashboard::x, this, std::placeholders::_1)



Dashboard::Dashboard(bool windowed)

{
    Initialize(windowed);

}


Dashboard::~Dashboard()
{

}

void Dashboard::Initialize(bool windowed)
{
}





void Dashboard::Render()
{
    ImGuiIO & io = ImGui::GetIO();
    std::stringstream ss;
    ss << "Framerate: " << io.Framerate << " (fps)";
    ImGui::Text(ss.str().c_str());
}



void Dashboard::OnEvent(Event & event)
{
    if (event.GetEventType() == EventType::WindowResize)
    {
        WindowResizeEvent e = (WindowResizeEvent&)event;
        //m_manager->OnSizeChanged(m_window->GetWidth(), m_window->GetHeight());
    }
//    LOG_TRACE("{0}", event.ToString());
}
