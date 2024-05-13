// 쉐이더는 기본적으로
// hlsl이라는 전혀 다른 언어를 사용합니다.
// C++을 익혔다면 그닥 어렵지는 않지만
// 센스가 없으면 고생할수 있습니다.
// 언제나 랜더링 파이프라인 지식에 기반해서 작성해줘야 합니다.

// 함수의 이름은 내맘대로 해도 됩니다.
// 그런데 어떠한 규칙을 만들면 편해져요
// 이 규칙은 회사마다 다르고
// 여러분들은 애초에 엔진이나 그래픽스 프로그래머로 들어간다면
// 각 쉐이더 뒤쪽에는 버텍스면 _VS
// 각 쉐이더 뒤쪽에는 픽셀이면 _PS
// 규칙을 만들었습니다. <= 회사마다 매번 달라질수 있다.

#include "EngineShaderBase.hlsli"

// 인풋레이아웃의 개념
// 인풋레이아웃은 2가지를 역할을 합니다.
// 내가 만든 버텍스 버퍼가 특정 시맨틱 가지고 있다는것을 정보를 담아주는 용도.
// 2번째는 어떤 버텍스 쉐이더에 어떤 시맨틱이 들어가 있는지에 대한 정보를 담당합니다.


// 리턴할 구조체도 만들어야 한다.
struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

// 내가 여기에다가 스트럭트를 넣는다고 이게 쉐이더에서 
// CPU쪽에서 넣어주기로 한 데이터로 인정되지 않아요
// CPU에서 내가 행렬이나 데이터 등등을 만들어서
// 넣어주고 싶다면
// 상수버퍼라고 하는 인터페이스와 전용 문법을 이용해야만
// 다이렉트에 넣어줄수가 있습니다.
// hlsl에서 struct 이런 데이터가 있을거야. 라는 정의만 내려줄수 있고


//struct FTransform
//{
//    float4 Scale;
//    float4 Rotation;
//    float4 Position;
//    float4x4 ScaleMat;
//    float4x4 RotationMat;
//    float4x4 PositionMat;
//    float4x4 World;
//    float4x4 View;
//    float4x4 Projection;
//    float4x4 WVP;
//};

// 버텍스 쉐이더에 넣어줄수 있

cbuffer FCuttingData : register(b2)
{
    //       0, 0
    float4 CuttingPosition;
    //      0.5 0.5
    float4 CuttingSize;
    float4x4 PivotMat;
};

cbuffer FVertexUV : register(b3)
{
    //       0, 0
    float4 PlusUV;
};


struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};


ImageVSOutPut WidgetImageShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    
    // World.
    
    float4x4 PivotWorld = mul(World, PivotMat);
    // float4x4 PivotWorld = World;
    
    Out.POSITION = mul(_Input.POSITION, PivotWorld);
    Out.POSITION = mul(Out.POSITION, View);
    Out.POSITION = mul(Out.POSITION, Projection);
    
    Out.TEXCOORD.x = (_Input.TEXCOORD.x * CuttingSize.x) + CuttingPosition.x;
    Out.TEXCOORD.y = (_Input.TEXCOORD.y * CuttingSize.y) + CuttingPosition.y;
    
    Out.TEXCOORD.x += CuttingSize.x * PlusUV.x;
    Out.TEXCOORD.y += CuttingSize.y * PlusUV.y;
    
    
    
    // 00,    1. 0
    
    
    // 01,   1 1
    
       // Rect에 존재하는 녀석이다.
    // 0.5 0.5,    1. 0.5
    
    
    // 0.5 1,    1 1

    return Out;
}

// 텍스처는 상수버퍼와 슬롯을 공유하지 않습니다.
// b0 buffer 0번 슬롯
// t0 texture 0번 슬롯
// s0 Sampler 0번 슬롯

// 언리얼 엔진이나
// 유니티는 OpenGL로도 내부가
// 그래서 자기들만의 쉐이더 언어를 또 만듭니다.
// 언리얼 쉐이더 랭귀지.
// HLSL => OpenGL shader 언어로 변경하는 기능도 지원합니다.







TextureSet(Image, 0)
//Texture2D Image : register(t0); 
//SamplerState Image_Sampler : register(s0);

cbuffer ResultColorValue : register(b10)
{
    float4 PlusColor;
    float4 MulColor;
    float4 AlphaColor;
};


ImagePSOutPut WidgetImageShader_PS(ImageVSOutPut _Input)
{
        // 언어를 배울때는 왜 안돼 어리석은 초보적인 생각은 그만두고 배워야한다.
        // 그냥 구조체처럼 초기화 하는게 안되는데.
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    
    // Name##.Sample(##Name##_Sampler, TEXCOORD.xy);
    
    // Rect에 존재하는 녀석이다.
    // 00,    10
    
    
    // 01,    11
    Out.COLOR = Sampling(Image, _Input.TEXCOORD);
    Out.COLOR.xyz += PlusColor.xyz;
    Out.COLOR.xyzw *= MulColor.xyzw;
    // #define Sampling(Name, TEXCOORD) Name##.Sample(##Name##_Sampler, TEXCOORD.xy);
    // Image.Sample(Image_Sampler, _Input.TEXCOORD.xy);
    
    return Out;
}
