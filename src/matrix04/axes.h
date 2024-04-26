/**
 * @file axes.h
 * @brief 坐标轴
 * @note opengl-axes 右手坐标系, 也算是图像坐标系(x->右, y->上)
 * 
 * @author chujun
 * @date 2024-4-25
*/

#include <array>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Array
{
public:
    using Float18Array = std::array<float, 18>;
};
class Axes : public Array
{
public:
    Axes() :mLen(0.5f),mWidth(5.f),mPosVbo(0),mColorVbo(0),mAxesVao(0),mRotActive(false),mTheta(0.01),mPhi(0.01)
    {
        mFloat18Pos = {0.0f, 0.0f, 0.0f, mLen, 0.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 0.0f, mLen, 0.0f,
                       0.0f, 0.0f, 0.0f, 0.0f, 0.0f, mLen}; 
        mFloat18Color = {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}; 
        mRotation = glm::vec3(0.0, 0.0, 0.0);
        mAxesPos  = glm::vec3(0.0, 0.0, 0.0);
    }

    Float18Array mFloat18Pos;
    Float18Array mFloat18Color;
    
    float mLen;
    float mWidth;

    unsigned int mPosVbo;
    unsigned int mColorVbo;
    unsigned int mAxesVao;

    glm::vec3 mRotation;
    glm::vec3 mAxesPos;
    bool mRotActive;

    float mTheta;
    float mPhi;
};