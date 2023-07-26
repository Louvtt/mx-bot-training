#ifndef _MX_APPLICATION_HPP_
#define _MX_APPLICATION_HPP_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "time.hpp"


namespace mx {

class Application
{
private:
    GLFWwindow* m_window;
    Time m_time;

public:
    Application(const char* name);
    virtual ~Application();

    void run();

private:
    void preRender();
    void postRender();

protected:
    virtual void update();
    virtual void render();
};

}

extern mx::Application* createApplication(int argc, char** argv);

#endif //_MX_APPLICATION_HPP_