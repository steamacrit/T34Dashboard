#include "pch.h"
#include "Dashboard.h"
#include "DashboardWindow.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl.h>

#include "Events/ApplicationEvents.h"

#include "Widgets/WindowWidget.h"
#include "Widgets/TextWidget.h"

WID wnd_id;
WID text_id;
Editor editor;

#define BIND_EVENT_FN(x) std::bind(&Dashboard::x, this, std::placeholders::_1)

//std::shared_ptr<W_Window> test_win{ nullptr };
//std::shared_ptr<W_Text> text{ nullptr };
//std::shared_ptr<W_Slider> slider{ nullptr };
//Renderable * Dashboard::m_dragging_widget{ nullptr };


Dashboard::Dashboard(DashboardWindow * window)
{
    m_window = window;
    m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));

    m_edit_mode = true;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui::GetIO().IniFilename = nullptr;
    ImGui_ImplGlfw_InitForOpenGL(m_window->GetGLFWWindow(), true);

    ImGui_ImplOpenGL3_Init("#version 410");

    WindowWidget * wnd = new WindowWidget("Main");
    wnd_id = wnd->GetID();
    m_windows[wnd_id] = wnd;
    text_id = wnd->AddChild(new TextWidget("This is a test!"));

    editor.SetWidget(wnd);
}


Dashboard::~Dashboard()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Dashboard::Render()
{
    ImGuiIO& io = ImGui::GetIO();
    
    io.DisplaySize = ImVec2((float)m_window->GetWidth(), (float)m_window->GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    for (auto wnd : m_windows)
        wnd.second->Render();

    static bool show = true;
    if (show)
        ImGui::ShowDemoWindow(&show);

    editor.Render();
    ImGui::SetWindowFocus("Properties");
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
/*
    if (ImGui::IsMouseDragging())
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        if (!mouse_dragging)
        {
            ImVec2 mouse_pos = ImGui::GetMousePos();
            mouse_dragging = true;
            LOG_INFO("Mouse Drag Start ({0}, {1})", mouse_pos.x, mouse_pos.y);
        }
    }
    else if (mouse_dragging)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        ImVec2 mouse_pos = ImGui::GetMousePos();
        ImVec2 mouse_drag_delta = ImGui::GetMouseDragDelta();
        mouse_dragging = false;
        LOG_INFO("Mouse Drag Stop ({0}, {1}) -> Delta ({2}, {3})", 
            mouse_pos.x, mouse_pos.y, mouse_drag_delta.x, mouse_drag_delta.y);
    }
*/
/*
    // Draw Main Window
    ImVec2 pos = { 0, 0 };
    ImVec2 size = { (float)m_window->GetWidth(), (float)m_window->GetHeight() };

    ImVec4 color = { 0.5f, 0.25f, 0.0f, 1.0f };
    ImVec4 color_bg = { 0.2f, 0.2f, 0.2f, 1.0f };
    ImVec4 color_active = { 1.0f, 0.5f, 0.0f, 1.0f };

    ImGui::PushStyleColor(ImGuiCol_WindowBg, color_bg);
    ImGui::PushStyleColor(ImGuiCol_Border, color);
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, color);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, color);      // Background of checkbox, radio button, plot, slider, text input
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, color);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, color);
    ImGui::PushStyleColor(ImGuiCol_TitleBg, color);
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, color);
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, color);
    ImGui::PushStyleColor(ImGuiCol_ResizeGrip, color);
    ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, color_active);
    ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, color_active);

    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowPos(pos);

    ImGui::Begin("FRC Team 34 Dashboard", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::End();



    ImGui::PopStyleColor(8);
*/

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