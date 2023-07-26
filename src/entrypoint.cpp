#include "mx/application.hpp"
#include "mx/mx.hpp"
#include <cstdio>
#include <exception>

int main(int argc, char** argv)
{
    try {
        mx::Application* app = createApplication(argc, argv);
        app->run();
        delete app;
    }
    catch(std::exception e)
    {
        fprintf(stderr, "[ERROR]: %s", e.what());
        return 1;
    }

    return 0;
}