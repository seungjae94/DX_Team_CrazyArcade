#include "PreCompile.h"
#include "EngineFile.h"
#include "EngineDebug.h"
#include "EngineSerializer.h"

UEngineFile::UEngineFile() 
{
}

UEngineFile::UEngineFile(std::filesystem::path _Path)
	: UEnginePath(_Path)
{

}

UEngineFile::~UEngineFile() 
{
	Close();
}

void UEngineFile::Close()
{
	if (nullptr != FileHandle)
	{
		fclose(FileHandle);
	}
}

void UEngineFile::Read(void* _Data, size_t _Size)
{
	fread_s(_Data, _Size, _Size, 1, FileHandle);
}

void UEngineFile::Open(EIOOpenMode _OpenType, EIODataType _DataType)
{
	std::string Path = GetFullPath();

	std::string Mode;

	switch (_OpenType)
	{
	case EIOOpenMode::Write:
		OpenMode = EIOOpenMode::Write;
		Mode += "w";
		break;
	case EIOOpenMode::Read:
		OpenMode = EIOOpenMode::Read;
		Mode += "r";
		break;
	default:
		break;
	}

	switch (_DataType)
	{
	case EIODataType::Binary:
		Mode += "b";
		break;
	case EIODataType::Text:
		Mode += "t";
		break;
	default:
		break;
	}

	fopen_s(&FileHandle, Path.c_str(), Mode.c_str());

	if (nullptr == FileHandle)
	{
		MsgBoxAssert("파일 오픈에 실패했습니다" + Path);
	}
}

void UEngineFile::Save(UEngineSerializer& _Data)
{
	std::vector<char>& SaveData = _Data.Data;

	if (OpenMode != EIOOpenMode::Write)
	{
		MsgBoxAssert("쓰기 모드로 오픈하지 않은 파일로 쓰려고 했습니다.");
	}

	char* StartPtr = &SaveData[0];
	fwrite(StartPtr, SaveData.size(), 1, FileHandle);
}

__int64 UEngineFile::GetFileSize()
{
	return static_cast<int>(std::filesystem::file_size(Path));
}

void UEngineFile::Load(UEngineSerializer& _Data)
{
	if (OpenMode != EIOOpenMode::Read)
	{
		MsgBoxAssert("읽기 모드로 오픈하지 않은 파일로 읽으려고 했습니다.");
	}

	__int64 Size = GetFileSize();

	if (0 >= Size)
	{
		MsgBoxAssert("사이즈가 0인 파일을 읽으려고 했습니다" + GetFullPath());
	}

	_Data.BufferResize(static_cast<int>(Size));
	fread(&_Data.Data[0], Size, 1, FileHandle);
}

std::string UEngineFile::GetString()
{
	Open(EIOOpenMode::Read, EIODataType::Text);
	UEngineSerializer Ser;
	Load(Ser);
	Close();

	return Ser.ToString();
}