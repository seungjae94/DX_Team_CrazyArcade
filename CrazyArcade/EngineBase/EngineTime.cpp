#include "PreCompile.h"
#include "EngineTime.h"
#include <Windows.h>

UEngineTime::UEngineTime()
{
	TimeCheckStart();
}

UEngineTime::~UEngineTime()
{
}

//typedef union _LARGE_INTEGER {
//    struct {
//        DWORD LowPart;
//        LONG HighPart;
//    } DUMMYSTRUCTNAME;
//    struct {
//        DWORD LowPart;
//        LONG HighPart;
//    } u;
//    LONGLONG QuadPart;
//} LARGE_INTEGER;


void UEngineTime::TimeCheckStart()
{
	// 초당 샐수 있는 양인데.
	QueryPerformanceFrequency(&Count);

	QueryPerformanceCounter(&PrevTime);

	dCount = static_cast<double>(Count.QuadPart);
}

float UEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);

	__int64 Tick = (CurTime.QuadPart - PrevTime.QuadPart);

	// 정밀도를 높이기 위해서 double로 계산한다.
	double dTick = static_cast<double>(Tick);
	DeltaTime = dTick / dCount;
	PrevTime.QuadPart = CurTime.QuadPart;
	return static_cast<float>(DeltaTime);
}

FEngineTimeStamp UEngineTime::GetCurTime()
{
	FEngineTimeStamp TimeStamp = {};
	const std::chrono::system_clock::time_point Now = std::chrono::system_clock::now();
	time_t TimeNow = std::chrono::system_clock::to_time_t(Now);
	tm TimeStruct;
	localtime_s(&TimeStruct, &TimeNow);

	std::chrono::system_clock::duration Duration = Now.time_since_epoch();
	std::chrono::milliseconds MilliSecondObj = std::chrono::duration_cast<std::chrono::milliseconds>(Duration) % 1000;
	int MilliSecond = static_cast<int>(MilliSecondObj.count());

	TimeStamp.Hour = TimeStruct.tm_hour;
	TimeStamp.Minute = TimeStruct.tm_min;
	TimeStamp.Second = TimeStruct.tm_sec;
	TimeStamp.MilliSecond = MilliSecond;

	return TimeStamp;
}

FEngineTimeStamp FEngineTimeStamp::operator-(const FEngineTimeStamp& _Other) const
{
	int ThisTotalMilliSecond = Hour * 60 * 60 * 1000 + Minute * 60 * 1000 + Second * 1000 + MilliSecond;
	int OtherTotalMilliSecond = _Other.Hour * 60 * 60 * 1000 + _Other.Minute * 60 * 1000 + _Other.Second * 1000 + _Other.MilliSecond;

	int ResultTotalMilliSecond = (ThisTotalMilliSecond - OtherTotalMilliSecond + 24 * 60 * 60 * 1000) % (24 * 60 * 60 * 1000);

	FEngineTimeStamp Result = {};
	Result.MilliSecond = ResultTotalMilliSecond % 1000;
	ResultTotalMilliSecond /= 1000;
	Result.Second = ResultTotalMilliSecond % 60;
	ResultTotalMilliSecond /= 60;
	Result.Minute = ResultTotalMilliSecond % 60;
	ResultTotalMilliSecond /= 60;
	Result.Hour = ResultTotalMilliSecond % 24;
	return Result;
}

float FEngineTimeStamp::TimeToFloat() const
{
	int TotalMilliSecond = Hour * 60 * 60 * 1000 + Minute * 60 * 1000 + Second * 1000 + MilliSecond;
	return static_cast<float>(TotalMilliSecond / 1000) + (MilliSecond / 1000.0f);
}
