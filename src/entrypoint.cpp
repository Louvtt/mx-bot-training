#include "mx/application.hpp"
#include "mx/mx.hpp"
#include <cstdio>
#include <exception>

#include "spdlog/spdlog.h"

int main(int argc, char** argv)
{
    mx::Application* app = nullptr;
    try {
        app = createApplication(argc, argv);
        app->run();
    }
    catch(std::exception e)
    {
        spdlog::error("[ERROR]: {}", e.what());
        return 1;
    }
    delete app;

    return 0;
}