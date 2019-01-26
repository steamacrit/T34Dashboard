#include "pch.h"
#include "Renderable.h"
#include "../fuid.h"

#include "../Dashboard.h"

Renderable::Renderable(const RenderableType & type)
    : m_type(type) 
{ 
    m_id = UID().ToString();
}

Renderable::~Renderable() 
{ 
    m_children.clear();
}

void Renderable::Render()
{
    if (ImGui::IsMouseDragging())
    {

        m_position = ImGui::GetMousePos();
        ImGui::SetCursorPos(m_position);
    }

//    Dashboard::SetActiveWidget(this);
}

void Renderable::RenderChildren() 
{
    for (auto it = m_children.begin(); it != m_children.end(); it++)
        it->second->Render();
}

/*
void Renderable::SetParent(std::shared_ptr<Renderable> parent)
{
    if (m_parent)
        if (m_parent == parent)
            return;
        else
            m_parent->RemoveChild(this);

    m_parent = parent;
    m_parent->AddChild(this);
}
*/

void Renderable::AddChild(std::shared_ptr<Renderable> child)
{
//    child->SetParent(this);
    m_children[child->m_id] = child;
}

void Renderable::RemoveChild(std::shared_ptr<Renderable> child)
{
    auto it = m_children.find(child->m_id.c_str());
    if (it != m_children.end())
        m_children.erase(it);
}

void Renderable::RemoveChild(std::string id)
{
    for (auto it = m_children.begin(); it != m_children.end(); it++)
    {
        if (id.compare(it->first) == 0)
        {
            m_children.erase(it);
            return;
        }
    }
}

void Renderable::DeleteChild(std::shared_ptr<Renderable>  child)
{
    auto it = m_children.find(child->m_id);
    if (it != m_children.end())
        m_children.erase(it);
}

void Renderable::DeleteChild(std::string id)
{
    for (auto it = m_children.begin(); it != m_children.end(); it++)
    {
        if (id.compare(it->first) == 0)
        {
            m_children.erase(it);
            return;
        }
    }
}