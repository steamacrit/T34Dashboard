#pragma once

#include "Renderable.h"
#include <string>

class WindowWidget : public Renderable
{
public:   
    WindowWidget(const std::string & title = "Debug");
    ~WindowWidget();

    inline const std::string & GetTitle() { return m_title; }
    inline void SetTitle(const std::string & title) { m_title = title; }
    inline void SetTitle(const char * title) { m_title = title; }
    inline void SetFlags(ImGuiWindowFlags flags) { m_flags = m_flags; }

    inline WID AddChild(Renderable * child) { assert(child); m_children[child->GetID()] = child; return child->GetID(); }
    void RemoveChild(WID id);
    inline void RemoveChild(Renderable * child) { assert(child); RemoveChild(child->GetID()); }

    void Render() override;
    void RenderProperties() override;

protected:
    
  
private:
    std::string m_title;
    ImGuiWindowFlags m_flags;
    WindowProperties m_props;

    std::unordered_map<WID, Renderable *> m_children;
};