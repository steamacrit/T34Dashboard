#pragma once

#include "Widget.h"
#include <string>


class TextWidget : public BoundWidget
{
public:
    TextWidget(const std::string & text = "");
    ~TextWidget();

    inline void SetText(const std::string & text) { m_props.text.SetValue(text); }
    inline const std::string & GetText() { return m_props.text.GetValue(); }
    
    void Render();
    void RenderProperties() override {};

protected:

private:
    TextProperties m_props;
};