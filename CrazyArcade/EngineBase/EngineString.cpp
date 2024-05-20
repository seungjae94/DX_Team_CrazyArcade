#include "PreCompile.h"
#include "EngineString.h"
#include <Windows.h>
#include "EngineDebug.h"

UEngineString::UEngineString() 
{
}

UEngineString::~UEngineString() 
{
}

std::wstring UEngineString::AnsiToUniCode(std::string_view _View)
{
	if (0 == _View.size())
	{
		return L"";
	}

	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했습니다.");
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했거나 크기가 0인 문자열을 넣어줬습니다");
		return L"";
	}

	return Result;
}

std::string UEngineString::UniCodeToAnsi(std::wstring_view _View)
{
	if (0 == _View.size())
	{
		return "";
	}

	int Size = WideCharToMultiByte(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0, 0, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했습니다.");
		return "";
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size, 0, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했거나 크기가 0인 문자열을 넣어줬습니다");
		return "";
	}

	return Result;
}

std::string UEngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}

std::vector<std::string> UEngineString::StringCutting(std::string& _Value, std::vector<std::string> _CutText)
{
	std::vector<std::string> Result;

	size_t StartFindOffset = 0;
	size_t EndFindOffset = 0;

	while (true)
	{
		std::vector<size_t> Count;

		for (size_t i = 0; i < _CutText.size(); i++)
		{
			EndFindOffset = _Value.find_first_of(_CutText[i], StartFindOffset);

			if (std::string::npos != EndFindOffset)
			{
				Count.push_back(EndFindOffset);
				// break;
			}
		}

		EndFindOffset = std::string::npos;
		for (size_t i = 0; i < Count.size(); i++)
		{
			if (EndFindOffset >= Count[i])
			{
				EndFindOffset = Count[i];
			}
		}

		if (EndFindOffset == std::string::npos)
		{
			break;
		}

		std::string ParseString = _Value.substr(StartFindOffset, EndFindOffset - StartFindOffset);
		Result.push_back(ParseString);

		StartFindOffset = EndFindOffset + 1;
	}

	return Result;
}

std::vector<std::string> UEngineString::StringCutting(std::string& _Value, std::string_view _Start, std::string_view _End)
{
	std::vector<std::string> Result;

	size_t StartFindOffset = 0;

	while (true)
	{
		// _Start부터 시작해서 뒤로 이동하면서 1글짜식 찾아라 find_first_of 앞에서 부터
		// StartFindOffset <= 0 
		// StartFindOffset <= _Value.find_first_of(_Start, StartFindOffset); 14
		// [ 찾았다. 14글자에 있었다.
		StartFindOffset = _Value.find_first_of(_Start, StartFindOffset);

		if (std::string::npos == StartFindOffset)
		{
			break;
		}

		// _Start부터 시작해서 뒤로 이동하면서 1글짜식 찾아라 find_first_of 앞에서 부터
		// 14 부터 찾아라 _End
		// 14 ]
		// EndFindOffset 14보다는 큰 수가 나온다.
		size_t EndFindOffset = _Value.find_first_of(_End, StartFindOffset);

		// std::string::npos 1896215023153153 size_t 최대값이에요
		if (std::string::npos == EndFindOffset)
		{
			break;
		}

		// [ 한칸 뒤에 있을테니까 StartFindOffset + 1
		// EndFindOffset - StartFindOffset - 1 = 2
		// [ 위치에서부터 2글짜 잘라네세요가 됩니다.
		std::string ParseString = _Value.substr(StartFindOffset + 1, EndFindOffset - StartFindOffset - 1);
		Result.push_back(ParseString);
		StartFindOffset = EndFindOffset;
	}

	return Result;
}