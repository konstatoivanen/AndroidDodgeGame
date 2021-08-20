#pragma once
#include <math.h>

struct float2
{
    float x;
    float y;

    float2() = default;
    constexpr float2(float x, float y) : x(x), y(y) {}
    constexpr float2(float v) : x(v), y(v) {}

    inline float& operator[](size_t i) { return (&x)[i]; }
    inline constexpr const float& operator[](size_t i) const { return (&x)[i]; }
    inline constexpr float2 operator + (const float2& o) const { return { x + o.x, y + o.y }; }
    inline constexpr float2 operator - (const float2& o) const { return { x - o.x, y - o.y }; }
    inline constexpr float2 operator * (const float2& o) const { return { x * o.x, y * o.y }; }
    inline constexpr float2 operator / (const float2& o) const { return { x / o.x, y / o.y }; }
    inline constexpr float2 operator * (const float& o) const { return { x * o, y * o }; }
    inline constexpr float2 operator / (const float& o) const { return { x / o, y / o }; }
};

struct float3
{
    float x;
    float y;
    float z;

    float3() = default;
    constexpr float3(float x, float y, float z) : x(x), y(y), z(z) {}
    constexpr float3(float v) : x(v), y(v), z(v) {}

    inline float& operator[](size_t i) { return (&x)[i]; }
    inline constexpr const float& operator[](size_t i) const { return (&x)[i]; }
    inline constexpr float3 operator + (const float3& o) const { return { x + o.x, y + o.y, z + o.z }; }
    inline constexpr float3 operator - (const float3& o) const { return { x - o.x, y - o.y, z - o.z }; }
    inline constexpr float3 operator * (const float3& o) const { return { x * o.x, y * o.y, z * o.z }; }
    inline constexpr float3 operator / (const float3& o) const { return { x / o.x, y / o.y, z / o.z }; }
    inline constexpr float3 operator * (const float& o) const { return { x * o, y * o, z * o }; }
    inline constexpr float3 operator / (const float& o) const { return { x / o, y / o, z / o }; }
};

struct float4
{
    float x;
    float y;
    float z;
    float w;

    float4() = default;
    constexpr float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    constexpr float4(float v) : x(v), y(v), z(v), w(v) {}

    inline float& operator[](size_t i) { return (&x)[i]; }
    inline constexpr const float& operator[](size_t i) const { return (&x)[i]; }
    inline constexpr float4 operator + (const float4& o) const { return { x + o.x, y + o.y, z + o.z, w + o.w }; }
    inline constexpr float4 operator - (const float4& o) const { return { x - o.x, y - o.y, z - o.z, w - o.w }; }
    inline constexpr float4 operator * (const float4& o) const { return { x * o.x, y * o.y, z * o.z, w * o.w }; }
    inline constexpr float4 operator / (const float4& o) const { return { x / o.x, y / o.y, z / o.z, w / o.w }; }
    inline constexpr float4 operator * (const float& o) const { return { x * o, y * o, z * o, w * o }; }
    inline constexpr float4 operator / (const float& o) const { return { x / o, y / o, z / o, w / o }; }
};


struct float4x4
{
    float4 c0;
    float4 c1;
    float4 c2;
    float4 c3;

    inline float4& operator[](size_t i) { return (&c0)[i]; }
    inline constexpr const float4& operator[](size_t i) const { return (&c0)[i]; }
    inline constexpr float4x4 operator * (const float& o) const { return { c0 * o, c1 * o, c2 * o, c3 * o }; }
};

inline float4x4 operator * (const float4x4& m1, const float4x4& m2)
{ 
    float4x4 m;
    m.c0 = m1[0] * m2[0][0] + m1[1] * m2[0][1] + m1[2] * m2[0][2] + m1[3] * m2[0][3];
    m.c1 = m1[0] * m2[1][0] + m1[1] * m2[1][1] + m1[2] * m2[1][2] + m1[3] * m2[1][3];
    m.c2 = m1[0] * m2[2][0] + m1[1] * m2[2][1] + m1[2] * m2[2][2] + m1[3] * m2[2][3];
    m.c3 = m1[0] * m2[3][0] + m1[1] * m2[3][1] + m1[2] * m2[3][2] + m1[3] * m2[3][3];
    return m;
}

typedef float4 quaternion;
typedef float4 color;

