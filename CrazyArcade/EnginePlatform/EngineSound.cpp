#include "PreCompile.h"
#include "EngineSound.h"
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDebug.h>

// lib를 사용하는법

// 아예 사라져야 한다. 빌드가 되기 전에 아예 사라져야 한다.
// 이때 보통 사용하는게 ifdef


#ifdef _DEBUG
// Debug 일때는
#pragma comment(lib, "fmodL_vc.lib")
#else
// Release 일때는 
#pragma comment(lib, "fmod_vc.lib")
#endif

float UEngineSound::GlobalVolume = 1.0f;

void UEngineSoundPlayer::SetVolume(float _Volume)
{
	Control->setVolume(_Volume * UEngineSound::GlobalVolume);
}

UEngineSoundPlayer UEngineSoundPlayer::Replay()
{
	*this = UEngineSound::SoundPlay(Name);
	return *this;
}

// FMOD와 관련된 사운드를 로드할수 있는 권한.
FMOD::System* SoundSystem = nullptr;

class ResControl
{
public:
	ResControl()
	{
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
			return;
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
			return;
		}
	}
	~ResControl()
	{
		if (nullptr != SoundSystem)
		{
			SoundSystem->release();
			SoundSystem = nullptr;
		}
	}
};

ResControl Inst;


UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
}


void UEngineSound::ResLoad(std::string_view _Path)
{
	// FMOD_DEFAULT; => 반복재생이 안된다.
	SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);
	if (nullptr == SoundHandle)
	{
		MsgBoxAssert("사운드 로드에 실패했습니다." + std::string(_Path));
		return;
	}

	// SoundSystem->playSound(SoundHandle, nullptr, false, nullptr);
}

void UEngineSound::SetGlobalVolume(float _Value)
{
	GlobalVolume = _Value;

	if (GlobalVolume <= 0.0f)
	{
		GlobalVolume = 0.0f;
	}

	if (GlobalVolume >= 1.0f)
	{
		GlobalVolume = 1.0f;
	}
}

UEngineSoundPlayer UEngineSound::SoundPlay(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == IsRes(UpperName.c_str()))
	{
		MsgBoxAssert("로드하지 사운드를 재생하려고 했습니다." + UpperName);
		return UEngineSoundPlayer();
	}

	std::shared_ptr <UEngineSound> FindSound = FindRes(UpperName);

	UEngineSoundPlayer Result;
	Result.Name = _Name;
	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Result.Control);
	Result.Control->setLoopCount(0);
	Result.SetVolume(1.0f);

	if (nullptr == Result.Control)
	{
		MsgBoxAssert("사운드 재생에 대한 제어 권한을 가져오지 못했습니다.");
		return Result;
	}


	return Result;
}

void UEngineSound::Update()
{
	// 매프레임마다 호출되어야 한다.
	// 그래서 FMOD 라이브러리가 다수의 사운드를 제어해준다.
	if (nullptr == SoundSystem)
	{
		MsgBoxAssert("사운드 시스템에 치명적인 오류가 있습니다.");
	}

	SoundSystem->update();
}

void UEngineSound::Load(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == IsRes(UpperName))
	{
		MsgBoxAssert("이미 로드한 리소스를 또 로드 하려고 했습니다.");
		return;
	}

	std::shared_ptr<UEngineSound> NewSound = CreateResName(_Path, _Name);
	NewSound->ResLoad(_Path);
}