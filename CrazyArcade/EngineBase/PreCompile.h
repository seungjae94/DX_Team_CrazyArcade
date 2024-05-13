#pragma once

#include <WS2tcpip.h> //서버용
#include <WinSock2.h> //서버용
#include <Windows.h>
#include <assert.h>
#include <string>
#include <string_view>
#include <functional>
#include <memory>

#include <map>
#include <list>
#include <set>
#include <vector>

#include <chrono>

#include <thread>
#include <mutex>
#include <atomic>



// 다이렉트의 수학적인 부분
#include <DirectXPackedVector.h> // 다이렉트벡터 헤더
#include <DirectXCollision.h> 
// 다이렉트용 충돌헤더 <= 저는 충돌구현 안합니다. <= 다이렉트가 지원해주는데 내가 왜만들어
// 선생님 기준으로 말해주겠습니다.
// 보통웃기는게 2~3년차가 이런걸 많이 따진다. 
// 그래픽카드적인 연산 제외하고도 cpu적인 최적화도 되어 있다.
// SIMD 연산이라던가 <= 추후 설명
