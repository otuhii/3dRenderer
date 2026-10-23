//
// Created by otuhii on 10/23/26.
//

#ifndef RENDERER_APPLICATION_H
#define RENDERER_APPLICATION_H

#include <Window.h>

#include <memory>
#include <glad/gl.h>

class Application {
public:
    static Application& GetInstance() {
        static Application app;
        return app;
    }

    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    void Run();

private:
    Application();
    ~Application();

    std::unique_ptr<Window> main_window_{};
    //...some other stuff later: renderer, inout handler and all that
};


#endif //RENDERER_APPLICATION_H
