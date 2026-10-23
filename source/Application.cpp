//
// Created by otuhii on 10/23/26.
//

#include <Application.h>

Application::Application()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    main_window_ = std::make_unique<Window>(640, 480, "test application");
}

Application::~Application()
{
    main_window_.reset();
    glfwTerminate();
}

void Application::Run()
{
    while (!main_window_->ShouldClose())
    {
        main_window_->PollEvents();

        //...do some stuff

        main_window_->SwapBuffers();
    }
}
