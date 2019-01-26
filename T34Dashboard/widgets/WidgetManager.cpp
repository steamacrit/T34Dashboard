#include "pch.h"
#include "WidgetManager.h"
#include "WindowWidget.h"
#include "TextWidget.h"

WidgetManager::WidgetManager(float width, float height)
{

}

WidgetManager::~WidgetManager()
{
    for (auto it = m_windows.begin(); it != m_windows.end(); it++)
        delete it->second;

    m_windows.clear();
}

void WidgetManager::OnSizeChanged(uint32_t width, uint32_t height)
{

}

void WidgetManager::Render()
{
    for (auto w : m_windows)
        w.second->Render();

    ImGui::Begin("Test Parent");
    ImVec2 size(450.0f, 250.0f);
    ImGui::BeginChild("Child", size, true);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::EndChild();
    ImGui::End();
}

const uint32_t WidgetManager::NewWindow(const std::string & title)
{
    WindowWidget * win = new WindowWidget(title);
    m_windows[win->GetID()] = win;
    return win->GetID();
}


const uint32_t WidgetManager::NewWindow(const uint32_t & parent_id, const std::string & title)
{
    WindowWidget * win = new WindowWidget(title);
    m_windows[win->GetID()] = win;
    auto pwin = m_windows.find(parent_id);
    if (pwin != m_windows.end())
        pwin->second->AddChild(win);

    return win->GetID();
}

const uint32_t WidgetManager::NewText(const uint32_t & parent_id, const std::string & text)
{
    TextWidget * tw = nullptr;
    auto pwin = m_windows.find(parent_id);
    if (pwin != m_windows.end())
    {
        tw = new TextWidget(text);
        pwin->second->AddChild(tw);
        return tw->GetID();
    }

    return 0;
}

void WidgetManager::AddChild(const std::string & parent_id, Renderable * child)
{

}

void WidgetManager::AddChild(const Renderable * parent, Renderable * child)
{

}

void WidgetManager::RemoveChild(const std::string & parent_id, const std::string & child_id)
{

}

void WidgetManager::RemoveChild(const Renderable * parent, const std::string &  child_id)
{

}