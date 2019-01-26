#pragma once

#include "../pch.h"
#include <imgui/imgui.h>

enum class RenderableType
{
    Window,
    Text,
    SliderFloat
};

class Renderable
{
public:
    Renderable(const RenderableType & type);
    virtual ~Renderable();

    virtual void Render();
    void RenderChildren();

    inline const std::string GetID() const { return m_id; }
    inline const RenderableType GetType() const { return m_type; }
    //void SetParent(std::shared_ptr<Renderable> parent);

    void AddChild(std::shared_ptr<Renderable> child);
    void RemoveChild(std::shared_ptr<Renderable> child);
    void RemoveChild(std::string id);
    void DeleteChild(std::shared_ptr<Renderable> child);
    void DeleteChild(std::string id);

private:
    std::unordered_map<std::string, std::shared_ptr<Renderable>> m_children;

protected:
    std::string m_id;
    RenderableType m_type;    
    std::shared_ptr<Renderable> m_parent{ nullptr };

    ImVec2 m_position{ 50.0f, 50.0f };
    ImVec2 m_size{ 50.0f, 50.0f };;
};
