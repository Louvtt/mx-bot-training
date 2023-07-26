#include <iostream>
#include "mx/application.hpp"
#include "mx/mx.hpp"

mx::Application* createApplication(int argc, char **argv)
{
    return new mx::Application();
}