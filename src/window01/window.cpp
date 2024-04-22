/**
 * @file window.cpp
 * @brief 第一个OpenGL窗口
 * 
 * @author chujun
 * @date 2024-04-17
 * @version 1.0.0
*/
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

using namespace  std;

void FrameBufferSizeCallback(GLFWwindow* aWindow, int aWidth, int aHeight);
void ProcessInput(GLFWwindow* aWindow);
int	main(int argc, char **argv)
{
    /// init glfw
    if (!glfwInit())
    {
        cerr << " GLFW Init Failed! " << endl;
        return -1;
    } 

    /// opengl3.3 core-profile model
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGl", NULL, NULL);
    
    if (window == NULL)
    {
        cout << " Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    glClearColor(0.2f, 0.3f , 0.3f, 1.0f);

    /// @brief IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        ProcessInput(window);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void FrameBufferSizeCallback(GLFWwindow* aWindow, int aWidth, int aHeight)
{
    glViewport(0, 0, aWidth, aHeight);
}
void ProcessInput(GLFWwindow* aWindow)
{
    if (glfwGetKey(aWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(aWindow, true);
}