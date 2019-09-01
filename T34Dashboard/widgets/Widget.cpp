#include "pch.h"
#include "../T34Dashboard.h"
#include "Widget.h"
#include "fuid.h"
#include "crc.h"


Widget::Widget(const WidgetType this_type, WidgetProperties * properties)
    : m_type(this_type)
    , m_id(CRC::fromString(UID().ToString()))
{
    T34_ASSERT(properties, "Widget contructor - properties = nullptr");
    m_base_props = properties;
}

Widget::~Widget()
{
    for (auto it = m_children.begin(); it != m_children.end(); it++)
        delete it->second;

    m_children.clear();
}

void Widget::RenderChildren()
{
    for (auto it = m_children.begin(); it != m_children.end(); it++)
        it->second->Render();
}

void Widget::AddChild(Widget * widget)
{
    if (widget)
        m_children[widget->GetID()] = widget;
}

void Widget::RemoveChild(const uint32_t & child_id)
{
    auto it = m_children.find(child_id);
    if (it != m_children.end())
        m_children.erase(it);
}



BoundWidget::BoundWidget(const WidgetType this_type, WidgetProperties * properties)
    : Widget(WidgetType::Window, properties)
{

}

BoundWidget::~BoundWidget()
{

}