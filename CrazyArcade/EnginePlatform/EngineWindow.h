#pragma once
#include <Windows.h>
#include <string>
#include <EngineBase\EngineMath.h>
#include <memory>
#include <functional>

class UWindowImage;
// Ό³Έν :
class UEngineWindow
{
public:
	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;


	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(std::function<void()> _Update, std::function<void()> _End);

	std::shared_ptr<UWindowImage> GetWindowImage() const
	{
		return WindowImage;
	}

	std::shared_ptr<UWindowImage> GetBackBufferImage() const
	{
		return BackBufferImage;
	}


	FVector GetWindowScale() const
	{
		return Scale;
	}

	void SetClearColor(Color8Bit _Color)
	{
		_Color.A = 0;
		ClearColor = _Color;
	}

	void SetWindowTitle(std::string_view _Text)
	{
		SetWindowTextA(hWnd, _Text.data());
	}

	void Off()
	{
		WindowLive = false;
	}

	HWND GetHWND() const
	{
		return hWnd;
	}

	void SetFocus()
	{
		::SetFocus(hWnd);
	}


	void Open(std::string_view _Title = "Title", std::string_view _IconPath = "");

	void SetWindowPosition(const FVector& _Pos);
	void SetWindowScale(const FVector& _Scale);

	void ScreenClear();
	void ScreenUpdate();

	void SetWindowSmallIcon();
	
	bool IsFocus()
	{
		return IsFocusValue;
	}


	bool IsCursor()
	{
		return IsCursorValue;
	}
	void CursorOff();
	void CursorOn();

	inline float4 GetScreenMousePrevPos()
	{ 
		return ScreenMousePrevPos; 
	}
	inline float4 GetScreenMousePos()
	{ 
		return ScreenMousePos; 
	}
	inline float4 GetScreenMouseDir()
	{ 
		return ScreenMouseDir; 
	}
	inline float4 GetScreenMouseDirNormal() 
	{ 
		return ScreenMouseDirNormal; 
	}

	void CalculateMouseUpdate(float _DeltaTime);
	static void SetUserWindowCallBack(std::function<bool(HWND, UINT, WPARAM, LPARAM)> _UserWndProcFunction);

protected:

private:
	static bool WindowLive;
	static HINSTANCE hInstance;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static std::function<bool(HWND, UINT, WPARAM, LPARAM)> UserWndProcFunction;
	static std::map<HWND, UEngineWindow*> AllWindow;

	Color8Bit ClearColor = Color8Bit::WhiteA;
	bool IsFocusValue = true;

	HWND hWnd = nullptr;
	FVector Scale;
	FVector Position;
	bool IsCursorValue = true;

	std::shared_ptr<UWindowImage> WindowImage = nullptr;
	std::shared_ptr<UWindowImage> BackBufferImage = nullptr;

	float4 ScreenMousePrevPos;
	float4 ScreenMousePos;
	float4 ScreenMouseDir;
	float4 ScreenMouseDirNormal;

	FVector GetMousePosition();
};
