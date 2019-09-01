#pragma once


#include <imgui/imgui.h>
#include "Properties.h"

enum class WidgetType
{
    Window,
    ChildWindow,
    Text,
    Slider
};

class Widget
{
public:
    Widget(const WidgetType this_type, WidgetProperties * properties);
    virtual ~Widget();

    inline const uint32_t & GetID() { return m_id; }

    inline bool GetIsVisible() { return m_base_props->visible.GetValue(); }
    inline void SetVisible(bool visible = true) { m_base_props->visible.GetValue() = visible; }

    inline ImVec2 GetPosition() const { return ImVec2(m_base_props->position_x.GetValue(), m_base_props->position_y.GetValue()); }
    inline float GetPositionX() const { return m_base_props->position_x.GetValue(); }
    inline float GetPositionY() const { return m_base_props->position_y.GetValue(); }

    void SetPosition(const ImVec2 & pos) { m_base_props->position_x.SetValue(pos.x); m_base_props->position_x.SetValue(pos.y); }
    void SetPosition(const float x, const float y) { m_base_props->position_x.SetValue(x); m_base_props->position_x.SetValue(y); }
    void SetPositionX(const float x) { m_base_props->position_x.SetValue(x); }
    void SetPositionY(const float y) { m_base_props->position_x.SetValue(y); }

    inline ImVec2 GetSize() const { return ImVec2(m_base_props->size_w.GetValue(), m_base_props->size_h.GetValue()); }
    inline float GetSizeWidth() const { return m_base_props->size_w.GetValue(); }
    inline float GetSizeHeight() const { return m_base_props->size_h.GetValue(); }

    void SetSize(const ImVec2 & size) { m_base_props->size_w.SetValue(size.x); m_base_props->size_h.SetValue(size.y); }
    void SetSize(const float width, float height) { m_base_props->size_w.SetValue(width); m_base_props->size_h.SetValue(height); }
    void SetSizeWidth(const float width) { m_base_props->size_w.SetValue(width); }
    void SetSizeHeight(const float height) { m_base_props->size_h.SetValue(height); }

    virtual void Render() = 0;
    virtual void RenderProperties() = 0;

protected:
    void AddChild(Widget * renderable);
    void RemoveChild(const uint32_t & child_id);
    void RenderChildren();

private:
    const WidgetType m_type;
    WidgetProperties * m_base_props;

    const uint32_t m_id;

    std::unordered_map<uint32_t, Widget *> m_children;
};

class BoundWidget : public Widget
{
public:
    BoundWidget(const WidgetType this_type, WidgetProperties * properties);
    virtual ~BoundWidget();

    virtual void Render() = 0;
    virtual void RenderProperties() = 0;
};