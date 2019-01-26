#pragma once

#include "Renderable.h"
#include <string>


class TextWidget : public Renderable
{
public:
    TextWidget(const std::string & text = "");
    ~TextWidget();

    inline const std::string & GetText() const { return m_text; }

    void Render();
    void RenderProperties() override {};

protected:

private:
    std::string m_text;
};