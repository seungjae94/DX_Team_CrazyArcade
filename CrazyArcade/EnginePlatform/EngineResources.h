#pragma once
#include <string>
#include <map>
#include <EngineBase/EnginePath.h>
#include <EngineBase/PathObject.h>

// 설명 : 템플릿은 이상한 생각하지 말자.
// 복사해 그 자료형으로 바꿔 템플릿 삭제해.
template<typename ResType>
class UEngineResources : public UPathObject
{
public:
	// constrcuter destructer
	UEngineResources() {}
	~UEngineResources() {}

	// delete Function
	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;

	static std::shared_ptr<ResType> FindRes(std::string_view _Name)
	{
		std::lock_guard<std::mutex> Lock(NameResourcesMutex);

		std::string UpperName = UEngineString::ToUpper(_Name);

		if (false == NameResources.contains(UpperName))
		{
			return nullptr;
		}
		
		return NameResources[UpperName];
	}

	static bool IsRes(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);
		return NameResources.contains(UpperName);
	}

	static std::shared_ptr<ResType> CreateResName(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return CreateResName(_Path, FileName);
	}

	static std::shared_ptr<ResType> CreateResName(std::string_view _Path, std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		NewRes->SetName(_Name);
		NewRes->SetPath(_Path);

		if (true == NameResources.contains(UpperName))
		{
			MsgBoxAssert("이미 존재하는 리소스를 또 로드하려고 했습니다." + UpperName);
		}

		NameResources[UpperName] = NewRes;
		return NewRes;
	}

	static std::shared_ptr<ResType> CreateResUnName()
	{
		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		UnNameResources.push_back(NewRes);
		return NewRes;
	}

	////

	// anyc 나
	// thread safe가 함수에 붙어있으면 
	static std::shared_ptr<ResType> ThreadSafeCreateResName(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return ThreadSafeCreateResName(_Path, FileName);
	}

	static std::shared_ptr<ResType> ThreadSafeCreateResName(std::string_view _Path, std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		NewRes->SetName(_Name);
		NewRes->SetPath(_Path);

		{
			std::lock_guard<std::mutex> Lock(NameResourcesMutex);
			if (true == NameResources.contains(UpperName))
			{
				MsgBoxAssert("이미 존재하는 리소스를 또 로드하려고 했습니다." + UpperName);
			}

			NameResources[UpperName] = NewRes;
		}
		return NewRes;
	}

	static std::shared_ptr<ResType> ThreadSafeCreateResUnName()
	{
		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();

		{
			std::lock_guard<std::mutex> Lock(UnNameResourcesMutex);
			UnNameResources.push_back(NewRes);
		}

		return NewRes;
	}


	static void ResourcesRelease()
	{
		// 클리어했을때
		// 아무도 이안에 있는 리소스들을 쓰는애들이 없다면
		// 알아서 삭제될 것이다.
		UnNameResources.clear();
		NameResources.clear();
	}

protected:

private:
	// 당연히 그 자료형 그대로 쓰고
	// 텍스처면 텍스처 그대로
	// 랜더타겟이면 랜더타겟 그대로
	// 사운드면 사운드 그대로 쓰고 싶을 것이다.
	// class MapNode
	// {
	//    std::shared_ptr<ResType> Value;
	// }
	static std::mutex NameResourcesMutex;
	static std::map<std::string, std::shared_ptr<ResType>> NameResources;

	static std::mutex UnNameResourcesMutex;
	static std::list<std::shared_ptr<ResType>> UnNameResources;
	// std::string Name = "NONE";
	// std::string Path = "NONE";
};

// 템플릿일때는 문제가 없습니다.
// 전역변수는 헤더에 추가할수가 없죠?
// 템플릿이면 무넺가 해결됩니다.
// 템플릿 static 변수를 선언하는 방법을 배워야 한다.
template<typename ResType>
std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::NameResources;

template<typename ResType>
std::mutex UEngineResources<ResType>::NameResourcesMutex;

// 템플릿 static 변수 선언하는법.
template<typename ResType>
std::list<std::shared_ptr<ResType>> UEngineResources<ResType>::UnNameResources;

template<typename ResType>
std::mutex UEngineResources<ResType>::UnNameResourcesMutex;
