#include "pch.h"
#include "Editor.h"
#include "Widgets/Renderable.h"

#include <imgui/imgui.h>

Editor::Editor()
{
}


Editor::~Editor()
{
}

void Editor::Render()
{
    assert(m_widget);
    
    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    m_widget->RenderProperties();
    ImGui::End();
}