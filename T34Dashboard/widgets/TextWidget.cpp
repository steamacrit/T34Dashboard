#include "pch.h"
#include "TextWidget.h"

TextWidget::TextWidget(const std::string & text)
    : BoundWidget(WidgetType::Text, &m_props)
{
    m_props.text.SetValue(text);
}

TextWidget::~TextWidget()
{
}

void TextWidget::Render()
{
    ImGui::Text(m_props.text.GetValue().c_str());
}
