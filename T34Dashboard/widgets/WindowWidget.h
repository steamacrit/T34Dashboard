#pragma once

#include "Widget.h"
#include <string>

class WindowWidget : public Widget
{
public:   
    WindowWidget(const std::string & title = "Debug");
    ~WindowWidget();

    inline const std::string & GetTitle() { return m_title; }
    inline void SetTitle(const std::string & title) { m_title = title; }
    inline void SetTitle(const char * title) { m_title = title; }
    inline void SetFlags(ImGuiWindowFlags flags) { m_props.window_flags = flags; }

    inline WID AddChild(Widget * child) { assert(child); m_children[child->GetID()] = child; return child->GetID(); }
    void RemoveChild(WID id);
    inline void RemoveChild(Widget * child) { assert(child); RemoveChild(child->GetID()); }

    void Render() override;
    void RenderProperties() override;

protected:
    
  
private:
    std::string m_title;
    WindowProperties m_props;

    std::unordered_map<WID, Widget *> m_children;
};