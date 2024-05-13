#pragma once
#include <vector>
#include "EngineThread.h"
#include <Windows.h>


enum class EThreadWorkType
{
	Work,
	Destroy,
};


struct FJob
{
	std::function<void()> WorkFunction;
};

// 쓰레드 풀을 만드는 방식은 다양한 방식 있는데.

// 설명 :
class UThreadPool
{
public:
	// constrcuter destructer
	UThreadPool();
	~UThreadPool();

	// delete Function
	UThreadPool(const UThreadPool& _Other) = delete;
	UThreadPool(UThreadPool&& _Other) noexcept = delete;
	UThreadPool& operator=(const UThreadPool& _Other) = delete;
	UThreadPool& operator=(UThreadPool&& _Other) noexcept = delete;

	void Initialize(const std::string_view& _ThreadName, int _ThreadCount = 0);

	void Work(std::function<void()> _Function);

	void End();

protected:

private:
	// IOCP의 역할은
	// 각각 입출력 데이터를 처리하는 일들이
	// 어느쪽이 여유가 있는지 확인해주고
	// 몰려드는 데이터의 버퍼역할도 해주고
	HANDLE IOCPHandle = nullptr;
	int ThreadCount = -1;

	// typedef std::atomic<bool> atomic_bool;

	std::atomic_bool IsRun = false;;

	std::atomic_int RunThreadCount = 0;

	std::vector<std::shared_ptr<UEngineThread>> Threads;

	static void ThreadPoolWorkFunction(UThreadPool* _Pool, HANDLE _IOCPHandle);
};

// 일이 100개 있다.

// 쓰레드는 5개 가 있어요.

// IOCP는 저 쓰레들을 등록작업을 거쳐서 다 기억하고 있습니다.

// IOCP는 자신에게 등록된 쓰레드들을 다음과 같이 구분한다.

// waiting
// Release
// Paused

// 최초의 각 쓰레드의 상태
// [waiting][waiting][waiting][waiting][waiting]

// 일을 처리하려면 컴퓨터에 앉아야 한다고 하자.
// job qeueue [일][일][일][일][일][일][일][일][일][일]
// Waiting Queue 바깥에서 대기하고 있는 사람
// Release Queue 컴퓨터 자리에 앉아있는 사람
// Paused Queue 컴퓨터 자리에 앉아있는데 끝나서 손든 사람 일끝났어요.

// 일이 1개가 들어왔어.
// job qeueue [일][일][일][일][일][일][일][일][일][일]
// Waiting Queue [waiting][waiting][waiting][waiting]
// Release Queue [Release[일]]
// Paused Queue 

// 일이 1개가 들어왔어.
// job qeueue [일][일][일][일][일][일][일][일][일][일]
// Waiting Queue [waiting][waiting][waiting]
// Release Queue [Release[일]][waiting[일]]
// Paused Queue 

// release에 존재하는 쓰레드중 1개가 일을 끝내면
// job qeueue [일][일][일][일][일][일][일][일][일][일]
// Waiting Queue [waiting][waiting][waiting] // 아직 자리로 가지도 않은 상태
// Release Queue [waiting[일]]
// Paused Queue [Paused] 

// 일이 1개 들어왔어
// job qeueue [일][일][일][일][일][일][일][일][일][일]
// Waiting Queue [waiting][waiting][waiting]
// Release Queue [waiting[일]]
// Paused Queue [Paused[일]] 

// job qeueue [일][일][일][일][일][일][일][일][일][일]
// Waiting Queue [waiting][waiting][waiting]
// Release Queue [waiting[일]]
// Paused Queue [Paused] // 컴퓨터전원도 끄고 쉬고 있는 상태가 될수도 있다.

// iocp로 관리하는데 일을 표현하자면 10초마다 1개씩 준다고 치자.
// 
// 쓰레드가 일을 한다는 것은 CPU의 코어라고 부르는 컴퓨터의 자리에 앉아서
// 전원도 키고 프로램도 키고 내가 밭은 일도 열람고 어떻게 해야하는지도 보고.
// 쓰레드가 일을 하기 위해서 뭔가 준비를 하는 작업을 컨텍스트 스위칭이라고 합니다
// 컨텍스트 스위칭이 일어나지 않은 쓰레드를 busy쓰레드라고 합니다.
// 
// 쓰레드가 자신이 붙잡고 있던 쓰레드를 놓게 되면 당연히 캐쉬에서 메모리도 비우고
// 그 cpu를 다른 쓰레드와 일할수 있는 상태로 만들어 놓을거에요.


