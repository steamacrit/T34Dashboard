#include "pch.h"
#include "DashboardWindow.h"

#include "Dashboard.h"
#include "Editor.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl.h>


void ErrorCallback(int error, const char * description)
{
    LOG_ERROR("GLFW({0} - {1}", error, description);
}

std::shared_ptr<DashboardWindow> DashboardWindow::m_instance = nullptr;

DashboardWindow::DashboardWindow()
    : m_glfw_initialized(false)
    , m_window(nullptr)
    , m_edit_mode(false)
    , m_dashboard(nullptr)
    , m_editor(nullptr)
{
}


DashboardWindow::~DashboardWindow()
{
    Destroy();
    glfwTerminate();
}

std::shared_ptr<DashboardWindow> DashboardWindow::GetInstance()
{
    if (m_instance == nullptr)
        m_instance.reset(new DashboardWindow);

    return m_instance;
}

bool DashboardWindow::Create(bool fullscreen)
{
    if (!m_glfw_initialized)
    {
        int success = glfwInit();
        T34_ASSERT(success, "Could not intialize GLFW!");
        glfwSetErrorCallback(ErrorCallback);
        m_glfw_initialized = true;
    }

    if (m_window != nullptr)
        Destroy();

    if (fullscreen)
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    const char * title = "FRC Team 34 Dashboard";
    int32_t width = 1024;
    int32_t height = 720;

    LOG_INFO("Creating window {0} ({1}, {2})", title, width, height);



    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);

    //    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1); // Enable vsync


    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
        LOG_ERROR("{0}", glewGetErrorString(err));
    else
    {
        int32_t ogl_major, ogl_minor;
        glGetIntegerv(GL_MAJOR_VERSION, &ogl_major);
        glGetIntegerv(GL_MINOR_VERSION, &ogl_minor);
        LOG_DEBUG("OpenGL: v{0}.{1}", ogl_major, ogl_minor);
    }

    glEnable(GL_DEPTH_TEST);

    // Set GLFW callbacks


    /*
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, false);
    //ImGui_ImplGlfwGL3_Init(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    */

    /*



    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
    {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.event_callback(event);
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    switch (action)
    {
    case GLFW_PRESS:
    {
    KeyPressedEvent event(key, 0);
    data.event_callback(event);
    break;
    }
    case GLFW_RELEASE:
    {
    KeyReleasedEvent event(key);
    data.event_callback(event);
    break;
    }
    case GLFW_REPEAT:
    {
    KeyPressedEvent event(key, 1);
    data.event_callback(event);
    break;
    }
    }
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
    {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    switch (action)
    {
    case GLFW_PRESS:
    {
    MouseButtonPressedEvent event(button);
    data.event_callback(event);
    break;
    }
    case GLFW_RELEASE:
    {
    MouseButtonReleasedEvent event(button);
    data.event_callback(event);
    break;
    }
    }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    MouseScrolledEvent event((float)xOffset, (float)yOffset);
    data.event_callback(event);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
    {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    MouseMovedEvent event((float)xPos, (float)yPos);
    data.event_callback(event);
    });
    */

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui::GetIO().IniFilename = nullptr;
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);

    ImGui_ImplOpenGL3_Init("#version 410");

    glfwGetWindowSize(m_window, &width, &height);

//    m_base_window.reset(new WindowWidget);
//    m_base_window->SetFlags(ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs);

//    m_base_window->SetPosition(0.0f, 0.0f);
//    m_base_window->SetSize(width, height);

    glfwSetWindowSizeCallback(m_window,
        [](GLFWwindow * window, int32_t width, int32_t height)
    {
        DashboardWindow * win = (DashboardWindow *)glfwGetWindowUserPointer(window);
        win->OnResize(window, width, height);
    });

/*
    bool connected = false;
    nt_inst = nt::NetworkTableInstance::GetDefault();
    //nt_inst.StartServer();
    //nt_inst.StartClient("");
    nt_inst.
        //nt_inst.StartDSClient();
        connected = nt_inst.IsConnected();
    nt_table = nt_inst.GetTable("Usage");
    std::vector<nt::NetworkTableEntry> entries = nt_inst.GetEntries("/SmartDashboard/DB/", 0);
*/

    m_time = 0.0f;

    m_dashboard.reset(new Dashboard());
    m_editor.reset(new Editor(m_dashboard));

    return true;
}

void DashboardWindow::Destroy()
{
    if (m_window != nullptr)
        glfwDestroyWindow(m_window);

    m_window = nullptr;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DashboardWindow::OnResize(GLFWwindow * m_window, int32_t width, int32_t height)
{
//    m_base_window->SetSize(width, height);

    ImGuiIO io = ImGui::GetIO();
    io.DisplaySize.x = width;
    io.DisplaySize.y = height;
}

int DashboardWindow::Run()
{
    ImVec4 clear_color = ImVec4(1.0f, 0.7f, 0.0f, 1.00f);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        Render();

        glfwSwapBuffers(m_window);
    }


    return 0;
}

void DashboardWindow::Render()
{
    ImGuiIO & io = ImGui::GetIO();
    int32_t w;
    int32_t h;

    glfwGetWindowSize(m_window, &w, &h);

    io.DisplaySize = ImVec2((float)w, (float)h);

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
    m_time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_edit_mode = true;

    if (m_edit_mode)
        m_editor->Render();
    else
        m_dashboard->Render();
    



    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}