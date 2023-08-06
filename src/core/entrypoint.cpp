#include "mx/mx.hpp"
#include <cstdio>
#include <exception>

#include "spdlog/spdlog.h"

int main(int argc, char** argv)
{
    std::unique_ptr<mx::Application> app = nullptr;
    try {
        spdlog::trace("Creating Application");
        app = createApplication(argc, argv);
        spdlog::trace("Running Application");
        app->run();
        spdlog::trace("Quitting Application");
    }
    catch(std::exception e)
    {
        spdlog::error("[ERROR]: {}", e.what());
        app.reset();
        return 1;
    }
    app.reset();

    return 0;
}