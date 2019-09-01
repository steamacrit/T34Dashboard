#pragma once

class Dashboard;

class Editor
{
public:
    Editor(std::shared_ptr<Dashboard> dashboard);
    ~Editor();

    void Render();

private:
    std::shared_ptr<Dashboard> m_dashboard;
};

