#include "pch.h"
#include "WindowWidget.h"

WindowWidget::WindowWidget(const std::string & title)
    : Widget(WidgetType::Window, &m_props)
    , m_title(title)
{
}

WindowWidget::~WindowWidget()
{
    for (auto child : m_children)
        delete child.second;

    m_children.clear();
}

void WindowWidget::RemoveChild(WID id)
{
    auto child = m_children.find(id);
    if (child != m_children.end())
    {
        delete child->second;
        m_children.erase(child);
    }
}

void WindowWidget::Render()
{
    if (!GetIsVisible())
        return;

    if (m_props.position_x.HasChanged() || m_props.position_y.HasChanged())
        ImGui::SetNextWindowPos(ImVec2(m_props.position_x.GetValue(), m_props.position_y.GetValue()));

    if (m_props.size_w.HasChanged() || m_props.size_h.HasChanged())
        ImGui::SetNextWindowSize(ImVec2(m_props.size_w.GetValue(), m_props.size_h.GetValue()));

//    m_flags = m_props.window_flags;

    bool open;
    if (ImGui::Begin(m_title.c_str(), &open, m_props.window_flags))
    {

        for (auto child : m_children)
            child.second->Render();
    }

    ImVec2 pos = ImGui::GetWindowPos();
    m_props.position_x.SetValueDirect(pos.x);
    m_props.position_y.SetValueDirect(pos.y);

    ImVec2 size = ImGui::GetWindowSize();
    m_props.size_w.SetValueDirect(size.x);
    m_props.size_h.SetValueDirect(size.y);


    SetVisible(open);

    ImGui::End();
}

void WindowWidget::RenderProperties()
{
    ImVec2 frame_size = ImGui::GetIO().DisplaySize;
    float & x = m_props.position_x.GetValue();
    float & y = m_props.position_y.GetValue();
    float & w = m_props.size_w.GetValue();
    float & h = m_props.size_h.GetValue();
    bool & movable = m_props.fg_movable.GetValue();
    bool & resize = m_props.fg_resize.GetValue();
    bool & titlebar = m_props.fg_titlebar.GetValue();

    ImGui::Text("Name: %s", m_title.c_str());
    ImGui::BeginChild("Location:", ImVec2(300.0f, 100.0f), true);
        m_props.position_x.SetChanged(ImGui::SliderFloat("##X", &x, 0.0f, frame_size.x));
        m_props.position_y.SetChanged(ImGui::SliderFloat("##Y", &y, 0.0f, frame_size.y));
        
        if (ImGui::Checkbox("##Movable", &movable))
        {
            if (movable)
                m_props.window_flags ^= ImGuiWindowFlags_NoMove;
            else
                m_props.window_flags |= ImGuiWindowFlags_NoMove;
        }
    ImGui::EndChild();

    ImGui::BeginChild("Size:", ImVec2(300.0f, 100.0f), true);
        m_props.size_w.SetChanged(ImGui::SliderFloat("##W", &w, 1.0f, frame_size.x));
        m_props.size_h.SetChanged(ImGui::SliderFloat("##H", &h, 0.0f, frame_size.y));
        
        if (ImGui::Checkbox("##Resize", &resize))
        {
            if (resize)
                m_props.window_flags ^= ImGuiWindowFlags_NoResize;
            else
                m_props.window_flags |= ImGuiWindowFlags_NoResize;
        }
    ImGui::EndChild();

    ImGui::BeginChild("Appearance:", ImVec2(300.0f, 100.0f), true);
    if (ImGui::Checkbox("##Titlebar", &titlebar))
        {
            if (titlebar)
                m_props.window_flags ^= ImGuiWindowFlags_NoTitleBar;
            else
                m_props.window_flags |= ImGuiWindowFlags_NoTitleBar;
        }
    ImGui::EndChild();


}