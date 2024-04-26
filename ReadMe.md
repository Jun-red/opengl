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

# 着色器(shader)
    所谓 “可编程着色器” ，着色器到底指的是什么? 
    shader是运行在GPU上的程序(通过GLSL编写),这些小程序为图形渲染管线的某个特定部分而运行(比如顶点着色器、几何、片段).
从基本意义上说，着色器只是一种把输入转化为输出的程序。因为在管线中各个着色器独立运行，不能相互通信，因此他们之间唯一的沟通只有通过输入和输出.着色器中通过：
    in 指定输入变量；
    out 指定输出变量；
    uniform 从应用程序在CPU上传递数据到GPU上的着色器方式,是全局的,意味着可以在任意着色器阶段都可以被访问.
    注意：参考 <Vertex Shader> 那一节，在顶点着色器中，每一个输入变量也叫顶点属性.

    uniform 的一般用法:
        * 获取指定字段的ID(glGetUniformLocation)
        * 根据ID设置数据(glUniformxx)
    注意：使用uniform之前一定打开着色器对象!


# 坐标系统
## 概念
    坐标系统(coordinate system),。opengl是3D图形渲染库,里面包含了大量的坐标系统的转换.我们最常用的有5个不同的坐标系统:
    * 局部空间(local space) ———— 局部坐标是对象相对于局部原点的坐标,也就是物体起始的坐标
    * 世界空间(world space) ———— 
    * 观察空间(View space)  ———— opengl的摄像机(也称为视觉空间),从观察者的视角所观察的空间
        ** 由观察坐标变换到裁剪空间有两种不同的方式,每种方式都定义了不同的平截头体，分为正射投影矩阵 和 透视投影矩阵
    * 裁剪空间(clip space) ———— opengl希望可见的所有顶点都为标准化设备坐标(Normalized device coordinate,NDC),[-1,1]之外的都会被裁剪掉
    * 屏幕空间(screen space) ———— 变化到裁剪空间后执行透视除法(除以w分量，产生距离感)

    注意：这些坐标系统的转换到发生在顶点着色器中.

    涉及到的矩阵变换包含：
    * 模型矩阵(model matrix) ———— 将局部坐标系转换到世界坐标系
    * 观察矩阵(View matrix) ———— 由一系列位移和旋转组合,平移/旋转场景从而使得特定的对象被变换到摄像机的前方
    * 投影矩阵(projection matrix) ———— 将顶点坐标从观察变换到裁剪空间.他指定了一个范围坐标,比如范围在[-1000,1000]，投影矩阵会将这个指定范围内
的坐标系统变换为标准化设备坐标的范围(-1,1).由投影矩阵创建的观察箱被称为平截头体,每个出现在平截头体范围内的坐标都将会出现在屏幕上. 
    * 透视除法(perspective division)————一旦所有的顶点被变换到裁剪空间，最终操作————透视除法将会执行,在这个过程中自动将x y z分量除以w分量。

    为什么opengl输出的结果会有深度感?
    在opengl中，修改每个顶点的w分量是通过透视投影矩阵完成的。透视投影矩阵将三维空间中的顶点坐标转换到透视投影后的4维齐次坐标。这个四维坐标的w分量通常被设置
为顶点到观察者的距离，以便在透视投影后实现远近物体大小的视觉效果。修改w分量的依据是将顶点的三维坐标投影到相机视锥体（View Frustum）上，即从观察者的视角将物体
投影到屏幕上的过程。在这个过程中，顶点到相机的距离（也称为深度或z坐标）将被考虑，并根据透视投影的需要进行修改。通常，靠近相机的顶点将具有较小的w值，而远离相机
的顶点将具有较大的w值。
    所以说，透视投影有两个作用: 1. 创建平截头体，约束范围； 2. 将三维转到4维 ？？？

    综上, 一个顶点坐标将经历 模型矩阵 、 观察矩阵 、 投影矩阵(正交投影、透视投影) 转换到了 裁剪空间内。
    然后,opengl自动对裁剪坐标进行透视除法从而将他们转换到标准化设备坐标。

## 运用
    * 模型矩阵
        模型矩阵包含了位移、缩放、旋转操作，矩阵将被应用到所有的顶点上，以变换他们到全局的世界空间。
        /// 以下操作是创建一个绕x轴 向 后 旋转55度的矩阵(为什么是向后,因为是右手准则,大拇指指向向量方向,四指合拢方向(逆时针)为正)
        glm::mat4 model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    * 观察矩阵
        当在世界坐标系中，我们默认处于世界坐标系的原点(0,0,0)处,因此需要场景向后移动，使整个场景在我的观察视角里。由于我们处在右手坐标系中
    正z轴是朝向后方的(屏幕外)，所以观察者需要沿着z轴的正方向移动，场景沿着z轴的负方向移动来实现。
        glm::mat4  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    * 透视投影矩阵
        glm::mat4 projection; projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);

# Z 缓冲
    opengl存储深度信息在一个叫做Z缓冲(Z-buffer)的缓冲中，他允许opengl决定何时覆盖一个像素而何时不覆盖,这个过程称为深度测试(depth-test)，由opengl默认完成.
Z缓冲也称为深度缓冲，GLFW会自动为你生成这样一个缓冲（就像它也有一个颜色缓冲来存储输出图像的颜色）。深度值存储在每个片段里面（作为片段的z值），当片段想要输出它的
颜色时，OpenGL会将它的深度值和z缓冲进行比较，如果当前的片段在其它片段之后，它将会被丢弃，否则将会覆盖。
    现在我们想启用深度测试，需要开启glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);