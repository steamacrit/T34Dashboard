#pragma once

class Dashboard;
class Editor;

struct GLFWwindow;

class DashboardWindow
{
public:
    ~DashboardWindow();

    static std::shared_ptr<DashboardWindow> GetInstance();
    bool Create(bool fullscreen = false);
    void Destroy();

    int Run();
    void Render();

private:
    static std::shared_ptr<DashboardWindow> m_instance;
    GLFWwindow * m_window;
    bool m_glfw_initialized;
    bool m_fullscreen;
    float m_time;

    bool m_edit_mode;
    std::unique_ptr<Editor> m_editor;
    std::shared_ptr<Dashboard> m_dashboard;

private:
    DashboardWindow();

    void OnResize(GLFWwindow * m_window, int32_t width, int32_t height);
};

