#include "pch.h"
#include "T34Dashboard.h"
#include "DashboardWindow.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl.h>

static bool s_glfw_initialized = false;

void ErrorCallback(int error, const char * description)
{
    LOG_ERROR("GLFW({0} - {1}", error, description);
}

DashboardWindow::DashboardWindow(bool windowed)
{
    Initialize(windowed);
}

DashboardWindow::~DashboardWindow()
{
    m_dashboard.reset();
    glfwTerminate();
}

void DashboardWindow::Initialize(bool windowed)
{
    if (!windowed)
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    m_data.title = "FRC Team 34 Dashboard";
    m_data.width = 1024;
    m_data.height = 720;

    LOG_INFO("Creating window {0} ({1}, {2})", m_data.title, m_data.width, m_data.height);

    if (!s_glfw_initialized)
    {
        // TODO: glfwTerminate on system shutdown
        int success = glfwInit();
        T34_ASSERT(success, "Could not intialize GLFW!");
        glfwSetErrorCallback(ErrorCallback);
        s_glfw_initialized = true;
    }

    m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_data);

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

    m_dashboard.reset(new Dashboard(this));

/*
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, false);
    //ImGui_ImplGlfwGL3_Init(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
*/

/*

// Set GLFW callbacks
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.event_callback(event);
    });

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
}

int DashboardWindow::Run()
{
    ImVec4 clear_color = ImVec4(0.4f, 0.4f, 0.4f, 1.00f);
/*
    bool show_demo_window = true;

    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGuiIO & io = ImGui::GetIO(); (void)io;
    //io.MouseDrawCursor = true;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

*/    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        
/*
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        //ImGui_ImplGlfwGL3_NewFrame();
        ImGui::NewFrame();

        m_dashboard->Render();

        //ImGui::ShowStyleEditor(nullptr);
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
 //       if (show_demo_window)
//            ImGui::ShowDemoWindow(&show_demo_window);
*/
/*
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }


        ImGui::Render();
*/
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        m_dashboard->Render();

//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);

    }

/*
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    //ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
*/
    return 0;
}


