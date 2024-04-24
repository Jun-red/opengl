/**
 * @file main.cpp
 * @brief study《着色器》
 * 
 * @author chujun
 * @date 2024-4-24
 * 
*/
#include <vector>

#include "shader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"



using namespace std;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

VertexData gVD[3];
glm::vec3 color(0.2f, 0.2f , 0.3f);
glm::vec3 offset_pos;

void FrameBufferSizeCallback(GLFWwindow* aWindow, int aWidth, int aHeight)
{
    glViewport(0, 0, aWidth, aHeight);
}
void ProcessInput(GLFWwindow* aWindow)
{
    if (glfwGetKey(aWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(aWindow, true);
}

void ImguiInit(GLFWwindow* aWindow)
{
    ImGui::CreateContext();     // Setup Dear ImGui context
    ImGui::StyleColorsDark();       // Setup Dear ImGui style
    ImGui_ImplGlfw_InitForOpenGL(aWindow, true);     // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init("#version 330");
}
void ImguiRender(GLFWwindow* aWindow)
{
    
    bool show_demo_window = true;  // show 官方 window
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    /// 显示 官方demo
    if (show_demo_window) 
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
    
    ImGui::Begin("Hello-Shader");
    ImGui::ColorEdit3("color-1",    glm::value_ptr(gVD[0].color));
    ImGui::ColorEdit3("color-2",    glm::value_ptr(gVD[1].color));
    ImGui::ColorEdit3("color-3",    glm::value_ptr(gVD[2].color));
    ImGui::End();
    
    /// 0 - 1
    // cout << gVD[0].color.r << "  " << gVD[0].color.g << "  " << gVD[0].color.b << "  "<< endl;
    // cout << gVD[1].color.r << "  " << gVD[1].color.g << "  " << gVD[1].color.b << "  "<< endl;
    // cout << gVD[2].color.r << "  " << gVD[2].color.g << "  " << gVD[2].color.b << "  "<< endl;

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
int main()
{
#pragma region GLFWINIT
    GLFWwindow* window = nullptr;
    if (!glfwInit())
    {
        cerr << "glfw init failed!" << endl;
        return -1;
    } 
    /// opengl3.3 core-profile model
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello-Shader", NULL, NULL);

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
    glClearColor(color.r, color.g, color.b, 1.0f);

#pragma endregion

#pragma region SHADER
    
    std::string base_path = "/home/ysc/驱动/opengl/src/shader03/";
    std::string vs_file = base_path + "vertex_shader.vs";
    std::string fs_file = base_path + "fragment_shader.fs";
    Shader myShader(vs_file.c_str(), fs_file.c_str());

    cout << sizeof(gVD) << endl;
    cout << offsetof(VertexData, pos) << endl;
    cout << offsetof(VertexData, color) << endl;

    gVD[0].pos = glm::vec3(0.5f, -0.5f, 0.0f);
    gVD[0].color = glm::vec3(1.0f, 0.0f, 0.0f);

    gVD[1].pos = glm::vec3(-0.5f, -0.5f, 0.0f);
    gVD[1].color = glm::vec3( 0.0f, 1.0f, 0.0f);

    gVD[2].pos = glm::vec3(0.0f,  0.5f, 0.0f);
    gVD[2].color = glm::vec3(0.0f, 0.0f, 1.0f);

    glGenVertexArrays(1, &myShader.VAO);
    glGenBuffers(1, &myShader.VBO);
    glBindVertexArray(myShader.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, myShader.VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(offsetof(VertexData, color)));
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#pragma endregion

#pragma region IMGUI 
    ImguiInit(window);
#pragma endregion


    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

#pragma region IMGUI 
        ImguiRender(window);
#pragma endregion


        /// 先激活着色器
        glUseProgram(myShader.MyShader);
#if 1       
        float  offset = glfwGetTime(); // 获取运行的秒数
        float offset_x = sin(offset) / 2.0f ; // 通过sin约束到[-1,1] , 则/2 -> [-0.5, 0.5] , 则+0.5 -> [0,1]
        float offset_y = cos(offset) / 2.0f ; // 通过sin约束到[-1,1] , 则/2 -> [-0.5, 0.5] , 则+0.5 -> [0,1]
    
        gVD[0].pos.x = offset_x;
        gVD[0].pos.y = offset_y;
        gVD[1].pos.x = offset_x - 0.5;
        gVD[1].pos.y = offset_y; 
        gVD[2].pos.x = ( gVD[0].pos.x +  gVD[1].pos.x ) / 2;
        gVD[2].pos.y = gVD[0].pos.y + 0.5; 
        // myShader.SetUniform4f("myColor",  value, 0.0f,0.0f);
#endif
        /// 开始绘制
        glBindVertexArray(myShader.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, myShader.VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gVD), gVD, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

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