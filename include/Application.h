//
// Created by otuhii on 10/23/26.
//

#ifndef RENDERER_APPLICATION_H
#define RENDERER_APPLICATION_H

#include <Window.h>

#include <memory>

class Application {
public:
    Application();

    ~Application();

private:
    std::unique_ptr<Window> main_window_{};
    //...some other stuff later: renderer, inout handler and all that
};


#endif //RENDERER_APPLICATION_H
