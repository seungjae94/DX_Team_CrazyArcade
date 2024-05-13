#include "EngineShaderBase.hlsli"

// 다이렉트 x에서 
struct FEngineVertexInstancing
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    // 자동으로 주니 어떻게 레이아웃도 만들필요가 없어요.
    uint Index : SV_InstanceID; // 인스턴싱으로 그려지는 애들중에 몇번째 그려지는 애인지 들어 있다.
};

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
    int Index : SV_InstanceID;
};

struct FCuttingData 
{
    float4 CuttingPosition;
    float4 CuttingSize;
    float4x4 PivotMat;
};

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

// 스트럭처드 버퍼는 텍스처 버퍼를 사용합니다.
// 한번에 1000개를 그릴거면 1000개의 transform이 여기 내부에 들어가 있어야 한다
StructuredBuffer<FTransform> TransInstancing : register(t1);

// 애니메이션이나 이런건 어떻게 할거냐.
StructuredBuffer<FCuttingData> CuttingDataInstancing : register(t2);

// 한번에 n개를 그릴수 있는 구조를 만들어야 하는데.
// 10개 이하면 안쓰는게 좋다.

ImageVSOutPut ImageShaderInstanced_VS(FEngineVertexInstancing _Input)
{
    int Index = _Input.Index;
    
    FTransform Trans = TransInstancing[Index];
    FCuttingData Cutting = CuttingDataInstancing[Index];
    
    
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    float4x4 PivotWorld = mul(Trans.World, Cutting.PivotMat);
    Out.POSITION = mul(_Input.POSITION, PivotWorld);
    Out.POSITION = mul(Out.POSITION, Trans.View);
    Out.POSITION = mul(Out.POSITION, Trans.Projection);
    
    Out.TEXCOORD.x = (_Input.TEXCOORD.x * Cutting.CuttingSize.x) + Cutting.CuttingPosition.x;
    Out.TEXCOORD.y = (_Input.TEXCOORD.y * Cutting.CuttingSize.y) + Cutting.CuttingPosition.y;
    Out.Index = Index;
    
    return Out;
}

TextureSet(Image, 0)

struct ResultColorValue 
{
    float4 PlusColor;
    float4 MulColor;
    float4 AlphaColor;
};


// 애니메이션이나 이런건 어떻게 할거냐.
StructuredBuffer<ResultColorValue> ResultColorValueInstancing : register(t3);

ImagePSOutPut ImageShaderInstanced_PS(ImageVSOutPut _Input)
{
    int Index = _Input.Index;

    
    ResultColorValue ColorData = ResultColorValueInstancing[Index];
    
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    Out.COLOR = Sampling(Image, _Input.TEXCOORD);
    Out.COLOR.xyz += ColorData.PlusColor.xyz;
    Out.COLOR.xyzw *= ColorData.MulColor.xyzw;
    return Out;
}
