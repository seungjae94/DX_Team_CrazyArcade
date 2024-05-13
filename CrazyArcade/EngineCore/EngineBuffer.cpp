#include "PreCompile.h"
#include "EngineBuffer.h"

UEngineBuffer::UEngineBuffer() 
{

}

UEngineBuffer::~UEngineBuffer() 
{
	Release();
}

void UEngineBuffer::Release()
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
	}
}