#pragma once

#include "Renderable.h"

class WidgetManager
{
public:
    WidgetManager(float width, float height);
    ~WidgetManager();

    void OnSizeChanged(uint32_t width, uint32_t height);

    void Render();

    const uint32_t NewWindow(const std::string & title = "Debug");
    const uint32_t NewWindow(const uint32_t & parent_id, const std::string & title = "Debug");

    const uint32_t NewText(const uint32_t & parent_id, const std::string & text);

    void AddChild(const std::string & parent_id, Renderable * child);
    void AddChild(const Renderable * parent, Renderable * child);

    void RemoveChild(const std::string & parent_id, const std::string & child_id);
    void RemoveChild(const Renderable * parent, const std::string &  child_id);

private:
    std::unordered_map<uint32_t, Renderable *> m_windows;
    
};