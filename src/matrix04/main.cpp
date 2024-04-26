/**
 * @file main.cpp
 * @brief study 《矩阵》
 * @note 
 *  <1> 向量的加减 https://blog.csdn.net/dengziyun/article/details/118303598
 *  a. 向量之间只要方向相同、模长相等，就认为是同一个向量
 *  b. 向量的加减为平行四边形法则——都是平行四边形的对角线，相减连接两箭头(a-b = a+(-b))，相加为另一条对角线
 * 
 *  <2> 向量点积
 *  a.   a * b  的结果为两个向量的夹角  
 *  
 *  <3> 向量叉乘
 *  a.  叉乘的结果是垂直(相交)
 * 
 * @author chujun
 * @date 2024-4-25
 * 
*/

#include <iostream>
#include <string> 



#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "axes.h"
#include "shader.h"


using namespace std;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

glm::vec3 color(0.2f, 0.2f , 0.3f);
std::string button_name = "StartRot";

#pragma region GLM
void PrintMat4(const glm::mat4& matrix)
{
    std::cout << "glm::mat4& matrix :" << std::endl;
    const float* ptr = glm::value_ptr(matrix);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // 计算矩阵中元素的索引
            int index = i * 4 + j;
            // 打印矩阵中元素
            std::cout << ptr[index] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------" << std::endl;
}
void PrintVec4(const glm::vec4& vec)
{
    std::cout << "glm::vec4& vec :" << std::endl;
    std::cout << vec.x << "  "<< vec.y << "  " << vec.z << std::endl;
    std::cout << "------------------------------" << std::endl;
}
void GlmMath()
{
    /// 1. 经过打印发现 translate 是改变平移分量
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    PrintMat4(trans);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    PrintMat4(trans);

    trans = glm::translate(trans, glm::vec3(3.0f, 2.0f, 0.0f));
    PrintMat4(trans);

    vec = trans * vec;
    PrintVec4(vec);

    // glm::mat4  view ;
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // PrintMat4(view);
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
void ImguiInit(GLFWwindow* aWindow)
{
    ImGui::CreateContext();     // Setup Dear ImGui context
    ImGui::StyleColorsDark();       // Setup Dear ImGui style
    ImGui_ImplGlfw_InitForOpenGL(aWindow, true);     // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init("#version 330");
}
void ImguiRender(GLFWwindow* aWindow, Axes* axes)
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
    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
    ImGui::Begin("Matrix");
    ImGui::Text("R-Reset;S-Start/Stop.");
    if (ImGui::Button("RESET"))
    {
        axes->mRotation = glm::vec3(0.0f, 0.0f, 0.0f);
        axes->mAxesPos = glm::vec3(0.0f, 0.0f, 0.0f);
        axes->mRotActive = false;
        button_name = "StartRot";
    }
    if (ImGui::Button(button_name.c_str())) 
    {
        axes->mRotActive = !axes->mRotActive;
        button_name = axes->mRotActive ? "StopRot" : "StartRot";
    }
    ImGui::SliderFloat("Axes-Width", &axes->mWidth, 1.0, 10.0);
    ImGui::End();
    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
int main()
{
    cout << "Hello Matrix" << endl;

    GlmMath();
#pragma region OPENGL
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
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello-Matrix", NULL, NULL);
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

#pragma region AXES 
    Axes axes;
#pragma endregion

#pragma region SHADER
    std::string base_path = "/home/ysc/驱动/opengl/src/matrix04/";
    std::string vs_file = base_path + "vertex_shader.vs";
    std::string fs_file = base_path + "fragment_shader.fs";
    Shader myShader(vs_file.c_str(), fs_file.c_str());
#pragma endregion

    glGenVertexArrays(1, &axes.mAxesVao);
    glGenBuffers(1, &axes.mPosVbo);
    glGenBuffers(1, &axes.mColorVbo);

    glBindVertexArray(axes.mAxesVao);
        glBindBuffer(GL_ARRAY_BUFFER, axes.mPosVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axes.mFloat18Pos), axes.mFloat18Pos.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);

        glBindBuffer(GL_ARRAY_BUFFER, axes.mColorVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axes.mFloat18Color), axes.mFloat18Color.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

#pragma region IMGUI 
    ImguiInit(window);
#pragma endregion


#pragma region MATRIX 
    glm::mat4  view ;
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection ;
    projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    glUseProgram(myShader.MyShader);  /// 先打开着色器对象,才能应用uniform
    myShader.SetUniformMatrix4fv("view", view);
    myShader.SetUniformMatrix4fv("projection", projection);

#pragma endregion

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
        glUseProgram(myShader.MyShader);
        glm::mat4 model, rotation_matrix  ,translation_matrix  ;
        translation_matrix = glm::translate(translation_matrix, axes.mAxesPos);
        if (axes.mRotActive)
        {
            axes.mRotation.x += axes.mTheta;
            axes.mRotation.y += axes.mPhi;
        }
        rotation_matrix =glm::rotate(rotation_matrix, glm::radians(axes.mRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation_matrix =glm::rotate(rotation_matrix, glm::radians(axes.mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation_matrix =glm::rotate(rotation_matrix, glm::radians(axes.mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        // model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translation_matrix * rotation_matrix; // 先旋转 后 平移
        myShader.SetUniformMatrix4fv("model", model);

        ImguiRender(window, &axes);
        glBindVertexArray(axes.mAxesVao);
        glLineWidth(axes.mWidth); // 改变线段的宽度
        glDrawArrays(GL_LINES, 0 , 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
