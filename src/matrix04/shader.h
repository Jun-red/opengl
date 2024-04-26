/**
 * @file shader.h
 * @brief 着色器类
 * 
 * @author chujun
 * @date 2024-4-25
*/
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstddef>

#include "glad/glad.h"
#include <GLFW/glfw3.h>


class Shader
{
public:
    Shader(const char* vs_path, const char* fs_path)
    {
        std::cout << " Hello Shader! " << std::endl;
        
        BuildVertexShader(vs_path);
        BuildFragShader(fs_path);
        LinkShader();
    }
    int SetUniform4f(const char* name, glm::vec4 data)
    {
        int id = glGetUniformLocation(MyShader, name);
        if (id != -1) /// if not found, then id is -1
        {
            glUniform4f(id, data.r, data.g, data.b, 1.0f);
        }
    }

    int SetUniform4f(const char* name, float r, float g, float b, float w = 1.0f)
    {
        int id = glGetUniformLocation(MyShader, name);
        if (id != -1) /// if not found, then id is -1
        {
            glUniform4f(id, r, g, b, w);
        }
    }

    int SetUniformMatrix4fv(const char* name, glm::mat4& matrix)
    {
        int id = glGetUniformLocation(MyShader, name);
        if (id != -1) /// if not found, then id is -1
        {
            /// @param[location] 指定 uniform 变量的位置
            /// @param[count] 定要传递的矩阵的数量。通常是1，但你也可以传递多个矩阵数组
            /// @param[transpose] 指定是否要转置矩阵。如果为GL_TRUE，则矩阵在传递到着色器之前会被转置。通常使用 GL_FALSE
            /// @param[value]  一个指向要传递的矩阵数据的指针。矩阵数据通常是一个浮点数数组
            glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
        } else {
            std::cout << "uniform name :" << name << "is not found" << std::endl;
        }
    }
private:
    void BuildVertexShader(const char* vs_path)
    {
        VsPath.open(vs_path);
        VsSteam << VsPath.rdbuf();
        VsPath.close();
        VsCode = VsSteam.str();
        const char* vShaderCode = VsCode.c_str();

        VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(VertexShader, 1, &vShaderCode, NULL);
        glCompileShader(VertexShader);
        GetShaderInfo(VertexShader, "Vertex");
    }

    void BuildFragShader(const char* fs_path)
    {
        FsPath.open(fs_path);
        FsSteam << FsPath.rdbuf();
        FsPath.close();
        FsCode = FsSteam.str();
        const char* vFragCode = FsCode.c_str();

        FragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(FragShader, 1, &vFragCode, NULL);
        glCompileShader(FragShader);
        GetShaderInfo(FragShader, "Fragment");
    }
    void GetShaderInfo(unsigned int shader, const std::string& name)
    {
        int  success;
        char infoLog[512];
        if (name == "ShaderLink")
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success) 
            {
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::ShaderLink::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        } else {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
    }
    void LinkShader()
    {
        MyShader = glCreateProgram();
        glAttachShader(MyShader, VertexShader);
        glAttachShader(MyShader, FragShader);
        glLinkProgram(MyShader);
        GetShaderInfo(MyShader, "ShaderLink");

        // glUseProgram(MyShader);

        glDeleteShader(VertexShader);
        glDeleteShader(FragShader);
    }
public:

    std::ifstream VsPath;
    std::stringstream VsSteam;
    std::string VsCode;

    std::ifstream FsPath;
    std::stringstream FsSteam;
    std::string FsCode;
    
    unsigned int VertexShader;
    unsigned int FragShader;
    unsigned int MyShader;
};