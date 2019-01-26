#pragma once

class Renderable;

class Editor
{
public:
    Editor();
    ~Editor();

    inline void SetWidget(Renderable * widget) { m_widget = widget; }
    void Render();

private:
    Renderable * m_widget;
};

