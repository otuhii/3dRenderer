//
// Created by otuhii on 10/23/26.
//

#include <Window.h>


Window::Window(int window_width, int window_height, const std::string &title_message)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(
        window_width,
        window_height,
        title_message.c_str(),
        NULL, NULL
    );

    if (!window_)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetFramebufferSizeCallback(window_, FrameBufferSizeCallback);
    glfwMakeContextCurrent(window_);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(window_);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(window_);
}

void Window::PollEvents() const
{
    glfwPollEvents();

    //separate input later
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window_, 1);
    }
}

Window::~Window()
{
    glfwDestroyWindow(window_);
}

void Window::FrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
