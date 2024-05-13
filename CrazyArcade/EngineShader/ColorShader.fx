#include "EngineShaderBase.hlsli"

// 픽셀쉐이더의 상수버퍼 0번은 달라도 된다.
struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
};

ImageVSOutPut ColorShader_VS(FEngineVertex _Input)
{
        // 언어를 배울때는 왜 안돼 어리석은 초보적인 생각은 그만두고 배워야한다.
        // 그냥 구조체처럼 초기화 하는게 안되는데.
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    
    Out.POSITION = _Input.POSITION;
    // 자동컴파일할때 
    // 상수버퍼를 쉐이더안에서 사용하지 않으면
    // 상수버퍼를 쓴다고 생각하지 않는다.
    // 쉐이더는 의미없는 코드를 용납하지 않습니다.
    // float4x4 POS = mul(_Input.POSITION, WVP);
    
    // int a = 1 + 1;
    
    // 실제적인 결과에 영향을 미치는 코드를 쳐야만 실제 상수버퍼가 있다고 인지 합니다.
    Out.POSITION = mul(_Input.POSITION, WVP);
   
    
    //Out.POSITION *= World;
    //Out.POSITION *= View;
    //Out.POSITION *= Projection;
    
   // hlsl 스위즐링(swizzling) 문법.
   // Out.POSITION.xyz = _Input.POSITION.xyz * 2.0f;
   // Out.POSITION.w = 1.0f;
    return Out;
}


// 픽셀쉐이더의 상수버퍼 0번은 달라도 된다.
cbuffer OutPutColor : register(b0)
{
    float4 Color;
};


struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

ImagePSOutPut ColorShader_PS(ImageVSOutPut _Input)
{
        // 언어를 배울때는 왜 안돼 어리석은 초보적인 생각은 그만두고 배워야한다.
        // 그냥 구조체처럼 초기화 하는게 안되는데.
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    // Out.COLOR = Color;
    Out.COLOR = Color;
    
    return Out;
}
