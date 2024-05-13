#pragma once
#include "EnginePath.h"
#include "EngineSerializer.h"

enum class EIOOpenMode
{
	None,
	Write,
	Read,
};

enum class EIODataType
{
	Binary,
	Text,
};

// Ό³Έν :
class UEngineFile : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineFile();
	UEngineFile(std::filesystem::path _Path);
	~UEngineFile();

	// delete Function
	//UEngineFile(const UEngineFile& _Other) = delete;
	//UEngineFile(UEngineFile&& _Other) noexcept = delete;
	//UEngineFile& operator=(const UEngineFile& _Other) = delete;
	//UEngineFile& operator=(UEngineFile&& _Other) noexcept = delete;

	__int64 GetFileSize();

	void Open(EIOOpenMode _OpenType, EIODataType _DataType);

	void Save(UEngineSerializer& _Data);
	void Load(UEngineSerializer& _Data);

	void Read(void* _Data, size_t _Size);

	void Close();

	std::string GetString();

protected:

private:
	EIOOpenMode OpenMode = EIOOpenMode::None;
	FILE* FileHandle = nullptr;

};

