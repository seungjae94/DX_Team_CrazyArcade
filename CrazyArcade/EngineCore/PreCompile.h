#pragma once

#include <EnginePlatform/PreCompile.h>

// 프리컴파일 헤더의 진짜 목적
// 
// DX
#include <d3d11_4.h> // 다이렉트x 메인헤더 버전4 이전 버전과의 차이는 선생님도 관심 없음
#include <d3dcompiler.h> // 쉐이더 컴파일러 인터페이스. 쉐이더가 뭔지는 추후 배움

// FMOD
#include <EnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

#include <EnginePlatform/EngineSound.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineResources.h>
#include <EnginePlatform/EngineInput.h>


#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")