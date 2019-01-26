#include "pch.h"
#include "Renderable.h"
#include "fuid.h"
#include "crc.h"


Renderable::Renderable(const RenderableType this_type)
    : type(this_type)
    , id(CRC::fromString(UID().ToString()))
    , m_position(ImVec2(0.0f, 0.0f))
{
   
}

Renderable::~Renderable()
{
    for (auto it = m_children.begin(); it != m_children.end(); it++)
        delete it->second;

    m_children.clear();
}

void Renderable::RenderChildren()
{
    for (auto it = m_children.begin(); it != m_children.end(); it++)
        it->second->Render();
}

void Renderable::AddChild(Renderable * renderable)
{
    if (renderable)
        m_children[renderable->GetID()] = renderable;
}

void Renderable::RemoveChild(const uint32_t & child_id)
{
    auto it = m_children.find(child_id);
    if (it != m_children.end())
        m_children.erase(it);
}