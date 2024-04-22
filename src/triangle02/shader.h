
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
    unsigned int VAO;
    unsigned int VBO;

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