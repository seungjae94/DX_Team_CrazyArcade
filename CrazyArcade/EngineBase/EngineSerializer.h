#pragma once
#include <vector>
#include <string>
#include "EngineMath.h"

// 직렬화
// 
// 설명 :
class UEngineFile;
class UEngineSerializeObject;
class UEngineSerializer
{
	friend UEngineFile;

public:
	// constrcuter destructer
	UEngineSerializer();
	~UEngineSerializer();

	void Paste(int Offset, const void* _Data, size_t _Size);

	void Write(const void* _Data, size_t _Size);

	void WriteText(const std::string& _Text);

	void operator<<(UEngineSerializeObject& _Data);

	void operator<<(UEngineSerializeObject* _Data);

	void operator<<(const float& _Data)
	{
		Write(&_Data, sizeof(float));
	}

	void operator<<(const int& _Data)
	{
		Write(&_Data, sizeof(int));
	}

	void operator<<(const bool& _Data)
	{
		Write(&_Data, sizeof(bool));
	}

	void operator<<(const float4& _Data)
	{
		Write(&_Data, sizeof(float4));
	}


	void operator<<(const std::string& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		operator<<(Size);
		Write(_Data.c_str(), Size);
	}

	template<typename DataType>
	void operator<<(const std::vector<DataType>& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		operator<<(Size);

		for (size_t i = 0; i < _Data.size(); i++)
		{
			operator<<(_Data[i]);
		}
	}

	template<typename KeyType, typename DataType>
	void operator<<(const std::map<KeyType, DataType>& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		operator<<(Size);
		
		for (std::pair<KeyType, DataType> Iterator : _Data)
		{
			operator << (Iterator.first);
			operator << (Iterator.second);
		}
	}


	void Read(void* _Data, size_t _Size);

	void operator>>(float& _Data)
	{
		Read(&_Data, sizeof(float));
	}

	void operator>>(int& _Data)
	{
		Read(&_Data, sizeof(int));
	}

	void operator>>(bool& _Data)
	{
		Read(&_Data, sizeof(bool));
	}

	void operator>>(float4& _Data)
	{
		Read(&_Data, sizeof(float4));
	}


	void operator>>(std::string& _Data)
	{
		int Size = 0;
		operator>>(Size);

		if (Size == 0)
		{
			return;
		}
		_Data.resize(Size);
		Read(&_Data[0], Size);
	}

	void operator>>(UEngineSerializeObject& _Data);

	void operator>>(UEngineSerializeObject* _Data);

	template<typename DataType>
	void operator>>(std::vector<DataType>& _Data)
	{
		int Size = 0;
		operator>>(Size);

		if (Size == 0)
		{
			return;
		}

		_Data.resize(Size);
		for (size_t i = 0; i < Size; i++)
		{
			operator>>(_Data[i]);
		}
	}

	template<typename KeyType, typename DataType>
	void operator>>(std::map<KeyType, DataType>& _Data)
	{
		int Size = 0;
		operator>>(Size);

		if (Size == 0)
		{
			return;
		}

		for (size_t i = 0; i < Size; i++)
		{
			KeyType Key;
			DataType Data;
			operator>>(Key);
			operator>>(Data);
			_Data[Key] = Data;
		}
	}


	int BufferSize()
	{
		return static_cast<int>(Data.size());
	}

	int RemainSize()
	{
		return static_cast<int>(Data.size() - WriteOffset);
	}

	void Reset();

	void ResetRead();
	void ResetWrite();

	void BufferResize(int _Size);

	std::string ToString();

	int WriteSize()
	{
		return WriteOffset;
	}

	void* DataPtr()
	{
		return &Data[0];
	}

	char* DataCharPtr()
	{
		return &Data[0];
	}

	char* DataCharPtrToWriteOffset()
	{
		return &Data[WriteOffset];
	}

	char* DataCharPtrToReadOffset()
	{
		return &Data[ReadOffset];
	}

	int GetWriteOffset()
	{
		return WriteOffset;
	}

	int GetReadOffset()
	{
		return ReadOffset;
	}

	void SetWriteOffset(int _Offset)
	{
		WriteOffset = _Offset;
	}

	void AddWriteOffset(int _Offset)
	{
		WriteOffset += _Offset;
	}


	void DataToReadOffsetPush();

	void AddReadOffset(int _Value);

protected:

private:
	int WriteOffset = 0;
	int ReadOffset = 0;

	std::vector<char> Data;
};

// 파일로 저장되었다가 
// 파일에서 읽어들수 있는 오브젝트들은 이걸 상속받을 것이다.
class UEngineSerializeObject
{
public:
	virtual void Serialize(UEngineSerializer& _Ser) = 0;
	virtual void DeSerialize(UEngineSerializer& _Ser) = 0;
};

