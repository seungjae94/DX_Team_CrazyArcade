
#define TextureSet(Name, Slot) Texture2D Name : register(t##Slot##); SamplerState Name##_Sampler : register(s##Slot##);

// ##는 치환된후에 삭제되라
#define Sampling(Name, TEXCOORD) Name##.Sample(##Name##_Sampler, ##TEXCOORD##.xy);

// HLSL의 디파인과
// c++의 디파인이 거의 치환됩니다.
// #define Sampling(Name) ##Name##Value 
// Sampling(MyEngine) => ##Name##Value ???
// 1. ##Name##Value
// 2. ##MyEngine##Value
// 3. MyEngineValue
// 에러가 나는데 NameValue라는 변수를 이해할수 없습니다.