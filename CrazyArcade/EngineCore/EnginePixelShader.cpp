#include "PreCompile.h"
#include "EnginePixelShader.h"
#include <EngineBase/EngineString.h>
#include "EngineCore.h"

UEnginePixelShader::UEnginePixelShader() 
{
	Type = EShaderType::Pixel;
}

UEnginePixelShader::~UEnginePixelShader() 
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
	}
}

void UEnginePixelShader::ResLoad(std::string_view _EntryPoint, UINT _High /*= 5*/, UINT _Low /*= 0*/)
{
	
	// 마소의 typedef 스탠다드
	// LPCWSTR => const wchar_t* _Path
	// LP  => 포인터넣어주세요
	// C => const
	// W => wchar_t
	// STR => 문자열

	// LPCSTR => const char* _Path
	// LP  => 포인터넣어주세요
	// C => const
	// W 없음 => char
	// STR => 문자열
	
   //LPCWSTR pFileName, <= 쉐이더 파일 경로
   //CONST D3D_SHADER_MACRO* pDefines,
   //ID3DInclude* pInclude,
   //LPCSTR pEntrypoint,
   //LPCSTR pTarget,
   //UINT Flags1,
   //UINT Flags2,
   //ID3DBlob** ppCode,

	EntryName = _EntryPoint;

	std::string Path = GetPath();
	const char* PathPtr = Path.c_str();
	std::wstring WPath = UEngineString::AnsiToUniCode(PathPtr);
	const wchar_t* WPathPtr = WPath.c_str();

	CONST D3D_SHADER_MACRO* pDefines = nullptr;
	// 주소값이 1인 포인터를 넣어준건데.
	// 다이렉트가 아 그냥 쉐이더파일안에 있는 include 그냥 쓰겠다고 ok
	ID3DInclude* pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	const char* pEntrypoint = _EntryPoint.data();

	// 앞쪽이 
	std::string Version = "ps_" + std::to_string(_High) + "_" + std::to_string(_Low);

	// 쉐이더도 버전이 있습니다.
	// 저는 5_0으로 하려고 합니다.
	const char* Target = Version.c_str();

	int Flag0 = 0;

#ifdef _DEBUG
	// 오타난거 아님 D3D10
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	// 나중에 행렬을 쉐이더에 알려줄때 행렬이 전치되서 들어가는걸
	// 막는거야 눈에 보이는데로 들어갑니다.
	// 전치되는 이유 나도 모름.
	// 메모리 정렬이 그래픽카드가 역순이라고 합니다.
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	int Flag1 = 0;

	HRESULT Result = D3DCompileFromFile(
		WPathPtr,
		pDefines,
		pInclude,
		pEntrypoint,
		Target,
		Flag0,
		Flag1,
		&ShaderCodeBlob,
		&ErrorCodeBlob
	);
	// ErrorCodeBlob에러에 대한 내용이 여기 담긴다.

	if (S_OK != Result)
	{
		std::string ErrorString = reinterpret_cast<char*>(ErrorCodeBlob->GetBufferPointer());
		MsgBoxAssert(ErrorString);
		return;
	}

	Result = GEngine->GetDirectXDevice()->CreatePixelShader(
		ShaderCodeBlob->GetBufferPointer(), 
		ShaderCodeBlob->GetBufferSize(),
		nullptr,
		&ShaderPtr
		);

	if (S_OK != Result)
	{
		MsgBoxAssert("쉐이더 생성에 실패했습니다.");
		return;
	}

	ShaderResCheck();
}

void UEnginePixelShader::Setting()
{
#ifdef _DEBUG
	if (nullptr == ShaderPtr)
	{
		MsgBoxAssert("만들어지지 않은 픽셀 쉐이더를 세팅하려고 했습니다" + GetName());
	}
#endif

	GEngine->GetDirectXContext()->PSSetShader(ShaderPtr, nullptr, 0);
}