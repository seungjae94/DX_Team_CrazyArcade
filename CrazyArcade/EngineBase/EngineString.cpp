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
	// 윈도우 지원합니다.
	// 국가코드와 컴파일시의 문자열의 배합을 알고 있는것은 window이기 때문
	// 변환함수가 있다면 window가 지원해 줘야 합니다.
	// MultiByteToWideChar는 멀티바이트를 유니코드로 변경할수 있다.
	// 이함수의 역할이 2가지가 있습니다.
	// 첫번째 
	// 문자열을 변환하면 크기가 변경됩니다.

	// 1바이트이거나 2바이트인 문자열 => 멀티바이트
	// 무조건 2바이트 하는 => 유니코드
	// 바이트 사이즈가 바뀔겁니다.

	// char Arr[5000] => 멀티바이트 문자열
	// wchar_t wArr[] => 그걸 변환한걸 받을 wide바이트 배열 ??????????
	// 일반적으로 얼마나 필요한데? 
	// 이 함수는 2가지 역할이 있다.
	// 변환할 문자열만 넣어줬을때는
	// 변환되어지는 크기를 리턴합니다.
	// int Size = 필요한 wchar_배열의 크기를 리턴합니다.

	//UINT CodePage, = CP_ACP 현재 window에 설정된 초기 문자열 인코딩으로 처리해달라
	//DWORD dwFlags, = 변환할때 추가 정보가 있나요? 아니요 0 => 디폴트 너의 플래그애서 알고 싶지 않아 0=> 디폴트로 해줘
	//LPCCH lpMultiByteStr, = 변환할 문자열
	//int cbMultiByte, => 변환할 문자열의 길이
	//LPWSTR lpWideCharStr, => wide 바이트 문자열 => 변환을 받을 nullptr 넣어주면 이녀석은 크기를 리턴한다
	//int cchWideChar => wide 바이트 문자열의 크기
	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했거나 크기가 0인 문자열을 넣어줬습니다");
		return L"";
	}

	// std::string이나 std::wstring 내부에 std::vector<char>
	// std::vector<char> Vector;
	// Vector[0] => char&
	// &Vector[0] => *char

	//wchar_t* Arr = new wchar_t[Size];
	//delete Arr;
	std::wstring Result;
	Result.resize(Size);

	// 변환되어진 개수가 나오는데.
	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("문자열 변환에 실패했거나 크기가 0인 문자열을 넣어줬습니다");
		return L"";
	}

	// 자연스럽게 RValue 레퍼런스가 되니까 추가 생성은 이루어지지 않겠죠.
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