#include "pch.h"
#include "Dashboard.h"
#include "Editor.h"
#include "Widgets/Widget.h"

#include <imgui/imgui.h>

Editor::Editor(std::shared_ptr<Dashboard> dashboard)
    : m_dashboard(dashboard)
{
}


Editor::~Editor()
{
}

void Editor::Render()
{
    ImGuiIO & io = ImGui::GetIO();


    ImGui::BeginChild("DashboardEdit", ImVec2(io.DisplaySize.x, io.DisplaySize.y));// ("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::BeginChild("DashboardEdit2", ImVec2(io.DisplaySize.x, io.DisplaySize.y));// ("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        m_dashboard->Render();
//    m_widget->RenderProperties();
    ImGui::EndChild();
    ImGui::EndChild();
}