/**
 * @file main.cpp
 * @brief 你好,三角形
 * @note https://zhuanlan.zhihu.com/p/381493151
 * 
 * @author chujun
 * @date 2024-4-22
*/

#include "shader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace std;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600



bool GlfwInit(GLFWwindow* &window);
void FrameBufferSizeCallback(GLFWwindow* aWindow, int aWidth, int aHeight);
void ProcessInput(GLFWwindow* aWindow);


int main()
{
    GLFWwindow* window = nullptr;
    if (!GlfwInit(window))
    {
        cerr << "GlfwInit Failed!" << endl;
        return -1;
    }
    std::string base_path = "/home/ysc/驱动/opengl/src/triangle02/";
    std::string vs_file = base_path + "vertex_shader.vs";
    std::string fs_file = base_path + "fragment_shader.fs";
    Shader myShader(vs_file.c_str(), fs_file.c_str());

    float vertices[] = {
        // 第一个三角形
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, 0.5f, 0.0f,  // 左上角
        // 第二个三角形
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };
    cout << "============================================" << endl;
#pragma region VertexObject
    glGenVertexArrays(1, &myShader.VAO);
    glGenBuffers(1, &myShader.VBO);
    glBindVertexArray(myShader.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, myShader.VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#pragma endregion   

#pragma region IMGUI 
    ImGui::CreateContext();     // Setup Dear ImGui context
    ImGui::StyleColorsDark();       // Setup Dear ImGui style
    ImGui_ImplGlfw_InitForOpenGL(window, true);     // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init("#version 330");
    bool show_demo_window = true;
    bool show_another_window = false;
    float f = 0.0f;
    int counter = 0;
#pragma endregion
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);


#pragma region IMGUI 
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /// 显示 官方demo
        if (show_demo_window) 
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        
        /// 个人 窗口
        // Create a window called "Hello, world!" and append into it.
        ImGui::Begin("hello world!");
        // Display some text (you can use a format strings too)
        ImGui::Text("This is some useful text.");
        // Edit bools storing our window open/close state
        ImGui::Checkbox("Demo Window", &show_demo_window);      
        ImGui::Checkbox("Another Window", &show_another_window);
        // Edit 1 float using a slider from 0.0f to 1.0f  ———— (滑块控制)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        // Buttons return true when clicked (most widgets return true when edited/activated)
        if (ImGui::Button("Button"))
        {
            ++counter;
        }
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        /// 另一个 个人 窗口
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
            {
                show_another_window = false;
            }
            ImGui::End();
        }
#pragma endregion
        glClear(GL_COLOR_BUFFER_BIT);
#pragma region IMGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion
#pragma region RENDER
        glUseProgram(myShader.MyShader);
        glBindVertexArray(myShader.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
#pragma endregion
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glDeleteVertexArrays(1, &myShader.VAO);
    glDeleteBuffers(1, &myShader.VBO);
    glDeleteProgram(myShader.MyShader);
    glfwTerminate();
    return 0;
}
#pragma region glfw init
bool GlfwInit(GLFWwindow* &window)
{
    if (!glfwInit())
    {
        cerr << "glfw init failed!" << endl;
        return -1;
    }
    /// opengl3.3 core-profile model
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello-Triangle", NULL, NULL);
    
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
    return 1;
}
#pragma endregion

void FrameBufferSizeCallback(GLFWwindow* aWindow, int aWidth, int aHeight)
{
    glViewport(0, 0, aWidth, aHeight);
}
void ProcessInput(GLFWwindow* aWindow)
{
    if (glfwGetKey(aWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(aWindow, true);
}