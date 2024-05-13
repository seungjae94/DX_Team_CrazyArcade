
// 단순히 트랜스폼을 struct로 정의하는게 아니라.
// 상수버퍼라는것으로 선언해야 합니다.

// cbuffer 상수버퍼 쓰겠다.
// 상수버퍼는 16개까지 세팅이 가능하고
// b0 슬롯에 넣겠다.
// register(b15) 까지
// 하지만 상수버퍼에는 516kb이상이 되면 세팅이 불가능합니다.
// 크기에 제한이 있습니다.
// 672by
// 2개만 모여도 
cbuffer FTransform : register(b10)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldPosition;
    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 PositionMat;
    float4x4 ParentMat;
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};

struct FTransform 
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldPosition;
    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 PositionMat;
    float4x4 ParentMat;
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};


cbuffer FBaseRenderValue : register(b11)
{
    float AccTime;
    float Temp0;
    float ScreenX;
    float ScreenY;
};
