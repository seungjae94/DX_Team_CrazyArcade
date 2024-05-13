#pragma once
#include <EngineBase/NameObject.h>
#include "imgui.h"

// 우린 이것만 사용합니다.
// 여러분들이 나만의 창을 띄우고 싶어.

// 설명 :
class ULevel;
class UEngineEditorGUI;
class UEngineEditorWindow : public UNameObject
{
	friend UEngineEditorGUI;

public:
	// constrcuter destructer
	UEngineEditorWindow();
	// 순수 가상함수 => 클래스는 추상클래스가 된다.
	// 순수가상함수 용법의 1번만 이용하고 싶다면 소멸차 pure를 걸면 된다.
	~UEngineEditorWindow() = 0;

	// delete Function
	UEngineEditorWindow(const UEngineEditorWindow& _Other) = delete;
	UEngineEditorWindow(UEngineEditorWindow&& _Other) noexcept = delete;
	UEngineEditorWindow& operator=(const UEngineEditorWindow& _Other) = delete;
	UEngineEditorWindow& operator=(UEngineEditorWindow&& _Other) noexcept = delete;

	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

protected:
	virtual void Init() {}
	virtual void Tick(ULevel* Level, float _Delta);
	// 순수 가상함수 => 클래스는 추상클래스가 된다.
	// 1. 객체화 시킬수 없다. => 순수가상함수는 구현이 되어있을수도 있고 없을수도 있다.
	// 2. 자식에게 강요할수 함수의 구현 강요할 있죠. 
	virtual void OnGui(ULevel* Level, float _Delta) = 0	{}

private:
	std::string Title;
	bool IsActive = true;

	void Begin();
	void End();
};

