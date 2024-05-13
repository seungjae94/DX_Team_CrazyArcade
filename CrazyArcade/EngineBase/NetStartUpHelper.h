#pragma once

// 네트워크라는건
// 네트워크라는건
// 내가 상대가 컴퓨터에게 뭔가 데이터를 보낸다.
// 상대가 나에게 데이터를 보낸다죠.

// 설명 :
class UNetStartUpHelper
{
public:
	// constrcuter destructer
	UNetStartUpHelper();
	~UNetStartUpHelper();

	// delete Function
	UNetStartUpHelper(const UNetStartUpHelper& _Other) = delete;
	UNetStartUpHelper(UNetStartUpHelper&& _Other) noexcept = delete;
	UNetStartUpHelper& operator=(const UNetStartUpHelper& _Other) = delete;
	UNetStartUpHelper& operator=(UNetStartUpHelper&& _Other) noexcept = delete;

	static void NetStartUp();
protected:

private:

};

