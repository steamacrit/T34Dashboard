#pragma once


#include <imgui/imgui.h>
#include "Properties.h"

enum class RenderableType
{
    Window,
    ChildWindow,
    Text,
    Slider
};

class Renderable
{
public:
    Renderable(const RenderableType this_type);
    virtual ~Renderable();

    inline const uint32_t & GetID() { return id; }

    inline bool GetIsVisible() { return m_is_visible; }
    inline void SetVisible(bool visible = true) { m_is_visible = visible; }

    inline ImVec2 GetPosition() const { return m_position; }
    inline float GetPositionX() const { return m_position.x; }
    inline float GetPositionY() const { return m_position.y; }

    inline void SetPosition(const ImVec2 & pos) { m_position = pos; m_update_position = true; }
    inline void SetPosition(const float x, const float y) { m_position.x = x; m_position.y = y; m_update_position = true; }
    inline void SetPositionX(const float x) { m_position.x = x; m_update_position = true; }
    inline void SetPositionY(const float y) { m_position.y = y; m_update_position = true; }
    inline bool IsPositionUpdated() { return m_update_position; }

    inline ImVec2 GetSize() const { return m_size; }
    inline float GetSizeWidth() const { return m_size.x; }
    inline float GetSizeHeight() const { return m_size.y; }

    inline void SetSize(const ImVec2 & pos) { m_position = pos; }
    inline void SetSize(const float width, float height) { m_size.x = width; m_size.y = height; }
    inline void SetSizeWidth(const float width) { m_position.x = width; }
    inline void SetSizeHeight(const float height) { m_position.y = height; }

    virtual void Render() = 0;
    virtual void RenderProperties() = 0;

protected:
    void AddChild(Renderable * renderable);
    void RemoveChild(const uint32_t & child_id);
    void RenderChildren();

private:
    const RenderableType type;
    const uint32_t id;
    bool m_is_visible{ true };
    bool m_update_position{ false };
    ImVec2 m_position;
    ImVec2 m_size;

    std::unordered_map<uint32_t, Renderable *> m_children;
};

