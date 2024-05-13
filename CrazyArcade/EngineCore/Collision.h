#pragma once
#include "SceneComponent.h"
#include <set>

// 설명 :

// double 레퍼런스 카운트 가지나요?
// 기본 자료형 레퍼런스를 내부에 들수가 없어.
// std::shared_ptr<double>

// 클래스는 어떻습니까? 내부에 int하나 들고 있는것
// 어려운 일이 아니다.
// enable_shared_from_this 내부에 레퍼런스 카운트를 맴버변수로 가지게 된다.
// 쉐어드 ptr로 관리된다면 내 this를 어딘가로 리턴하는 행위는 
// 레퍼런스 카운트가 증가하는 행위입니다.
// std::enable_shared_from_this<UCollision>

class UCollision : public USceneComponent, public std::enable_shared_from_this<UCollision>
{
	GENERATED_BODY(USceneComponent)

public:
	// constrcuter destructer
	UCollision();
	~UCollision();

	// delete Function
	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

	// 목적성을 분명히 하기 위해서 굳이 같은 수준의 함수인데도 이름만 바꿔서 다시 만든다.
	// 내가 어떤 그룹에 속한 콜리전인지 정하기 위해서
	template<typename EnumType>
	void SetCollisionGroup(EnumType _Index)
	{
		SetCollisionGroup(static_cast<int>(_Index));
	}

	void SetCollisionGroup(int _Index);

	// 충돌하면 하고 싶은게 뭐야?
	template<typename EnumType>
	bool CollisionEnter(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionEnter(static_cast<int>(_TargetGroup), _Function);
	}

	// 최초 충돌 했을때 1번
	bool CollisionEnter(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);

	template<typename EnumType>
	bool CollisionStay(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionStay(static_cast<int>(_TargetGroup), _Function);
	}


	// 콜리전 충돌중이면 계속
	bool CollisionStay(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);

	template<typename EnumType>
	bool CollisionExit(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionExit(static_cast<int>(_TargetGroup), _Function);
	}


	// 충돌이 끝났을때 1번
	bool CollisionExit(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);

	bool Collision(int _TargetGroup, 
		std::function<void(std::shared_ptr<UCollision>)> _Enter = nullptr, 
		std::function<void(std::shared_ptr<UCollision>)> _Stay = nullptr, 
		std::function<void(std::shared_ptr<UCollision>)> _Exit = nullptr);

	void SetCollisionType(ECollisionType _CollisionType)
	{
		CollisionType = _CollisionType;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order) override;

	void SetActive(bool _Value) override
	{
		Super::SetActive(_Value);
		FirstCheck.clear();
		OtherCheck.clear();
		ExitCheck.clear();
	}

protected:
	void BeginPlay() override;
	void Tick(float _Delta) override;

private:
	ECollisionType CollisionType = ECollisionType::CirCle;

	// 순환참조를 막자.
	std::set<UCollision*> FirstCheck;
	std::set<UCollision*> OtherCheck;
	std::set<UCollision*> ExitCheck;
};

