// 왜 FVector아 니라 계속 float4를 고집했는지
// hlsl에서 float4개의 집합인 자료형의 이름이 float4
// 그대로 쉐이더에서 사용할수 있는 버텍스 구조체가 됩니다.

struct FEngineVertex
{
    // 내가 정점을 어떻게 구성했는지는 알려줘야 랜더링이 가능합니다.
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};