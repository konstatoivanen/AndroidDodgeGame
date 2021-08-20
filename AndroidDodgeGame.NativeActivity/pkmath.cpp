#include "pkmath.h"

quaternion euler_to_quaternion(const float3& euler)
{
    float3 h = euler * 0.5f * PK_FLOAT_DEG2RAD;
    float3 c = { cosf(h.x), cosf(h.y), cosf(h.z) };
    float3 s = { sinf(h.x), sinf(h.y), sinf(h.z) };

    quaternion q;
    q.w = c.x * c.y * c.z + s.x * s.y * s.z;
    q.x = s.x * c.y * c.z - c.x * s.y * s.z;
    q.y = c.x * s.y * c.z + s.x * c.y * s.z;
    q.z = c.x * c.y * s.z - s.x * s.y * c.z;
    return q;
}

float2 normalize(const float2& v)
{
    return v / sqrtf(v.x * v.x + v.y * v.y);
}

float3 normalize(const float3& v)
{
    return v / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float4 normalize(const float4& v)
{
    return v / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float4x4 matrix_inverse(const float4x4& m)
{
    float Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
    float Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
    float Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

    float Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
    float Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
    float Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

    float Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
    float Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
    float Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

    float Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
    float Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
    float Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

    float Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
    float Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
    float Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

    float Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
    float Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
    float Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

    float4 Fac0 = { Coef00, Coef00, Coef02, Coef03 };
    float4 Fac1 = { Coef04, Coef04, Coef06, Coef07 };
    float4 Fac2 = { Coef08, Coef08, Coef10, Coef11 };
    float4 Fac3 = { Coef12, Coef12, Coef14, Coef15 };
    float4 Fac4 = { Coef16, Coef16, Coef18, Coef19 };
    float4 Fac5 = { Coef20, Coef20, Coef22, Coef23 };

    float4 Vec0 = { m[1][0], m[0][0], m[0][0], m[0][0] };
    float4 Vec1 = { m[1][1], m[0][1], m[0][1], m[0][1] };
    float4 Vec2 = { m[1][2], m[0][2], m[0][2], m[0][2] };
    float4 Vec3 = { m[1][3], m[0][3], m[0][3], m[0][3] };

    float4 Inv0 = (Vec1 * Fac0) - (Vec2 * Fac1) + (Vec3 * Fac2);
    float4 Inv1 = (Vec0 * Fac0) - (Vec2 * Fac3) + (Vec3 * Fac4);
    float4 Inv2 = (Vec0 * Fac1) - (Vec1 * Fac3) + (Vec3 * Fac5);
    float4 Inv3 = (Vec0 * Fac2) - (Vec1 * Fac4) + (Vec2 * Fac5);

    float4 SignA = { +1, -1, +1, -1 };
    float4 SignB = { -1, +1, -1, +1 };
    float4x4 Inverse = { Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB };

    float4 Row0 = { Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0] };

    float4 Dot0 = m[0] * Row0;
    float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

    return Inverse * (1.0f / Dot1);
}

float4x4 matrix_trs(const float3& position, const quaternion& rotation, const float3& scale)
{
    float qxx(rotation.x * rotation.x);
    float qyy(rotation.y * rotation.y);
    float qzz(rotation.z * rotation.z);
    float qxz(rotation.x * rotation.z);
    float qxy(rotation.x * rotation.y);
    float qyz(rotation.y * rotation.z);
    float qwx(rotation.w * rotation.x);
    float qwy(rotation.w * rotation.y);
    float qwz(rotation.w * rotation.z);

    float4x4 m = PK_FLOAT4X4_IDENTITY;

    m[3].x = position.x;
    m[3].y = position.y;
    m[3].z = position.z;

    m[0][0] = scale[0] * (1.0f - 2.0f * (qyy + qzz));
    m[0][1] = scale[0] * (2.0f * (qxy + qwz));
    m[0][2] = scale[0] * (2.0f * (qxz - qwy));

    m[1][0] = scale[1] * (2.0f * (qxy - qwz));
    m[1][1] = scale[1] * (1.0f - 2.0f * (qxx + qzz));
    m[1][2] = scale[1] * (2.0f * (qyz + qwx));

    m[2][0] = scale[2] * (2.0f * (qxz + qwy));
    m[2][1] = scale[2] * (2.0f * (qyz - qwx));
    m[2][2] = scale[2] * (1.0f - 2.0f * (qxx + qyy));

    return m;
}

float4x4 matrix_tr(const float3& position, const quaternion& rotation)
{
    float qxx(rotation.x * rotation.x);
    float qyy(rotation.y * rotation.y);
    float qzz(rotation.z * rotation.z);
    float qxz(rotation.x * rotation.z);
    float qxy(rotation.x * rotation.y);
    float qyz(rotation.y * rotation.z);
    float qwx(rotation.w * rotation.x);
    float qwy(rotation.w * rotation.y);
    float qwz(rotation.w * rotation.z);

    float4x4 m = PK_FLOAT4X4_IDENTITY;

    m[3].x = position.x;
    m[3].y = position.y;
    m[3].z = position.z;

    m[0][0] = 1.0f - 2.0f * (qyy + qzz);
    m[0][1] = 2.0f * (qxy + qwz);
    m[0][2] = 2.0f * (qxz - qwy);

    m[1][0] = 2.0f * (qxy - qwz);
    m[1][1] = 1.0f - 2.0f * (qxx + qzz);
    m[1][2] = 2.0f * (qyz + qwx);

    m[2][0] = 2.0f * (qxz + qwy);
    m[2][1] = 2.0f * (qyz - qwx);
    m[2][2] = 1.0f - 2.0f * (qxx + qyy);
    return m;
}

float4x4 matrix_trs(const float3& position, const float3& euler, const float3& scale)
{
    return matrix_trs(position, euler_to_quaternion(euler), scale);
}

float4x4 matrix_tr(const float3& position, const float3& euler)
{
    return matrix_tr(position, euler_to_quaternion(euler));
}

float4x4 matrix_perspective(float fov, float aspect, float zNear, float zFar)
{
    const float tanHalfFovy = tan(fov * PK_FLOAT_DEG2RAD / 2.0f);
    float4x4 proj = PK_FLOAT4X4_ZERO;
    proj[0][0] = 1.0f / (aspect * tanHalfFovy);
    proj[1][1] = 1.0f / (tanHalfFovy);
    proj[2][2] = (zFar + zNear) / (zFar - zNear);
    proj[2][3] = 1.0;
    proj[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    return proj;
}

float4x4 matrix_viewprojection(float fov, float aspect, float zNear, float zFar, const float3& position, const float3& euler)
{
    float4x4 v = matrix_inverse(matrix_tr(position, euler));
    float4x4 p = matrix_perspective(fov, aspect, zNear, zFar);
    return p * v;
}

uint wanghash(uint seed)
{
    uint u = seed + 57;
    uint v = seed + 17;
    uint s = seed;

    seed = (u * 1664525u + v) + s;

    seed = (seed ^ 61u) ^ (seed >> 16u);
    seed *= 9u;
    seed = seed ^ (seed >> 4u);
    seed *= 0x27d4eb2d;
    seed = seed ^ (seed >> 15u);

    return seed;
}
