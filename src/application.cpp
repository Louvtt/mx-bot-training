#include "mx/application.hpp"


#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/gl.h>

#include <stdio.h>
#include <stdexcept>


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

mx::Application::Application()
: m_time()
{
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()) {
        throw std::runtime_error("GLFW Failed to load");
    }

    const char* glsl_version = "#version 460";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Window initialisation
    m_window = glfwCreateWindow(800, 600, "MxBotLauncher", NULL, NULL);
    if(m_window == nullptr) {
        throw std::runtime_error("Failed to create the window");
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Init OpenGL
    int version = gladLoadGL(glfwGetProcAddress);
    if(version == 0) {
        throw std::runtime_error("Failed to load openGL");
    }
    printf("Loaded GL: %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    // Init imgui
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }
}

mx::Application::~Application()
{
    // Imgui shutdown
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    // glfw shutdown
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void mx::Application::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        preRender();

        // update time
        m_time.frameCount ++;
        m_time.time = glfwGetTime();

        // application dependant
        update();
        render();

        postRender();
    }
}

void mx::Application::preRender()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(.1f, .1f, .1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void mx::Application::postRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);
}

void mx::Application::update()
{}
void mx::Application::render()
{
    // Default interface
    ImGui::Begin("Demo");
    
    ImGui::End();
}