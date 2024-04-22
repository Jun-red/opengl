# OPenGL
## 什么是OpenGL？
    opengl 是一种用于渲染2D和3D图形的跨平台图形库，他提供了一组函数和接口，用于在计算机上进行图形渲染和处理。通俗地讲，就像是一套用于绘制
各种图形的工具包。

## 什么是核心模式和立即渲染模式？
    * 立即渲染模式：也称为固定功能管线模式，是opengl早期版本的一种渲染模式。
    * 核心模式： 是Opengl3.2 版本引入的一种渲染方式，也称为现代渲染模式。在核心模式下，OpenGL不提供固定功能管线，而是完全基于可编程着色器
的渲染流程。

## 两种模式的区别？
    立即渲染模式，基于固定功能管线；
    核心模式是现代opengl的渲染模式，基于可编程着色器。

# GLFW
## 什么是GLFW？
    glfw（Graphics library Framework）,是一个轻量级的开源库，用于创建和管理窗口，上下文以及处理用户输入，他提供了一种跨平台的方式来创建
OPENGL、Vulkan等图形API的窗口和上下文，使开发者能够编写独立于操作系统的图形应用程序。

## GLFW的功能？
    * 创建窗口和opengl上下文
    * 处理用户输入，包括键盘，鼠标和游戏手柄的输入
    * 支持多个窗口
    * 提供了简单的时间管理功能

# GLAD 
## 什么是 GLAD ？
    glad(opengl loader generator)， 是一个用于加载opengl函数指针的工具库，主要是在你的opengl应用程序中方便地加载和调用opengl函数。
放在所有头文件之前。

# 图形渲染管线
    Graphics pipeline, 大多译为管线，是指将3D坐标(在opengl中任何事物都在3D空间中)转为2D坐标(屏幕和窗口都是2D像素组成)的过程。
图形渲染管线可以为： 顶点着色器、 几何着色器、 形状(图元)装配、 光栅化、 片段着色器、 测试与混合  6个阶段(着色器)组成。 有些着色器可以由
开发者配置，因此【核心模式】是基于可编程着色器的渲染流程。OpenGL 着色器是用 opengl着色器语言( opengl shading language, GLSL).
    开发者可以配置的着色器包括：顶点着色器、几何着色器、片段着色器。
    *顶点着色器：主要目的是把3D坐标转换为另一种3D坐标
    *几何着色器：將一組頂點作為輸入,這些頂點形成圖元
    *片段着色器：計算最終像素的顏色

    現代OPENGL 要求我們至少設置一個頂點或者片段shader.

# IMGUI
    https://blog.csdn.net/Xixixihohoho/article/details/136321581

# VBO
    頂點緩衝對象(Vertex Buffer Object, VBO), 他會在GPU內存中(通常稱為 顯存 (xian cun)) 中存儲大量頂點。使用緩衝對象的好處是我們可以一次性
發送大批數據到顯存上。
    VBO的創建過程如下:
    1. 指定緩衝ID，生成VBO對象
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    2. 將對象綁定到緩衝目標上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    從這一刻起,我們使用的任何(在GL_ARRAY_BUFFER目標上的)緩衝調用都會用來配置當前綁定的緩衝(VBO).

    這句話是什麼意思? ## 以下案例為 點雲處理的demo
    a. glBindBuffer(GL_ARRAY_BUFFER, My_VBO);
    b. glBufferData(GL_ARRAY_BUFFER, cloud->points.size() * sizeof(PointT), cloud->points.data(), GL_STATIC_DRAW);
    c. glBindBuffer(GL_ARRAY_BUFFER, 0);

    /// @brief
    經過上述demo，我們可知OPENGL更像是 "區域代碼"(類似與C++的作用於)。即，當 a行代碼執行後，接下來的代碼都屬於My_VBO的作用於。

    3. 將定義的頂點數據(cpu) 拷貝到 緩衝的內存中(gpu)
    glBufferData(GL_ARRAY_BUFFER, size, data, TYPE);

    總之,VBO頂點緩衝對象管理顯存(xian cun),該顯卡內存存儲的是來自CPU的頂點數據。

# Vertex Shader
    顶点着色器(vertex shader) 是通过GLSL进行编程的. 如何实现输入的数据(VBO)的哪一个部分对应顶点着色器的哪一个顶点属性呢?
注意上述引出了顶点属性，比如:
    "
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    "
    这里的aPos 就是一个顶点属性(该属性描述了位置),那么该属性对应VBO中的那一部分呢?
    通过glVertexAttribPointer(#parm); 进行映射

# VAO
    顶点数组对象(Vertex Array Object, VAO), 可以像顶点缓冲对象那样被绑定,任何随后的顶点属性调用都会储存在这个VAO中.请注意"任何随后",
这几个词与VBO一致，说明OPENGL是 "区域代码"，VAO随后的指令句属于VAO的作用域.




