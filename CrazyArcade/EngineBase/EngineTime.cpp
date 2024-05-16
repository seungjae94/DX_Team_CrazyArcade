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
