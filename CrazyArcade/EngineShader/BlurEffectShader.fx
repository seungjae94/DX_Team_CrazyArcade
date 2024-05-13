#include "EngineShaderBase.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};


ImageVSOutPut BlurEffect_VS(FEngineVertex _Input)
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

#define GAUX 7
#define GAUY 7

static float Gau[GAUY][GAUX] =
{
    { 0.000f, 0.000f, 0.001f, 0.001f, 0.001f, 0.000f, 0.000f },
    { 0.000f, 0.002f, 0.012f, 0.002f, 0.012f, 0.002f, 0.000f },
    { 0.001f, 0.012f, 0.068f, 0.109f, 0.068f, 0.012f, 0.001f },
    { 0.001f, 0.020f, 0.109f, 0.172f, 0.109f, 0.020f, 0.001f },
    { 0.001f, 0.012f, 0.068f, 0.109f, 0.068f, 0.012f, 0.001f },
    { 0.000f, 0.002f, 0.012f, 0.020f, 0.012f, 0.002f, 0.000f },
    { 0.000f, 0.000f, 0.001f, 0.001f, 0.001f, 0.000f, 0.000f },
};

// ¥ÎªÛ¿Ã BackBuffer
TextureSet(Image, 0)

ImagePSOutPut BlurEffect_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    // Out.COLOR = Sampling(Image, _Input.TEXCOORD);
    
    
    float2 PixelUV = { 1.0f / 1280.0f, 1.0f / 720.0f };
    float2 StartUV = _Input.TEXCOORD.xy + (-PixelUV * 3.0f);
    float2 CurUV = StartUV;
    float4 ResultColor = 0.0f;
    
    for (int Y = 0; Y < GAUY; ++Y)
    {
        for (int X = 0; X < GAUX; ++X)
        {
            // float4 Color = Sampling(Image, CurUV);
            ResultColor.rgba += Image.Sample(Image_Sampler, CurUV.xy) * Gau[Y][X];
            CurUV.x += PixelUV.x;
        }
        CurUV.x = StartUV.x;
        CurUV.y += PixelUV.y;
    }
    
    Out.COLOR.rgba = ResultColor.rgba;
    
    //if (1.0f <= Out.COLOR.a)
    //{
    //    Out.COLOR.a = 1.0f;
    //}
    
    return Out;
}
