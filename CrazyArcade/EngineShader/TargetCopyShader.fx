#include "EngineShaderBase.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};


ImageVSOutPut TargetCopy_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = _Input.POSITION;
    Out.TEXCOORD = _Input.TEXCOORD;
    return Out;
}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

// ¥ÎªÛ¿Ã BackBuffer
TextureSet(Image, 0)

ImagePSOutPut TargetCopy_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    Out.COLOR = Sampling(Image, _Input.TEXCOORD);
    
    if (1.0f <= Out.COLOR.a)
    {
        Out.COLOR.a = 1.0f;
    }
    
    return Out;
}
