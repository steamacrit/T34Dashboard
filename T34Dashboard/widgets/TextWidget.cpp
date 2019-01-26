#include "pch.h"
#include "TextWidget.h"

TextWidget::TextWidget(const std::string & text)
    : Renderable(RenderableType::Text)
    , m_text(text)
{
}

TextWidget::~TextWidget()
{
}

void TextWidget::Render()
{
    ImGui::Text(m_text.c_str());
}
