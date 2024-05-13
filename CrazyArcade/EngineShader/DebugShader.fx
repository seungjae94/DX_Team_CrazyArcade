#include "EngineShaderBase.hlsli"

// 리턴할 구조체도 만들어야 한다.
struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};


ImageVSOutPut DebugShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = mul(_Input.POSITION, WVP);
    return Out;
}

cbuffer DebugColorValue : register(b8)
{
    float4 DebugColor;
};

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

ImagePSOutPut DebugShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    
    Out.COLOR = DebugColor;
    
    return Out;
}
