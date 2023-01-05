#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>

// 설명 : 스크린에 존재 및 그려질것들의 기본기능 지원클래스.
class GameEngineLevel;
class GameEngineActor
{
	friend GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	float4 GetPos()
	{
		return Pos;
	}

	void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}


protected:
	// 구현을 안할수도 있어야함.

	// 시작하기전에 뭔가 준비해야할것이 있을때
	virtual void Start() {}

	// 키입력을 받거나 인공지능을 점수를 계산하거나 하는 등
	virtual void Update() {}

	// 화면에 그려지는 기능
	virtual void Render() {}

private:
	float4 Pos = { 0.0f, 0.0f };
};

