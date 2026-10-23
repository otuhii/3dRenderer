//
// Created by otuhii on 10/23/26.
//

#ifndef RENDERER_WINDOW_H
#define RENDERER_WINDOW_H

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


class Window {
public:
    Window(
        int window_width, int window_height,
        const std::string& title_message
    );

    Window(Window const&) = delete;
    Window& operator=(Window const&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    bool ShouldClose() const;
    void SwapBuffers() const;
    void PollEvents() const;

    ~Window();
private:
    GLFWwindow* window_{};

    static void FrameBufferSizeCallback(
        GLFWwindow* window,
        int width, int height
    );
};


#endif //RENDERER_WINDOW_H
