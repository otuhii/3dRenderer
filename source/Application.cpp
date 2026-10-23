//
// Created by otuhii on 10/23/26.
//

#include "../include/Application.h"

Application::Application()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    main_window_ = std::make_unique<Window>(640, 480, "test application");
}

Application::~Application()
{
    main_window_.reset();
    glfwTerminate();
}
