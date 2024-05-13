#include "PreCompile.h"
#include "EngineSerializer.h"

UEngineSerializer::UEngineSerializer() 
{
}

UEngineSerializer::~UEngineSerializer() 
{
}

void UEngineSerializer::BufferResize(int _Size)
{
	Data.resize(_Size);
}

void UEngineSerializer::Write(const void* _Data, size_t _Size)
{
	if (WriteOffset + _Size >= Data.size())
	{
		Data.resize(Data.capacity() * 2 + _Size);
	}

	// &Data[WriteOffset] 주속값에
	// _Size 크기만큼
	// _Data 주소값에 있는 데이터를 
	// _Size 크기만큼 복사해라.
	// &Data[WriteOffset]<= _Data
	memcpy_s(&Data[WriteOffset], _Size, _Data, _Size);
	WriteOffset += static_cast<int>(_Size);
}

void UEngineSerializer::WriteText(const std::string& _Text)
{
	Write(_Text.c_str(), _Text.size());
}


void UEngineSerializer::Read(void* _Data, size_t _Size)
{
	memcpy_s(_Data, _Size, &Data[ReadOffset], _Size);
	ReadOffset += static_cast<int>(_Size);
}

std::string UEngineSerializer::ToString()
{
	return static_cast<char*>(&Data[0]);
}

void UEngineSerializer::operator<<(UEngineSerializeObject& _Data)
{
	_Data.Serialize(*this);
}

void UEngineSerializer::operator<<(UEngineSerializeObject* _Data)
{
	_Data->Serialize(*this);
}

void UEngineSerializer::operator>>(UEngineSerializeObject& _Data)
{
	_Data.DeSerialize(*this);
}

void UEngineSerializer::operator>>(UEngineSerializeObject* _Data)
{
	_Data->DeSerialize(*this);
}

void UEngineSerializer::Reset()
{
	WriteOffset = 0;
	ReadOffset = 0;
}

void UEngineSerializer::ResetRead()
{
	ReadOffset = 0;
}

void UEngineSerializer::ResetWrite()
{
	WriteOffset = 0;
}