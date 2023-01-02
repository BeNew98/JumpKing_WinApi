#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// 윈도우는 핸들 방식이라는것을 이용한다.
// 핸들방식이란 우리에게 os가 관리한다는 증명으로 숫자 1를 줍니다.
// 그 숫자를 핸들이라고 합니다.

// 설명 :
class GameEngineWindow
{
public:
	// 윈도우를 만들어 주는 기능입니다.
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName);

	static void WindowSize(float4 _Size);
	static void WindowPos(float4 _Pos);

	static int WindowLoop();

	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

protected:

private:
	static HWND hWnd;
};