constexpr float PK_FLOAT_PI = 3.14159274F;
constexpr float PK_FLOAT_2PI = 2.0f * 3.14159274F;
constexpr float PK_FLOAT_DEG2RAD = 0.0174532924F;
constexpr float PK_FLOAT_RAD2DEG = 57.29578F;

constexpr float2 PK_FLOAT2_ONE = { 1.0f, 1.0f };
constexpr float3 PK_FLOAT3_ONE = { 1.0f, 1.0f, 1.0f };
constexpr float4 PK_FLOAT4_ONE = { 1.0f, 1.0f, 1.0f, 1.0f };

constexpr float2 PK_FLOAT2_ZERO = { 0.0f, 0.0f };
constexpr float3 PK_FLOAT3_ZERO = { 0.0f, 0.0f, 0.0f };
constexpr float4 PK_FLOAT4_ZERO = { 0.0f, 0.0f, 0.0f, 0.0f };

constexpr float2 PK_FLOAT2_UP = { 0.0f, 1.0f };
constexpr float2 PK_FLOAT2_DOWN = { 0.0f, -1.0f };
constexpr float2 PK_FLOAT2_LEFT = { -1.0f, 0.0f };
constexpr float2 PK_FLOAT2_RIGHT = { 1.0f, 0.0f };

constexpr float3 PK_FLOAT3_LEFT = { 1.0f,  0.0f,  0.0f };
constexpr float3 PK_FLOAT3_RIGHT = { -1.0f,  0.0f,  0.0f };
constexpr float3 PK_FLOAT3_UP = { 0.0f,  1.0f,  0.0f };
constexpr float3 PK_FLOAT3_DOWN = { 0.0f, -1.0f,  0.0f };
constexpr float3 PK_FLOAT3_FORWARD = { 0.0f,  0.0f,  1.0f };
constexpr float3 PK_FLOAT3_BACKWARD = { 0.0f,  0.0f, -1.0f };

constexpr color PK_COLOR_WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
constexpr color PK_COLOR_GRAY = { 0.5f, 0.5f, 0.5f, 1.0f };
constexpr color PK_COLOR_BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
constexpr color PK_COLOR_CLEAR = { 0.0f, 0.0f, 0.0f, 0.0f };
constexpr color PK_COLOR_RED = { 1.0f, 0.0f, 0.0f, 1.0f };
constexpr color PK_COLOR_GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
constexpr color PK_COLOR_BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
constexpr color PK_COLOR_CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };
constexpr color PK_COLOR_MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };
constexpr color PK_COLOR_YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };

constexpr float4x4 PK_FLOAT4X4_IDENTITY = 
{
    {1.0f,0.0f,0.0f,0.0f},
    {0.0f,1.0f,0.0f,0.0f},
    {0.0f,0.0f,1.0f,0.0f},
    {0.0f,0.0f,0.0f,1.0f}
};

constexpr float4x4 PK_FLOAT4X4_ZERO = { PK_FLOAT4_ZERO, PK_FLOAT4_ZERO, PK_FLOAT4_ZERO, PK_FLOAT4_ZERO };

constexpr quaternion PK_QUATERNION_IDENTITY = { 1.0f, 0.0f, 0.0f, 0.0f };

quaternion euler_to_quaternion(const float3& euler);

float2 normalize(const float2& v);

float3 normalize(const float3& v);

float4 normalize(const float4& v);

float4x4 matrix_inverse(const float4x4& matrix);

float4x4 matrix_trs(const float3& position, const quaternion& rotation, const float3& scale);

float4x4 matrix_tr(const float3& position, const quaternion& rotation);

float4x4 matrix_trs(const float3& position, const float3& euler, const float3& scale);

float4x4 matrix_tr(const float3& position, const float3& euler);

float4x4 matrix_perspective(float fov, float aspect, float zNear, float zFar);

float4x4 matrix_viewprojection(float fov, float aspect, float zNear, float zFar, const float3& position, const float3& euler);

uint wanghash(uint seed);

inline float max(float x, float y) { return x > y ? x : y; }

inline float min(float x, float y) { return x < y ? x : y; }

inline float lerp(float x, float y, float z) { return  x + z * (y - x); }

inline float lerpinquad(float a, float b, float c) { return (b - a) * c * c + a; }

inline float lerpoutquad(float a, float b, float c) { return -(b - a) * c * (c - 2) + a; }